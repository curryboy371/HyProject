// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"


#include "GameplayTagContainer.h"


#include "HyTypes.generated.h"



#pragma region HyFrameworkStruct

USTRUCT(BlueprintType)
struct FCharacterInitTagSet
{
	GENERATED_BODY()

public:
	FCharacterInitTagSet()
	{
		InputTag = FGameplayTag::EmptyTag;
		EquipTag = FGameplayTag::EmptyTag;
		ActionTag = FGameplayTag::EmptyTag;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | Init | Tags")
	FGameplayTag InputTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | Init | Tags")
	FGameplayTag EquipTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | Init | Tags")
	FGameplayTag ActionTag;
};


#pragma endregion



/**
 * 
 */
UCLASS()
class HYFRAMEWORK_API UHyTypes : public UObject
{
	GENERATED_BODY()
	
	
	
	
};
