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
	FGameplayTag GetItemType() const {return ItemType;}

	template<typename T> requires std::derived_from<T, FInv_ItemFragment>
	const T* GetFragmentOfTypeWithTag(const FGameplayTag FragmentTag) const;

	template<typename T> requires std::derived_from<T, FInv_ItemFragment>
	const T* GetFragmentOfType() const;

	template<typename T> requires std::derived_from<T, FInv_ItemFragment>
	T* GetFragmentOfTypeMutable();
	
private:

	UPROPERTY(EditAnywhere, Category = "Inventory", meta = (ExcludeBaseStruct)) // add only children
	TArray<TInstancedStruct<FInv_ItemFragment>> Fragments;
	
	UPROPERTY(EditAnywhere, Category= "Inventory")
	EInv_ItemCategory ItemCategory{EInv_ItemCategory::None};

	UPROPERTY(EditAnywhere, Category = "Inventory")
	FGameplayTag ItemType;
	
};

template<typename T>
requires std::derived_from<T, FInv_ItemFragment>
const T* FInv_ItemManifest::GetFragmentOfTypeWithTag(const FGameplayTag FragmentTag) const
{
	for (const TInstancedStruct<FInv_ItemFragment>& Fragment : Fragments)
	{
		if (const T* FragmentPtr = Fragment.GetPtr<T>())
		{
			if (!FragmentPtr->GetFragmentTag().MatchesTag(FragmentTag)) continue;
			return FragmentPtr;
		}
	}
	
	return nullptr;
}

template <typename T> requires std::derived_from<T, FInv_ItemFragment>
const T* FInv_ItemManifest::GetFragmentOfType() const
{
	for (const TInstancedStruct<FInv_ItemFragment>& Fragment : Fragments)
	{
		if (const T* FragmentPtr = Fragment.GetPtr<T>())
		{
			return FragmentPtr;
		}
	}
	
	return nullptr;
}

template <typename T> requires std::derived_from<T, FInv_ItemFragment>
T* FInv_ItemManifest::GetFragmentOfTypeMutable()
{
	for (TInstancedStruct<FInv_ItemFragment>& Fragment : Fragments)
	{
		if (T* FragmentPtr = Fragment.GetMutablePtr<T>())
		{
			return FragmentPtr;
		}
	}
	
	return nullptr;
}
