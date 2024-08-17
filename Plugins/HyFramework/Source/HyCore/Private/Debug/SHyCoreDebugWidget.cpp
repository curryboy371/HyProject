// Fill out your copyright notice in the Description page of Project Settings.


#include "Debug/SHyCoreDebugWidget.h"
#include "SlateOptMacros.h"
#include "HyCoreLoggingEngineSubsystem.h"
#include "HyCoreMacro.h"

#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SComboBox.h"
#include "Widgets/Text/STextBlock.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

// localize for all languages
#define LOCTEXT_NAMESPACE "SHyCoreDebugWidget"


void SHyCoreDebugWidget::Construct(const FArguments& InArgs)
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

    FSlateFontInfo ComboBoxStyle = DefaultTextStyle;
    ComboBoxStyle.Size = 30.f;


    // 콤보박스에 추가할 옵션들 초기화

    LogPrintOptions.Add(MakeShared<FString>(TEXT("HideLog")));
    LogPrintOptions.Add(MakeShared<FString>(TEXT("SelectLog")));
    LogPrintOptions.Add(MakeShared<FString>(TEXT("PrintAllLog")));

    SelectedItem = LogPrintOptions.Last();

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

                        // X Button
                        + SVerticalBox::Slot()
                        .AutoHeight()
                        .HAlign(HAlign_Right)
                        .Padding(FMargin(0.f, 0.f, 0.f, 15.f)) // Bottom padding for spacing
                        [
                            SNew(SButton)
                                .OnClicked(this, &SHyCoreDebugWidget::OnExitButtonClicked)
                                [
                                    SNew(STextBlock)
                                        .Text(FText::FromString("X"))
                                        .Justification(ETextJustify::Center)
                                ]
                        ]

                        // 콤보박스
                        + SVerticalBox::Slot()
                        .AutoHeight()
                        .Padding(10.f)
                        [

                            SNew(SComboBox<FComboItemType>)
                                .OptionsSource(&LogPrintOptions)
                                .OnSelectionChanged(this, &SHyCoreDebugWidget::OnSelectionComboBoxChanged)
                                .OnGenerateWidget(this, &SHyCoreDebugWidget::OnGenerateComboBoxWidget)
                                [
                                    SNew(STextBlock)
                                        .Text(this, &SHyCoreDebugWidget::GetSelectedComboBoxText)
                                        .Font(ComboBoxStyle)
                                ]
                        ]


                        // LogCategory Button
                        DEFINE_LOG_CATEGORY_SLATE()
                ]
        ];
}


FReply SHyCoreDebugWidget::OnLogButtonClicked(const FString& InLogCategoryName)
{
    // 버튼 클릭시 먼저 호출되고
    if (UHyCoreLoggingEngineSubsystem* LoggingSubsystem = GET_LOGGING_SUBSYSTEM)
    {
        bool bEnable = LoggingSubsystem->IsEnableLogCategory(InLogCategoryName);
        LoggingSubsystem->SetLogCategoryEnable(InLogCategoryName, !bEnable);
    }

	return FReply::Handled();
}

FReply SHyCoreDebugWidget::OnExitButtonClicked()
{
    SetVisibility(EVisibility::Collapsed);
    return FReply::Handled();
}

FSlateColor SHyCoreDebugWidget::GetButtonTextColor(const FString& InLogCategoryName)
{
    // FReply::Handled() 반환되면 Slate UI가 다시 렌더링되면서 이 함수가 호출됨
    bool bEnable = false;

    if (UHyCoreLoggingEngineSubsystem* LoggingSubsystem = GET_LOGGING_SUBSYSTEM)
    {
        bEnable = LoggingSubsystem->IsEnableLogCategory(InLogCategoryName);
    }

    return bEnable ? EnableTextColor : DisableTextColor;
}

TSharedRef<SWidget> SHyCoreDebugWidget::OnGenerateComboBoxWidget(FComboItemType InItem)
{
    return SNew(STextBlock).Text(FText::FromString(*InItem));
}

void SHyCoreDebugWidget::OnSelectionComboBoxChanged(FComboItemType NewValue, ESelectInfo::Type SelectInfo)
{
    SelectedItem = NewValue;

    if (UHyCoreLoggingEngineSubsystem* LoggingSubsystem = GET_LOGGING_SUBSYSTEM)
    {
        if(SelectedItem == LogPrintOptions[0])
			LoggingSubsystem->SetLogPrintType(ELogPrintType::ELOG_Hide);
		else if (SelectedItem == LogPrintOptions[1])
			LoggingSubsystem->SetLogPrintType(ELogPrintType::ELOG_Select);
		else if (SelectedItem == LogPrintOptions[2])
			LoggingSubsystem->SetLogPrintType(ELogPrintType::ELOG_Output_ALL);
    }
}

FText SHyCoreDebugWidget::GetSelectedComboBoxText() const
{
    return FText::FromString(*SelectedItem);
}


#undef LOCTEXT_NAMESPACE

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

