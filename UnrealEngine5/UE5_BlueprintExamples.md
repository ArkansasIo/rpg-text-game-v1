# ?? UNREAL ENGINE 5 - BLUEPRINT EXAMPLES

## Complete Blueprint System Examples for Your RPG

---

## ?? Data Table Access Examples

### **1. Get Item by ID**

**Blueprint Graph:**
```
Event BeginPlay
  ?
Get Data Table Row (DT_Items)
  - Data Table: DT_Items
  - Row Name: [ItemID as Name]
  - Out Row ? [FRPGItemData]
  ?
Branch (Is Valid?)
  - True ? Display Item Info
  - False ? Log Error
```

**C++ Equivalent:**
```cpp
FRPGItemData* ItemData = ItemDataTable->FindRow<FRPGItemData>(
    FName(*FString::FromInt(ItemID)), 
    TEXT("ItemLookup")
);

if (ItemData)
{
    // Use item data
    ItemName = ItemData->Name;
    ItemDamage = ItemData->Stats.Damage;
}
```

---

### **2. Get All Items by Rarity**

**Blueprint Function:**
```
Function: GetItemsByRarity
Input: Rarity (Enum)
Output: Array of FRPGItemData

Logic:
  Get Data Table Row Names (DT_Items)
    ?
  For Each Loop
    ?
  Get Data Table Row
    ?
  Branch: Row.Rarity == Input Rarity?
    - True ? Add to Array
    ?
  Return Array
```

---

### **3. Display Item Tooltip (Widget)**

**Widget Blueprint (WBP_ItemTooltip):**

Variables:
- ItemData (FRPGItemData)

Widget Hierarchy:
```
Canvas Panel
??? Border
    ??? Vertical Box
        ??? Text Block (Item Name) - Bind: ItemData.Name
        ??? Text Block (Description) - Bind: ItemData.Description
        ??? Horizontal Box
        ?   ??? Image (Icon) - Bind: ItemData.Icon
        ?   ??? Text Block (Type) - Bind: ItemData.Type
        ??? Text Block (Stats) - Bind: Format Stats
        ??? Text Block (Value) - Bind: ItemData.VendorPrice
```

**Format Stats Function:**
```
Function: FormatStats
Input: ItemData (FRPGItemData)
Output: Text

Logic:
  String = ""
  
  If ItemData.Stats.Damage > 0:
    Append: "Damage: {Damage}\n"
  
  If ItemData.Stats.Armor > 0:
    Append: "Armor: {Armor}\n"
  
  If ItemData.Stats.Strength > 0:
    Append: "+{Strength} Strength\n"
    
  Return as Text
```

---

## ?? Character Creation System

### **Blueprint: BP_CharacterCreator**

**Variables:**
```
- SelectedRace (FRPGRaceData)
- SelectedClass (FRPGClassData)
- SelectedSpecialization (String)
- CharacterName (String)
- PreviewMesh (Skeletal Mesh Component)
```

**Event Graph:**
```
Event BeginPlay
  ?
Load Race Data (DT_Races)
  ?
Populate Race Selection UI
  ?
Load Class Data (DT_Classes)
  ?
Populate Class Selection UI
```

**Function: OnRaceSelected**
```
Input: RaceIndex (Int)

Get Data Table Row (DT_Races)
  - Row Name: Race Names[RaceIndex]
  ?
Set SelectedRace = Row Data
  ?
Update Preview Mesh
  ?
Display Race Description
  ?
Show Racial Bonuses:
  - +{Strength} Strength
  - +{Agility} Agility
  - Abilities: {RacialAbilities}
```

**Function: CreateCharacter**
```
Validate Inputs
  - Check Name not empty
  - Check Race selected
  - Check Class selected
  ?
Create Character Struct:
  - Name = CharacterName
  - Race = SelectedRace.RaceName
  - Class = SelectedClass.ClassName
  - BaseStats = SelectedRace.BaseStats + SelectedClass.BaseStats
  ?
Save to Game Instance
  ?
Open Game World
```

---

## ?? Combat System

### **Blueprint: BP_CombatComponent**

