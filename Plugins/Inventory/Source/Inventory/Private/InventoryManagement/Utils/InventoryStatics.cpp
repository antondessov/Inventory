﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryManagement/Utils/InventoryStatics.h"

#include "InventoryManagement/Components/Inv_InventoryComponent.h"
#include "Items/Components/Inv_ItemComponent.h"
#include "Types/Inv_GridTypes.h"

UInv_InventoryComponent* UInventoryStatics::GetInventoryComponent(const APlayerController* PlayerController)
{
	if (!IsValid(PlayerController)) return nullptr;

	UInv_InventoryComponent* InventoryComponent = PlayerController->FindComponentByClass<UInv_InventoryComponent>();
	return InventoryComponent;
}

EInv_ItemCategory UInventoryStatics::GetItemCategoryFromItemComp(UInv_ItemComponent* ItemComponent)
{
	if (!IsValid(ItemComponent)) return EInv_ItemCategory::None;
	return ItemComponent->GetItemManifest().GetItemCategory();
}
