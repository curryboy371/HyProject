#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "HyTableTypes.h"
#include "GameplayTagContainer.h"

#include "Item_TableEntity.generated.h"

USTRUCT(BlueprintType)
struct HYTABLE_API FItem_TableEntity : public FHyTableRowBase
{
	GENERATED_USTRUCT_BODY()

	FItem_TableEntity()
	{
		ItemID = 0;
		ItemPath = "";
		EquipmentSlot = FGameplayTag::EmptyTag;
		HandSocketName = NAME_None;
		HandSubSocketName = NAME_None;
		BodySocketName = NAME_None;
		StartSocketName = NAME_None;
		EndSocketName = NAME_None;
		WeaponRadius = 0.f;
		WeaponHeight = 0.f;
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HyTable)
	int32 ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HyTable)
	FString ItemPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HyTable)
	FGameplayTag EquipmentSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HyTable)
	FName HandSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HyTable)
	FName HandSubSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HyTable)
	FName BodySocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HyTable)
	FGameplayTag WeaponCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HyTable)
	FName StartSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HyTable)
	FName EndSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HyTable)
	float WeaponRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HyTable)
	float WeaponHeight;
};
