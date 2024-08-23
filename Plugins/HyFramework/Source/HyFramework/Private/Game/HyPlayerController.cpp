// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/HyPlayerController.h"

bool AHyPlayerController::GetMouseRaycastHitLocation(FVector& OutLocation)
{
	float MouseX, MouseY;
	if (!GetMousePosition(MouseX, MouseY))
	{
		return false;
	}

	FVector WorldLocation, WorldDirection;
	if (DeprojectScreenPositionToWorld(MouseX, MouseY, WorldLocation, WorldDirection))
	{
		FHitResult HitResult;
		FVector StartLocation = WorldLocation;
		FVector EndLocation = WorldLocation + (WorldDirection * 10000.0f);

		// raycast
		if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility))
		{
			OutLocation = HitResult.Location;
			return true;
		}
	}

    return false;
}
