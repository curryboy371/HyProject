// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/HyEquippableItem.h"

#include <GameFramework/Character.h>


#include "HyCoreMacro.h"


void AHyEquippableItem::OnEquipped(TObjectPtr<ACharacter> InOwner)
{
	if (!InOwner)
	{
		ERR_V("InOwner is nullptr");
		return;
	}

	ItemOwner = InOwner;
	SetOwner(ItemOwner);

	OnItemEquipped();


}

void AHyEquippableItem::OnUnEquipped()
{

	OnItemUnEquipped();
}
