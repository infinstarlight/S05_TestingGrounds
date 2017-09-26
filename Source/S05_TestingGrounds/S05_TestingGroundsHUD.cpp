// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "S05_TestingGrounds.h"
#include "S05_TestingGroundsHUD.h"
#include "Engine/Canvas.h"
#include "TextureResource.h"
#include "CanvasItem.h"

AS05_TestingGroundsHUD::AS05_TestingGroundsHUD()
{
	// Set the crosshair texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshiarTexObj(TEXT("/Game/Static/Player/Textures/FirstPersonCrosshair"));
	CrosshairTex = CrosshiarTexObj.Object;
}


void AS05_TestingGroundsHUD::DrawHUD()
{
	Super::DrawHUD();

	// Draw very simple crosshair

	// find center of the Canvas
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	// offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
	const FVector2D CrosshairDrawPosition( (Center.X),
										   (Center.Y));

	// draw the crosshair
	FCanvasTileItem TileItem( CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem( TileItem );
}

FVector2D AS05_TestingGroundsHUD::GetRadarCenterPosition()
{
	//If the canvas is valid, return the center as a 2d vector
	return (Canvas) ? FVector2D(Canvas->SizeX*RadarStartLocation.X, Canvas->SizeY*RadarStartLocation.Y) : FVector2D(0, 0);
}

void AS05_TestingGroundsHUD::DrawRadar()
{
	FVector2D RadarCenter = GetRadarCenterPosition();

	for (float i = 0; i < 360; i += DegreeStep)
	{
		//We want to draw a circle in order to represent our radar
		//In order to do so, we calculate the sin and cos of almost every degree
		//It it impossible to calculate each and every possible degree because they are infinite
		//Lower the degree step in case you need a more accurate circle representation

		//We multiply our coordinates by radar size 
		//in order to draw a circle with radius equal to the one we will input through the editor
		float fixedX = FMath::Cos(i) * RadarRadius;
		float fixedY = FMath::Sin(i) * RadarRadius;

		//Actual draw
		DrawLine(RadarCenter.X, RadarCenter.Y, RadarCenter.X + fixedX, RadarCenter.Y + fixedY, FLinearColor::Gray, 1.f);
	}
}