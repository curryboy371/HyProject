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

    UFUNCTION(BlueprintCallable, Category = "CControl", meta = (BlueprintThreadSafe))
    void ResetHyAniminstace();

    UFUNCTION(BlueprintCallable, Category = "CControl", meta = (BlueprintThreadSafe))
    void SetHyAnimInstance();

    UFUNCTION(BlueprintCallable, Category = "CControl", meta = (BlueprintThreadSafe))
    class UHyAnimInstance* GetHyAnimInstance();

public:

    /*레이어가 활성화되면 호출되는 함수*/
    UFUNCTION(BlueprintNativeEvent, Category = "Hy | CControl | Layer")
    void OnActivated();
    virtual void OnActivated_Implementation();

    /*레이어가 해제 호출되는 함수*/
    UFUNCTION(BlueprintNativeEvent, Category = "Hy | CControl | Layer")
    void OnDeactivated();
    virtual void OnDeactivated_Implementation();
	
protected:
    UPROPERTY(BlueprintReadOnly, Category = "Hy | CControl | Layer", meta = (BlueprintThreadSafe))
    class UHyAnimInstance* ReturnValue;

};
