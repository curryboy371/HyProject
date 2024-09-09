// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "HyCoreTypes.h"
#include "HyFXTypes.h"

#include "GameplayTagContainer.h"

#include "ActionsTypes.generated.h"

/**
 * 
 */


#pragma region ActionsEnum

 // Action 종료 타입
UENUM(BlueprintType)
enum class EActionHandleType : uint8
{
	// StoreAction 실행 > 진행중이던 Action 종료
    EActionHandle_Free UMETA(DisplayName = "EActionHandle_Free"),

	// 진행중이던 Action 즉시 Stop Exit > StoreAction 실행
    EActionHandle_Stop UMETA(DisplayName = "EActionHandle_Stop"),

	// 각 Action의 조건 실행, 조건이 참이면 Stop ( 조건반환을 항상 false로 하고 조건함수 안에서 Handle하기도 함 )
    EActionHandle_ConditionalStop UMETA(DisplayName = "EActionHandle_ConditionalStop"),

    // 진행중인 액션에 Noti를 넣어주는 기능
    EActionHandle_Noti UMETA(DisplayName = "EActionHandle_Noti"),

    // 진행중인 액션에 FX를 실행하는 기능
    EActionHandle_FX UMETA(DisplayName = "EActionHandle_SpawnFX"),
};


// Action 우선순위
UENUM(BlueprintType)
enum class EActionPriority : uint8 
{
	EEmpty UMETA(DisplayName = "None Priority"),
	ENone UMETA(DisplayName = "Very Low"),
	ELow UMETA(DisplayName = "Low"),
	EMedium UMETA(DisplayName = "Medium"),
	EHigh UMETA(DisplayName = "High"),
	EHighest UMETA(DisplayName = "Highest"),
};

// Action 타입 종류
UENUM(BlueprintType)
enum class EActionType : uint8
{
    EActionType_Normal UMETA(DisplayName = "EActionType_Normal"),
    EActionType_Doing UMETA(DisplayName = "EActionType_Doing"),
    EActionType_Damaged UMETA(DisplayName = "EActionType_Damaged"),
    EActionType_Attack UMETA(DisplayName = "EActionType_Attack"),
    EActionType_Skill UMETA(DisplayName = "EActionType_Skill"),
};




// Action 변경시 블렌드를 설정하기 위한 타입
UENUM(BlueprintType)
enum class EMontageBlendType : uint8 
{
	// 블랜드 사용 안함
	EMontageBlend_None UMETA(DisplayName = "EMontageBlend_None"),

	// 시작시에만 블렌드 사용
	EMontageBlend_Start UMETA(DisplayName = "EMontageBlend_Start"),

	// 끝났을시에만 블렌드 사용
	EMontageBlend_End UMETA(DisplayName = "EMontageBlend_End"),

	// 시작, 종료 모두 블렌드
	EMontageBlend_Both UMETA(DisplayName = "EMontageBlend_Both"),
};

#pragma endregion



#pragma region ActionsStruct

USTRUCT(BlueprintType)
struct FActionConfig 
{
    GENERATED_BODY()

public:
    FActionConfig()
    {
        bPlayEffectOnActionStart = false;
        bAutoExecute = true;

        MontageBlend = EMontageBlendType::EMontageBlend_Both;

        SkillRange = 0.0f;
    }

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | Actions")
    bool bPlayEffectOnActionStart;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | Actions")
    FActionFX ActionFX;

    // if true action montage play, false not play
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | Actions")
    bool bAutoExecute;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | Actions")
    EMontageBlendType MontageBlend;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | Actions")
    float SkillRange;
};



USTRUCT(BlueprintType)
struct FActionState : public FTagBase 
{
    GENERATED_BODY()

    FActionState()
    {
        ActionMontage = nullptr;
        Action = nullptr;
    };


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | Actions")
    TObjectPtr<class UAnimMontage> ActionMontage;

    /* Instanced 프로퍼티
    1.	객체 소유권 관리: 
        Instanced 특성을 사용하면 소유자 객체가 파괴될 때 해당 객체의 인스턴스도 함께 파괴됩니다. 
        이를 통해 메모리 누수를 방지하고 객체의 수명을 명확하게 관리할 수 있습니다.
    2.	블루프린트 편집기에서의 편의성: 
        Instanced 특성을 사용하면 블루프린트 편집기에서 해당 객체의 인스턴스를 직접 편집할 수 있습니다. 
        이를 통해 개발자는 블루프린트 에디터 내에서 객체의 속성을 쉽게 설정하고 조정할 수 있습니다.
    3.	객체의 독립성 보장: 
        Instanced 특성을 사용하면 객체의 인스턴스가 다른 객체와 독립적으로 존재하지 않도록 보장할 수 있습니다. 
        이는 객체가 특정 소유자 객체와 강하게 결합되어야 할 때 유용합니다.
    */

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Hy | Actions")
    TObjectPtr<class UActionsBaseAction> Action;
};

USTRUCT(BlueprintType)
struct FActionsSet : public FTagBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hy | Actions")
    TSubclassOf<class UActionsDataAsset> ActionsSet;
};


USTRUCT(BlueprintType)
struct FActionMontageInfo 
{
    GENERATED_USTRUCT_BODY()
public:
    FActionMontageInfo()
    {
        ActionMontage = nullptr;
        StartSectionName = NAME_None;
        ReproductionSpeed = 1.f;
        MontageBlend = EMontageBlendType::EMontageBlend_Both;
    }

    FActionMontageInfo(class UAnimMontage* InAnimMontage)
    {
        ActionMontage = InAnimMontage;
        StartSectionName = NAME_None;
        ReproductionSpeed = 1.f;
        MontageBlend = EMontageBlendType::EMontageBlend_Both;
    }

    UPROPERTY(BlueprintReadWrite, Category = "Hy | Actions")
    TObjectPtr<class UAnimMontage> ActionMontage;

    UPROPERTY(BlueprintReadWrite, Category = "Hy | Actions")
    EMontageBlendType MontageBlend;

    UPROPERTY(BlueprintReadWrite, Category = "Hy | Actions")
    float ReproductionSpeed;

    UPROPERTY(BlueprintReadWrite, Category = "Hy | Actions")
    FName StartSectionName;

};


USTRUCT(BlueprintType)
struct FActionExcuteData : public FTagBase
{
    GENERATED_BODY()

    FActionExcuteData()
    {
        ActionPriority = EActionPriority::EEmpty;
        ActionContext = FString();
    }

    FActionExcuteData(const FGameplayTag& InGameplayTag, const EActionPriority InPriority = EActionPriority::ENone, const FString& InActionContext = "")
        :FTagBase(InGameplayTag), ActionPriority(InPriority), ActionContext(InActionContext)
    {

    }

    void ResetData(const bool bIncludeTag = true)
    {
        if (bIncludeTag)
        {
            TagName = FGameplayTag::EmptyTag;
        }

        ActionPriority = EActionPriority::EEmpty;
        ActionContext = FString();
    }

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hy | Actions")
    EActionPriority ActionPriority;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hy | Actions")
    FString ActionContext;
};

#pragma endregion

UCLASS()
class ACTIONSSYSTEM_API UActionsTypes : public UObject
{
	GENERATED_BODY()
	
	
	
	
};
