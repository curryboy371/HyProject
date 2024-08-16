// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/CControlInputInterface.h"

#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "GameFramework/PlayerController.h"

#include "HyCoreMacro.h"

// Add default functionality here for any ICControlInputInterface functions that are not pure virtual.


void ICControlInputInterface::InputContentSetup(TObjectPtr<UInputMappingContext> InInputContext, TObjectPtr<APlayerController> InPC)
{
	if (!InInputContext)
	{
		ERR_V("InInputContext is invaild");
		return;
	}

	if (!InPC)
	{
		ERR_V("InPC is invaild");
		return;
	}

	if (UEnhancedInputLocalPlayerSubsystem* SubSystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(InPC->GetLocalPlayer()))
		SubSystem->AddMappingContext(InInputContext, 0);
}
