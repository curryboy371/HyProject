// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/HyEquippableItem.h"

#include "InvenTypes.h"

#include "HyWeapon.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API AHyWeapon : public AHyEquippableItem
{
	GENERATED_BODY()
	
public:
    AHyWeapon();

    virtual void InitializeItem(const struct FItem_TableEntity* InItemTableInfo);

public:

    UFUNCTION(BlueprintPure, Category = Hy)
    FORCEINLINE FName GetBodySocketName() const { return ItemTableInfo.BodySocketName;}

    UFUNCTION(BlueprintPure, Category = Hy)
    FORCEINLINE FName GetHandSocketName() const { return ItemTableInfo.HandSocketName; }

    UFUNCTION(BlueprintPure, Category = Hy)
    FORCEINLINE FName GetSubHandSocketName() const { return ItemTableInfo.HandSubSocketName; }

    FORCEINLINE class USkeletalMeshComponent* GetMeshComponent() const { return SkeletalMesh; };

    FORCEINLINE class USceneComponent* GetSubHandleComp() const { return SubHandleComp; };



protected:
    UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Hy | Weapon")
    EWeaponMeshType WeaponMeshType = EWeaponMeshType::EWeaponMesh_StaticMesh;

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Hy | Weapon")
    TObjectPtr<class USkeletalMeshComponent> SkeletalMesh;

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Hy | Weapon")
    TObjectPtr<class UStaticMeshComponent> SubWeaponMesh;

    UPROPERTY(BlueprintReadOnly, EditAnyWhere, Category = "Hy | Weapon")
    TObjectPtr<class USceneComponent> SubHandleComp;

};
