// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/HyManagerBase.h"
#include "HyCheatManager.generated.h"

/**
 * exec 콘솔 명령(주로 치트)을 모아두는 manager class
 * 
 * 
 */
UCLASS()
class HYFRAMEWORK_API UHyCheatManager : public UHyManagerBase
{
	GENERATED_BODY()
	
public:
	virtual void InitManager();
	virtual void ReleaseManager();
};
