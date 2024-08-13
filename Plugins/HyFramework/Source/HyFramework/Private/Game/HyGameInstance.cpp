// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/HyGameInstance.h"

#include "HyCoreLogging.h"

void UHyGameInstance::Init()
{
	UGameInstance::Init();
	LOG_V("LogTest");



	LOG_GUARD;

	LOG_GUARD_V("teset");

}

const bool UHyGameInstance::GetInputDataSet(const FGameplayTag& InInputTag, FInputDataSet& OutInputData)
{
	for (const FInputDataSet& InputData : InputDataSet)
	{
		if (InputData.TagName == InInputTag)
		{
			OutInputData = InputData;
			return true;
		}
	}

	ERR_V("Invalid Input Tag %s", *InInputTag.ToString());
	return false;
}
