// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "PlayerChar.generated.h"

UCLASS()
class GAM312_NOLASCO_API APlayerChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerChar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// UFUNCTION() macro makes the function visible to Unreal's reflection system
	UFUNCTION()
		void MoveForward(float axisValue); // Function to move the character forward/backward

	UFUNCTION()
		void MoveRight(float axisValue); // Function to move the character right/left

	UFUNCTION()
		void StartJump(); // Function to initiate jumping

	UFUNCTION()
		void StopJump(); // Function to stop jumping

	UFUNCTION()
		void FindObject(); // Function to find an object (implementation not shown)

	UPROPERTY(VisibleAnywhere)
		UCameraComponent* PlayerCamComp; // Camera component for the player character

};
