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




#pragma endregion



#pragma region HyCoreStruct

USTRUCT(BlueprintType)
struct FTagBase {

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

#pragma endregion

#pragma region HyCoreClass



#pragma endregion

UCLASS()
class HYCORE_API UHyCoreTypes : public UObject
{
	GENERATED_BODY()
	
	
	
	
};
