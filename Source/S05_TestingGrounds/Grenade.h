// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grenade.generated.h"

UCLASS()
class S05_TESTINGGROUNDS_API AGrenade : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrenade();
	
	//Radius of impulse
	UPROPERTY(EditAnywhere)
		float ImpulseRadius;

	//Strength of impulse
	UPROPERTY(EditAnywhere)
		float ImpulseStrength;

	//Array of nearby actors
	UPROPERTY(EditAnywhere)
		TArray<AActor*> NearbyActors;

	UPROPERTY(EditAnywhere, Category = "Sweep")
		float SphereHeight = 200;

	UPROPERTY(EditAnywhere, Category = "Sweep")
		float SphereRadius = 200;


	UPROPERTY(EditAnywhere, Category = "Sweep")
		int32 Segments = 100;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(EditAnywhere, Category = Mesh)
		class USceneComponent* FP_MuzzleLocation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* Mesh1P;

	UFUNCTION(BlueprintCallable)
		void Throw();

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AGrenade> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* FireSound;

	
	
};
