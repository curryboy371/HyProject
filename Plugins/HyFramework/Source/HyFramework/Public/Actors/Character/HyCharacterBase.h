// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTagContainer.h"
#include "GameFramework/DamageType.h"

#include "HyTypes.h"

#include "CControlTypes.h"

#include "ActionsTypes.h"


#include "InputActionValue.h"

#include "Interface/CControlCharacterInterface.h"
#include "Interface/ActionsCharacterInterface.h"
#include "Interface/CollisionCharacterInterface.h"


#include "HyCharacterBase.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEquipTagChanged, const FGameplayTag&, EquipTag);


UCLASS()
class HYFRAMEWORK_API AHyCharacterBase : public ACharacter
										, public ICControlCharacterInterface
										, public IActionsCharacterInterface	
										, public ICollisionCharacterInterface

{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHyCharacterBase(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void CharacterDefaultSetup();
	virtual void ComponenetSetup();

protected:

	void CharacterSetup();
	void CharacterActorComponentSetup();
	void CharacterCombatArrowSetup();

	void SetDelegateFunctions();
	void CharacterWidgetSetup();
	void CharacterDebugHudSetup();


	void MatchArrowComponenLocation();

public:
	// Guid
	const FGuid& GetMyGuid() const { return MyGuid; }
	FGuid& GetMyGuidRef() { return MyGuid; }

	const FGuid& GetTargetGuid() const { return TargetGuid; }
	FGuid& GetTargetGuidRef() { return TargetGuid; }

	const bool IsTargetAvailable();

	const FGameplayTag& GetCharacterTypeTag() const { return CharacterTypeTag; }

public:
	// ICControlCharacterInterface을(를) 통해 상속됨
	virtual const bool IsDead() override;
	virtual const bool IsCombatMode() override;

	virtual FGameplayTag GetEquipTag() override;

	virtual void SetCombatMode(const bool bCombatMode) override;


	const bool IsCrouching() const;

	// about Inventory...
	const bool IsWeaponOnHand();


public:
	// IActionsCharacterInterface을(를) 통해 상속됨
	virtual bool TriggerAction(FActionExcuteData& InActionExcuteData, const FString& InContext = "", bool bCanBeStored = false) override;
	virtual void SetStoredAction(FActionExcuteData& InActionExcuteData, const FString InContext = "", bool bForce = false) override;
	virtual void HandleAction(EActionHandleType InExitType, float BlendOut = 0.5f) override;

	virtual void SetPerformingActionPriority(EActionPriority InPriority = EActionPriority::ENone) override;

	virtual bool CompareCurrentPriority(EActionPriority InPriority) const override;


	virtual const bool IsEmptyStoredAction() const override;
	virtual const bool IsCanStoreAction(EActionPriority InPriority) const override;

	virtual const FGameplayTag GetCurAction() const override;
	virtual const FGameplayTag GetStoredAction() const override;

public:
	// Anim 
	void SwitchEquipLayer(const FGameplayTag& InEquipTag);

	void SetHyAnimInstance();

	void SetStencilOutline(bool IsShow, EStencilOutLine StencilType );

public:
	// Combat
	bool GetClosestCombatArrow(const FVector& InAttackerLocation, const float InOwnerAttackRange, FVector& OutCombatArrowLocation);

	void SetDashWarpingTarget(const FVector& InTargetLocation);
	void ReleaseWarpingTarget();

	virtual bool FindTarget() { return false;  };

public:
	UFUNCTION(BlueprintCallable, Category = "Input")
	void InputAttack(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void InputMove(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void CompletedMove(const FInputActionValue& Value);

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

	UFUNCTION(BlueprintCallable, Category = "Input")
	void InputCrouch(const FInputActionValue& Value);

protected:
	// ICollisionCharacterInterface을(를) 통해 상속됨
	virtual void EnableAttackCollider(const FAttackCollisionSettings& InAttackCollisionSet) override;
	virtual void DisableAttackCollider() override;


	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
public:
	const bool IsDead() const;

	const bool IsCanAction(EKeyInput InKeyAction) const;

protected:
	// Debug
	void DebugUpdate();

	void DebugRenderWidget();


public:


	TObjectPtr<class UHyInventorySystemComponent> GetInventorySystemComp() { return InventorySystemComp; }
	TObjectPtr<class UActionsSystemComponent> GetActionsSystemComp() { return ActionsSystemComp; }
	TObjectPtr<class UHyCollisionSystemComponent> GetCollisionSystemComp() { return CollisionSystemComp; }
	TObjectPtr<class UHyCharacterMovementComponent> GetCharacterMovementComp() { return HyCharacterMovement; }

protected:
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hy | Component")
	TArray<TObjectPtr<class UHyActorComponent>> HyActorComponents;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hy | Component")
	TObjectPtr<class UActionsSystemComponent> ActionsSystemComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hy | Component")
	TObjectPtr<class UHyInventorySystemComponent> InventorySystemComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hy | Component")
	TObjectPtr<class UHyCollisionSystemComponent> CollisionSystemComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hy | Component")
	TObjectPtr<class UMotionWarpingComponent> MotionWarpingComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hy | Component")
	TObjectPtr<class USceneComponent> CombatArrowParentComp;



	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hy | Component")
	//TObjectPtr<class UHyFXComponent> FXComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hy | Component")
	TObjectPtr<class USceneComponent> HUDLocationComp;

	UPROPERTY()
	TObjectPtr<class UHyCharacterMovementComponent> HyCharacterMovement;

protected:
	class TSharedPtr<class SHyCharacterHudDebugWidget> SCharacterDebugWidget;

	TMap<ECombatDirection, TObjectPtr<class UArrowComponent>> CombatArrowComponentMap;

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
	


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | Character")
	FGameplayTag CharacterTypeTag;

	FGuid MyGuid;
	FGuid TargetGuid;

};
