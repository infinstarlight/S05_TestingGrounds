// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class S05_TESTINGGROUNDS_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

	//Enable or Disable glow effect
	void SetGlowEffect(bool Status);

	FORCEINLINE UTexture2D* GetPickupTexture() { return PickupTexture;  }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Static Mesh of Pickup
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* PickupSM;

	//Texture of item we want to add to secrets or Inventory
	UPROPERTY(EditAnywhere, Category = "PickupProperties")
		UTexture2D* PickupTexture;

	//Name of Item
	UPROPERTY(EditAnywhere, Category = "PickupProperties")
		FString ItemName;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
