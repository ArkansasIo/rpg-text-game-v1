#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Inventory/EquipmentSystem.h"
#include "ShopSystem.generated.h"

// Shop type enumeration
UENUM(BlueprintType)
enum class EShopType : uint8
{
	GeneralStore,
	WeaponShop,
	ArmorShop,
	AlchemyShop,
	Tavern,
	Blacksmith,
	Enchanter
};

// Shop inventory item
USTRUCT(BlueprintType)
struct FShopItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop")
	int32 ItemId = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop")
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop")
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop")
	int32 Price = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop")
	int32 Quantity = -1; // -1 means unlimited

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop")
	bool bIsEquipment = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop")
	FEquipmentItem Equipment;
};

// Shop trade log
USTRUCT(BlueprintType)
struct FShopTransaction
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop")
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop")
	int32 Price = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop")
	bool bIsBuy = true; // true = player bought, false = player sold

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop")
	float TransactionTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop")
	int32 Quantity = 1;
};

// Event delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_Two(FOnItemPurchased, const FShopItem&, Item, int32, Quantity);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_Two(FOnItemSold, const FString&, ItemName, int32, Price);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_One(FOnShopInventoryChanged, UShopSystem*, Shop);

/**
 * Shop System - handles all shop functionality including buying/selling
 */
UCLASS(Blueprintable, BlueprintType)
class RPGPROJECT_API UShopSystem : public UObject
{
	GENERATED_BODY()

public:
	UShopSystem();

	// Initialization
	UFUNCTION(BlueprintCallable, Category = "Shop")
	void InitializeShop(const FString& InShopName, EShopType InShopType);

	// Buying and selling
	UFUNCTION(BlueprintCallable, Category = "Shop")
	bool BuyItem(int32 ItemIndex, int32 Quantity, int32& OutTotalPrice);

	UFUNCTION(BlueprintCallable, Category = "Shop")
	bool SellItem(const FString& ItemName, int32 Price);

	UFUNCTION(BlueprintCallable, Category = "Shop")
	bool CanBuyItem(int32 ItemIndex, int32 PlayerGold) const;

	// Shop inventory management
	UFUNCTION(BlueprintCallable, Category = "Shop")
	void AddItemToShop(const FShopItem& NewItem);

	UFUNCTION(BlueprintCallable, Category = "Shop")
	void RemoveItemFromShop(int32 ItemIndex);

	UFUNCTION(BlueprintCallable, Category = "Shop")
	void RestockItem(int32 ItemIndex, int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Shop")
	void RestockAllItems();

	// Getters
	UFUNCTION(BlueprintCallable, Category = "Shop")
	const FString& GetShopName() const { return ShopName; }

	UFUNCTION(BlueprintCallable, Category = "Shop")
	EShopType GetShopType() const { return ShopType; }

	UFUNCTION(BlueprintCallable, Category = "Shop")
	const TArray<FShopItem>& GetInventory() const { return Inventory; }

	UFUNCTION(BlueprintCallable, Category = "Shop")
	FShopItem GetItemByIndex(int32 Index) const;

	UFUNCTION(BlueprintCallable, Category = "Shop")
	FShopItem GetItemByName(const FString& ItemName) const;

	UFUNCTION(BlueprintCallable, Category = "Shop")
	int32 GetInventorySize() const { return Inventory.Num(); }

	UFUNCTION(BlueprintCallable, Category = "Shop")
	int32 FindItemIndex(const FString& ItemName) const;

	UFUNCTION(BlueprintCallable, Category = "Shop")
	float GetAverageItemPrice() const;

	UFUNCTION(BlueprintCallable, Category = "Shop")
	int32 GetTotalInventoryValue() const;

	// History/logs
	UFUNCTION(BlueprintCallable, Category = "Shop")
	const TArray<FShopTransaction>& GetTransactionHistory() const { return TransactionHistory; }

	UFUNCTION(BlueprintCallable, Category = "Shop")
	void ClearTransactionHistory();

	UFUNCTION(BlueprintCallable, Category = "Shop")
	int32 GetTotalSales() const;

	UFUNCTION(BlueprintCallable, Category = "Shop")
	int32 GetTotalPurchases() const;

	// Shop types factory methods
	UFUNCTION(BlueprintCallable, Category = "Shop", meta = (WorldContext = "WorldContextObject"))
	static UShopSystem* CreateGeneralShop(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Shop", meta = (WorldContext = "WorldContextObject"))
	static UShopSystem* CreateWeaponShop(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Shop", meta = (WorldContext = "WorldContextObject"))
	static UShopSystem* CreateArmorShop(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Shop", meta = (WorldContext = "WorldContextObject"))
	static UShopSystem* CreateAlchemyShop(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Shop", meta = (WorldContext = "WorldContextObject"))
	static UShopSystem* CreateBlacksmithShop(UObject* WorldContextObject);

	// Utility
	UFUNCTION(BlueprintCallable, Category = "Shop")
	FString GetShopDescription() const;

	UFUNCTION(BlueprintCallable, Category = "Shop")
	void DisplayShopInventory() const;

	// Events
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Events")
	FOnItemPurchased OnItemPurchased;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Events")
	FOnItemSold OnItemSold;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Events")
	FOnShopInventoryChanged OnInventoryChanged;

protected:
	// Shop information
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shop")
	FString ShopName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shop")
	EShopType ShopType;

	// Shop inventory
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shop")
	TArray<FShopItem> Inventory;

	// Original quantities for restocking
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shop")
	TArray<int32> OriginalQuantities;

	// Transaction history
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shop")
	TArray<FShopTransaction> TransactionHistory;

	// Shop statistics
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shop")
	int32 TotalGoldFromSales = 0;

private:
	void RecordTransaction(const FString& ItemName, int32 Price, bool bIsBuy, int32 Quantity = 1);
};
