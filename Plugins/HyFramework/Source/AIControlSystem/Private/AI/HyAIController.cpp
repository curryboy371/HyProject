// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/HyAIController.h"

#include "Interface/ActionsCharacterInterface.h"

#include "GameFramework/Character.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

#include <BehaviorTree/Blackboard/BlackboardKeyType_Bool.h>
#include <BehaviorTree/Blackboard/BlackboardKeyType_Enum.h>
#include <BehaviorTree/Blackboard/BlackboardKeyType_Float.h>
#include <BehaviorTree/Blackboard/BlackboardKeyType_Int.h>
#include <BehaviorTree/Blackboard/BlackboardKeyType_Object.h>
#include <BehaviorTree/Blackboard/BlackboardKeyType_Vector.h>

#include <Navigation/CrowdFollowingComponent.h>
#include <Navigation/PathFollowingComponent.h>

#include "HyCoreMacro.h"



AHyAIController::AHyAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{

	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComp"));
}

void AHyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (!InPawn)
	{
		ERR_V("InPawn is nullptr");
		return;
	}

	if (!BehaviorTree)
	{
		ERR_V("BehaviorTree is nullptr");
		return;
	}

	OwnerActionsInterface = Cast<IActionsCharacterInterface>(InPawn);
	if (!OwnerActionsInterface)
	{
		ERR_V("OwnerActionsInterface is nullptr");
		return;
	}

	UBlackboardData* const BBData = BehaviorTree->BlackboardAsset;
	if (BBData == nullptr)
	{
		ERR_V("BlackboardData is nullptr");
		return;
	}

	if (!BlackboardComponent)
	{
		ERR_V("BlackboardComponent is nullptr");
		return;
	}

	BlackboardComponent->InitializeBlackboard(*BBData);
	Blackboard = BlackboardComponent;
	HomeLocation = InPawn->GetActorLocation();

	BlackBoardKeyBindings();

	BehaviorTreeComponent->StartTree(*BehaviorTree);

}

void AHyAIController::OnUnPossess()
{
	Super::OnUnPossess();

}

void AHyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AHyAIController::BlackBoardKeyBindings()
{
	if (!BlackboardComponent)
	{
		ERR_V("BlackboardComponent is nullptr");
		return;
	}


	// Fetch the Keys
	targetActorKey = BlackboardComponent->GetKeyID("TargetActor");
	targetPointLocationKey = BlackboardComponent->GetKeyID("TargetLocation");
	targetActorDistanceKey = BlackboardComponent->GetKeyID("TargetActorDistance");
	targetDistanceKey = BlackboardComponent->GetKeyID("TargetLocationDistance");
	isPausedKey = BlackboardComponent->GetKeyID("Paused");
	homeDistanceKey = BlackboardComponent->GetKeyID("HomeDistance");

	BlackBoardKeyInit();
}

void AHyAIController::BlackBoardKeyInit()
{
	if (!BlackboardComponent)
	{
		ERR_V("BlackboardComponent is nullptr");
		return;
	}

	BlackboardComponent->SetValue<UBlackboardKeyType_Float>(targetDistanceKey, MAX_FLT);
	BlackboardComponent->SetValue<UBlackboardKeyType_Vector>(targetPointLocationKey, HomeLocation);
	BlackboardComponent->SetValue<UBlackboardKeyType_Bool>(isPausedKey, false);

}
