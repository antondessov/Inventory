﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Blueprint/UserWidget.h"
#include "Inv_HoverItem.generated.h"

class UInv_InventoryItem;
class UImage;
class UTextBlock;
/**
 *  The HoverItem is the item that will appear and follow the mouse
 *  when an inventory item on the grid has been clicked
 */
UCLASS()
class INVENTORY_API UInv_HoverItem : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetImageBrush(const FSlateBrush& Brush) const;
	void UpdateStackCount(const int32 Count) const;

	FGameplayTag GetItemType() const;
	int32 GetStackCount() const {return StackCount;}
	bool IsStackable() const {return bIsStackable;}
	void SetIsStackable(const bool bStackable);
	int32 GetPreviousGridIndex() const {return PreviousGridIndex;}
	void SetPreviousGridIndex(const int32 Index) {PreviousGridIndex = Index;}
	FIntPoint GetGridDimensions() const {return GridDimensions;}
	void SetGridDimensions(const FIntPoint InDimensions) {GridDimensions = InDimensions;}
	UInv_InventoryItem* GetInventoryItem() const;
	void SetInventoryItem(UInv_InventoryItem* InInventoryItem);
	
	
	
private:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Icon;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_StackCount;
	
	int32 PreviousGridIndex;
	FIntPoint GridDimensions;
	TWeakObjectPtr<UInv_InventoryItem> InventoryItem;
	bool bIsStackable = false;
	int32 StackCount = 0;
	
};
