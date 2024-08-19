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


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEquipTagChanged, const FGameplayTag&, EquipTag);


UCLASS()
class HYFRAMEWORK_API AHyCharacterBase : public ACharacter, public ICControlCharacterInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	//AHyCharacterBase();

	// Sets default values for this character's properties
	AHyCharacterBase(const FObjectInitializer& ObjectInitializer);

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
	virtual FGameplayTag GetEquipTag() override;

	virtual void SetCombatMode(const bool bCombatMode) override;



protected:
	void CharacterSetup();
	void CharacterWidgetSetup();

	void CharacterDebugHudSetup();
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

	UFUNCTION(BlueprintCallable, Category = "Input")
	void InputSprint(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void CompletedSprint(const FInputActionValue& Value);

protected:
	// Debug
	void DebugUpdate();

	void DebugRenderWidget();

protected:

protected:
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hy | Component")
	TObjectPtr<class UActionsSystemComponent> ActionsSystemComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hy | Component")
	TObjectPtr<class UMotionWarpingComponent> MotionWarpingComp;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hy | Component")
	//TObjectPtr<class UHyFXComponent> FXComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hy | Component")
	TObjectPtr<class USceneComponent> HUDLocationComp;

	UPROPERTY()
	TObjectPtr<class UHyCharacterMovementComponent> HyCharacterMovement;

protected:
	class TSharedPtr<class SHyCharacterHudDebugWidget> SCharacterDebugWidget;


public:
	UPROPERTY(BlueprintAssignable, Category = "Hy | Anim | Layer")
	FOnEquipTagChanged OnEquipTagChanged;


public:
	


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hy | Anim")
	TObjectPtr<class UHyAnimInstance> HyAnimInstance;


protected:
	// BlueprintSetting
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | Init")
	FCharacterDefaultTagSet CharacterDefaultTagSet;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Hy | Input")
	FCharacterInputData CharacterInputData;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Hy | Character")
	FCharacterStateData CharacterStateData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | Debug")
	FCharacterDebugData CharacterDebugData;
	
};
