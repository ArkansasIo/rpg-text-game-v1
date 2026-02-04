#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "EquipmentSystem.generated.h"

// Equipment slot enumeration
UENUM(BlueprintType)
enum class EEquipmentSlotType : uint8
{
	EES_Weapon		UMETA(DisplayName = "Weapon"),
	EES_Armor		UMETA(DisplayName = "Armor"),
	EES_Helmet		UMETA(DisplayName = "Helmet"),
	EES_Boots		UMETA(DisplayName = "Boots"),
	EES_Accessory	UMETA(DisplayName = "Accessory"),
	EES_Offhand		UMETA(DisplayName = "Off-Hand"),
	EES_None		UMETA(DisplayName = "None")
};

// Equipment quality tiers
UENUM(BlueprintType)
enum class EEquipmentQuality : uint8
{
	EEQ_Common		UMETA(DisplayName = "Common"),
	EEQ_Uncommon	UMETA(DisplayName = "Uncommon"),
	EEQ_Rare		UMETA(DisplayName = "Rare"),
	EEQ_Epic		UMETA(DisplayName = "Epic"),
	EEQ_Legendary	UMETA(DisplayName = "Legendary"),
	EEQ_Mythic		UMETA(DisplayName = "Mythic")
};

// Equipment item structure
USTRUCT(BlueprintType)
struct FEquipmentItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	FString EquipmentID = TEXT("item_001");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	FString EquipmentName = TEXT("Iron Sword");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	FString Description = TEXT("A sturdy iron blade");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	EEquipmentSlotType EquipmentSlot = EEquipmentSlotType::EES_Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	EEquipmentQuality Quality = EEquipmentQuality::EEQ_Common;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float AttackBonus = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float DefenseBonus = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float MagicPowerBonus = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float HealthBonus = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float ManaBonus = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float StaminaBonus = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 SellValue = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 RequiredLevel = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString IconPath = TEXT("/Engine/EditorResources/S_ItemIcon");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float Weight = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	bool bIsUnique = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	bool bIsBoundToCharacter = false;

	FString GetQualityColorHex() const
	{
		switch (Quality)
		{
			case EEquipmentQuality::EEQ_Common:
				return TEXT("#FFFFFF");		// White
			case EEquipmentQuality::EEQ_Uncommon:
				return TEXT("#1EFF00");		// Green
			case EEquipmentQuality::EEQ_Rare:
				return TEXT("#0070DD");		// Blue
			case EEquipmentQuality::EEQ_Epic:
				return TEXT("#A335EE");		// Purple
			case EEquipmentQuality::EEQ_Legendary:
				return TEXT("#FF8000");		// Orange
			case EEquipmentQuality::EEQ_Mythic:
				return TEXT("#E6CC80");		// Gold
			default:
				return TEXT("#FFFFFF");
		}
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_Two(FOnEquipmentChanged, const FEquipmentItem&, Equipment, bool, bEquipped);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEquipmentStatsChanged);

/**
 * Equipment Management System
 * Handles equipping/unequipping items and calculating bonuses
 */
UCLASS(BlueprintType)
class RPGPROJECT_API UEquipmentSystem : public UObject
{
	GENERATED_BODY()

public:
	UEquipmentSystem();

	// ==================== Equipment Slots ====================

	UPROPERTY(BlueprintReadWrite, Category = "Equipment")
	FEquipmentItem EquippedWeapon;

	UPROPERTY(BlueprintReadWrite, Category = "Equipment")
	FEquipmentItem EquippedArmor;

	UPROPERTY(BlueprintReadWrite, Category = "Equipment")
	FEquipmentItem EquippedHelmet;

	UPROPERTY(BlueprintReadWrite, Category = "Equipment")
	FEquipmentItem EquippedBoots;

	UPROPERTY(BlueprintReadWrite, Category = "Equipment")
	FEquipmentItem EquippedAccessory;

	UPROPERTY(BlueprintReadWrite, Category = "Equipment")
	FEquipmentItem EquippedOffhand;

	// ==================== Events ====================

	UPROPERTY(BlueprintAssignable, Category = "Equipment Events")
	FOnEquipmentChanged OnEquipmentChanged;

	UPROPERTY(BlueprintAssignable, Category = "Equipment Events")
	FOnEquipmentStatsChanged OnEquipmentStatsChanged;

	// ==================== Equipment Management ====================

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void EquipItem(const FEquipmentItem& Item);

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void UnequipItem(EEquipmentSlotType Slot);

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	FEquipmentItem* GetEquippedItem(EEquipmentSlotType Slot);

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void SwapEquipment(EEquipmentSlotType Slot, const FEquipmentItem& NewItem);

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void ClearAllEquipment();

	// ==================== Stat Calculations ====================

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	float GetTotalAttackBonus() const;

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	float GetTotalDefenseBonus() const;

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	float GetTotalMagicPowerBonus() const;

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	float GetTotalHealthBonus() const;

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	float GetTotalManaBonus() const;

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	float GetTotalStaminaBonus() const;

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	float GetTotalWeight() const;

	// ==================== Equipment Info ====================

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	int32 GetEquippedItemCount() const;

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	bool IsSlotEquipped(EEquipmentSlotType Slot) const;

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	FString GetEquipmentSetDescription() const;

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void DisplayEquipmentStats();

private:
	void NotifyEquipmentChanged(const FEquipmentItem& Item, bool bEquipped);
	void NotifyStatsChanged();
};
