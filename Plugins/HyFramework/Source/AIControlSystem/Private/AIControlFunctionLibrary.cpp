// Fill out your copyright notice in the Description page of Project Settings.


#include "AIControlFunctionLibrary.h"

#include "Actors/Character/HyCharacterBase.h"


float UAIControlFunctionLibrary::CalcDistanceBetweenCharacter(const ACharacter* characterA, const ACharacter* characterB)
{
    // 바운드 볼륨 거리를 제외한 Character간 거리 계산
    if (characterA && characterB) 
    {
        const FBox aBox = characterA->GetMesh()->Bounds.GetBox();
        const FBox bBox = characterB->GetMesh()->Bounds.GetBox();

        const float dist = characterA->GetDistanceTo(characterB);
        return dist - aBox.GetExtent().X - bBox.GetExtent().X;
    }
    return -1.0f;
}
