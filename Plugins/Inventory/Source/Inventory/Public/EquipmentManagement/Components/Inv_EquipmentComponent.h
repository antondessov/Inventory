// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "Inv_EquipmentComponent.generated.h"

struct FInv_ItemManifest;
struct FInv_EquipmentFragment;
class AInv_EquipActor;
class UInv_InventoryItem;
class UInv_InventoryComponent;
class APlayerController;
class USkeletalMeshComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class INVENTORY_API UInv_EquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	void SetOwningSkeletalMesh(USkeletalMeshComponent* InOwningSkeletalMesh);
	void SetIsProxy(bool bProxy);
	
protected:
	virtual void BeginPlay() override;

private:

	TWeakObjectPtr<UInv_InventoryComponent> InventoryComponent;
	TWeakObjectPtr<APlayerController> OwningPlayerController;
	TWeakObjectPtr<USkeletalMeshComponent> OwningSkeletalMesh;

	UFUNCTION()
	void OnItemEquipped(UInv_InventoryItem* EquippedItem);

	UFUNCTION()
	void OnItemUnequipped(UInv_InventoryItem* UnEquippedItem);

	void InitInventoryComponent();
	void InitPlayerController();
	AInv_EquipActor* SpawnEquippedActor(FInv_EquipmentFragment* EquipmentFragment, const FInv_ItemManifest& Manifest, USkeletalMeshComponent* AttachMesh);
	AInv_EquipActor* FindEquippedActor(const FGameplayTag& EquippedTypeTag);
	void RemoveEquippedActor(const FGameplayTag& EquipmentTypeTag);

	UFUNCTION()
	void OnPossessedPawnChange(APawn* OldPawn, APawn* NewPawn);

	
	
	UPROPERTY()
	TArray<TObjectPtr<AInv_EquipActor>> EquippedActors;

	bool bIsProxy{false};
};
