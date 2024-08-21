// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Debug/SHyCharacterHudDebugWidget.h"
#include "SlateOptMacros.h"

#include "HyCoreMacro.h"

#include "Widgets/Text/STextBlock.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SHyCharacterHudDebugWidget::Construct(const FArguments& InArgs)
{
    DefaultSettingSetup();

    TSharedRef<SVerticalBox> VerticalBox = SNew(SVerticalBox);

    for (int32 i = 0; i < (int32)EDebugWidgetTextType::EDebugText_END; ++i)
    {
        EDebugWidgetTextType WidgetTextType = (EDebugWidgetTextType)i;

        if (DebugTextBlockMap.Contains(WidgetTextType) == false)
        {
            TSharedPtr<STextBlock> NewTextBlock = SNew(STextBlock)
                .Text(FText::FromString(FString::Printf(TEXT("Text Block %d"), i + 1)))
                .Font(DefaultTextStyle)
                .Justification(ETextJustify::Center)
                .ColorAndOpacity(FSlateColor(FLinearColor::White));

            DebugTextBlockMap.Add(WidgetTextType, NewTextBlock);

            // VerticalBox에 추가
            VerticalBox->AddSlot()
                .AutoHeight()
                .Padding(5)
                [
                    NewTextBlock.ToSharedRef()
                ];
        }
    }

    ChildSlot
        [
            VerticalBox
        ];
}
void SHyCharacterHudDebugWidget::DefaultSettingSetup()
{
    DefaultTextStyle = FCoreStyle::Get().GetFontStyle("NormalText");
    DefaultTextStyle.Size = 20.f;
}

void SHyCharacterHudDebugWidget::UpdateDebugText(const EDebugWidgetTextType InDebugTextType, const FString& InString)
{
    if (DebugTextBlockMap.Contains(InDebugTextType) == false)
    {
        ERR_V("Invalid DebugTextType %d", (int32)InDebugTextType);
        return;
    }

    if (!DebugTextBlockMap[InDebugTextType].IsValid())
    {
        ERR_V("Invalid DebugText %d", (int32)InDebugTextType);
    }

    FString Title;
    switch (InDebugTextType)
    {
    case EDebugWidgetTextType::EDebugText_EquipTag:
        Title = TEXT("EquipTag");
        break;
    case EDebugWidgetTextType::EDebugText_CurActionTag:
        Title = TEXT("CurActionTag");
        break;
    case EDebugWidgetTextType::EDebugText_StoredActionTag:
        Title = TEXT("StoredActionTag");
        break;
    case EDebugWidgetTextType::EDebugText_CombatMode:
        Title = TEXT("CombatMode");
        break;

    case EDebugWidgetTextType::EDebugText_Direction:
        Title = TEXT("Direction");
		break;

    case EDebugWidgetTextType::EDebugText_CurLocomotion:
	    Title = TEXT("CurLocomotion");
	    break;

    case EDebugWidgetTextType::EDebugText_TargetLocomotion:
        Title = TEXT("TargetLocomotion");
        break;

    case EDebugWidgetTextType::EDebugText_VelocityLength:
        Title = TEXT("Velocity");
        break;

    case EDebugWidgetTextType::EDebugText_END:
    default:
        ERR_V("Invalid DebugTextType %d", (int32)InDebugTextType);
        return;
    }

    FString Res = Title + TEXT(" ") + InString;
    DebugTextBlockMap[InDebugTextType]->SetText(FText::FromString(Res));
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
