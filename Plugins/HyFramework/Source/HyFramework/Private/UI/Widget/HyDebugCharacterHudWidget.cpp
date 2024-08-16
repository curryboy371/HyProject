// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/HyDebugCharacterHudWidget.h"

#include "Components/TextBlock.h" 

void UHyDebugCharacterHudWidget::SetActionInfo(const FGameplayTag& InEquipTag, const FActionExcuteData& InCurActionData, const FActionExcuteData& InStoredActionData, const int32 InMontageIndex)
{
	if (ModeActionTxt)
	{
		FString ActionSetTagName = InEquipTag.ToString();

		FString StoredTagName = InStoredActionData.TagName.ToString();
		FString StoredTagString = FString::Printf(TEXT("%s (%d)"), *StoredTagName, InStoredActionData.ActionPriority);

		FString PerformanceTagName = InCurActionData.TagName.ToString();
		FString PerformanceTagString = FString::Printf(TEXT("%s (%d)"), *PerformanceTagName, InCurActionData.ActionPriority);


		//Actino Tag Render
		FText Text;
		ModeActionTxt->SetText(Text.FromString(ActionSetTagName));
		StoredActionTxt->SetText(Text.FromString(StoredTagString));
		PerformingActionTxt->SetText(Text.FromString(PerformanceTagString));

		// 인덱스 설정
		FString MontageIndexString = FString::FromInt(InMontageIndex);
		MontageIdxTxt->SetText(Text.FromString(MontageIndexString));
	}

}

void UHyDebugCharacterHudWidget::SetActionState(const FGameplayTag& InPerformingTag)
{
	// 상태 체크
	//if (SkillTxt)
	//{
	//	if (FNPTags::Get().IsSkillAction(InPerformingTag))
	//	{
	//		SkillTxt->SetColorAndOpacity(EnableColor);
	//	}
	//	else
	//	{
	//		SkillTxt->SetColorAndOpacity(DisableColor);
	//	}
	//}
	//
	//if (NormalTxt)
	//{
	//	if (FNPTags::Get().IsNormalAction(InPerformingTag))
	//	{
	//		NormalTxt->SetColorAndOpacity(EnableColor);
	//	}
	//	else
	//	{
	//		NormalTxt->SetColorAndOpacity(DisableColor);
	//	}
	//}
	//
	//if (MovingTxt)
	//{
	//	if (FNPTags::Get().IsMoveAction(InPerformingTag))
	//	{
	//		MovingTxt->SetColorAndOpacity(EnableColor);
	//	}
	//	else
	//	{
	//		MovingTxt->SetColorAndOpacity(DisableColor);
	//	}
	//}
	//
	//if (WalkingTxt)
	//{
	//	if (FNPTags::Get().IsMoveWalk(InPerformingTag))
	//	{
	//		WalkingTxt->SetColorAndOpacity(EnableColor);
	//	}
	//	else
	//	{
	//		WalkingTxt->SetColorAndOpacity(DisableColor);
	//	}
	//}
	//
	//if (StandingTxt)
	//{
	//	if (FNPTags::Get().IsStandAction(InPerformingTag))
	//	{
	//		StandingTxt->SetColorAndOpacity(EnableColor);
	//	}
	//	else
	//	{
	//		StandingTxt->SetColorAndOpacity(DisableColor);
	//	}
	//}
	//
	//if (AttackTxt)
	//{
	//	if (FNPTags::Get().IsAttackAction(InPerformingTag))
	//	{
	//		AttackTxt->SetColorAndOpacity(EnableColor);
	//	}
	//	else
	//	{
	//		AttackTxt->SetColorAndOpacity(DisableColor);
	//	}
	//}
	//
	//if (EvadingTxt)
	//{
	//	if (FNPTags::Get().IsEvadeAction(InPerformingTag))
	//	{
	//		EvadingTxt->SetColorAndOpacity(EnableColor);
	//	}
	//	else
	//	{
	//		EvadingTxt->SetColorAndOpacity(DisableColor);
	//	}
	//}
}

void UHyDebugCharacterHudWidget::SetTargetInfo(const FGuid& InMyGuid, const FGuid& inTargetGuid)
{
	FText Text;
	// guid출력 너무 길어서 6글자만 출력함.
	if (InfoTxt)
	{
		FString MyGuidShort = InMyGuid.ToString().Left(GuildStringNum);
		InfoTxt->SetText(Text.FromString(MyGuidShort));
	}

	if (TargetTxt)
	{
		if (inTargetGuid.IsValid() == false)
		{
			TargetTxt->SetText(Text.FromString(FString()));
		}
		else
		{
			FString TargetGuidShort = inTargetGuid.ToString().Left(GuildStringNum);
			TargetTxt->SetText(Text.FromString(TargetGuidShort));
		}
	}
}

void UHyDebugCharacterHudWidget::SetMoveInto(const FString& Acceleration, const FString& Velocity, const FString& InputScale, const FString& VelocityToAccRatioStr)
{
	FText Text;
	if (AccTxt)
	{
		AccTxt->SetText(Text.FromString(Acceleration));
	}

	if (VeloTxt)
	{
		VeloTxt->SetText(Text.FromString(Velocity));
	}

	if (InputScaleTxt)
	{
		InputScaleTxt->SetText(Text.FromString(InputScale));
	}

	if (VelToAccTxt)
	{
		VelToAccTxt->SetText(Text.FromString(VelocityToAccRatioStr));
	}
}
