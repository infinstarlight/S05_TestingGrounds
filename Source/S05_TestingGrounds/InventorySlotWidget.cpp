// Fill out your copyright notice in the Description page of Project Settings.

#include "S05_TestingGrounds.h"
#include "Character/Mannequin.h"
#include "InventorySlotWidget.h"

void UInventorySlotWidget::SetEquippedItem()
{
	AMannequin* Char = Cast<AMannequin>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Char)
	{
		Char->SetEquippedItem(ItemTexture);
	}
}

void UInventorySlotWidget::SetItemTexture(APickup* Item)
{
	//If the item is valid update the widget's texture.
	//If not, assign a null ptr to it so the widget won't broadcast wrong information to the player
	(Item) ? ItemTexture = Item->GetPickupTexture() : ItemTexture = nullptr;
}

