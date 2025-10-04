// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAM312_NOLASCO_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// Function to update health, hunger, and stamina bars in the UI
	UFUNCTION(BlueprintImplementableEvent)
		void UpdateBars(float Health1, float Hunger1, float Stamina1);
	
};
