// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTagContainer.h"

#include "HyTypes.h"

#include "CControlTypes.h"

#include "ActionsTypes.h"


#include "InputActionValue.h"

#include "Interface/CControlCharacterInterface.h"

#include "HyCharacterBase.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEquipLayerChanged, const FGameplayTag&, EquipTag);


UCLASS()
class HYFRAMEWORK_API AHyCharacterBase : public ACharacter, public ICControlCharacterInterface
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

	

public:
	// ICControlCharacterInterface을(를) 통해 상속됨
	virtual const bool IsDead() override;
	virtual const bool IsCombatMode() override;

	virtual void SetCombatMode(const bool bCombatMode) override;



protected:
	void CharacterSetup();

public:
	// Anim 
	void SwitchEquipLayer(const FGameplayTag& InEquipTag);


	void SetHyAnimInstance();
public:
	// Actions System
	bool TriggerAction(FActionExcuteData& InActionExcuteData, const FString& InContext = "", bool bCanBeStored = false);


public:
	UFUNCTION(BlueprintCallable, Category = "Input")
	void InputAttack(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void InputMove(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void InputJump(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void InputLook(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void InputEquip(const FInputActionValue& Value);

protected:
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hy | Component")
	TObjectPtr<class UActionsSystemComponent> ActionsSystemCom;



public:
	UPROPERTY(BlueprintAssignable, Category = "Hy | Anim | Layer")
	FOnEquipLayerChanged OnEquipLayerChanged;


public:
	


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hy | Anim")
	TObjectPtr<class UHyAnimInstance> HyAnimInstance;


protected:
	// BlueprintSetting
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | Init")
	FCharacterInitTagSet CharacterInitTagSet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | Movement")
	TMap<ECharacterMovementMode, FCharacterMovementData> CharacterMovementDataMap;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Hy | Input")
	FCharacterInputData CharacterInputData;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Hy | Character")
	FCharacterStateData CharacterStateData;

};
