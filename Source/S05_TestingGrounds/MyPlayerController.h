// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryWidget.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class S05_TESTINGGROUNDS_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void Possess(APawn* InPawn) override;

	//Open or close Inventory
	void HandleInventoryInput();


protected:
	//InventoryWidget Blueprint Reference
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UInventoryWidget> InventoryWidgetBP;

private:
	//InventoryWidget Reference
	UInventoryWidget* InventoryWidgetRef;

	//True if inventory is currently open - false otherwise
	bool bIsInventoryOpen;
	
};
