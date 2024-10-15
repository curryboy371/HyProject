// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/HyEquippableItem.h"

#include "InvenTypes.h"

#include "HyCoreTypes.h"

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

    UFUNCTION(BlueprintCallable, Category = Hy)
    void ActiveTrail(bool bActive, const EHyAttackTrailType InAttackTrailType = EHyAttackTrailType::AttackDefault);

    TObjectPtr<class UNiagaraComponent> ActiveWeaponTrail(const EHyAttackTrailType InAttackTrailType = EHyAttackTrailType::AttackDefault);

public:

    UFUNCTION(BlueprintPure, Category = Hy)
    FORCEINLINE FName GetBodySocketName() const { return ItemTableInfo.BodySocketName;}

    UFUNCTION(BlueprintPure, Category = Hy)
    FORCEINLINE FName GetHandSocketName() const { return ItemTableInfo.HandSocketName; }

    UFUNCTION(BlueprintPure, Category = Hy)
    FORCEINLINE FName GetSubHandSocketName() const { return ItemTableInfo.HandSubSocketName; }

    FORCEINLINE class USkeletalMeshComponent* GetMeshComponent() const { return SkeletalMesh; };

    FORCEINLINE class USceneComponent* GetSubHandleComp() const { return SubHandleComp; };


    FORCEINLINE EWeaponMeshType GetWeaponMeshType() const { return WeaponMeshType; }

protected:
    UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Hy | Weapon")
    EWeaponMeshType WeaponMeshType = EWeaponMeshType::EWeaponMesh_StaticMesh;

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Hy | Weapon")
    TObjectPtr<class USkeletalMeshComponent> SkeletalMesh;

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Hy | Weapon")
    TObjectPtr<class UStaticMeshComponent> SubWeaponMesh;

    UPROPERTY(BlueprintReadOnly, EditAnyWhere, Category = "Hy | Weapon")
    TObjectPtr<class USceneComponent> SubHandleComp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<class UNiagaraSystem> NiagaraDefaultTrail;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<EHyAttackTrailType, TObjectPtr<class UNiagaraSystem>> NiagaraTrailMap;

    UPROPERTY()
    TMap<EHyAttackTrailType, TObjectPtr<class UNiagaraComponent>> NiagaraCompMap;

protected:

};