**Variables:**
```
- CurrentHealth (Float)
- MaxHealth (Float)
- Damage (Int)
- Armor (Int)
- EquippedWeapon (FRPGItemData)
- StatusEffects (Array of FStatusEffect)
```

**Function: DealDamage**
```
Input: Target (Actor), BaseDamage (Int)

Calculate Final Damage:
  FinalDamage = BaseDamage
  
  If EquippedWeapon is valid:
    FinalDamage += EquippedWeapon.Stats.Damage
    FinalDamage += Random(Min, Max Weapon Damage)
  
  Apply Crit Chance:
    Roll = Random Float (0-100)
    If Roll < CritChance:
      FinalDamage *= 2.0
      Show "CRITICAL!" Text
  
  Apply Target Armor:
    DamageReduction = Target.Armor * 0.01
    FinalDamage *= (1 - DamageReduction)
  
  Deal Damage to Target:
    Target.TakeDamage(FinalDamage)
  
  Show Damage Number
  Play Hit Effect
```

**Function: TakeDamage**
```
Input: Damage (Float)

CurrentHealth -= Damage
  ?
Update Health Bar UI
  ?
Play Hurt Animation
  ?
If CurrentHealth <= 0:
  Die()
```

---

## ?? Inventory System

### **Blueprint: BP_InventoryComponent**

**Variables:**
```
- InventorySlots (Array of FInventorySlot)
- MaxSlots (Int) = 40
- EquippedItems (Map<EEquipmentSlot, FRPGItemData>)
```

**Struct: FInventorySlot**
```
- ItemData (FRPGItemData)
- Quantity (Int)
- IsEmpty (Bool)
```

**Function: AddItem**
```
Input: ItemData (FRPGItemData), Quantity (Int)
Output: Success (Bool)

Check if stackable:
  If ItemData.MaxStackSize > 1:
    Find existing stack
    If found:
      Add to stack
      Return True
  
Find empty slot:
  For Each slot in InventorySlots:
    If slot.IsEmpty:
      slot.ItemData = ItemData
      slot.Quantity = Quantity
      slot.IsEmpty = False
      
      Update Inventory UI
      Return True
  
  Return False (inventory full)
```

**Function: EquipItem**
```
Input: ItemData (FRPGItemData)

Determine Equipment Slot:
  Slot = Parse ItemData.Stats.Slot
  
Check if slot occupied:
  If EquippedItems contains Slot:
    Unequip current item
  
Equip new item:
  EquippedItems[Slot] = ItemData
  Remove from Inventory
  
Apply Stats:
  Add ItemData.Stats.Strength to PlayerStrength
  Add ItemData.Stats.Armor to PlayerArmor
  
Update Character Mesh:
  Attach mesh to socket
  
Update UI
```

---

## ??? Zone System

### **Blueprint: BP_ZoneManager**

**Function: LoadZone**
```
Input: ZoneID (Int)

Show Loading Screen
  ?
Get Zone Data (DT_Zones)
  - Row Name: ZoneID
  ?
Unload Current Zone
  ?
Load New Level:
  - Level Name: ZoneData.LevelAsset
  ?
Spawn Player at Entry Point
  ?
Load Zone NPCs (from DT_NPCs)
  ?
Load Zone Enemies (from DT_EnemySpawns)
  ?
Initialize Zone Services:
  - If HasBank: Enable Bank
  - If HasInn: Enable Inn
  - If HasAuctionHouse: Enable AH
  ?
Hide Loading Screen
  ?
Play Zone Music
```

---

## ?? Quest System

### **Blueprint: BP_QuestComponent**

**Variables:**
```
- ActiveQuests (Array of FQuestProgress)
- CompletedQuests (Array of Int) // Quest IDs
```

**Struct: FQuestProgress**
```
- QuestData (FRPGQuestData)
- ObjectiveProgress (Array of Int)
- IsComplete (Bool)
```

