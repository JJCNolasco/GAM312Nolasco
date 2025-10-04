// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ObjectiveWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAM312_NOLASCO_API UObjectiveWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// Functions to update the objectives in the UI
	UFUNCTION(BLueprintImplementableEvent)
		void UpdatematOBJ(float matsCollected);

	UFUNCTION(BLueprintImplementableEvent)
		void UpdatebuildOBJ(float objectsBuilt);
	
};
