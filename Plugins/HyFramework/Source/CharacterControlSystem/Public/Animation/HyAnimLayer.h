// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "HyAnimLayer.generated.h"

/**
 * 
 */
UCLASS()
class CHARACTERCONTROLSYSTEM_API UHyAnimLayer : public UAnimInstance
{
	GENERATED_BODY()
public:
    /*레이어가 활성화되면 호출되는 함수*/
    UFUNCTION(BlueprintNativeEvent, Category = "Hy | CControl | Layer")
    void OnActivated();
    virtual void OnActivated_Implementation() {};
	
	
};
