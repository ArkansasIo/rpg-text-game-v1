#include "EquipmentSystem.h"

UEquipmentSystem::UEquipmentSystem()
{
	// Initialize empty equipment items
	EquippedWeapon.EquipmentSlot = EEquipmentSlotType::EES_Weapon;
	EquippedArmor.EquipmentSlot = EEquipmentSlotType::EES_Armor;
	EquippedHelmet.EquipmentSlot = EEquipmentSlotType::EES_Helmet;
	EquippedBoots.EquipmentSlot = EEquipmentSlotType::EES_Boots;
	EquippedAccessory.EquipmentSlot = EEquipmentSlotType::EES_Accessory;
	EquippedOffhand.EquipmentSlot = EEquipmentSlotType::EES_Offhand;
}

void UEquipmentSystem::EquipItem(const FEquipmentItem& Item)
{
	if (Item.EquipmentSlot == EEquipmentSlotType::EES_None)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot equip item with no slot"));
		return;
	}

	// Unequip existing item in that slot first
	UnequipItem(Item.EquipmentSlot);

	// Equip the new item
	switch (Item.EquipmentSlot)
	{
		case EEquipmentSlotType::EES_Weapon:
			EquippedWeapon = Item;
			break;
		case EEquipmentSlotType::EES_Armor:
			EquippedArmor = Item;
			break;
		case EEquipmentSlotType::EES_Helmet:
			EquippedHelmet = Item;
			break;
		case EEquipmentSlotType::EES_Boots:
			EquippedBoots = Item;
			break;
		case EEquipmentSlotType::EES_Accessory:
			EquippedAccessory = Item;
			break;
		case EEquipmentSlotType::EES_Offhand:
			EquippedOffhand = Item;
			break;
		default:
			break;
	}

	NotifyEquipmentChanged(Item, true);
	NotifyStatsChanged();

	UE_LOG(LogTemp, Warning, TEXT("Equipped: %s"), *Item.EquipmentName);
}

void UEquipmentSystem::UnequipItem(EEquipmentSlotType Slot)
{
	FEquipmentItem UnequippedItem;
	UnequippedItem.EquipmentSlot = Slot;

	switch (Slot)
	{
		case EEquipmentSlotType::EES_Weapon:
			UnequippedItem = EquippedWeapon;
			EquippedWeapon = FEquipmentItem();
			EquippedWeapon.EquipmentSlot = EEquipmentSlotType::EES_Weapon;
			break;
		case EEquipmentSlotType::EES_Armor:
			UnequippedItem = EquippedArmor;
			EquippedArmor = FEquipmentItem();
			EquippedArmor.EquipmentSlot = EEquipmentSlotType::EES_Armor;
			break;
		case EEquipmentSlotType::EES_Helmet:
			UnequippedItem = EquippedHelmet;
			EquippedHelmet = FEquipmentItem();
			EquippedHelmet.EquipmentSlot = EEquipmentSlotType::EES_Helmet;
			break;
		case EEquipmentSlotType::EES_Boots:
			UnequippedItem = EquippedBoots;
			EquippedBoots = FEquipmentItem();
			EquippedBoots.EquipmentSlot = EEquipmentSlotType::EES_Boots;
			break;
		case EEquipmentSlotType::EES_Accessory:
			UnequippedItem = EquippedAccessory;
			EquippedAccessory = FEquipmentItem();
			EquippedAccessory.EquipmentSlot = EEquipmentSlotType::EES_Accessory;
			break;
		case EEquipmentSlotType::EES_Offhand:
			UnequippedItem = EquippedOffhand;
			EquippedOffhand = FEquipmentItem();
			EquippedOffhand.EquipmentSlot = EEquipmentSlotType::EES_Offhand;
			break;
		default:
			break;
	}

	if (!UnequippedItem.EquipmentName.IsEmpty())
	{
		NotifyEquipmentChanged(UnequippedItem, false);
		NotifyStatsChanged();
	}
}

FEquipmentItem* UEquipmentSystem::GetEquippedItem(EEquipmentSlotType Slot)
{
	switch (Slot)
	{
		case EEquipmentSlotType::EES_Weapon:
			return &EquippedWeapon;
		case EEquipmentSlotType::EES_Armor:
			return &EquippedArmor;
		case EEquipmentSlotType::EES_Helmet:
			return &EquippedHelmet;
		case EEquipmentSlotType::EES_Boots:
			return &EquippedBoots;
		case EEquipmentSlotType::EES_Accessory:
			return &EquippedAccessory;
		case EEquipmentSlotType::EES_Offhand:
			return &EquippedOffhand;
		default:
			return nullptr;
	}
}

