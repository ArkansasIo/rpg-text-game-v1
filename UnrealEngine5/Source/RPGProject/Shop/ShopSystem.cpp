#include "Shop/ShopSystem.h"

UShopSystem::UShopSystem()
{
	ShopName = TEXT("Unnamed Shop");
	ShopType = EShopType::GeneralStore;
}

void UShopSystem::InitializeShop(const FString& InShopName, EShopType InShopType)
{
	ShopName = InShopName;
	ShopType = InShopType;
	Inventory.Empty();
	OriginalQuantities.Empty();
	TransactionHistory.Empty();
	TotalGoldFromSales = 0;
}

bool UShopSystem::BuyItem(int32 ItemIndex, int32 Quantity, int32& OutTotalPrice)
{
	if (!Inventory.IsValidIndex(ItemIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid item index %d"), ItemIndex);
		return false;
	}

	FShopItem& Item = Inventory[ItemIndex];

	// Check quantity
	if (Item.Quantity != -1 && Item.Quantity < Quantity)
	{
		UE_LOG(LogTemp, Warning, TEXT("Not enough %s in stock. Requested: %d, Available: %d"), *Item.ItemName, Quantity, Item.Quantity);
		return false;
	}

	// Calculate total price
	OutTotalPrice = Item.Price * Quantity;

	// Decrease quantity
	if (Item.Quantity != -1)
	{
		Item.Quantity -= Quantity;
	}

	// Record transaction
	RecordTransaction(Item.ItemName, Item.Price, true, Quantity);

	// Broadcast event
	OnItemPurchased.Broadcast(Item, Quantity);
	OnInventoryChanged.Broadcast(this);

	return true;
}

bool UShopSystem::SellItem(const FString& ItemName, int32 Price)
{
	// Record transaction
	RecordTransaction(ItemName, Price, false, 1);

	// Increase gold from sales
	TotalGoldFromSales += Price;

	// Broadcast event
	OnItemSold.Broadcast(ItemName, Price);

	return true;
}

bool UShopSystem::CanBuyItem(int32 ItemIndex, int32 PlayerGold) const
{
	if (!Inventory.IsValidIndex(ItemIndex))
	{
		return false;
	}

	const FShopItem& Item = Inventory[ItemIndex];

	// Check quantity
	if (Item.Quantity == 0)
	{
		return false;
	}

	// Check gold
	return PlayerGold >= Item.Price;
}

void UShopSystem::AddItemToShop(const FShopItem& NewItem)
{
	Inventory.Add(NewItem);
	OriginalQuantities.Add(NewItem.Quantity);
	OnInventoryChanged.Broadcast(this);
}

void UShopSystem::RemoveItemFromShop(int32 ItemIndex)
{
	if (Inventory.IsValidIndex(ItemIndex))
	{
		Inventory.RemoveAt(ItemIndex);
		OriginalQuantities.RemoveAt(ItemIndex);
		OnInventoryChanged.Broadcast(this);
	}
}

void UShopSystem::RestockItem(int32 ItemIndex, int32 Amount)
{
	if (Inventory.IsValidIndex(ItemIndex))
	{
		FShopItem& Item = Inventory[ItemIndex];
		if (Item.Quantity != -1)
		{
			Item.Quantity = FMath::Min(Item.Quantity + Amount, OriginalQuantities[ItemIndex]);
		}
		OnInventoryChanged.Broadcast(this);
	}
}

void UShopSystem::RestockAllItems()
{
	for (int32 i = 0; i < Inventory.Num(); ++i)
	{
		if (Inventory[i].Quantity != -1)
		{
			Inventory[i].Quantity = OriginalQuantities[i];
		}
	}
	OnInventoryChanged.Broadcast(this);
}

FShopItem UShopSystem::GetItemByIndex(int32 Index) const
{
	if (Inventory.IsValidIndex(Index))
	{
		return Inventory[Index];
	}
	return FShopItem();
}

FShopItem UShopSystem::GetItemByName(const FString& ItemName) const
{
	for (const FShopItem& Item : Inventory)
	{
		if (Item.ItemName.Equals(ItemName, ESearchCase::IgnoreCase))
		{
			return Item;
		}
	}
	return FShopItem();
}

int32 UShopSystem::FindItemIndex(const FString& ItemName) const
{
	for (int32 i = 0; i < Inventory.Num(); ++i)
	{
		if (Inventory[i].ItemName.Equals(ItemName, ESearchCase::IgnoreCase))
		{
			return i;
		}
	}
	return -1;
}

float UShopSystem::GetAverageItemPrice() const
{
	if (Inventory.Num() == 0)
	{
		return 0.0f;
	}

	int32 TotalPrice = 0;
	for (const FShopItem& Item : Inventory)
	{
		TotalPrice += Item.Price;
	}

	return static_cast<float>(TotalPrice) / static_cast<float>(Inventory.Num());
}

int32 UShopSystem::GetTotalInventoryValue() const
{
	int32 TotalValue = 0;

	for (const FShopItem& Item : Inventory)
	{
		int32 ItemValue = Item.Price;
		if (Item.Quantity > 0)
		{
			ItemValue *= Item.Quantity;
		}
		TotalValue += ItemValue;
	}

	return TotalValue;
}

void UShopSystem::ClearTransactionHistory()
{
	TransactionHistory.Empty();
}

int32 UShopSystem::GetTotalSales() const
{
	int32 Total = 0;

	for (const FShopTransaction& Transaction : TransactionHistory)
	{
		if (Transaction.bIsBuy)
		{
			Total += Transaction.Price * Transaction.Quantity;
		}
	}

	return Total;
}

int32 UShopSystem::GetTotalPurchases() const
{
	int32 Total = 0;

	for (const FShopTransaction& Transaction : TransactionHistory)
	{
		if (!Transaction.bIsBuy)
		{
			Total += Transaction.Price;
		}
	}

	return Total;
}

UShopSystem* UShopSystem::CreateGeneralShop(UObject* WorldContextObject)
{
	UShopSystem* Shop = NewObject<UShopSystem>(WorldContextObject);
	Shop->InitializeShop(TEXT("General Store"), EShopType::GeneralStore);

	// Health Potion
	FShopItem HealthPotion;
	HealthPotion.ItemId = 1;
	HealthPotion.ItemName = TEXT("Health Potion");
	HealthPotion.Description = TEXT("Restores 50 HP");
	HealthPotion.Price = 25;
	HealthPotion.Quantity = -1; // Unlimited
	Shop->AddItemToShop(HealthPotion);

	// Mana Potion
	FShopItem ManaPotion;
	ManaPotion.ItemId = 2;
	ManaPotion.ItemName = TEXT("Mana Potion");
	ManaPotion.Description = TEXT("Restores 30 MP");
	ManaPotion.Price = 20;
	ManaPotion.Quantity = -1; // Unlimited
	Shop->AddItemToShop(ManaPotion);

	// Antidote
	FShopItem Antidote;
	Antidote.ItemId = 3;
	Antidote.ItemName = TEXT("Antidote");
	Antidote.Description = TEXT("Cures poison");
	Antidote.Price = 15;
	Antidote.Quantity = -1; // Unlimited
	Shop->AddItemToShop(Antidote);

	// Elixir
	FShopItem Elixir;
	Elixir.ItemId = 4;
	Elixir.ItemName = TEXT("Elixir");
	Elixir.Description = TEXT("Restores HP and MP");
	Elixir.Price = 50;
	Elixir.Quantity = -1; // Unlimited
	Shop->AddItemToShop(Elixir);

	return Shop;
}

UShopSystem* UShopSystem::CreateWeaponShop(UObject* WorldContextObject)
{
	UShopSystem* Shop = NewObject<UShopSystem>(WorldContextObject);
	Shop->InitializeShop(TEXT("Weapon Shop"), EShopType::WeaponShop);

	// Iron Sword
	FShopItem IronSword;
	IronSword.ItemId = 101;
	IronSword.ItemName = TEXT("Iron Sword");
	IronSword.Description = TEXT("A sturdy iron blade");
	IronSword.Price = 100;
	IronSword.Quantity = 5;
	IronSword.bIsEquipment = true;
	IronSword.Equipment.ItemName = TEXT("Iron Sword");
	IronSword.Equipment.Slot = EEquipmentSlot::Weapon;
	IronSword.Equipment.AttackPower = 15;
	IronSword.Equipment.SellValue = 50;
	Shop->AddItemToShop(IronSword);

	// Steel Sword
	FShopItem SteelSword;
	SteelSword.ItemId = 102;
	SteelSword.ItemName = TEXT("Steel Sword");
	SteelSword.Description = TEXT("A well-crafted steel blade");
	SteelSword.Price = 250;
	SteelSword.Quantity = 3;
	SteelSword.bIsEquipment = true;
	SteelSword.Equipment.ItemName = TEXT("Steel Sword");
	SteelSword.Equipment.Slot = EEquipmentSlot::Weapon;
	SteelSword.Equipment.AttackPower = 25;
	SteelSword.Equipment.SellValue = 125;
	Shop->AddItemToShop(SteelSword);

	// Magic Staff
	FShopItem MagicStaff;
	MagicStaff.ItemId = 103;
	MagicStaff.ItemName = TEXT("Magic Staff");
	MagicStaff.Description = TEXT("Channels magical energy");
	MagicStaff.Price = 200;
	MagicStaff.Quantity = 2;
	MagicStaff.bIsEquipment = true;
	MagicStaff.Equipment.ItemName = TEXT("Magic Staff");
	MagicStaff.Equipment.Slot = EEquipmentSlot::Weapon;
	MagicStaff.Equipment.AttackPower = 10;
	MagicStaff.Equipment.MagicPowerBonus = 20;
	MagicStaff.Equipment.SellValue = 100;
	Shop->AddItemToShop(MagicStaff);

	// Dagger
	FShopItem Dagger;
	Dagger.ItemId = 104;
	Dagger.ItemName = TEXT("Dagger");
	Dagger.Description = TEXT("Fast and deadly");
	Dagger.Price = 80;
	Dagger.Quantity = 10;
	Dagger.bIsEquipment = true;
	Dagger.Equipment.ItemName = TEXT("Dagger");
	Dagger.Equipment.Slot = EEquipmentSlot::Weapon;
	Dagger.Equipment.AttackPower = 12;
	Dagger.Equipment.SellValue = 40;
	Shop->AddItemToShop(Dagger);

	return Shop;
}

UShopSystem* UShopSystem::CreateArmorShop(UObject* WorldContextObject)
{
	UShopSystem* Shop = NewObject<UShopSystem>(WorldContextObject);
	Shop->InitializeShop(TEXT("Armor Shop"), EShopType::ArmorShop);

	// Leather Armor
	FShopItem LeatherArmor;
	LeatherArmor.ItemId = 201;
	LeatherArmor.ItemName = TEXT("Leather Armor");
	LeatherArmor.Description = TEXT("Basic protection");
	LeatherArmor.Price = 150;
	LeatherArmor.Quantity = 4;
	LeatherArmor.bIsEquipment = true;
	LeatherArmor.Equipment.ItemName = TEXT("Leather Armor");
	LeatherArmor.Equipment.Slot = EEquipmentSlot::Armor;
	LeatherArmor.Equipment.DefensePower = 10;
	LeatherArmor.Equipment.SellValue = 75;
	Shop->AddItemToShop(LeatherArmor);

	// Chainmail
	FShopItem Chainmail;
	Chainmail.ItemId = 202;
	Chainmail.ItemName = TEXT("Chainmail");
	Chainmail.Description = TEXT("Sturdy metal armor");
	Chainmail.Price = 350;
	Chainmail.Quantity = 2;
	Chainmail.bIsEquipment = true;
	Chainmail.Equipment.ItemName = TEXT("Chainmail");
	Chainmail.Equipment.Slot = EEquipmentSlot::Armor;
	Chainmail.Equipment.DefensePower = 20;
	Chainmail.Equipment.SellValue = 175;
	Shop->AddItemToShop(Chainmail);

	// Iron Helmet
	FShopItem IronHelmet;
	IronHelmet.ItemId = 203;
	IronHelmet.ItemName = TEXT("Iron Helmet");
	IronHelmet.Description = TEXT("Protects your head");
	IronHelmet.Price = 100;
	IronHelmet.Quantity = 5;
	IronHelmet.bIsEquipment = true;
	IronHelmet.Equipment.ItemName = TEXT("Iron Helmet");
	IronHelmet.Equipment.Slot = EEquipmentSlot::Head;
	IronHelmet.Equipment.DefensePower = 5;
	IronHelmet.Equipment.SellValue = 50;
	Shop->AddItemToShop(IronHelmet);

	// Steel Boots
	FShopItem SteelBoots;
	SteelBoots.ItemId = 204;
	SteelBoots.ItemName = TEXT("Steel Boots");
	SteelBoots.Description = TEXT("Reinforced footwear");
	SteelBoots.Price = 120;
	SteelBoots.Quantity = 6;
	SteelBoots.bIsEquipment = true;
	SteelBoots.Equipment.ItemName = TEXT("Steel Boots");
	SteelBoots.Equipment.Slot = EEquipmentSlot::Feet;
	SteelBoots.Equipment.DefensePower = 8;
	SteelBoots.Equipment.SellValue = 60;
	Shop->AddItemToShop(SteelBoots);

	// Magic Ring
	FShopItem MagicRing;
	MagicRing.ItemId = 205;
	MagicRing.ItemName = TEXT("Magic Ring");
	MagicRing.Description = TEXT("Enhances magic power");
	MagicRing.Price = 300;
	MagicRing.Quantity = 1;
	MagicRing.bIsEquipment = true;
	MagicRing.Equipment.ItemName = TEXT("Magic Ring");
	MagicRing.Equipment.Slot = EEquipmentSlot::Accessory;
	MagicRing.Equipment.MagicPowerBonus = 15;
	MagicRing.Equipment.SellValue = 150;
	Shop->AddItemToShop(MagicRing);

	return Shop;
}

UShopSystem* UShopSystem::CreateAlchemyShop(UObject* WorldContextObject)
{
	UShopSystem* Shop = NewObject<UShopSystem>(WorldContextObject);
	Shop->InitializeShop(TEXT("Alchemy Shop"), EShopType::AlchemyShop);

	// Lesser Health Potion
	FShopItem LesserHealthPotion;
	LesserHealthPotion.ItemId = 301;
	LesserHealthPotion.ItemName = TEXT("Lesser Health Potion");
	LesserHealthPotion.Description = TEXT("Restores 25 HP");
	LesserHealthPotion.Price = 10;
	LesserHealthPotion.Quantity = -1;
	Shop->AddItemToShop(LesserHealthPotion);

	// Greater Health Potion
	FShopItem GreaterHealthPotion;
	GreaterHealthPotion.ItemId = 302;
	GreaterHealthPotion.ItemName = TEXT("Greater Health Potion");
	GreaterHealthPotion.Description = TEXT("Restores 100 HP");
	GreaterHealthPotion.Price = 75;
	GreaterHealthPotion.Quantity = -1;
	Shop->AddItemToShop(GreaterHealthPotion);

	// Stamina Potion
	FShopItem StaminaPotion;
	StaminaPotion.ItemId = 303;
	StaminaPotion.ItemName = TEXT("Stamina Potion");
	StaminaPotion.Description = TEXT("Restores stamina");
	StaminaPotion.Price = 30;
	StaminaPotion.Quantity = -1;
	Shop->AddItemToShop(StaminaPotion);

	// Poison
	FShopItem Poison;
	Poison.ItemId = 304;
	Poison.ItemName = TEXT("Poison");
	Poison.Description = TEXT("Inflicts poison damage");
	Poison.Price = 40;
	Poison.Quantity = -1;
	Shop->AddItemToShop(Poison);

	return Shop;
}

UShopSystem* UShopSystem::CreateBlacksmithShop(UObject* WorldContextObject)
{
	UShopSystem* Shop = NewObject<UShopSystem>(WorldContextObject);
	Shop->InitializeShop(TEXT("Blacksmith"), EShopType::Blacksmith);

	// Legendary Sword
	FShopItem LegendarySword;
	LegendarySword.ItemId = 401;
	LegendarySword.ItemName = TEXT("Legendary Sword");
	LegendarySword.Description = TEXT("A mythical blade of great power");
	LegendarySword.Price = 2000;
	LegendarySword.Quantity = 1;
	LegendarySword.bIsEquipment = true;
	LegendarySword.Equipment.ItemName = TEXT("Legendary Sword");
	LegendarySword.Equipment.Slot = EEquipmentSlot::Weapon;
	LegendarySword.Equipment.AttackPower = 100;
	LegendarySword.Equipment.Quality = EEquipmentQuality::Mythic;
	LegendarySword.Equipment.SellValue = 1000;
	Shop->AddItemToShop(LegendarySword);

	return Shop;
}

FString UShopSystem::GetShopDescription() const
{
	FString Description = FString::Printf(
		TEXT("=== %s ===\n"),
		*ShopName
	);

	Description += FString::Printf(
		TEXT("Inventory Size: %d items\n"),
		Inventory.Num()
	);

	Description += FString::Printf(
		TEXT("Average Price: %.1f gold\n"),
		GetAverageItemPrice()
	);

	Description += FString::Printf(
		TEXT("Total Value: %d gold\n"),
		GetTotalInventoryValue()
	);

	Description += FString::Printf(
		TEXT("Total Sales: %d gold\n"),
		GetTotalSales()
	);

	return Description;
}

void UShopSystem::DisplayShopInventory() const
{
	UE_LOG(LogTemp, Warning, TEXT("=== %s ==="), *ShopName);
	UE_LOG(LogTemp, Warning, TEXT("Total items: %d"), Inventory.Num());

	for (int32 i = 0; i < Inventory.Num(); ++i)
	{
		const FShopItem& Item = Inventory[i];
		FString QuantityStr = Item.Quantity == -1 ? TEXT("Unlimited") : FString::Printf(TEXT("%d"), Item.Quantity);
		UE_LOG(LogTemp, Warning, TEXT("[%d] %s - %d gold (Qty: %s)"), i, *Item.ItemName, Item.Price, *QuantityStr);
	}
}

void UShopSystem::RecordTransaction(const FString& ItemName, int32 Price, bool bIsBuy, int32 Quantity)
{
	FShopTransaction Transaction;
	Transaction.ItemName = ItemName;
	Transaction.Price = Price;
	Transaction.bIsBuy = bIsBuy;
	Transaction.Quantity = Quantity;
	Transaction.TransactionTime = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;

	TransactionHistory.Add(Transaction);
}
