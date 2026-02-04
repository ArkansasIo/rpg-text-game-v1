// InventoryComponent.h
// Complete inventory system with 40-slot grid

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RPGTypes.h"
#include "InventoryComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RPGPROJECT_API UInventoryComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UInventoryComponent();

    virtual void BeginPlay() override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    // ==================== INVENTORY ====================
    
    UPROPERTY(ReplicatedUsing = OnRep_Inventory, BlueprintReadOnly, Category = "Inventory")
    TArray<FInventorySlot> InventorySlots;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
    int32 MaxSlots = 40;

    UFUNCTION()
    void OnRep_Inventory();

    // ==================== FUNCTIONS ====================
    
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool AddItem(FRPGItemData Item, int32 Quantity = 1);

    UFUNCTION(Server, Reliable, WithValidation, Category = "Inventory")
    void Server_AddItem(FRPGItemData Item, int32 Quantity);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool RemoveItem(int32 SlotIndex, int32 Quantity = 1);

    UFUNCTION(Server, Reliable, WithValidation, Category = "Inventory")
    void Server_RemoveItem(int32 SlotIndex, int32 Quantity);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool UseItem(int32 SlotIndex);

    UFUNCTION(Server, Reliable, WithValidation, Category = "Inventory")
    void Server_UseItem(int32 SlotIndex);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool MoveItem(int32 FromSlot, int32 ToSlot);

    UFUNCTION(Server, Reliable, WithValidation, Category = "Inventory")
    void Server_MoveItem(int32 FromSlot, int32 ToSlot);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void SortInventory();

    UFUNCTION(BlueprintPure, Category = "Inventory")
    int32 GetItemCount(int32 ItemID) const;

    UFUNCTION(BlueprintPure, Category = "Inventory")
    bool HasItem(int32 ItemID, int32 Quantity = 1) const;

    UFUNCTION(BlueprintPure, Category = "Inventory")
    int32 GetEmptySlotCount() const;

    UFUNCTION(BlueprintPure, Category = "Inventory")
    FInventorySlot GetSlot(int32 SlotIndex) const;

    // ==================== EVENTS ====================
    
    UPROPERTY(BlueprintAssignable, Category = "Inventory")
    FOnItemAdded OnItemAdded;

protected:
    int32 FindEmptySlot() const;
    int32 FindItemSlot(int32 ItemID) const;
    bool CanStackItem(const FRPGItemData& Item, int32 SlotIndex) const;
};


// InventoryComponent.cpp
#include "InventoryComponent.h"
#include "Net/UnrealNetwork.h"
#include "RPGCharacter.h"

UInventoryComponent::UInventoryComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    SetIsReplicatedByDefault(true);
}

void UInventoryComponent::BeginPlay()
{
    Super::BeginPlay();

    // Initialize inventory slots
    if (GetOwnerRole() == ROLE_Authority)
    {
        InventorySlots.SetNum(MaxSlots);
        for (int32 i = 0; i < MaxSlots; i++)
        {
            InventorySlots[i].SlotIndex = i;
            InventorySlots[i].bIsEmpty = true;
            InventorySlots[i].Quantity = 0;
        }
    }
}

void UInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(UInventoryComponent, InventorySlots);
}

void UInventoryComponent::OnRep_Inventory()
{
    // Update UI when inventory changes
}

bool UInventoryComponent::AddItem(FRPGItemData Item, int32 Quantity)
{
    if (GetOwnerRole() < ROLE_Authority)
    {
        Server_AddItem(Item, Quantity);
        return true;
    }

    // Check for existing stacks
    if (Item.MaxStackSize > 1)
    {
        int32 ExistingSlot = FindItemSlot(Item.ItemID);
        if (ExistingSlot != -1 && CanStackItem(Item, ExistingSlot))
        {
            InventorySlots[ExistingSlot].Quantity += Quantity;
            OnItemAdded.Broadcast(Item, Quantity, ExistingSlot);
            return true;
        }
    }

    // Find empty slot
    int32 EmptySlot = FindEmptySlot();
    if (EmptySlot != -1)
    {
        InventorySlots[EmptySlot].ItemData = Item;
        InventorySlots[EmptySlot].Quantity = Quantity;
        InventorySlots[EmptySlot].bIsEmpty = false;
        OnItemAdded.Broadcast(Item, Quantity, EmptySlot);
        return true;
    }

    return false; // Inventory full
}

void UInventoryComponent::Server_AddItem_Implementation(FRPGItemData Item, int32 Quantity)
{
    AddItem(Item, Quantity);
}

bool UInventoryComponent::Server_AddItem_Validate(FRPGItemData Item, int32 Quantity)
{
    return Quantity > 0 && Quantity <= 999;
}

bool UInventoryComponent::RemoveItem(int32 SlotIndex, int32 Quantity)
{
    if (GetOwnerRole() < ROLE_Authority)
    {
        Server_RemoveItem(SlotIndex, Quantity);
        return true;
    }

    if (SlotIndex < 0 || SlotIndex >= InventorySlots.Num())
        return false;

    FInventorySlot& Slot = InventorySlots[SlotIndex];
    if (Slot.bIsEmpty)
        return false;

    Slot.Quantity -= Quantity;
    if (Slot.Quantity <= 0)
    {
        Slot.bIsEmpty = true;
        Slot.Quantity = 0;
    }

    return true;
}

