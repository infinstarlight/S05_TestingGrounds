// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class S05_TESTINGGROUNDS_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//Adds widget to viewport and populates with items
	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
		void Show();

	//Removes widget from the viewport
	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
		void Hide();

	//Stores a reference in order to bind information on inventory slots
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<APickup*> ItemsArray;
	
	
};
