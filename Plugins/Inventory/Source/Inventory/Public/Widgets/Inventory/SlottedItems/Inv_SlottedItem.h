﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inv_SlottedItem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSlottedItemClicked, int32, GridIndex, const FPointerEvent&, MouseEvent);

class UInv_InventoryItem;
class UImage;
class UTextBlock;
/**
 * 
 */
UCLASS()
class INVENTORY_API UInv_SlottedItem : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	FSlottedItemClicked OnSlottedItemClicked;
	
	bool IsStackable() const { return bIsStackable; }
	void SetIsStackable(bool bStackable) {bIsStackable = bStackable;}
	UImage* GetImageIcon() const {return Image_Icon;}
	void SetGridIndex(int32 Index) {GridIndex = Index;}
	int32 GetGridIndex() const {return GridIndex;}
	void SetGridDimensions(int32 Dimensions) {GridDimensions = Dimensions;}
	FIntPoint GetGridDimensions() const {return GridDimensions;}
	void SetInventoryItem(UInv_InventoryItem* Item);
	UInv_InventoryItem* GetInventoryItem() const {return InventoryItem.Get();}
	void SetImageBrush(const FSlateBrush& Brush) const;
	void UpdateStackCount(int32 StackCount);
	
private:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Icon;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_StackCount;

	int32 GridIndex;
	FIntPoint GridDimensions;

	TWeakObjectPtr<UInv_InventoryItem> InventoryItem;
	bool bIsStackable = false;
};
