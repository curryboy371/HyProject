// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/HyActionComboBase.h"
#include "HyAction_ComboAttack.generated.h"

/**
 * 
 */
UCLASS()
class HYFRAMEWORK_API UHyAction_ComboAttack : public UHyActionComboBase
{
	GENERATED_BODY()
public:

	virtual bool IsStopConditional_Implementation();

};
