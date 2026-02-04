#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../RPGTypes.h"
#include "InventorySystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_One(FOnItemAddedDelegate, const FInventoryItem&, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_One(FOnItemRemovedDelegate, const FInventoryItem&, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_Two(FOnInventoryChangedDelegate, int32, ItemCount, float, InventoryWeight);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_One(FOnEquipmentChangedDelegate, const FEquipmentItem&, EquippedItem);

USTRUCT(BlueprintType)
struct FInventoryItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemRarity Rarity = EItemRarity::Common;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemType ItemType = EItemType::Consumable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Quantity = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Weight = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SellValue = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bStackable = true;
};

USTRUCT(BlueprintType)
struct FEquipmentItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FInventoryItem Item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEquipmentSlot EquipmentSlot = EEquipmentSlot::Head;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ArmorBonus = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageBonus = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RequiredLevel = 1;
};

/**
 * Inventory & Equipment Management System
 */
UCLASS(BlueprintType)
class RPGPROJECT_API UInventorySystem : public UObject
{
	GENERATED_BODY()

public:
	UInventorySystem();

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	TArray<FInventoryItem> InventorySlots;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	TMap<EEquipmentSlot, FEquipmentItem> EquippedItems;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	float MaxInventoryWeight = 50.0f;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	int32 InventoryCapacity = 20;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	int32 Gold = 0;

	// Delegates
	UPROPERTY(BlueprintAssignable, Category = "Inventory Events")
	FOnItemAddedDelegate OnItemAdded;

	UPROPERTY(BlueprintAssignable, Category = "Inventory Events")
	FOnItemRemovedDelegate OnItemRemoved;

	UPROPERTY(BlueprintAssignable, Category = "Inventory Events")
	FOnInventoryChangedDelegate OnInventoryChanged;

	UPROPERTY(BlueprintAssignable, Category = "Equipment Events")
	FOnEquipmentChangedDelegate OnEquipmentChanged;

	// Inventory Functions
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItem(const FInventoryItem& NewItem);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool RemoveItem(const FString& ItemID, int32 Quantity = 1);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FInventoryItem* FindItem(const FString& ItemID);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void UseItem(const FString& ItemID);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void DropItem(const FString& ItemID, int32 Quantity = 1);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	float GetCurrentInventoryWeight() const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool IsInventoryFull() const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SortInventory();

	// Equipment Functions
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	bool EquipItem(const FString& ItemID, EEquipmentSlot Slot);

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	bool UnequipItem(EEquipmentSlot Slot);

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	FEquipmentItem* GetEquippedItem(EEquipmentSlot Slot);

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	float CalculateTotalArmorBonus() const;

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	float CalculateTotalDamageBonus() const;

	// Gold Functions
	UFUNCTION(BlueprintCallable, Category = "Currency")
	void AddGold(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Currency")
	bool SpendGold(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Currency")
	int32 GetGold() const;

	// Utility
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	int32 GetAvailableSlots() const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void ClearInventory();

private:
	void NotifyInventoryChanged();
	bool CanAddItem(const FInventoryItem& Item) const;
};
