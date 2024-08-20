// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InvenTypes.generated.h"

#pragma region InventoryEnum

UENUM(BlueprintType)
enum class EWeaponMeshType : uint8
{
	EWeaponMesh_StaticMesh UMETA(DisplayName = "Static Weapon"),
	EWeaponMesh_SkeletalMesh UMETA(DisplayName = "Skeletal Weapon"),
};


UENUM(BlueprintType)
enum class EWeaponArmState : uint8
{
	// 무기를 장착하고 있지 않음 ( 미장착 )
	EWS_None UMETA(DisplayName = "None Equipped Weapon"),

	// 무기를 장착중이나 손에 없음 ( 비전투모드 )
	EWS_Unarmed UMETA(DisplayName = "Unarmed"),     

	// 무기를 장착중이고 손에 있음 ( 전투모드 )
	EWS_Armed UMETA(DisplayName = "Armed"),			

};


#pragma endregion


#pragma region InventoryStruct


#pragma endregion


/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UInvenTypes : public UObject
{
	GENERATED_BODY()
	
	
	
	
};
