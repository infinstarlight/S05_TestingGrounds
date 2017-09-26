// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once 
#include "GameFramework/HUD.h"
#include "S05_TestingGroundsHUD.generated.h"

UCLASS()
class AS05_TestingGroundsHUD : public AHUD
{
	GENERATED_BODY()

public:
	AS05_TestingGroundsHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

protected:

	//Start location of rader
	UPROPERTY(EditAnywhere, Category = Radar)
		FVector2D RadarStartLocation = FVector2D(0.9f, 0.2f);

	//Radius of radar
	UPROPERTY(EditAnywhere, Category = Radar)
		float RadarRadius = 100.0f;

	UPROPERTY(EditAnywhere, Category = Radar)
		float DegreeStep = 0.25f;

	//Pixel Size of the drawable radar actors
	UPROPERTY(EditAnywhere, Category = Radar)
		float DrawPixelSize = 5.0f;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

	//Returns the center of the radar as a 2D Vector
	FVector2D GetRadarCenterPosition();

	//Draws the radar
	void DrawRadar();
};

