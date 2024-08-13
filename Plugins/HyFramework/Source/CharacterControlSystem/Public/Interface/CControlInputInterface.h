// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

//#include "CControlTypes.h"

#include "CControlInputInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCControlInputInterface : public UInterface
{
	GENERATED_BODY()
public:

protected:
};

/**
 * 
 */
class CHARACTERCONTROLSYSTEM_API ICControlInputInterface
{
	GENERATED_BODY()

public:
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	virtual void InputSetup() = 0;

	virtual void InputFunctionMapping() = 0;

	virtual void InputActionDataSetup(struct FInputDataSet* InInputDataSet) = 0;

	virtual void InputActionMapping(class UEnhancedInputComponent* EnhancedInputComponent) = 0;


	void InputContentSetup(TObjectPtr<class UInputMappingContext> InInputContext, TObjectPtr<class APlayerController> InPC);

};
