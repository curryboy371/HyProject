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
