﻿#pragma once

#include "CoreMinimal.h"
#include "Types/Inv_GridTypes.h"
#include "GameplayTagContainer.h"
#include "Items/Fragments/Inv_ItemFragment.h"
#include "StructUtils/InstancedStruct.h"
#include "Inv_ItemManifest.generated.h"

/**
 * The Item Manifest contains all of the necessary data
 * for creating a new Inventory Item
 */
struct FInv_ItemFragment;

USTRUCT(BlueprintType)
struct INVENTORY_API FInv_ItemManifest
{
	GENERATED_BODY()

	UInv_InventoryItem* Manifest(UObject* NewOuter);
	
	EInv_ItemCategory GetItemCategory() const {return ItemCategory;}
	FGameplayTag GetItemTag() const {return ItemType;}
	
private:

	UPROPERTY(EditAnywhere, Category = "Inventory", meta = (ExcludeBaseStruct)) // add only children
	TArray<TInstancedStruct<FInv_ItemFragment>> Fragments;
	
	UPROPERTY(EditAnywhere, Category= "Inventory")
	EInv_ItemCategory ItemCategory{EInv_ItemCategory::None};

	UPROPERTY(EditAnywhere, Category = "Inventory")
	FGameplayTag ItemType;
};