void UEquipmentSystem::SwapEquipment(EEquipmentSlotType Slot, const FEquipmentItem& NewItem)
{
	UnequipItem(Slot);
	EquipItem(NewItem);
}

void UEquipmentSystem::ClearAllEquipment()
{
	UnequipItem(EEquipmentSlotType::EES_Weapon);
	UnequipItem(EEquipmentSlotType::EES_Armor);
	UnequipItem(EEquipmentSlotType::EES_Helmet);
	UnequipItem(EEquipmentSlotType::EES_Boots);
	UnequipItem(EEquipmentSlotType::EES_Accessory);
	UnequipItem(EEquipmentSlotType::EES_Offhand);

	NotifyStatsChanged();

	UE_LOG(LogTemp, Warning, TEXT("All equipment cleared"));
}

float UEquipmentSystem::GetTotalAttackBonus() const
{
	float Total = 0.0f;
	Total += EquippedWeapon.AttackBonus;
	Total += EquippedArmor.AttackBonus;
	Total += EquippedHelmet.AttackBonus;
	Total += EquippedBoots.AttackBonus;
	Total += EquippedAccessory.AttackBonus;
	Total += EquippedOffhand.AttackBonus;
	return Total;
}

float UEquipmentSystem::GetTotalDefenseBonus() const
{
	float Total = 0.0f;
	Total += EquippedWeapon.DefenseBonus;
	Total += EquippedArmor.DefenseBonus;
	Total += EquippedHelmet.DefenseBonus;
	Total += EquippedBoots.DefenseBonus;
	Total += EquippedAccessory.DefenseBonus;
	Total += EquippedOffhand.DefenseBonus;
	return Total;
}

float UEquipmentSystem::GetTotalMagicPowerBonus() const
{
	float Total = 0.0f;
	Total += EquippedWeapon.MagicPowerBonus;
	Total += EquippedArmor.MagicPowerBonus;
	Total += EquippedHelmet.MagicPowerBonus;
	Total += EquippedBoots.MagicPowerBonus;
	Total += EquippedAccessory.MagicPowerBonus;
	Total += EquippedOffhand.MagicPowerBonus;
	return Total;
}

float UEquipmentSystem::GetTotalHealthBonus() const
{
	float Total = 0.0f;
	Total += EquippedWeapon.HealthBonus;
	Total += EquippedArmor.HealthBonus;
	Total += EquippedHelmet.HealthBonus;
	Total += EquippedBoots.HealthBonus;
	Total += EquippedAccessory.HealthBonus;
	Total += EquippedOffhand.HealthBonus;
	return Total;
}

float UEquipmentSystem::GetTotalManaBonus() const
{
	float Total = 0.0f;
	Total += EquippedWeapon.ManaBonus;
	Total += EquippedArmor.ManaBonus;
	Total += EquippedHelmet.ManaBonus;
	Total += EquippedBoots.ManaBonus;
	Total += EquippedAccessory.ManaBonus;
	Total += EquippedOffhand.ManaBonus;
	return Total;
}

float UEquipmentSystem::GetTotalStaminaBonus() const
{
	float Total = 0.0f;
	Total += EquippedWeapon.StaminaBonus;
	Total += EquippedArmor.StaminaBonus;
	Total += EquippedHelmet.StaminaBonus;
	Total += EquippedBoots.StaminaBonus;
	Total += EquippedAccessory.StaminaBonus;
	Total += EquippedOffhand.StaminaBonus;
	return Total;
}

float UEquipmentSystem::GetTotalWeight() const
{
	float Total = 0.0f;
	if (!EquippedWeapon.EquipmentName.IsEmpty())
		Total += EquippedWeapon.Weight;
	if (!EquippedArmor.EquipmentName.IsEmpty())
		Total += EquippedArmor.Weight;
	if (!EquippedHelmet.EquipmentName.IsEmpty())
		Total += EquippedHelmet.Weight;
	if (!EquippedBoots.EquipmentName.IsEmpty())
		Total += EquippedBoots.Weight;
	if (!EquippedAccessory.EquipmentName.IsEmpty())
		Total += EquippedAccessory.Weight;
	if (!EquippedOffhand.EquipmentName.IsEmpty())
		Total += EquippedOffhand.Weight;
	return Total;
}

