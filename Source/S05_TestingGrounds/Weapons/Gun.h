// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	WT_Primary UMETA(DisplayName="Primary"),
	WT_Secondary UMETA(DisplayName="Secondary"),
	WT_Power UMETA(DisplayName="Power")
};

UCLASS()
class S05_TESTINGGROUNDS_API AGun : public AActor
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, Category = Enum)
		EWeaponType WeaponType;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FP_Gun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* FP_MuzzleLocation;

public:	
	// Sets default values for this actor's properties
	AGun();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ABallProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere)
		int CurrentAmmoInMag;

	UPROPERTY(EditAnywhere)
		int MaxAmmoInMag;

	UPROPERTY(EditAnywhere)
		int CurrentAmmoinInventory;

	UPROPERTY(EditAnywhere)
		int MaxAmmoInInventory;

	UPROPERTY(EditAnywhere)
		float ReloadTime;

	

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* FireSound;

	/** AnimMontages to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation1P;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation3P;

	class UAnimInstance* AnimInstance1P;
	class UAnimInstance* AnimInstance3P;

	/** Fires a projectile. */
	UFUNCTION(BlueprintCallable, Category = "Input")
	void OnFire();

	/** Reloads the weapon */
	UFUNCTION(BlueprintCallable, Category = "Input")
		void OnReload();

	/** AnimMontages to play each time we reload */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class UAnimMontage* ReloadAnimation1P;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class UAnimMontage* ReloadAnimation3P;

	class UAnimInstance* ReloadAnimInstance1P;
	class UAnimInstance* ReloadAnimInstance3P;
	
};
