// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/HyItem.h"
#include "HyEquippableItem.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API AHyEquippableItem : public AHyItem
{
	GENERATED_BODY()

public:
	virtual void InitializeItem(const struct FItem_TableEntity* InItemTableInfo);



public:
	virtual void OnEquipped(TObjectPtr<ACharacter> InOwner);
	virtual void OnUnEquipped();


public:
	UFUNCTION(BlueprintNativeEvent, Category = "Hy")
	void OnItemEquipped();
	virtual void OnItemEquipped_Implementation() {};

	UFUNCTION(BlueprintNativeEvent, Category = "Hy")
	void OnItemUnEquipped();
	virtual void OnItemUnEquipped_Implementation() {};


protected:
};
