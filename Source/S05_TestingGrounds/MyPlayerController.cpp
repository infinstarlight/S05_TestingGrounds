// Fill out your copyright notice in the Description page of Project Settings.

#include "S05_TestingGrounds.h"
#include "Character/Mannequin.h"
#include "MyPlayerController.h"

void AMyPlayerController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	if (InventoryWidgetBP)
	{
		//Create Inventory Widget based on the Blueprint reference we will input from within Editor
		InventoryWidgetRef = CreateWidget<UInventoryWidget>(this, InventoryWidgetBP);
	}

	//Initalization
	bIsInventoryOpen = false;
}

void AMyPlayerController::HandleInventoryInput()
{
	AMannequin* Char = Cast<AMannequin>(GetPawn());
	if (InventoryWidgetRef)
	{
		if (bIsInventoryOpen)
		{
			//Mark inventory as closed
			bIsInventoryOpen = false;

			//Remove from viewport
			InventoryWidgetRef->RemoveFromViewport();

			//Hide cursor of our game
			bShowMouseCursor = false;

			//Tell game we want to set input to Game Only
			FInputModeGameOnly InputMode;
			SetInputMode(InputMode);

			//Unpause Game
			SetPause(false);
		}
		else
		{
			//Mark the inventory as open
			bIsInventoryOpen = true;

			//Repopulate ItemsArray
			InventoryWidgetRef->ItemsArray = Char->GetInventory();

			//Show inventory
			InventoryWidgetRef->Show();

			//Show mouse cursor
			bShowMouseCursor = true;

			//Tells game we to set input to Game and UI
			FInputModeGameAndUI InputMode;
			SetInputMode(InputMode);

			//Pause
			SetPause(true);
		}
	}
}


