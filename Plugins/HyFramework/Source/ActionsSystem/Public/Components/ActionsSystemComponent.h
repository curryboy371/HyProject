// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/HyActorComponent.h"

#include "Actions/ActionsBaseAction.h"
#include "ActionsTypes.h"
#include "Data/ActionsDataAsset.h"


#include "GameplayTagContainer.h"


#include "ActionsSystemComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActionStarted, FGameplayTag, InActionTag);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActionEnded, FGameplayTag, InActionTag);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActionTriggered, FGameplayTag, InActionTag, EActionPriority, InPriority);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONSSYSTEM_API UActionsSystemComponent : public UHyActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActionsSystemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// UHyActorComponent을(를) 통해 상속됨
	void InitializeHyActorComponent() override;

	bool TriggerAction(const FActionExcuteData& InActionExcuteData, bool bCanBeStored = false);

	void LaunchAction(const FActionExcuteData& InActionExcuteData);
	void StoreAction(const FActionExcuteData& InActionExcuteData);
	void FreeAction();
	void PauseAction(bool bSetPause);
	void ActionStopImmeditaley(float InBlendOutTime = 0.0f);

	void ActionNotify();

public:
	void PlayMontage(const FActionMontageInfo& InMontageInfo, float InStartFrame);

	void InternalExitAction();

protected:
	void ActionStart(const FGameplayTag& InActionTag, const FString& InContext);
	void ActionEnd(const FGameplayTag& InActionTag);


	void TerminateCurrentAction();

	void SetMontageBlendType(const FActionMontageInfo& InMontageInfo);
public:
	void SetPerformingActionPriority(EActionPriority InPriority = EActionPriority::ENone);

	void SetStoredActionTag(const FActionExcuteData& InActionExcuteData, bool bForce = false);
	void SetDefaultStoredActionTag(const bool bForce = false);

	void SetDefaultActinoTag(const FActionExcuteData& InActionExcuteData) { DefaultActionExcuteData = InActionExcuteData; };

	void ClearPerformingActionState();

	TObjectPtr<class UActionsBaseAction> GetCurrentAction(const FGameplayTag& InActionTag);
	TObjectPtr<class UAnimMontage>  GetCurrentMontage(const FGameplayTag& InActionTag);
	
	TObjectPtr<class ACharacter>  GetCharacterOwner() { return CharacterOwner; };


	UFUNCTION(BlueprintCallable, Category = "Hy | Actions")
	bool CanExecuteAction(const FGameplayTag& InActionTag) const;
	
	UFUNCTION(BlueprintCallable, Category = "Hy | Actions")
	void SetEquipActions(const FGameplayTag& InEquipTag);

	UFUNCTION(BlueprintCallable, Category = "Hy | Actions")
	bool GetActionByTag(const FGameplayTag& InActionTag, FActionState& OutActionState) const;

	UFUNCTION(BlueprintCallable, Category = "Hy | Actions")
	bool GetEquipActionByTag(const FGameplayTag& InActionTag, const FGameplayTag& InEquipTag, FActionState& OutActionState) const;

	UFUNCTION(BlueprintCallable, Category = "Hy | Actions")
	bool GetCommonActionByTag(const FGameplayTag& InActionTag, FActionState& OutActionState) const;

	UFUNCTION(BlueprintCallable, Category = "Hy | Actions")
	const FGameplayTag GetPerformingActionTag() const;

	UFUNCTION(BlueprintCallable, Category = "Hy | Actions")
	const FGameplayTag GetStoredActionTag() const { return StoredActionExcuteData.TagName; };
	
	const FActionExcuteData& GetCurActionData() const { return CurActionExcuteData; };
	const FActionExcuteData& GetStoredActionData() const { return StoredActionExcuteData; };

	void SetCurActionPriority(EActionPriority InPriority) { CurActionExcuteData.ActionPriority = InPriority; };
	void SetStoredActionPriority(EActionPriority InPriority) { StoredActionExcuteData.ActionPriority = InPriority; };

	const bool IsActionStopCondition() const;

	const bool IsDefaultStoredAction() const;
	const bool IsLastMonstageSection() const;

	const bool IsEmptyStoredAction() const { return StoredActionExcuteData == FGameplayTag::EmptyTag; };


protected:
	void ResetActionState();


protected:
	UPROPERTY(BlueprintAssignable, Category = "Hy | Actions")
	FOnActionStarted OnActionStarted;

	UPROPERTY(BlueprintAssignable, Category = "Hy | Actions")
	FOnActionEnded OnActionFinished;
	
	UPROPERTY(BlueprintAssignable, Category = "Hy | Actions")
	FOnActionTriggered OnActionTriggered;

protected:
	UPROPERTY()
	TObjectPtr<class UAnimInstance> AnimInst;


protected:

/* Actions Set */
	/* Equip Tag과 관계없이 공통으로 계속 사용하게될 Common ActionDataSet*/
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Hy | Actions")
	TSubclassOf<class UActionsDataAsset> CMActionsDataSet;

	/* CMActionsDataSet을 Runtime에서 instance화 하여 사용함 */
	UPROPERTY(BlueprintReadOnly, Category = "Hy | Actions")
	TObjectPtr<UActionsDataAsset> CMActionsDataInst;

	/*	교체 하여 사용하는 ActionDataSet
		CurEquipTag 과 일치하는 ActionSet만 사용 가능	
	*/
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (TitleProperty = "TagName"), Category = "Hy | Actions")
	TArray<FActionsSet> EquipableActionSets;

	/* EquipableActionSets을 Runtime에서 instance화 하여 사용함 */
	UPROPERTY(BlueprintReadOnly, Category = "Hy | Actions")
	TMap<FGameplayTag, TObjectPtr<UActionsDataAsset>> EquipableActionsInstMap;

	/* Action State Values */
	UPROPERTY()
	TObjectPtr<UActionsBaseAction> PerformingAction;

	UPROPERTY(BlueprintReadOnly, Category = "Hy | Actions")
	FActionMontageInfo MontageInfo;

protected:
	/* 현재 상태에 맞는 EquipableActionsInstMap을 결정짓는 Tag*/
	FGameplayTag CurEquipTag;

	/* Action Tag */
	FActionExcuteData CurActionExcuteData;
	FActionExcuteData StoredActionExcuteData;

	FActionExcuteData DefaultActionExcuteData;

	bool bIsPerformingAction;


};
