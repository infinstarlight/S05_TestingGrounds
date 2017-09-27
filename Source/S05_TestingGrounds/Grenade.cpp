// Fill out your copyright notice in the Description page of Project Settings.

#include "S05_TestingGrounds.h"
#include "Grenade.h"


// Sets default values
AGrenade::AGrenade()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GrenadeMesh"));
	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));
}

// Called when the game starts or when spawned
void AGrenade::BeginPlay()
{
	Super::BeginPlay();

	//Get all nearby actors
	for (auto It = NearbyActors.CreateIterator(); It; It++)
	{
		//Get static mesh component for each actor
		UStaticMeshComponent* SM = Cast<UStaticMeshComponent>((*It)->GetRootComponent());

		/*If component is valid, apply radial impulse from location of Grenade actor
		halving as Radius and Strength the values from the editor.
		RTF_Linear impulse fall off means impulse will fall off to zero when max distance is reached
		*/
		if (SM)
		{
			SM->AddRadialImpulse(GetActorLocation(), ImpulseRadius, ImpulseStrength, ERadialImpulseFalloff::RIF_Linear, true);
		}
	}

	/*TArray is the collection that contains all the HitResults*/
	TArray<FHitResult> HitResults;

	/*The Start location of the sphere*/
	FVector StartLocation = GetActorLocation();

	/*The End location of the sphere is equal to the default location of the actor plus the height we will enter from the editor
	To extend this functionality, you can replace the height variable with a FVector*/
	FVector EndLocation = GetActorLocation();
	EndLocation.Z += SphereHeight;

	/*Search for static objects only*/
	ECollisionChannel ECC = ECollisionChannel::ECC_WorldStatic;

	/*Declare the Collision Shape, assign a Sphere shape and set it's radius*/
	FCollisionShape CollisionShape;
	CollisionShape.ShapeType = ECollisionShape::Sphere;
	CollisionShape.SetSphere(SphereRadius);

	/*Perform the actual raycast. This method returns true if there is at least 1 hit.*/
	bool bHitSomething = GetWorld()->SweepMultiByChannel(HitResults, StartLocation, EndLocation, FQuat::FQuat(), ECC, CollisionShape);

	/*If the raycast hit a number of objects, iterate through them and print their name in the console*/
	if (bHitSomething)
	{
		for (auto It = HitResults.CreateIterator(); It; It++)
		{
			GLog->Log((*It).Actor->GetName());
		}
	}

	/*In order to draw the sphere of the first image, I will use the DrawDebugSphere function which resides in the DrawDebugHelpers.h
	This function needs the center of the sphere which in this case is provided by the following equation*/
	FVector CenterOfSphere = ((EndLocation - StartLocation) / 2) + StartLocation;

	/*Draw the sphere in the viewport*/
	DrawDebugSphere(GetWorld(), CenterOfSphere, CollisionShape.GetSphereRadius(), Segments, FColor::Green, true);
}

// Called every frame
void AGrenade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGrenade::Throw()
{
	// try and fire a projectile
	if (ProjectileClass != NULL)
	{
		const FRotator SpawnRotation = FP_MuzzleLocation->GetComponentRotation();
		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
		const FVector SpawnLocation = FP_MuzzleLocation->GetComponentLocation();

		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			// spawn the projectile at the muzzle
			World->SpawnActor<AGrenade>(ProjectileClass, SpawnLocation, SpawnRotation);
		}
	}
}

