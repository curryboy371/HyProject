// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HyCoreDefineMacro.h"

#include "Widgets/SCompoundWidget.h"

typedef TSharedPtr<FString> FComboItemType;


#define DEF_BUTTON_FONT_NAME     ButtonFontInfo

#define BUTTON_FONT     FCoreStyle::Get().GetFontStyle("EmbossedText")
#define DEF_BUTTON_FONT_INFO     FSlateFontInfo DEF_BUTTON_FONT_NAME = BUTTON_FONT;

#define BUTTON_PADING   FMargin(10, 10.f, 10.f, 10.f)
#define BUTTON_FONT_SIZE    30.f

#define CREATE_BUTTON(CategoryName) \
    + SVerticalBox::Slot() \
        .AutoHeight() \
        .Padding(BUTTON_PADING) \
	    [ \
            SNew(SButton) \
            .OnClicked_Lambda([this]() { return OnLogButtonClicked(TEXT(#CategoryName)); }) \
            [ \
                SNew(STextBlock) \
                .Font(DEF_BUTTON_FONT_NAME) \
                .Text(FText::FromString(TEXT(#CategoryName))) \
                .ColorAndOpacity_Lambda([this]() { return GetButtonTextColor(TEXT(#CategoryName)); }) \
                .Justification(ETextJustify::Center) \
            ] \
        ]

// Define all log categories
#define DEFINE_LOG_CATEGORY_SLATE() \
    LOG_CATEGORY_LIST(CREATE_BUTTON) 

/**
 * 
 */
class HYCORE_API SHyCoreDebugWidget : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SHyCoreDebugWidget) {}
	SLATE_ARGUMENT(TWeakObjectPtr<class AHyCoreHUD>, OwnerHUDArg);
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	FReply OnLogButtonClicked(const FString& InLogCategoryName);
	FReply OnExitButtonClicked();

    FSlateColor GetButtonTextColor(const FString& InLogCategoryName);


    TSharedRef<SWidget> OnGenerateComboBoxWidget(FComboItemType InItem);
    void OnSelectionComboBoxChanged(FComboItemType NewValue, ESelectInfo::Type SelectInfo);
    FText GetSelectedComboBoxText() const;

private:
    DEF_BUTTON_FONT_INFO

	TWeakObjectPtr<class AHyCoreHUD> OwnerHUD;

    FLinearColor EnableTextColor = FLinearColor::White;
    FLinearColor DisableTextColor = FLinearColor::Gray;


    // Select Box
    TArray<FComboItemType> LogPrintOptions;
    FComboItemType SelectedItem;
};
