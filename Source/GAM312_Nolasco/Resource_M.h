// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Resource_M.generated.h"

UCLASS()
class GAM312_NOLASCO_API AResource_M : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResource_M();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		FString resourceName = "Wood"; // default name of the resource in the class details

	UPROPERTY(EditAnywhere)
		int resourceAmount = 5; // Amount of resource given per interaction

	UPROPERTY(EditAnywhere)
		int totalResource = 100; // Total amount of resources available before depletion

	UPROPERTY()
		FText tempText; // Temporary text variable to update the text render component

	UPROPERTY(EditAnywhere)
		UTextRenderComponent* ResourceNameTxt; // Text render component to display the resource name

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh; // Static mesh component to represent the resource visually

};
