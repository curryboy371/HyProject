// Fill out your copyright notice in the Description page of Project Settings.


#include "Debug/HyCoreDebugSCompoundWidget.h"
#include "SlateOptMacros.h"
#include "HyCoreLoggingEngineSubsystem.h"
#include "HyCoreMacro.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

// localize for all languages
#define LOCTEXT_NAMESPACE "HyCoreDebugSCompoundWidget"

void HyCoreDebugSCompoundWidget::Construct(const FArguments& InArgs)
{

    DEF_BUTTON_FONT_NAME.Size = BUTTON_FONT_SIZE;

	// 인자
    OwnerHUD = InArgs._OwnerHUDArg;
    const FMargin ContentPadding = FMargin(100.f, 100.f);
    const FMargin ButtonPadding = FMargin(10.f);

    const FText TitleText = LOCTEXT("GameTitle", "HUD Debug");
    const FText SubTitleText = LOCTEXT("SubTitle", "LogSwitch");

    const FText PlayText = LOCTEXT("PlayGame", "Play Game");
    const FText SettingsText = LOCTEXT("Settings", "Settings");

    FSlateFontInfo DefaultTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");

    FSlateFontInfo TitleTextStyle = DefaultTextStyle;
    TitleTextStyle.Size = 70.f;

    FSlateFontInfo SubTitleTextStyle = DefaultTextStyle;
    SubTitleTextStyle.Size = 50.f;

    ChildSlot
        .VAlign(VAlign_Fill)
        .HAlign(HAlign_Fill)
        [
            SNew(SOverlay)
                + SOverlay::Slot()
                .VAlign(VAlign_Top)
                .HAlign(HAlign_Left)
                .Padding(ContentPadding)
                [
                    SNew(SVerticalBox)

                        // Main Title
                        + SVerticalBox::Slot()
                        .AutoHeight()
                        .Padding(FMargin(0.f, 0.f, 0.f, 5.f)) // Bottom padding for spacing
                        [
                            SNew(STextBlock)
                                .Font(TitleTextStyle)
                                .Text(TitleText)
                                .Justification(ETextJustify::Left)
                        ]

                        // Sub Title
                        + SVerticalBox::Slot()
                        .AutoHeight()
                        .Padding(FMargin(0.f, 0.f, 0.f, 15.f)) // Bottom padding for spacing
                        [
                            SNew(STextBlock)
                                .Font(SubTitleTextStyle)
                                .Text(SubTitleText)
                                .Justification(ETextJustify::Left)
                        ]


                        // X Button
                        +SVerticalBox::Slot()
                        .AutoHeight()
                        .HAlign(HAlign_Right)
                        .Padding(FMargin(0.f, 0.f, 0.f, 15.f)) // Bottom padding for spacing
                        [
                            SNew(SButton)
                                .OnClicked(this, &HyCoreDebugSCompoundWidget::OnExitButtonClicked)
                                [
                                    SNew(STextBlock)
                                        .Text(FText::FromString("X"))
                                        .Justification(ETextJustify::Center)
                                ]
                        ]

                        // LogCategory Button
                        DEFINE_LOG_CATEGORY_SLATE()
                ]
        ];
}


FReply HyCoreDebugSCompoundWidget::OnButtonClicked(const FString& InLogCategoryName)
{
    // 버튼 클릭시 먼저 호출되고
    if (UHyCoreLoggingEngineSubsystem* LoggingSubsystem = GET_LOGGING_SUBSYSTEM)
    {
        bool bEnable = LoggingSubsystem->IsEnableLogCategory(InLogCategoryName);
        LoggingSubsystem->SetLogCategoryEnable(InLogCategoryName, !bEnable);
    }

	return FReply::Handled();
}

FReply HyCoreDebugSCompoundWidget::OnExitButtonClicked()
{
    SetVisibility(EVisibility::Collapsed);
    return FReply::Handled();
}

FSlateColor HyCoreDebugSCompoundWidget::GetButtonTextColor(const FString& InLogCategoryName)
{
    // FReply::Handled() 반환되면 Slate UI가 다시 렌더링되면서 이 함수가 호출됨
    bool bEnable = false;

    if (UHyCoreLoggingEngineSubsystem* LoggingSubsystem = GET_LOGGING_SUBSYSTEM)
    {
        bEnable = LoggingSubsystem->IsEnableLogCategory(InLogCategoryName);
    }

    return bEnable ? EnableTextColor : DisableTextColor;
}


#undef LOCTEXT_NAMESPACE

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

