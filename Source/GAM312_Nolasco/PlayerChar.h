// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Resource_M.h"
#include "Kismet/GameplayStatics.h"
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
		void FindObject(); // Function to find an object

	UPROPERTY(VisibleAnywhere)
		UCameraComponent* PlayerCamComp; // Camera component for the player character

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
		float Health = 100.0f; // Player health

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
		float Hunger = 100.0f; // Player hunger

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
		float Stamina = 100.0f; // Player Stamina

	UPROPERTY(EditAnywhere, Category = "Resources")
		int Wood; // Amount of wood resource

	UPROPERTY(EditAnywhere, Category = "Resources")
		int Stone; // Amount of stone resource

	UPROPERTY(EditAnywhere, Category = "Resources")
		int Berry; // Amount of berry resource

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
		TArray<int> ResourcesArray; // Array to hold resources

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
		TArray<FString> ResourcesNameArray; // Array to hold resource names

	UPROPERTY(EditAnywhere, Category = "HitMarker")
		UMaterialInterface* hitDecal; // Material for hit marker decal

	UFUNCTION(BlueprintCallable)
		void SetHealth(float amount); // Function to set health

	UFUNCTION(BlueprintCallable)
		void SetHunger(float amount); // Function to set hunger

	UFUNCTION(BlueprintCallable)
		void SetStamina(float amount); // Function to set stamina

	UFUNCTION()
		void DecreasesStats(); // Function that sets timer to decrease stats over time

	UFUNCTION()
		void GiveResource(float amount, FString resourceType); // Function to give resources based on type

};
