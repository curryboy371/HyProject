// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HyCharacterCombatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHyCharacterCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HYCORE_API IHyCharacterCombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual const bool IsTargetInRange(const float InRange) { return false; };
	virtual bool FindTarget() { return false; };

};
