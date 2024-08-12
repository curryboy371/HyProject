// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HyCoreTypes.h"
#include "UObject/NoExportTypes.h"
#include "CControlTypes.generated.h"

/**
 * 
 */



#pragma region CControlEnum


UENUM(BlueprintType)
enum class EKeyInput : uint8
{
	IA_Attack = 0,
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

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hy | CControl | Updates")
    TSubclassOf<class UHyAnimEquipLayer> EquipLayer;
};




USTRUCT(BlueprintType)
struct FCControlUpdates
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | CControl | Updates")
    bool bUpdateMovementData = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | CControl | Updates")
    bool bUpdateLocationData = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | CControl | Updates")
    bool bUpdateRotationData = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | CControl | Updates")
    bool bUpdateSpeedData = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | CControl | Updates")
    bool bUpdateAccelerationData = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | CControl | Updates")
    bool bUpdateAimData = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | CControl | Updates")
    bool bUpdateJumpData = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | CControl | Updates")
    bool bUpdateLeaningData = true;
};


#pragma endregion
