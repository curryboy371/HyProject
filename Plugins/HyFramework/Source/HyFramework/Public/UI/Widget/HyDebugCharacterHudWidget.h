// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseUI/HyUserWidgetBase.h"

#include "ActionsTypes.h"

#include "GameplayTagContainer.h"

#include "HyDebugCharacterHudWidget.generated.h"

/**
 * 
 */
UCLASS()
class HYFRAMEWORK_API UHyDebugCharacterHudWidget : public UHyUserWidgetBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Hy | Widget | Debug")
	void SetIsPlayerWidget(bool bRes);

	void SetActionInfo(const FGameplayTag& InEquipTag, const FActionExcuteData& InCurActionData, const FActionExcuteData& InStoredActionData, const int32 InMontageIndex);
	void SetActionState(const FGameplayTag& InPerformingTag);
	void SetTargetInfo(const FGuid& InMyGuid, const FGuid& inTargetGuid);
	void SetMoveInto(const FString& Acceleration, const FString& Velocity, const FString& InputScale, const FString& VelocityToAccRatioStr);

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ModeActionTxt;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* StoredActionTxt;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* PerformingActionTxt;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* MontageIdxTxt;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* SkillTxt;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* NormalTxt;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* MovingTxt;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* WalkingTxt;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* StandingTxt;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* AttackTxt;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* EvadingTxt;


	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* InfoTxt;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TargetTxt;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* AccTxt;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* VeloTxt;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* InputScaleTxt;


	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* VelToAccTxt;


	UPROPERTY(BlueprintReadWrite)
	FLinearColor EnableColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);  // 빨간색으로 초기화

	UPROPERTY(BlueprintReadWrite)
	FLinearColor DisableColor = FLinearColor(0.1f, 0.1f, 0.1f, 0.7f);  // 빨간색으로 초기화

	UPROPERTY(BlueprintReadWrite)
	int32 GuildStringNum = 8;
	
};
