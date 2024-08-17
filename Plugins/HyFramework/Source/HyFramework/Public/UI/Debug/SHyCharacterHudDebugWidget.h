// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseUI/SHyBaseWidget.h"

#include "HyTypes.h"


/**
 * 
 */
class HYFRAMEWORK_API SHyCharacterHudDebugWidget : public SHyBaseWidget
{
public:
	SLATE_BEGIN_ARGS(SHyCharacterHudDebugWidget) {}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	void DefaultSettingSetup();


	void UpdateDebugText(const EDebugWidgetTextType InDebugTextType, const FString& InString);

private:
	TMap<EDebugWidgetTextType, TSharedPtr<STextBlock>> DebugTextBlockMap;

private:
	FSlateFontInfo DefaultTextStyle;
};
