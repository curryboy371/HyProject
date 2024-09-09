// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "GameplayTagContainer.h"



#include "HyCoreTypes.generated.h"

/**
 * 
 */

#pragma region HyCoreEnum

UENUM(BlueprintType)
enum class EHyAttackTrailType : uint8
{
    // Default 공격할 때마다 항상 재생
    AttackDefault = 0,

    // Human 피격시
    AttackHuman,

    // Robot 피격시
    AttackRobot,

    End,
};



UENUM(BlueprintType)
enum class EHyDirection : uint8
{
    Front = 0,
    Back = 1,
    Left = 2,
    Right = 3
};


 // HyFramework Module Category Enum
UENUM(BlueprintType)
enum class ELogPrintType : uint8
{
    ELOG_Hide UMETA(DisplayName = "Hide All Log Categorys"),
    ELOG_Select UMETA(DisplayName = "Print Select Log Categorys"),
    ELOG_Output_ALL UMETA(DisplayName = "Print All Log Categorys")
};


UENUM(BlueprintType)
enum class ECameraShakeType : uint8
{
    ECS_Wave UMETA(DisplayName = "CS Wave"),
    ECS_PerlinNoise UMETA(DisplayName = "CS Perlin Noise"),
    ECS_Vertical UMETA(DisplayName = "CS Vertical"),
    ECS_Horizontal UMETA(DisplayName = "CS Horizontal"),
    ECS_DiagonalDownRL UMETA(DisplayName = "CS DiagonalDownRL"),
    ECS_DiagonalDownLR UMETA(DisplayName = "CS DiagonalDownLR"),
    ECS_Ulti UMETA(DisplayName = "CS Ulti"),
    ECS_VerticalVib UMETA(DisplayName = "ECS_VerticalVib"),
    ECS_HorizontalVib UMETA(DisplayName = "ECS_HorizontalVib"),
    ECS_None UMETA(DisplayName = "None"),
};



#pragma endregion



#pragma region HyCoreStruct

USTRUCT(BlueprintType)
struct FTagBase 
{

    GENERATED_BODY()

public:
    FTagBase()
    {
        TagName = FGameplayTag::EmptyTag;
    }

    FTagBase(const FGameplayTag& InTagName)
        :TagName(InTagName)
    {
    }

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | HyCore")
    FGameplayTag TagName;

    FORCEINLINE bool operator!=(const FGameplayTag& Other) const
    {
        return TagName != Other;
    }

    FORCEINLINE bool operator==(const FGameplayTag& Other) const
    {
        return TagName == Other;
    }

    FORCEINLINE bool operator!=(const FTagBase& Other) const
    {
        return TagName != Other.TagName;
    }

    FORCEINLINE bool operator==(const FTagBase& Other) const
    {
        return TagName == Other.TagName;
    }

};

// Struct for Camera Shake Settings
USTRUCT(BlueprintType)
struct FCameraShakeSettings
{
    GENERATED_BODY()

public:
    FCameraShakeSettings()
        : CameraShake(nullptr)
        , CameraShakeScale(1.f)
        , CameraShakeRadius(500.f)
        //, CameraShakePlaySpace(ECameraShakePlaySpace::CameraLocal)
    {}

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Shake")
    TSubclassOf<class UCameraShakeBase> CameraShake;

    // The scale of the camera shake effect
    UPROPERTY(EditAnywhere, Category = "Camera Shake")
    float CameraShakeScale;

    // 카메라 흔들림 범위
    UPROPERTY(EditAnywhere, Category = "Camera Shake")
    float CameraShakeRadius;

    //// The play space for the camera shake
    //UPROPERTY(EditAnywhere, Category = "Camera Shake")
    //ECameraShakePlaySpace CameraShakePlaySpace;
};

USTRUCT(BlueprintType)
struct FCharacterCombatDataSet
{
    GENERATED_BODY()

public:
    FCharacterCombatDataSet()
    {
        AirHitLocation = FVector::ZeroVector;
    }

    UPROPERTY(BlueprintReadOnly, Category = "Combat")
    FVector AirHitLocation;

};



#pragma endregion

#pragma region HyCoreClass



#pragma endregion

UCLASS()
class HYCORE_API UHyCoreTypes : public UObject
{
	GENERATED_BODY()
	
	
	
	
};
