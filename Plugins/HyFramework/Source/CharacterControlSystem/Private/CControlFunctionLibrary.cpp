// Fill out your copyright notice in the Description page of Project Settings.


#include "CControlFunctionLibrary.h"

#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"

#include "Animation/HyAnimInstance.h"

#include "HyCoreMacro.h"



UHyAnimInstance* UCControlFunctionLibrary::GetOwningAnimInstance(UObject* Object)
{
    if (!Object)
    {
        ERR_V("Object is nullptr");
        return nullptr;
    }

    ACharacter* OwningCharacter = Cast<ACharacter>(Object);
    if (OwningCharacter)
    {
        if (UAnimInstance* AnimInstance = OwningCharacter->GetMesh()->GetAnimInstance())
        {
            UHyAnimInstance* OwningAnimInstance = Cast<UHyAnimInstance>(AnimInstance);
            if (OwningAnimInstance)
            {
                return OwningAnimInstance;
            }
            else
            {
                ERR_V("OwningAnimInstance is nullptr");
            }
        }
        else 
        {
			ERR_V("AnimInstance is nullptr");
        }
    }
    else
    {
		ERR_V("OwningCharacter is nullptr");
    }

	return nullptr;
}

EHyDirection UCControlFunctionLibrary::GetDirectionFromAngle(const float InAngle)
{
    if (InAngle >= -45 && InAngle <= 45)
    {
        return EHyDirection::Front;
    }
    else if (InAngle >= 135 || InAngle <= -135)
    {
        return EHyDirection::Back;
    }
    else if (InAngle >= 45 && InAngle <= 135) 
    {
        return EHyDirection::Right;
    }
    else if (InAngle >= -135 && InAngle <= -45) 
    {
        return EHyDirection::Left;
    }

    return EHyDirection::Front;
}

EHyDirection UCControlFunctionLibrary::GetOppositeDirectionFromAngle(float InAngle)
{
    const EHyDirection Dir = GetDirectionFromAngle(InAngle);
    return GetOppositeDirection(Dir);
}

EHyDirection UCControlFunctionLibrary::GetOppositeDirection(EHyDirection InDirection)
{
    switch (InDirection) 
    {
    case EHyDirection::Front:
        return EHyDirection::Back;
    case EHyDirection::Back:
        return EHyDirection::Front;
    case EHyDirection::Left:
        return EHyDirection::Right;
    case EHyDirection::Right:
        return EHyDirection::Left;
    }

    return EHyDirection::Front;
}

FString UCControlFunctionLibrary::LocomotionStateToString(ELocomotionState InLocomotionState)
{
    switch (InLocomotionState)
    {
    case ELocomotionState::EIdle:
        return TEXT("Idle");
    case ELocomotionState::EWalk:
        return TEXT("Walk");
    case ELocomotionState::EJog:
        return TEXT("Jog");
    case ELocomotionState::ESprint:
        return TEXT("Sprint");
    default:
        return TEXT("Unknown");
    }
}
