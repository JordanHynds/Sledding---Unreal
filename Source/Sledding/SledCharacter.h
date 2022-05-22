// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SledCharacter.generated.h"

UCLASS()
class SLEDDING_API ASledCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASledCharacter();
	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUp(float Value);
	void LookRight(float Value);
	void MoveCharacter();
	void HandleInput(float offset);

	FVector2D mouseInput;
	void Jump();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly)
	class UCameraComponent *camera;

	UPROPERTY(EditDefaultsOnly)
	class USpringArmComponent *springArm;

private:
	UPROPERTY(EditAnywhere)
	float RotationRate = 3.0f;

	UPROPERTY(EditAnywhere)
	float Speed = 1.0f;

	bool b_MoveUp = false;
	bool b_MoveDown = false;
	bool b_MoveLeft = false;
	bool b_MoveRight = false;
};
