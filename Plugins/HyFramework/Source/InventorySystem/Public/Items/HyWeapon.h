// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/HyEquippableItem.h"
#include "HyWeapon.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API AHyWeapon : public AHyEquippableItem
{
	GENERATED_BODY()
	
public:







public:
    UFUNCTION(BlueprintPure, Category = Hy)
    FORCEINLINE FName GetBodySocketName() const { return BodySocketName; }

    UFUNCTION(BlueprintPure, Category = Hy)
    FORCEINLINE FName GetHandSocketName() const { return HandsSocketName; }


protected:
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Hy | Weapon")
    FName BodySocketName;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Hy | Weapon")
    FName HandsSocketName;
};
