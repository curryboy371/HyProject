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
		CameraBoomComp->TargetArmLength = 400.0f;
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
	// Input에 필요한 데이터를 세팅하고, InputContext를 PC에 맵핑함

	// TODO Gameinstance에서 뺄 수도 있음.
	// 나중에는 GameFramework에서 Input을 관리하도록 할 수도
	// Input은 프레임워크가 아닌 게임 모듈에서 자유롭게 사용하라고 ( EKeyInput Enum도 종속성을 풀어줘야함)

	if (UHyGameInstance* GameInst = GetWorld()->GetGameInstance<UHyGameInstance>())
	{
		FInputDataSet InputDataSet;
		if (GameInst->GetInputDataSet(CharacterInitTagSet.InputTag, InputDataSet))
		{
			if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
			{
				// Input Function Ptr을 먼저 맵핑
				InputFunctionMapping();

				// InputContext Setting
				InputContentSetup(InputDataSet.InputContext, PlayerController);

				// InputAction Data Setting
				InputActionDataSetup(&InputDataSet);
			}
			else
			{
				ERR_V("No PlayerController");
			}

		}
		else
		{
			ERR_V("No InputDataSet %s", *CharacterInitTagSet.InputTag.ToString());
		}
	}
	else
	{
		ERR_V("No GameInstance");
	}
}

void AHyMyPlayerBase::InputFunctionMapping()
{
	// Input 함수 이름과 함수 포인터 맵핑
	// Input 함수를 함수 이름으로 동적 바인딩 하지만, 실제로 실행시는 정적 바인딩처럼 함수 포인터로 호출하기 위함.

	InputFunctionMap.Add("InputAttack", &AHyMyPlayerBase::InputAttack);
	InputFunctionMap.Add("InputMove", &AHyMyPlayerBase::InputMove);
	InputFunctionMap.Add("InputJump", &AHyMyPlayerBase::InputJump);
	InputFunctionMap.Add("InputLook", &AHyMyPlayerBase::InputLook);
	InputFunctionMap.Add("InputEquip", &AHyMyPlayerBase::InputEquip);
}

void AHyMyPlayerBase::InputActionDataSetup(FInputDataSet* InInputDataSet)
{
	if (!InInputDataSet)
	{
		ERR_V("InInputDataSet is invaild");
		return;
	}

	// InputAction
	for (const FInputActionData& InputActionData : InInputDataSet->InputDatas)
	{
		if (InputActionData.InputAction)
		{
			if (UClass* CharacterClass = GetClass())
			{
				// Function이 존재하는지 체크
				UFunction* Function = CharacterClass->FindFunctionByName(InputActionData.ActionMethodName);
				if (Function)
				{
					// 함수 포인터 유무 확인.
					if (void (AHyMyPlayerBase:: * Func)(const FInputActionValue&) = InputFunctionMap.FindRef(InputActionData.ActionMethodName))
					{
						InputDatas.Add(InputActionData);
					}
					else
					{
						ERR_V("FunctionPtr is invaild %s", *InputActionData.ActionMethodName.ToString());
					}

				}
				else
				{
					ERR_V("Method %s not found in CharacterClass %s", *InputActionData.ActionMethodName.ToString(), *CharacterClass->GetName());
				}
			}
		}
		else
		{
			ERR_V("No InputAction");
		}
	}
}

void AHyMyPlayerBase::BeginPlay()
{
	Super::BeginPlay();

}

void AHyMyPlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	InputSetup();

	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		InputActionMapping(EnhancedInputComponent);
	}
}

void AHyMyPlayerBase::InputActionMapping(UEnhancedInputComponent* EnhancedInputComponent)
{
	// Input Data가 셋업이 완료된 후 호출됨
	// Input Data에 근거하여 input 함수를 Binding 한다
	// 동적 바인딩을 하나, 함수 이름이 아닌 함수 포인터로 바인딩을 시도함.
	// 따라서 인게임에서 정적 바인딩과 동일한 효과를 기대

	if (!EnhancedInputComponent)
	{
		ERR_V("EnhancedInputComponent is invaild");
		return;
	}

	// InputAction Mapping
	for (const FInputActionData& InputActionData : InputDatas)
	{
		if (InputActionData.InputAction)
		{
			if (UFunction* Function = FindFunction(InputActionData.ActionMethodName))
			{
				// 바인딩시에는 함수 포인터로 바인딩
				if (void (AHyMyPlayerBase:: * Func)(const FInputActionValue&) = InputFunctionMap.FindRef(InputActionData.ActionMethodName))
				{
					EnhancedInputComponent->BindAction(InputActionData.InputAction, InputActionData.TriggerEvent, this, Func);
				}
				else
				{
					ERR_V("FunctionPtr is invaild %s", *InputActionData.ActionMethodName.ToString());
				}
			}
			else
			{
				ERR_V("Method %s not found in CharacterClass %s", *InputActionData.ActionMethodName.ToString(), *GetClass()->GetName());
			}
		}
		else
		{
			ERR_V("No InputAction");
		}
	}
}
