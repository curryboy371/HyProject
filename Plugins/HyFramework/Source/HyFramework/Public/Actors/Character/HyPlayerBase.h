// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Character/HyCharacterBase.h"
#include "HyTypes.h"


#include "HyPlayerBase.generated.h"

/**
 * 
 */
UCLASS()
class HYFRAMEWORK_API AHyPlayerBase : public AHyCharacterBase
{
	GENERATED_BODY()
	
public:



public:
	virtual bool FindTarget();

};
