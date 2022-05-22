// Fill out your copyright notice in the Description page of Project Settings.

#include "SledCharacter.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ASledCharacter::ASledCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpingArm"));
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	springArm->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform, USpringArmComponent::SocketName);
	springArm->TargetArmLength = 350.0f;
	// springArm->SetWorldRotation(FRotator(-150.0f, 0.0f, 0.0f), true);

	camera->AttachToComponent(springArm, FAttachmentTransformRules::KeepRelativeTransform, USpringArmComponent::SocketName);
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ASledCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASledCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveCharacter();
	FRotator newYaw = springArm->GetRelativeRotation();
	newYaw.Yaw += mouseInput.X;
	springArm->SetRelativeRotation(newYaw);

	FRotator newPitch = springArm->GetComponentRotation();
	newPitch.Pitch = FMath::Clamp(newPitch.Pitch + mouseInput.Y, -80.0f, 0.0f);
	springArm->SetWorldRotation(newPitch);
}

// Called to bind functionality to input
void ASledCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASledCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASledCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ASledCharacter::LookUp);
	PlayerInputComponent->BindAxis("LookRight", this, &ASledCharacter::LookRight);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ASledCharacter::Jump);
}

void ASledCharacter::MoveForward(float Value)
{
	b_MoveUp = false;
	b_MoveDown = false;
	if (Value > 0)
	{
		b_MoveUp = true;
	}
	else if (Value < 0)
	{
		b_MoveDown = true;
	}
}

void ASledCharacter::MoveRight(float Value)
{
	b_MoveRight = false;
	b_MoveLeft = false;
	if (Value > 0)
	{
		b_MoveRight = true;
	}
	else if (Value < 0)
	{
		b_MoveLeft = true;
	}
}

void ASledCharacter::LookUp(float Value)
{
	mouseInput.Y = -Value;
}

void ASledCharacter::LookRight(float Value)
{
	mouseInput.X = Value;
}

void ASledCharacter::Jump()
{
	ACharacter::Jump();
}

void ASledCharacter::MoveCharacter()
{
	float ControlYaw = GetControlRotation().Yaw;
	if (b_MoveUp && b_MoveRight)
	{
		HandleInput(315);
	}
	else if (b_MoveUp && b_MoveLeft)
	{
		HandleInput(45);
	}
	else if (b_MoveDown && b_MoveRight)
	{
		HandleInput(225);
	}
	else if (b_MoveDown && b_MoveLeft)
	{
		HandleInput(135);
	}
	else if (b_MoveUp)
	{
		HandleInput(0);
	}
	else if (b_MoveDown)
	{
		HandleInput(180);
	}
	else if (b_MoveLeft)
	{
		HandleInput(90);
	}
	else if (b_MoveRight)
	{
		HandleInput(270);
	}
}


void ASledCharacter::HandleInput(float offset)
{
	float ControlYaw = GetControlRotation().Yaw;
	float CameraYaw = springArm->GetRelativeRotation().Yaw;
	float diff = FGenericPlatformMath::Abs(ControlYaw) - FGenericPlatformMath::Abs(CameraYaw);
	if (diff != offset)
	{
		FRotator CharacterRotation = GetControlRotation();
		CharacterRotation.Yaw = CameraYaw - offset;
		GetController()->SetControlRotation(CharacterRotation);
		AddMovementInput(GetActorForwardVector() * Speed);
	}
	else
	{

		AddMovementInput(GetActorForwardVector() * Speed);
	}
}