// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Character/HyMyPlayerBase.h"

#include "Game/HyPlayerController.h"

#include "Manager/HySpawnManager.h"

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

#include "Components/HyCharacterMovementComponent.h"

#include "CControlTypes.h"
#include "HyTypes.h"

#include "HyTableSubsystem.h"

#include "Table/PlayerPPM_TableEntity.h"

#include "HyCoreMacro.h"

AHyMyPlayerBase::AHyMyPlayerBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

	CharacterDefaultSetup();
	ComponenetSetup();
}

void AHyMyPlayerBase::CharacterDefaultSetup()
{
	bSprintBlurOn = false;

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
		if (GameInst->GetInputDataSet(CharacterDefaultTagSet.InputTag, InputDataSet))
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
			ERR_V("No InputDataSet %s", *CharacterDefaultTagSet.InputTag.ToString());
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
	InputFunctionMap.Add("CompletedMove", &AHyMyPlayerBase::CompletedMove);
	InputFunctionMap.Add("InputJump", &AHyMyPlayerBase::InputJump);
	InputFunctionMap.Add("InputLook", &AHyMyPlayerBase::InputLook);
	InputFunctionMap.Add("InputEquip", &AHyMyPlayerBase::InputEquip);

	InputFunctionMap.Add("InputSprint", &AHyMyPlayerBase::InputSprint);
	InputFunctionMap.Add("CompletedSprint", &AHyMyPlayerBase::CompletedSprint);

	InputFunctionMap.Add("InputCrouch", &AHyMyPlayerBase::InputCrouch);

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
	SetPostProcessVolume();


	Super::BeginPlay();

	LocalPlayerSetup();
}

void AHyMyPlayerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	UpdateBlurWeight();
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

void AHyMyPlayerBase::LocalPlayerSetup()
{
	// 언리얼 프레임워크가 생성하는 default character에 대해 세팅해줌
	AHyPlayerController* PC = Cast<AHyPlayerController>(GetController());
	if (!PC)
	{
		ERR_V("No PlayerController");
		return;
	}

	UHyInst* HyInst = UHyInst::Get();
	if (!HyInst)
	{
		ERR_V("HyInst is not set.");
		return;
	}

	UHySpawnManager* SpawnManager = HyInst->GetManager<UHySpawnManager>();
	if (!SpawnManager)
	{
		ERR_V("SpawnManager is not set.");
		return;
	}


	SpawnCompleted(); // Engine에서 생성하는 Character는 SpawnCompleted를 이곳에서 호출
	SpawnManager->SetLocalPlayer(this);

	SetPPMValue(EPPMType::EPPM_Stencil, 1.0f); // Stencil PPM On
	SetStencilOutline(true, EStencilOutLine::EStencil_MyPlayer);

	EnableInput(PC);

}

void AHyMyPlayerBase::SetPostProcessVolume()
{
	if (!FollowCameraComp)
	{
		ERR_V("FollowCameraComp is invaild");
		return;
	}

	// PPM 초기화
	FPostProcessSettings& PostProcessSettings = FollowCameraComp->PostProcessSettings;
	PostProcessSettings = FPostProcessSettings();
	PPMMaterialMap.Reset();

	// TableData로 PPM 세팅
	if (UHyTableSubsystem* TableSubSystem = GetGameInstance()->GetSubsystem<UHyTableSubsystem>())
	{
		TArray<FPlayerPPM_TableEntity*> PPMTableEntitys;
		if (TableSubSystem->GetTableAll<FPlayerPPM_TableEntity>(PPMTableEntitys))
		{
			for(auto PPMTableEntity : PPMTableEntitys)
			{
				if(!PPMTableEntity)
				{
					ERR_V("PPMTableEntity is invaild");
					continue;
				}

				EPPMType PPMType = static_cast<EPPMType>(PPMTableEntity->PPMID);
				if (PPMMaterialMap.Contains(PPMType))
				{
					ERR_V("PPMType is already exist %d", PPMType);
					continue;
				}
				if (PPMType <= EPPMType::EPPM_None && PPMType >= EPPMType::EPPM_MAX)
				{
					ERR_V("Invalid PPMType %d", PPMType);
					continue;
				}

				UMaterialInterface* Material = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, *PPMTableEntity->PPMPath));
				if (!Material)
				{
					ERR_V("Invalid PostProcess Material %s", *PPMTableEntity->PPMPath);
					continue;
				}

				UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);
				if (!DynamicMaterial)
				{
					ERR_V("Invalid DynamicMaterial %s", *PPMTableEntity->PPMPath);
					continue;
				}

				PostProcessSettings.AddBlendable(DynamicMaterial, 0.0f);
				PPMMaterialMap.Add(PPMType, DynamicMaterial);
			}
		}
	}
	else
	{
		ERR_V("No TableSubsystem");
	}
}

void AHyMyPlayerBase::SetPPMValue(EPPMType InPPMType, float InValue)
{
	if (!FollowCameraComp)
	{
		ERR_V("FollowCameraComp is invaild");
		return;
	}

	FPostProcessSettings& PostProcessSettings = FollowCameraComp->PostProcessSettings;

	int32 PPMIdx = static_cast<int32>(InPPMType) - 1; // None 제외
	if (PostProcessSettings.WeightedBlendables.Array.IsValidIndex(PPMIdx) == false)
	{
		ERR_V("Invalid PPMIdx %d", PPMIdx);
		return;
	}

	switch (InPPMType)
	{
	case EPPMType::EPPM_Stencil:
	case EPPMType::EPPM_Blur:
		PostProcessSettings.WeightedBlendables.Array[PPMIdx].Weight = InValue;
		break;
	case EPPMType::EPPM_SprintBlur:
		PostProcessSettings.WeightedBlendables.Array[PPMIdx].Weight = InValue;
		bSprintBlurOn = InValue > 0.0f;
		break;
	default:
		ERR_V("Invalid PPMType %d", PPMIdx);
		break;
	}
}

void AHyMyPlayerBase::UpdateBlurWeight()
{
	if(!HyCharacterMovement)
	{
		ERR_V("HyCharacterMovement is invaild");
		return;
	}

	if (HyCharacterMovement->GetCurLocomotionState() == ELocomotionState::ESprint)
	{
		float Velocity = HyCharacterMovement->Velocity.Size();
		float MaxVelocity = HyCharacterMovement->GetCharacterMaxStateSpeed(ELocomotionState::ESprint);

		if (MaxVelocity > 0.0f)
		{
			float VelocitRatio = Velocity / MaxVelocity;
			SetPPMValue(EPPMType::EPPM_SprintBlur, VelocitRatio);
		}
	}
	else
	{
		if (bSprintBlurOn)
		{
			SetPPMValue(EPPMType::EPPM_SprintBlur, 0.0f);
		}
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

const bool AHyMyPlayerBase::IsLocalPlayer()
{
	UHyInst* HyInst = UHyInst::Get();
	if (!HyInst)
	{
		ERR_V("HyInst is not set.");
		return false;
	}

	UHySpawnManager* SpawnManager = HyInst->GetManager<UHySpawnManager>();
	if (!SpawnManager)
	{
		ERR_V("SpawnManager is not set.");
		return false;
	}
	TObjectPtr<AHyMyPlayerBase> LocalPlayer = SpawnManager->GetLocalPlayer();

	if (!LocalPlayer)
	{
		ERR_V("LocalPlayer is nullptr");
		return false;
	}

	if (LocalPlayer->GetMyGuidRef() == MyGuid)
	{
		return true;
	}

	return false;
}
