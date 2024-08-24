// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "ActionsTypes.h"
#include "GameplayTagContainer.h"



#include "ActionsBaseAction.generated.h"

/**
 * 
 * 
 * Blueprintable : 에디터에서 Blueprint Class를 만들어 사용하기 위해 선언
 * BlueprintType : Blueprint에서 변수로 만들어 사용하기 위함
 * DefaultToInstanced : 클래스가 인스턴스된 객체를 기본 값으로 가지도록함
 * EditInlineNew : 에디터 detail에서 직접 생성, 및 편집 가능하도록
 * 
 */
UCLASS(Blueprintable, BlueprintType, DefaultToInstanced, EditInlineNew)
class ACTIONSSYSTEM_API UActionsBaseAction : public UObject
{
	GENERATED_BODY()
	
public:
    UActionsBaseAction();


    /*Called when the action is successfully triggered*/
    UFUNCTION(BlueprintNativeEvent, Category = "Actions")
    void OnActionStarted(const FString& InContext = FString());
    virtual void OnActionStarted_Implementation(const FString& InContext = FString()) {};


    /*Called when the action montage setup completed*/
    UFUNCTION(BlueprintNativeEvent, Category = "Actions")
    void OnActionSetupCompleted(const FString& InContext = FString());
    virtual void OnActionSetupCompleted_Implementation(const FString& InContext = FString()) {};

    /*Called when the action is finished. Normally if BindActionToAnimation is set to true
    this is called when the animation is finished*/
    UFUNCTION(BlueprintNativeEvent, Category = "Actions")
    void OnActionEnded();
    virtual void OnActionEnded_Implementation() {};

    /*Called when the action is successfully triggered and BEFORE the OnActionStarted.*/
    UFUNCTION(BlueprintNativeEvent, Category = "Actions")
    void OnActionTransition(class UActionsBaseAction* InpreAction);
    virtual void OnActionTransition_Implementation(class UActionsBaseAction* InpreAction) {};

    /*Called every frame if the ActionsManagerComponent of this character has bCanTick set to true*/
    UFUNCTION(BlueprintNativeEvent, Category = "Actions")
    void OnTick(float DeltaTime);
    virtual void OnTick_Implementation(float DeltaTime) {  };

    /* Action Notify */
    UFUNCTION(BlueprintNativeEvent, Category = "Actions")
    void OnActionNotify();
    virtual void OnActionNotify_Implementation() { };

    UFUNCTION(BlueprintNativeEvent, Category = "Actions")
    bool IsStopConditional();
    virtual bool IsStopConditional_Implementation() { return true; };



    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Actions")
    void PlayEffects();
    virtual void PlayEffects_Implementation();

    /*Implement this to select the name of the montage section that should be played when executing this action */
    UFUNCTION(BlueprintNativeEvent, Category = "Actions")
    FName GetMontageSectionName();
    virtual FName GetMontageSectionName_Implementation() { return NAME_None; };

    /*Implement this to select the name of the montage section that should be played when executing this action */
    UFUNCTION(BlueprintCallable, Category = "Actions")
    void SetActionMontageInfo(const FActionMontageInfo& InMontageInfo) {};

    FActionMontageInfo& GetActionMontageInfo() { return MontageInfo; };


    /*Interrupt current action AND animation Immediately*/
    UFUNCTION(BlueprintCallable, Category = "Actions")
    void StopActionImmediately() {};


    UFUNCTION(BlueprintNativeEvent, Category = "Actions")
    float GetPlayRate();
    virtual float GetPlayRate_Implementation() { return AnimRate; };

    /*Play the animation montage related to this action. Called automatically by default*/
    UFUNCTION(BlueprintCallable, Category = "Actions")
    void ExecuteAction();

    /*Called to force the end of the action. Does not stop the animation but allows the trigger of eventually stored
    actions or set the actual state to the default one*/
    UFUNCTION(BlueprintCallable, Category = "Actions")
    void ExitAction();

    virtual void Internal_OnActivated(TObjectPtr<class UActionsSystemComponent> InActionSystemCom, TObjectPtr<class UAnimMontage> InAnimMontage, const FString& InContext);
    virtual void Internal_OnDeactivated();


    void PrepareMontageInfo();

    void BindMontageEvents();
    void UnbindMontageEvents();

    UFUNCTION()
    void HandleMontageFinished(class UAnimMontage* InAnimMontage, bool InbInterruptted);

    UFUNCTION()
    void HandleMontageStarted(class UAnimMontage* InAnimMontage);


    virtual void ClearActionState() {};


    bool GetTerminated() const { return bTerminated; }
    void SetTerminated(bool val) { bTerminated = val; }



    bool GetMontageRate(float& OutMontageRate);
    bool GetMontageProgress(float& OutPregress);

    int32 GetCurMontageSectionIdx();
    int32 GetCurMontageSectionLength();

public:
    const FActionConfig& GetActionConfig() { return ActionConfig; }

    TObjectPtr<class ACharacter> GetCharacterOwner() { return CharacterOwner; }
    void SetCharacterOwner(TObjectPtr<class ACharacter> InOwner) { CharacterOwner = InOwner; }

    UFUNCTION(BlueprintPure, Category = "Actions")
    FGameplayTag GetActionTag() const { return ActionTag ; }

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Actions")
    TObjectPtr<class UActionsSystemComponent> ActionSystemCom;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Actions")
    FActionConfig ActionConfig;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Actions")
    bool bBindMontageEvent = true; // true is Montage Animation event Bind

    UPROPERTY(BlueprintReadOnly, Category = "Actions")
    TObjectPtr<class ACharacter> CharacterOwner;

    UPROPERTY(BlueprintReadOnly, Category = "Actions")
    TObjectPtr<class UAnimMontage> animMontage;

    UPROPERTY(BlueprintReadWrite, Category = "Actions")
    FActionMontageInfo MontageInfo;

    UPROPERTY(BlueprintReadOnly, Category = "Actions")
    FGameplayTag ActionTag;

    bool bIsExecutingAction = false;

    bool bTerminated = false;

    float AnimRate = 1.0f;
    float StartFrame = 0.0f;

    float ElapsedTime = 0.0f;
    float DeltaTimeInterval = 0.2f;
};
