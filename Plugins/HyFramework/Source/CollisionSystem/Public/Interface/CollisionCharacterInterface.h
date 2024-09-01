// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "CollisionTypes.h"

#include "CollisionCharacterInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCollisionCharacterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class COLLISIONSYSTEM_API ICollisionCharacterInterface
{
	GENERATED_BODY()

public:
	virtual void EnableAttackCollider(const FAttackCollisionSettings& InAttackCollisionSet) {};
	virtual void NotifyAttackCollider(const FAttackCollisionSettings& InAttackCollisionSet) {};
	virtual void DisableAttackCollider() {};


	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
