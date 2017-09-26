// Fill out your copyright notice in the Description page of Project Settings.

#include "S05_TestingGrounds.h"
#include "Mannequin.h"
#include "MyPlayerController.h"
#include "../Weapons/Gun.h"


// Sets default values
AMannequin::AMannequin()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);
}

// Called when the game starts or when spawned
void AMannequin::BeginPlay()
{
	Super::BeginPlay();
	if (GunBlueprint == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Gun blueprint missing."));
		return;
	}

	Gun = GetWorld()->SpawnActor<AGun>(GunBlueprint);
	

	//Attach gun mesh component to Skeleton, doing it here because the skelton is not yet created in the constructor
	if (IsPlayerControlled()) {
		Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint")); 
	}
	else {
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint_0"));
	}

	Gun->AnimInstance1P = Mesh1P->GetAnimInstance();
	Gun->AnimInstance3P = GetMesh()->GetAnimInstance();
	

	if (InputComponent != nullptr) {
		InputComponent->BindAction("Fire", IE_Pressed, this, &AMannequin::PullTrigger);
		InputComponent->BindAction("Reload", IE_Pressed, this, &AMannequin::ReloadWeapon);
		InputComponent->BindAction("Activate", IE_Pressed, this, &AMannequin::PickupItem);
		InputComponent->BindAction("Drop Item", IE_Pressed, this, &AMannequin::DropEquippedItem);
		
		FInputActionBinding InventoryBinding;
		//We need this bind to execute on pause state
		InventoryBinding.bExecuteWhenPaused = true;
		InventoryBinding.ActionDelegate.BindDelegate(this, FName("HandleInventoryInput"));
		InventoryBinding.ActionName = FName("Inventory");
		InventoryBinding.KeyEvent = IE_Pressed;

		//Binding the Inventory action
		InputComponent->AddActionBinding(InventoryBinding);
	}

	//Initializing our reference
	LastItemSeen = nullptr;

	Inventory.SetNum(MAX_INVENTORY_ITEMS);
}

// Called every frame
void AMannequin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Raycast();

}

// Called to bind functionality to input
void AMannequin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	
}

void AMannequin::UnPossessed() {
	Super::UnPossessed();
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint_0"));
}

void AMannequin::PullTrigger()
{
	Gun->OnFire();
}

void AMannequin::ReloadWeapon()
{
	Gun->OnReload();
}

void AMannequin::Raycast()
{
	//Calculating start and end location
	FVector StartLocation = FirstPersonCameraComponent->GetComponentLocation();
	FVector EndLocation = StartLocation + (FirstPersonCameraComponent->GetForwardVector() * RaycastRange);

	FHitResult RaycastHit;

	//Raycast should ignore the character
	FCollisionQueryParams CQP;
	CQP.AddIgnoredActor(this);

	//Raycast
	GetWorld()->LineTraceSingleByChannel(RaycastHit, StartLocation, EndLocation, ECollisionChannel::ECC_WorldDynamic, CQP);


	APickup* Pickup = Cast<APickup>(RaycastHit.GetActor());

	if (LastItemSeen && LastItemSeen != Pickup)
	{
		//If our character sees a different pickup then disable the glowing effect on the previous seen item
		LastItemSeen->SetGlowEffect(false);
	}

	if (Pickup)
	{
		//Enable the glow effect on the current item
		LastItemSeen = Pickup;
		Pickup->SetGlowEffect(true);
	}//Re-Initialize 
	else LastItemSeen = nullptr;

}

void AMannequin::PickupItem()
{
	if (LastItemSeen)
	{
		//Find the first available slot
		int32 AvailableSlot = Inventory.Find(nullptr);

		if (AvailableSlot != INDEX_NONE)
		{
			//Add the item to the first valid slot we found
			Inventory[AvailableSlot] = LastItemSeen;
			//Destroy the item from the game
			LastItemSeen->Destroy();
		}
		else GLog->Log("You can't carry any more items!");
	}
}

void AMannequin::HandleInventoryInput()
{
	AMyPlayerController* Con = Cast<AMyPlayerController>(GetController());
	if (Con) Con->HandleInventoryInput();
}

void AMannequin::SetEquippedItem(UTexture2D * Texture)
{
	if (Texture)
	{
		//For this scenario we make the assumption that
		//every pickup has a unique texture.
		//So, in order to set the equipped item we just check every item
		//inside our Inventory. Once we find an item that has the same image as the
		//Texture image we're passing as a parameter we mark that item as CurrentlyEquipped.
		for (auto It = Inventory.CreateIterator(); It; It++)
		{
			if ((*It) && (*It)->GetPickupTexture() && (*It)->GetPickupTexture()->HasSameSourceArt(Texture))
			{
				CurrentlyEquippedItem = *It;
				GLog->Log("I've set a new equipped item: " + CurrentlyEquippedItem->GetName());
				break;
			}
		}
	}
	else GLog->Log("The Player has clicked an empty inventory slot");
}

void AMannequin::DropEquippedItem()
{
	if (CurrentlyEquippedItem)
	{
		int32 IndexOfItem;
		if (Inventory.Find(CurrentlyEquippedItem, IndexOfItem))
		{
			//Location of drop
			FVector DropLocation = GetActorLocation() + (GetActorForwardVector() * 200);

			//Making a transform with default rotation and scale
			FTransform Transform; Transform.SetLocation(DropLocation);

			//Default actor spawn parameters
			FActorSpawnParameters SpawnParams;

			//Spawning our pickup
			APickup* PickupToSpawn = GetWorld()->SpawnActor<APickup>(CurrentlyEquippedItem->GetClass(), Transform, SpawnParams);

			if (PickupToSpawn)
			{
				//Unreference item we've dropped
				Inventory[IndexOfItem] = nullptr;
			}
		}
	}
}