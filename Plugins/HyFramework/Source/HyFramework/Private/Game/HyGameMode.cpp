// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/HyGameMode.h"


#include "HyCoreLoggingEngineSubsystem.h"

#include "Debug/HyCoreHUD.h"

AHyGameMode::AHyGameMode()
{
	HUDClass = AHyCoreHUD::StaticClass();
}

void AHyGameMode::SetLogDebugWidgetVisibility(bool bVisiblity)
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		AHyCoreHUD* HUDInst = Cast<AHyCoreHUD>(PlayerController->GetHUD());
		if (HUDInst)
		{
			HUDInst->SetWidgetVisibility(bVisiblity);
		}
	}
}
