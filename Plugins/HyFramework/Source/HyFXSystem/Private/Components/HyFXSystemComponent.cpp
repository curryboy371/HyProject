// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HyFXSystemComponent.h"

UHyFXSystemComponent::UHyFXSystemComponent()
{
}

void UHyFXSystemComponent::InitializeHyActorComponent()
{
	Super::InitializeHyActorComponent();

}

void UHyFXSystemComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UHyFXSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
