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
        : CameraShakeType(ECameraShakeType::ECS_None)
        , CameraShakeScale(1.f)
        , CameraShakePlaySpace(ECameraShakePlaySpace::CameraLocal)
    {}

    // The type of camera shake to apply
    UPROPERTY(EditAnywhere, Category = "Camera Shake")
    ECameraShakeType CameraShakeType;

    // The scale of the camera shake effect
    UPROPERTY(EditAnywhere, Category = "Camera Shake")
    float CameraShakeScale;

    // The play space for the camera shake
    UPROPERTY(EditAnywhere, Category = "Camera Shake")
    ECameraShakePlaySpace CameraShakePlaySpace;
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