int32 UEquipmentSystem::GetEquippedItemCount() const
{
	int32 Count = 0;
	if (!EquippedWeapon.EquipmentName.IsEmpty()) Count++;
	if (!EquippedArmor.EquipmentName.IsEmpty()) Count++;
	if (!EquippedHelmet.EquipmentName.IsEmpty()) Count++;
	if (!EquippedBoots.EquipmentName.IsEmpty()) Count++;
	if (!EquippedAccessory.EquipmentName.IsEmpty()) Count++;
	if (!EquippedOffhand.EquipmentName.IsEmpty()) Count++;
	return Count;
}

bool UEquipmentSystem::IsSlotEquipped(EEquipmentSlotType Slot) const
{
	switch (Slot)
	{
		case EEquipmentSlotType::EES_Weapon:
			return !EquippedWeapon.EquipmentName.IsEmpty();
		case EEquipmentSlotType::EES_Armor:
			return !EquippedArmor.EquipmentName.IsEmpty();
		case EEquipmentSlotType::EES_Helmet:
			return !EquippedHelmet.EquipmentName.IsEmpty();
		case EEquipmentSlotType::EES_Boots:
			return !EquippedBoots.EquipmentName.IsEmpty();
		case EEquipmentSlotType::EES_Accessory:
			return !EquippedAccessory.EquipmentName.IsEmpty();
		case EEquipmentSlotType::EES_Offhand:
			return !EquippedOffhand.EquipmentName.IsEmpty();
		default:
			return false;
	}
}

FString UEquipmentSystem::GetEquipmentSetDescription() const
{
	FString Description = TEXT("Equipment Set:\n");

	if (!EquippedWeapon.EquipmentName.IsEmpty())
		Description += FString::Printf(TEXT("Weapon: %s\n"), *EquippedWeapon.EquipmentName);
	if (!EquippedArmor.EquipmentName.IsEmpty())
		Description += FString::Printf(TEXT("Armor: %s\n"), *EquippedArmor.EquipmentName);
	if (!EquippedHelmet.EquipmentName.IsEmpty())
		Description += FString::Printf(TEXT("Helmet: %s\n"), *EquippedHelmet.EquipmentName);
	if (!EquippedBoots.EquipmentName.IsEmpty())
		Description += FString::Printf(TEXT("Boots: %s\n"), *EquippedBoots.EquipmentName);
	if (!EquippedAccessory.EquipmentName.IsEmpty())
		Description += FString::Printf(TEXT("Accessory: %s\n"), *EquippedAccessory.EquipmentName);
	if (!EquippedOffhand.EquipmentName.IsEmpty())
		Description += FString::Printf(TEXT("Off-Hand: %s\n"), *EquippedOffhand.EquipmentName);

	Description += FString::Printf(
		TEXT("\nStats:\n+%.1f ATK | +%.1f DEF | +%.1f MAGIC | +%.0f HP | +%.0f MP\nWeight: %.1f"),
		GetTotalAttackBonus(), GetTotalDefenseBonus(), GetTotalMagicPowerBonus(),
		GetTotalHealthBonus(), GetTotalManaBonus(), GetTotalWeight()
	);

	return Description;
}

void UEquipmentSystem::DisplayEquipmentStats()
{
	FString Stats = FString::Printf(
		TEXT("=== Equipment Stats ===\n")
		TEXT("Equipped Items: %d\n")
		TEXT("Total Attack: +%.1f\n")
		TEXT("Total Defense: +%.1f\n")
		TEXT("Total Magic Power: +%.1f\n")
		TEXT("Total Health: +%.0f\n")
		TEXT("Total Mana: +%.0f\n")
		TEXT("Total Stamina: +%.0f\n")
		TEXT("Total Weight: %.1f"),
		GetEquippedItemCount(),
		GetTotalAttackBonus(),
		GetTotalDefenseBonus(),
		GetTotalMagicPowerBonus(),
		GetTotalHealthBonus(),
		GetTotalManaBonus(),
		GetTotalStaminaBonus(),
		GetTotalWeight()
	);

	UE_LOG(LogTemp, Warning, TEXT("%s"), *Stats);
}

void UEquipmentSystem::NotifyEquipmentChanged(const FEquipmentItem& Item, bool bEquipped)
{
	OnEquipmentChanged.Broadcast(Item, bEquipped);
}

void UEquipmentSystem::NotifyStatsChanged()
{
	OnEquipmentStatsChanged.Broadcast();
}
