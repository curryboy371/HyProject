// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HyCoreHUD.generated.h"

 
/**
 * 
 */
UCLASS()
class HYCORE_API AHyCoreHUD : public AHUD
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "HyCore")
	void SetWidgetVisibility(bool bVisibility);

protected:
	TSharedPtr<class SWidget> HyCoreSWidgetContainer;
	TSharedPtr<class HyCoreDebugSCompoundWidget> HyCoreDebugSWidget;

};