**Function: AcceptQuest**
```
Input: QuestID (Int)

Get Quest Data (DT_Quests)
  ?
Check Requirements:
  - Player Level >= RequiredLevel
  - Not already active
  - Not already completed
  ?
Create Quest Progress:
  Progress.QuestData = Data
  Progress.ObjectiveProgress = [0, 0, 0...]
  Progress.IsComplete = False
  ?
Add to ActiveQuests
  ?
Show Quest Accepted UI
  ?
Update Quest Log
```

**Function: UpdateQuestProgress**
```
Input: ObjectiveType (String), TargetID (Int), Amount (Int)

For Each quest in ActiveQuests:
  For Each objective in quest.Objectives:
    If objective.Type == ObjectiveType:
      If objective.TargetID == TargetID:
        objective.CurrentProgress += Amount
        
        If objective.CurrentProgress >= objective.RequiredCount:
          Mark Objective Complete
          Show "Objective Complete" notification
          
          Check if all objectives complete:
            If yes:
              quest.IsComplete = True
              Show "Quest Complete!" notification
```

---

## ?? Shop System

### **Widget Blueprint: WBP_ShopUI**

**Function: PopulateShop**
```
Get Shop Items:
  - Filter Items by Vendor Type
  - Filter by Player Level
  ?
For Each Item:
  Create Shop Item Widget (WBP_ShopItem)
  Set Item Data
  Bind OnClick ? BuyItem
  Add to Item List
```

**Function: BuyItem**
```
Input: ItemData (FRPGItemData)

Check Player Gold >= Item Price
  ?
If True:
  Subtract Gold
  Add Item to Inventory
  Play Purchase Sound
  Show "Purchased!" message
Else:
  Show "Not enough gold!" message
```

---

## ?? UI Examples

### **Widget: WBP_CharacterSheet**

**Bind Functions:**
```
Character Name Text:
  Bind ? Get Player Character ? Get Character Name

Level Text:
  Bind ? "Level " + Get Player Level

Health Bar:
  Bind ? CurrentHealth / MaxHealth

Stats Display:
  Bind ? Format Stats Function
  
Equipment Slots:
  For Each Slot (Head, Chest, Legs, etc.):
    Bind Icon ? Get Equipped Item Icon
    OnClick ? Show Item Tooltip
```

---

## ?? Network Replication (Multiplayer)

### **Replicated Variables:**
```cpp
UPROPERTY(Replicated)
int32 CurrentHealth;

UPROPERTY(Replicated)
TArray<FInventorySlot> Inventory;

UPROPERTY(ReplicatedUsing = OnRep_EquippedWeapon)
FRPGItemData EquippedWeapon;
```

### **Server RPCs:**
```cpp
UFUNCTION(Server, Reliable, WithValidation)
void Server_EquipItem(int32 ItemID);

UFUNCTION(Server, Reliable, WithValidation)
void Server_UseAbility(int32 AbilityID, AActor* Target);
```

---

## ?? Complete Example: Loot Chest

**Blueprint: BP_LootChest**

```
Variables:
  - LootTableID (Int)
  - ChestRarity (Enum)
  - HasBeenLooted (Bool)

Event: OnInteract (by Player)
  ?
  Branch: HasBeenLooted?
    True ? Show "Already looted" message
    False ? Continue
  ?
  Roll Loot:
    Get Loot Table (DT_LootTables, LootTableID)
    For Each Item in Loot Table:
      Roll = Random (0-100)
      If Roll < Item.DropChance:
        Generate Item (ItemID, Quality)
        Add to Loot Array
  ?
  Show Loot UI to Player
    - Display all items
    - Click item ? Add to Inventory
  ?
  Set HasBeenLooted = True
  ?
  Play Open Animation
  ?
  After 30 seconds: Respawn Chest
```

---

## ?? Tips for UE5 Blueprints

1. **Use Data Tables** for all static game data
2. **Create Component-based systems** (InventoryComponent, QuestComponent, etc.)
3. **Use Interfaces** for common interactions (IInteractable, IDamageable)
4. **Implement Event Dispatchers** for UI updates
5. **Cache Data Table references** in Game Instance
6. **Use Blueprint Function Libraries** for shared logic
7. **Replicate for Multiplayer** using Server RPCs

---

**All your 430+ items and game systems are ready to use in Unreal Engine 5!** ??
