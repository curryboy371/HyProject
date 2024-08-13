// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HyCoreTypes.h"
#include "InputTriggers.h"

#include "UObject/NoExportTypes.h"
#include "CControlTypes.generated.h"

/**
 * 
 */



#pragma region CControlEnum


UENUM(BlueprintType)
enum class EKeyInput : uint8
{
    IA_None = 0,
	IA_Attack,
    IA_Equip,
	IA_Skill1,
	IA_Jump,
	IA_Move,
	IA_Look,
};

#pragma endregion


#pragma region CControlStruct

// Layer Structs

USTRUCT(BlueprintType)
struct FHyAnimEquipLayerSet : public FTagBase
{
    GENERATED_BODY()

public:
    FHyAnimEquipLayerSet() {}

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CControl | Layer")
    TSubclassOf<class UHyAnimEquipLayer> EquipLayer;
};

// Input Structs



USTRUCT(BlueprintType)
struct FInputActionData
{
    GENERATED_BODY()

public:
    FInputActionData()
        : 
          InputKey(EKeyInput::IA_None)
        , InputAction(nullptr)
        , TriggerEvent(ETriggerEvent::Triggered)
        , ActionMethodName(NAME_None)
    {
    }

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Action")
    EKeyInput InputKey;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Action")
    class UInputAction* InputAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Action")
    ETriggerEvent TriggerEvent;

    // Method name to call
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Action")
    FName ActionMethodName;  
};

USTRUCT(BlueprintType)
struct FInputDataSet : public FTagBase
{
    GENERATED_BODY()

public:
    FInputDataSet() 
    {
        InputContext = nullptr;
    }

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CControl | Input")
    class UInputMappingContext* InputContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CControl | Input")
    TArray<FInputActionData> InputDatas;
};


USTRUCT(BlueprintType)
struct FCControlUpdates
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CControl | Updates")
    bool bUpdateMovementData = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CControl | Updates")
    bool bUpdateLocationData = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CControl | Updates")
    bool bUpdateRotationData = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CControl | Updates")
    bool bUpdateSpeedData = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CControl | Updates")
    bool bUpdateAccelerationData = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CControl | Updates")
    bool bUpdateAimData = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CControl | Updates")
    bool bUpdateJumpData = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CControl | Updates")
    bool bUpdateLeaningData = true;
};


#pragma endregion
