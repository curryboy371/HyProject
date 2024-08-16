// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

//#include "CControlTypes.h"

#include "CControlCharacterInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCControlCharacterInterface : public UInterface
{
	GENERATED_BODY()
public:

protected:
};

/**
 * 
 */
class CHARACTERCONTROLSYSTEM_API ICControlCharacterInterface
{
	GENERATED_BODY()

public:
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	virtual const bool IsDead() = 0;
	virtual const bool IsCombatMode() = 0;

	virtual struct FGameplayTag GetEquipTag() = 0;

	virtual void SetCombatMode(const bool bCombatMode) = 0;

};
