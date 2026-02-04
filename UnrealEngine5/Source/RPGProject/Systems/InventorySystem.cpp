#include "InventorySystem.h"

UInventorySystem::UInventorySystem()
{
	MaxInventoryWeight = 50.0f;
	InventoryCapacity = 20;
	Gold = 0;
	InventorySlots.Reserve(InventoryCapacity);
}

bool UInventorySystem::AddItem(const FInventoryItem& NewItem)
{
	if (!CanAddItem(NewItem))
	{
		return false;
	}

	// Try to stack with existing item
	if (NewItem.bStackable)
	{
		FInventoryItem* ExistingItem = FindItem(NewItem.ItemID);
		if (ExistingItem)
		{
			ExistingItem->Quantity += NewItem.Quantity;
			OnInventoryChanged.Broadcast(InventorySlots.Num(), GetCurrentInventoryWeight());
			return true;
		}
	}

	// Add as new item
	if (InventorySlots.Num() < InventoryCapacity)
	{
		InventorySlots.Add(NewItem);
		OnItemAdded.Broadcast(NewItem);
		NotifyInventoryChanged();
		return true;
	}

	return false;
}

bool UInventorySystem::RemoveItem(const FString& ItemID, int32 Quantity)
{
	FInventoryItem* Item = FindItem(ItemID);
	if (!Item)
	{
		return false;
	}

	Item->Quantity -= Quantity;
	if (Item->Quantity <= 0)
	{
		OnItemRemoved.Broadcast(*Item);
		InventorySlots.RemoveAll([ItemID](const FInventoryItem& InventoryItem)
		{
			return InventoryItem.ItemID == ItemID;
		});
	}

	NotifyInventoryChanged();
	return true;
}

FInventoryItem* UInventorySystem::FindItem(const FString& ItemID)
{
	return InventorySlots.FindByPredicate([ItemID](const FInventoryItem& Item)
	{
		return Item.ItemID == ItemID;
	});
}

void UInventorySystem::UseItem(const FString& ItemID)
{
	FInventoryItem* Item = FindItem(ItemID);
	if (Item && Item->ItemType == EItemType::Consumable)
	{
		RemoveItem(ItemID, 1);
		// TODO: Apply item effects
	}
}

void UInventorySystem::DropItem(const FString& ItemID, int32 Quantity)
{
	FInventoryItem* Item = FindItem(ItemID);
	if (Item)
	{
		// TODO: Create dropped item in world
		RemoveItem(ItemID, Quantity);
	}
}

float UInventorySystem::GetCurrentInventoryWeight() const
{
	float TotalWeight = 0.0f;
	for (const FInventoryItem& Item : InventorySlots)
	{
		TotalWeight += Item.Weight * Item.Quantity;
	}
	return TotalWeight;
}

bool UInventorySystem::IsInventoryFull() const
{
	return InventorySlots.Num() >= InventoryCapacity || GetCurrentInventoryWeight() >= MaxInventoryWeight;
}

void UInventorySystem::SortInventory()
{
	InventorySlots.Sort([](const FInventoryItem& A, const FInventoryItem& B)
	{
		return static_cast<int32>(A.ItemType) < static_cast<int32>(B.ItemType);
	});
}

bool UInventorySystem::EquipItem(const FString& ItemID, EEquipmentSlot Slot)
{
	FInventoryItem* Item = FindItem(ItemID);
	if (!Item || Item->ItemType != EItemType::Equipment)
	{
		return false;
	}

	// Unequip existing item if present
	if (EquippedItems.Contains(Slot))
	{
		UnequipItem(Slot);
	}

	// Equip new item
	FEquipmentItem EquippedItem;
	EquippedItem.Item = *Item;
	EquippedItem.EquipmentSlot = Slot;

	EquippedItems.Add(Slot, EquippedItem);
	RemoveItem(ItemID, 1);
	OnEquipmentChanged.Broadcast(EquippedItem);

	return true;
}

bool UInventorySystem::UnequipItem(EEquipmentSlot Slot)
{
	if (!EquippedItems.Contains(Slot))
	{
		return false;
	}

	FEquipmentItem* EquippedItem = EquippedItems.Find(Slot);
	if (EquippedItem && !AddItem(EquippedItem->Item))
	{
		return false; // Failed to add back to inventory
	}

	EquippedItems.Remove(Slot);
	return true;
}

FEquipmentItem* UInventorySystem::GetEquippedItem(EEquipmentSlot Slot)
{
	return EquippedItems.Find(Slot);
}

float UInventorySystem::CalculateTotalArmorBonus() const
{
	float TotalArmor = 0.0f;
	for (const auto& EquippedPair : EquippedItems)
	{
		TotalArmor += EquippedPair.Value.ArmorBonus;
	}
	return TotalArmor;
}

float UInventorySystem::CalculateTotalDamageBonus() const
{
	float TotalDamage = 0.0f;
	for (const auto& EquippedPair : EquippedItems)
	{
		TotalDamage += EquippedPair.Value.DamageBonus;
	}
	return TotalDamage;
}

void UInventorySystem::AddGold(int32 Amount)
{
	Gold += Amount;
}

bool UInventorySystem::SpendGold(int32 Amount)
{
	if (Gold >= Amount)
	{
		Gold -= Amount;
		return true;
	}
	return false;
}

int32 UInventorySystem::GetGold() const
{
	return Gold;
}

int32 UInventorySystem::GetAvailableSlots() const
{
	return InventoryCapacity - InventorySlots.Num();
}

void UInventorySystem::ClearInventory()
{
	InventorySlots.Clear();
	EquippedItems.Clear();
	NotifyInventoryChanged();
}

void UInventorySystem::NotifyInventoryChanged()
{
	OnInventoryChanged.Broadcast(InventorySlots.Num(), GetCurrentInventoryWeight());
}

bool UInventorySystem::CanAddItem(const FInventoryItem& Item) const
{
	if (GetCurrentInventoryWeight() + Item.Weight > MaxInventoryWeight)
	{
		return false;
	}

	if (Item.bStackable)
	{
		return true; // Can always stack
	}

	return InventorySlots.Num() < InventoryCapacity;
}
