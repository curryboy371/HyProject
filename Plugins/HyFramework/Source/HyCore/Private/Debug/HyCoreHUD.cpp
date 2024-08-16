// Fill out your copyright notice in the Description page of Project Settings.


#include "Debug/HyCoreHUD.h"

#include "Debug/HyCoreDebugSCompoundWidget.h"
#include "Widgets/SWeakWidget.h" 
#include "Engine/Engine.h"


void AHyCoreHUD::BeginPlay()
{
	Super::BeginPlay();

	HyCoreDebugSWidget = SNew(HyCoreDebugSCompoundWidget).OwnerHUDArg(this);

	GEngine->GameViewport->AddViewportWidgetContent(
		SAssignNew(HyCoreSWidgetContainer, SWeakWidget).PossiblyNullContent(HyCoreDebugSWidget.ToSharedRef())
	);
}

void AHyCoreHUD::SetWidgetVisibility(bool bVisibility)
{
	if (HyCoreDebugSWidget.IsValid())
	{
		HyCoreDebugSWidget->SetVisibility(bVisibility ? EVisibility::Visible : EVisibility::Collapsed);
	}
}
