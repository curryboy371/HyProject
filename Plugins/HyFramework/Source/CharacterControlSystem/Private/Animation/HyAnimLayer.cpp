// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/HyAnimLayer.h"

#include "Animation/HyAnimInstance.h"

#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"

#include "CControlFunctionLibrary.h"
#include "HyCoreMacro.h"


void UHyAnimLayer::ResetHyAniminstace()
{
    ReturnValue = nullptr;
}   

void UHyAnimLayer::SetHyAnimInstance()
{
    ReturnValue = UCControlFunctionLibrary::GetOwningAnimInstance(TryGetPawnOwner());
}

UHyAnimInstance* UHyAnimLayer::GetHyAnimInstance()
{
    if (!ReturnValue)
    {
        SetHyAnimInstance();
    }

    return ReturnValue;
}

//UHyAnimInstance* UHyAnimLayer::GetOwningAnimInstance()
//{
//    if (!HyAnimInstance)
//    {
//        SetHyAnimInstance();
//    }
//
//    return HyAnimInstance;
//}

void UHyAnimLayer::OnActivated_Implementation()
{
    SetHyAnimInstance();
}

void UHyAnimLayer::OnDeactivated_Implementation()
{
    ResetHyAniminstace();
}
