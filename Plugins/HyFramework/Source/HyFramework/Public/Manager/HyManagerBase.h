// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HyManagerBase.generated.h"

/**
 * 
 */
UCLASS()
class HYFRAMEWORK_API UHyManagerBase : public UObject
{
	GENERATED_BODY()
public:
	UHyManagerBase()
	{
		ManagerID = NextManagerID;
		NextManagerID++;
	}

	virtual void InitManager() {};
	virtual void ReleaseManager() {};
	
	static void ResetManagerID() { NextManagerID = 0; }

public:
	const uint8 GetManagerID() { return ManagerID; }

protected:
	uint8 ManagerID;

	static uint8 NextManagerID;

};
