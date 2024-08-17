// Fill out your copyright notice in the Description page of Project Settings.


#include "Debug/HyCoreHUD.h"

#include "Debug/SHyCoreDebugWidget.h"
#include "Widgets/SWeakWidget.h" 
#include "Engine/Engine.h"


void AHyCoreHUD::BeginPlay()
{
	Super::BeginPlay();


}

void AHyCoreHUD::SetWidgetVisibility(bool bVisibility)
{
	if (bVisibility)
	{
		if (!HyCoreDebugSWidget.IsValid())
		{
			HyCoreDebugSWidget = SNew(SHyCoreDebugWidget).OwnerHUDArg(this);

			GEngine->GameViewport->AddViewportWidgetContent(
				SAssignNew(HyCoreSWidgetContainer, SWeakWidget).PossiblyNullContent(HyCoreDebugSWidget.ToSharedRef())
			);
		}
	}

	if (HyCoreDebugSWidget.IsValid())
	{
		HyCoreDebugSWidget->SetVisibility(bVisibility ? EVisibility::Visible : EVisibility::Collapsed);
	}
}
