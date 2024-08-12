// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTagContainer.h"

#include "HyTypes.h"

#include "ActionsTypes.h"


#include "InputActionValue.h"

#include "HyCharacterBase.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEquipLayerChanged, const FGameplayTag&, EquipTag);


UCLASS()
class HYFRAMEWORK_API AHyCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHyCharacterBase();

	virtual void CharacterDefaultSetup();
	virtual void ComponenetSetup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	

protected:
	void CharacterSetup();

public:
	// Anim 
	void SwitchEquipLayer(const FGameplayTag& InEquipTag);


	void SetHyAnimInstance();
public:
	// Actions System
	bool TriggerAction(const FActionExcuteData& InActionExcuteData, bool bCanBeStored = false);

protected:
	void InputAttack(const FInputActionValue& Value);
	void InputMove(const FInputActionValue& Value);
	void InputJump(const FInputActionValue& Value);
	void InputLook(const FInputActionValue& Value);
	void InputEquip(const FInputActionValue& Value);

protected:
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hy | Component")
	TObjectPtr<class UActionsSystemComponent> ActionsSystemCom;



public:
	UPROPERTY(BlueprintAssignable, Category = "Hy | Anim | Layer")
	FOnEquipLayerChanged OnEquipLayerChanged;



protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hy | Anim")
	TObjectPtr<class UHyAnimInstance> HyAnimInstance;







protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | Init")
	FCharacterInitTagSet CharacterInitTagSet;
};