void UInventoryComponent::Server_RemoveItem_Implementation(int32 SlotIndex, int32 Quantity)
{
    RemoveItem(SlotIndex, Quantity);
}

bool UInventoryComponent::Server_RemoveItem_Validate(int32 SlotIndex, int32 Quantity)
{
    return SlotIndex >= 0 && Quantity > 0;
}

bool UInventoryComponent::UseItem(int32 SlotIndex)
{
    if (GetOwnerRole() < ROLE_Authority)
    {
        Server_UseItem(SlotIndex);
        return true;
    }

    if (SlotIndex < 0 || SlotIndex >= InventorySlots.Num())
        return false;

    FInventorySlot& Slot = InventorySlots[SlotIndex];
    if (Slot.bIsEmpty)
        return false;

    // Handle consumables
    if (Slot.ItemData.Type == EItemType::Consumable)
    {
        ARPGCharacter* Character = Cast<ARPGCharacter>(GetOwner());
        if (Character)
        {
            // Apply consumable effects (healing, mana, buffs, etc.)
            // This would be implemented based on item data
            
            RemoveItem(SlotIndex, 1);
            return true;
        }
    }

    return false;
}

void UInventoryComponent::Server_UseItem_Implementation(int32 SlotIndex)
{
    UseItem(SlotIndex);
}

bool UInventoryComponent::Server_UseItem_Validate(int32 SlotIndex)
{
    return SlotIndex >= 0;
}

bool UInventoryComponent::MoveItem(int32 FromSlot, int32 ToSlot)
{
    if (GetOwnerRole() < ROLE_Authority)
    {
        Server_MoveItem(FromSlot, ToSlot);
        return true;
    }

    if (FromSlot < 0 || FromSlot >= MaxSlots || ToSlot < 0 || ToSlot >= MaxSlots)
        return false;

    FInventorySlot Temp = InventorySlots[FromSlot];
    InventorySlots[FromSlot] = InventorySlots[ToSlot];
    InventorySlots[ToSlot] = Temp;

    return true;
}

void UInventoryComponent::Server_MoveItem_Implementation(int32 FromSlot, int32 ToSlot)
{
    MoveItem(FromSlot, ToSlot);
}

bool UInventoryComponent::Server_MoveItem_Validate(int32 FromSlot, int32 ToSlot)
{
    return FromSlot >= 0 && ToSlot >= 0;
}

void UInventoryComponent::SortInventory()
{
    // Sort inventory by rarity, then type, then level
    InventorySlots.Sort([](const FInventorySlot& A, const FInventorySlot& B)
    {
        if (A.bIsEmpty && !B.bIsEmpty) return false;
        if (!A.bIsEmpty && B.bIsEmpty) return true;
        if (A.bIsEmpty && B.bIsEmpty) return false;

        if (A.ItemData.Rarity != B.ItemData.Rarity)
            return A.ItemData.Rarity > B.ItemData.Rarity;
        
        if (A.ItemData.Type != B.ItemData.Type)
            return A.ItemData.Type < B.ItemData.Type;

        return A.ItemData.RequiredLevel > B.ItemData.RequiredLevel;
    });
}

int32 UInventoryComponent::GetItemCount(int32 ItemID) const
{
    int32 Count = 0;
    for (const FInventorySlot& Slot : InventorySlots)
    {
        if (!Slot.bIsEmpty && Slot.ItemData.ItemID == ItemID)
        {
            Count += Slot.Quantity;
        }
    }
    return Count;
}

bool UInventoryComponent::HasItem(int32 ItemID, int32 Quantity) const
{
    return GetItemCount(ItemID) >= Quantity;
}

int32 UInventoryComponent::GetEmptySlotCount() const
{
    int32 Count = 0;
    for (const FInventorySlot& Slot : InventorySlots)
    {
        if (Slot.bIsEmpty)
            Count++;
    }
    return Count;
}

FInventorySlot UInventoryComponent::GetSlot(int32 SlotIndex) const
{
    if (SlotIndex >= 0 && SlotIndex < InventorySlots.Num())
        return InventorySlots[SlotIndex];
    
    return FInventorySlot();
}

int32 UInventoryComponent::FindEmptySlot() const
{
    for (int32 i = 0; i < InventorySlots.Num(); i++)
    {
        if (InventorySlots[i].bIsEmpty)
            return i;
    }
    return -1;
}

int32 UInventoryComponent::FindItemSlot(int32 ItemID) const
{
    for (int32 i = 0; i < InventorySlots.Num(); i++)
    {
        if (!InventorySlots[i].bIsEmpty && InventorySlots[i].ItemData.ItemID == ItemID)
            return i;
    }
    return -1;
}

bool UInventoryComponent::CanStackItem(const FRPGItemData& Item, int32 SlotIndex) const
{
    if (SlotIndex < 0 || SlotIndex >= InventorySlots.Num())
        return false;

    const FInventorySlot& Slot = InventorySlots[SlotIndex];
    return !Slot.bIsEmpty && 
           Slot.ItemData.ItemID == Item.ItemID && 
           Slot.Quantity < Item.MaxStackSize;
}
