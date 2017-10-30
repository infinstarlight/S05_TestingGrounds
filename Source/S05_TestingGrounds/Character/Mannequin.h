// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pickup.h"
#include "GameFramework/Character.h"
#include "Mannequin.generated.h"



UCLASS()
class S05_TESTINGGROUNDS_API AMannequin : public ACharacter
{
	GENERATED_BODY()

#define MAX_INVENTORY_ITEMS 4
public:
	// Sets default values for this character's properties
	AMannequin();

	//Actor to be selected
	UPROPERTY(EditAnywhere, Category = "Physics")
		AActor* ActorToMove;

	//Force that will be applied to chosen Actor
	UPROPERTY(EditAnywhere, Category = "Physics")
		FVector ForceToAdd = FVector(0, 0, 5000);

	//Function that applies force to actor
	UFUNCTION(BlueprintCallable, Category = "Physics")
		void MoveChosenActor();

	/** Location on Character mesh where Grenade should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USceneComponent* FP_grenadeLocation;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		float RaycastRange = 250.0f;

	

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void UnPossessed() override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<class AGun> GunBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<class AGrenade> GrenadeBlueprint;


	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void PullTrigger();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void ReloadWeapon();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void OnThrow();

	//Handles the Pickup Input
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void PickupItem();

	//Handles the Pickup Input for Weapon
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void PickupWeapon();

	
	//TODO: Create Weapon Inventory
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
		TArray<AGun*> WeaponInventory;

	TArray<AGun*> GetWeaponInventory() { return WeaponInventory; }

	TArray<APickup*> GetInventory() { return Inventory; }

	void SetEquippedItem(UTexture2D* Texture);

private:
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	AGun* Gun;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		AGrenade* Grenade;

	/*Raycasts in front of the character to find usable items*/
	void Raycast();

	/*Reference to the last seen pickup item. Nullptr if none*/
	APickup* LastItemSeen;

	AGun* LastWeaponSeen;

	UFUNCTION()
		void HandleInventoryInput();

	//Actual Inventory
	UPROPERTY(VisibleAnywhere)
		TArray<APickup*> Inventory;

	//Reference currently equipped item
	APickup* CurrentlyEquippedItem;

	//Drop currently equipped item
	UFUNCTION()
		void DropEquippedItem();

};