// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "HyCoreTypes.h"
#include "HyFXTypes.h"

#include "ActionsTypes.generated.h"

/**
 * 
 */


 // Action 종료 타입
UENUM(BlueprintType)
enum class EActionHandleExitType : uint8
{
	// StoreAction 실행 > 진행중이던 Action 종료
	EActionExit_Free UMETA(DisplayName = "EActionExit_Free"), 

	// 진행중이던 Action 즉시 Stop Exit > StoreAction 실행
	EActionExit_Stop UMETA(DisplayName = "EActionExit_Stop"), 

	// 각 Action의 조건 실행, 조건이 참이면 Stop ( 조건반환을 항상 false로 하고 조건함수 안에서 Handle하기도 함 )
	EActionExit_Conditional UMETA(DisplayName = "EActionExit_Conditional"),
};


// Action 우선순위
UENUM(BlueprintType)
enum class EActionPriority : uint8 
{
	ENone UMETA(DisplayName = "Very Low"),
	ELow UMETA(DisplayName = "Low"),
	EMedium UMETA(DisplayName = "Medium"),
	EHigh UMETA(DisplayName = "High"),
	EHighest UMETA(DisplayName = "Highest"),
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
        //MontageReproductionType = EMontageReproductionType::ERootMotion;
    }

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | Actions")
    bool bPlayEffectOnActionStart;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | Actions")
    FActionFX ActionFX;

    // if true action montage play, false not play
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | Actions")
    bool bAutoExecute;

    //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | Actions")
    //EMontageReproductionType MontageReproductionType;

    //UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "MontageReproductionType == EMontageReproductionType::ERootMotionScaled"), Category = "Hy | Actions")
    //float RootMotionScale = 1.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | Actions")
    EMontageBlendType MontageBlend;

    //UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "MontageReproductionType == EMontageReproductionType::EMotionWarped"), "Hy | Actions")
    //FNPWarpInfo WarpInfo;

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
        MontageBlend = EMontageBlendType::EMontageBlend_Both;
    }

    FActionMontageInfo(class UAnimMontage* InAnimMontage)
    {
        ActionMontage = InAnimMontage;
        StartSectionName = NAME_None;
        MontageBlend = EMontageBlendType::EMontageBlend_Both;
    }

    UPROPERTY(BlueprintReadWrite, Category = "Hy | Actions")
    TObjectPtr<class UAnimMontage> ActionMontage;

    UPROPERTY(BlueprintReadWrite, Category = "Hy | Actions")
    EMontageBlendType MontageBlend;

    //UPROPERTY(BlueprintReadWrite, Category = "Hy | Actions")
    //float ReproductionSpeed;

    UPROPERTY(BlueprintReadWrite, Category = "Hy | Actions")
    FName StartSectionName;

    //UPROPERTY(BlueprintReadWrite, Category = "Hy | Actions")
    //EMontageReproductionType ReproductionType;

    //UPROPERTY(BlueprintReadWrite, meta = (EditCondition = "MontageReproductionType == EMontageReproductionType::ERootMotionScaled"), Category = "Hy | Actions")
    //float RootMotionScale;
    //
    //UPROPERTY(BlueprintReadWrite, meta = (EditCondition = "MontageReproductionType == EMontageReproductionType::EMotionWarped"), Category = "Hy | Actions")
    //FNPWarpReproductionInfo WarpInfo;
};



UCLASS()
class ACTIONSSYSTEM_API UActionsTypes : public UObject
{
	GENERATED_BODY()
	
	
	
	
};
