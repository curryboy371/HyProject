// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Character/HyMyPlayerBase.h"

//Input
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

//Camera
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/PostProcessComponent.h"

#include "Game/HyGameInstance.h"
#include "Game/HyPlayerController.h"


#include "HyCoreLogging.h"

AHyMyPlayerBase::AHyMyPlayerBase()
{

	CharacterDefaultSetup();
	ComponenetSetup();
}

void AHyMyPlayerBase::CharacterDefaultSetup()
{

	CameraBoomComp = nullptr;
	FollowCameraComp = nullptr;
}

void AHyMyPlayerBase::ComponenetSetup()
{
	CameraBoomComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoomCom"));
	if (CameraBoomComp)
	{
		CameraBoomComp->SetupAttachment(RootComponent);
		CameraBoomComp->TargetArmLength = 800.0f;
		CameraBoomComp->bUsePawnControlRotation = true;
	}

	FollowCameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCameraCom"));
	if (FollowCameraComp)
	{
		FollowCameraComp->SetupAttachment(CameraBoomComp, USpringArmComponent::SocketName);
		FollowCameraComp->bUsePawnControlRotation = false;
	}

}

void AHyMyPlayerBase::InputSetup()
{
	// TODO Gameinstance에서 뺄 수도 있음.
	// 나중에는 GameFramework에서 Input을 관리하도록 할 수도 있고 ( Input은 자유롭게 사용하라고 )
	// InputMode 관련 Tag는 추가되면 넣어줘야함

	if (UHyGameInstance* GameInst = GetWorld()->GetGameInstance<UHyGameInstance>())
	{
		// InputContext
		if (UInputMappingContext * InputContext = GameInst->GetInputDataSet().InputContext)
		{
			if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
			{
				if (UEnhancedInputLocalPlayerSubsystem* SubSystem =
					ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
					SubSystem->AddMappingContext(InputContext, 0);

			}
			else
			{
				ERR_V("No PlayerController");
			}



		}
		else
		{
			ERR_V("No InputContext");
		}

		// InputAction
		for (const auto& InputActionEntry : GameInst->GetInputDataSet().InputDataMap)
		{
			const FInputActionData& ActionData = InputActionEntry.Value;

			if (ActionData.InputAction && ActionData.CharacterClass)
			{
				if (ActionData.CharacterClass->IsChildOf(ACharacter::StaticClass()))
				{
					if (UClass* CharacterClass = ActionData.CharacterClass->GetClass())
					{
						// Function이 존재하는지 체크
						UFunction* Function = CharacterClass->FindFunctionByName(ActionData.ActionMethodName);
						if (Function)
						{
							InputDataMap.Add(InputActionEntry.Key, ActionData);
						}
						else
						{
							ERR_V("Method %s not found in CharacterClass %s", *ActionData.ActionMethodName.ToString(), *ActionData.CharacterClass->GetName());
						}
					}
				}
				else
				{
					ERR_V("CharacterClass %s is not a subclass of ACharacter", *ActionData.CharacterClass->GetName());
				}
			}
			else
			{
				//ERR_V("No InputAction or CharacterClass for InputActionKey %s", *InputActionEntry.Key.ToString());
			}
		}

	}
	else
	{
		ERR_V("No GameInstance");
	}


}

void AHyMyPlayerBase::BeginPlay()
{
	Super::BeginPlay();

	InputSetup();
}

void AHyMyPlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		for(auto& InputData : InputDataMap)
		{
			if (InputData.Value.InputAction)
			{
				EnhancedInputComponent->BindAction(InputData.Value.InputAction, InputData.Value.TriggerEvent, this, InputData.Value.ActionMethodName);
			}
		}
	}
}
