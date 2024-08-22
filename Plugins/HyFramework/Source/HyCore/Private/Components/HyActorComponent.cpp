#include "Components/HyActorComponent.h"

#include "GameFramework/Character.h"

// Sets default values for this component's properties
UHyActorComponent::UHyActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHyActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHyActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHyActorComponent::InitializeHyActorComponent()
{
	if (GetOwner() == nullptr)
	{
		return;
	}

	CharacterOwner = Cast<ACharacter>(GetOwner());
}

