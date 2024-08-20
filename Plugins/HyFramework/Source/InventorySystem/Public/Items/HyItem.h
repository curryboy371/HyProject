// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Table/Item_TableEntity.h"

#include "HyItem.generated.h"


USTRUCT(BlueprintType)
struct FBaseItem 
{
    GENERATED_BODY()
public:
    FBaseItem()
    {
        ItemGuid.Invalidate();
        ItemClass = nullptr;
        Count = 0;
    };

    FBaseItem(const TSubclassOf<class AHyItem>& InItem, int32 InCount)
    {
        ItemGuid = FGuid::NewGuid();
        ItemClass = InItem;
        Count = InCount;
    };

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<class AHyItem> ItemClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Count = 1;

    FORCEINLINE bool operator==(const FBaseItem& Other) const
    {
        return this->ItemClass == Other.ItemClass;
    }

    FORCEINLINE bool operator!=(const FBaseItem& Other) const
    {
        return this->ItemClass != Other.ItemClass;
    }

    FORCEINLINE bool operator!=(const TSubclassOf<class AHyItem>& Other) const
    {
        return this->ItemClass != Other;
    }

    FORCEINLINE bool operator==(const TSubclassOf<class AHyItem>& Other) const
    {
        return this->ItemClass == Other;
    }

protected:
    UPROPERTY(BlueprintReadOnly, Category = Hy)
    FGuid ItemGuid;

};

UCLASS()
class INVENTORYSYSTEM_API AHyItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHyItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

    virtual void InitializeItem(const struct FItem_TableEntity* InItemTableInfo);


	FORCEINLINE void SetItemOwner(TObjectPtr<class APawn> InOwner) { ItemOwner = InOwner;}

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Hy")
	TObjectPtr<class APawn> ItemOwner;

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Hy)
    TObjectPtr<class USceneComponent> RootComp;

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Hy)
    TObjectPtr<class UStaticMeshComponent> ItemMesh;

    FItem_TableEntity ItemTableInfo;
};
