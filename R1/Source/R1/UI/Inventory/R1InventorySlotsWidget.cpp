// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/R1InventorySlotsWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "UI/Inventory/R1InventorySlotWidget.h"
#include "Item/R1InventorySubsystem.h"
#include "Subsystems/SubsystemBlueprintLibrary.h"
#include "UI/Inventory/R1InventoryEntryWidget.h"
UR1InventorySlotsWidget::UR1InventorySlotsWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UR1InventorySlotWidget> FindSlotWidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/Item/Inventory/WBP_InventorySlot.WBP_InventorySlot_C'"));
	
	if (FindSlotWidgetClass.Succeeded())
	{
		SlotWidgetClass = FindSlotWidgetClass.Class;
	}

	ConstructorHelpers::FClassFinder<UR1InventoryEntryWidget> FindEntryWidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/Item/Inventory/WBP_InventoryEntry.WBP_InventoryEntry_C'"));
	
	if (FindEntryWidgetClass.Succeeded())
	{
		EntryWidgetClass = FindEntryWidgetClass.Class;
	}
}

void UR1InventorySlotsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SlotWidgets.SetNum(X_COUNT * Y_COUNT);

	for (int32 y = 0; y < Y_COUNT; y++)
	{
		for (int32 x = 0; x < X_COUNT; x++)
		{
			int32 index = y * X_COUNT + x;

			UR1InventorySlotWidget* SlotWidget = CreateWidget<UR1InventorySlotWidget>(GetOwningPlayer(), SlotWidgetClass);
			SlotWidgets[index] = SlotWidget;
			GridPanel_Slots->AddChildToUniformGrid(SlotWidget, y, x);
		}
	}

	EntryWidgets.SetNum(X_COUNT * Y_COUNT);

	UR1InventorySubsystem* Inventory = Cast<UR1InventorySubsystem>(USubsystemBlueprintLibrary::GetWorldSubsystem(this, UR1InventorySubsystem::StaticClass()));

	const TArray<TObjectPtr<UR1ItemInstance>>& Items = Inventory->GetItems();

	for (int32 i = 0; i < Items.Num(); i++)
	{
		const TObjectPtr<UR1ItemInstance>& Item = Items[i];
		FIntPoint ItemSlotPos = FIntPoint(i % X_COUNT, i / X_COUNT);
		OnInventoryEntryChanged(ItemSlotPos, Item);
	}
}
void UR1InventorySlotsWidget::OnInventoryEntryChanged(const FIntPoint& ItemSlotPos, TObjectPtr<UR1ItemInstance> Item)
{
	int32 SlotIndex = ItemSlotPos.Y * X_COUNT + ItemSlotPos.X;

	if (UR1InventoryEntryWidget* EntryWidget = EntryWidgets[SlotIndex])
	{
		if (Item == nullptr)
		{
			CanvasPanel_Entries->RemoveChild(EntryWidget);
			EntryWidgets[SlotIndex] = nullptr;
		}
	}
	else
	{
		EntryWidget = CreateWidget<UR1InventoryEntryWidget>(GetOwningPlayer(), EntryWidgetClass);
		EntryWidgets[SlotIndex] = EntryWidget;

		UCanvasPanelSlot* CanvasPanelSlot = CanvasPanel_Entries->AddChildToCanvas(EntryWidget);
		CanvasPanelSlot->SetAutoSize(true);
		CanvasPanelSlot->SetPosition(FVector2D(ItemSlotPos.X * 50, ItemSlotPos.Y * 50));

		//TODO 테스트용
		EntryWidget->Init(this, Item, 1);
	}
}
//
//bool UR1InventorySlotsWidget::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
//{
//   Super::NativeOnDragOver(InGeometry, InDragDropEvent, InOperation);
//	return false;
//}
//
//void UR1InventorySlotsWidget::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
//{
//	Super::NativeOnDragLeave(InDragDropEvent, InOperation);
//}
//
//bool UR1InventorySlotsWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
//{
//	FReplay Replay =  Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
//	return false;
//}
