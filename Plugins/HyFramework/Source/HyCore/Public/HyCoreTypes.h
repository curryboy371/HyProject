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

 // HyFramework Module Category Enum
UENUM(BlueprintType)
enum class ELogPrintType : uint8
{
    ELOG_Hide UMETA(DisplayName = "Hide All Log Categorys"),
    ELOG_Select UMETA(DisplayName = "Print Select Log Categorys"),
    ELOG_Output_ALL UMETA(DisplayName = "Print All Log Categorys")
};

// HyFramework Module Category Enum
UENUM(BlueprintType)
enum class EHyModule : uint8
{
    EHyModule_HyFramework UMETA(DisplayName = "HyFramework"),
    EHyModule_HyCore UMETA(DisplayName = "HyCore"),
    EHyModule_ActionsSystem UMETA(DisplayName = "ActionsSystem"),
    EHyModule_AIControlSystem UMETA(DisplayName = "AIControlSystem"),
    EHyModule_CharacterControlSystem UMETA(DisplayName = "CharacterControlSystem"),
    EHyModule_CollisionSystem UMETA(DisplayName = "CollisionSystem"),
    EHyModule_InventorySystem UMETA(DisplayName = "InventorySystem"),
    EHyModule_HyFXSystem UMETA(DisplayName = "HyFXSystem")
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

class EHyModuleHelper
{
public:
    static const bool FromString(const FString& String, EHyModule& OutHyModuleValue)
    {
        if (String == "HyFramework")
        {
            OutHyModuleValue = EHyModule::EHyModule_HyFramework;
            return true;
        }
        if (String == "HyCore")
        {
            OutHyModuleValue = EHyModule::EHyModule_HyCore;
            return true;
        }
        if (String == "ActionsSystem")
        {
            OutHyModuleValue = EHyModule::EHyModule_ActionsSystem;
            return true;

        }

        if (String == "AIControlSystem")
        {
            OutHyModuleValue = EHyModule::EHyModule_AIControlSystem;
            return true;
        }

        if (String == "CharacterControlSystem")
        {
            OutHyModuleValue = EHyModule::EHyModule_CharacterControlSystem;
            return true;
        }
        if (String == "CollisionSystem")
        {
            OutHyModuleValue = EHyModule::EHyModule_CollisionSystem;
            return true;
        }
        if (String == "InventorySystem")
        {
            OutHyModuleValue = EHyModule::EHyModule_InventorySystem;
            return true;
        }
        if (String == "HyFXSystem")
        {
            OutHyModuleValue = EHyModule::EHyModule_HyFXSystem;
            return true;
        }

        return false;
    }

    static FString ToString(EHyModule InEnumValue)
    {
        switch (InEnumValue)
        {
        case EHyModule::EHyModule_HyFramework:
            return "HyFramework";
        case EHyModule::EHyModule_HyCore:
            return "HyCore";
        case EHyModule::EHyModule_ActionsSystem:
            return "ActionsSystem";
        case EHyModule::EHyModule_AIControlSystem:
            return "AIControlSystem";
        case EHyModule::EHyModule_CharacterControlSystem:
            return "CharacterControlSystem";
        case EHyModule::EHyModule_CollisionSystem:
            return "CollisionSystem";
        case EHyModule::EHyModule_InventorySystem:
            return "InventorySystem";
        case EHyModule::EHyModule_HyFXSystem:
            return "HyFXSystem";
        default:
            return "None";
        }
    }
};


#pragma endregion

UCLASS()
class HYCORE_API UHyCoreTypes : public UObject
{
	GENERATED_BODY()
	
	
	
	
};
