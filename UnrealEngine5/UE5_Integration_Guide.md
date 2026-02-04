# ?? UNREAL ENGINE 5 INTEGRATION GUIDE

## ?? Overview

This guide shows how to integrate your complete RPG system (430+ items, 80+ database tables, character systems) into **Unreal Engine 5**.

---

## ?? Integration Options

### **Option 1: Data Tables (Easiest)**
- Export SQL data to JSON/CSV
- Import into UE5 Data Tables
- Use Blueprint to read data
- **Best for:** Single-player, client-side data

### **Option 2: REST API Backend**
- Keep C# backend as web API
- UE5 makes HTTP requests
- Real-time database sync
- **Best for:** Multiplayer, live data

### **Option 3: Native C++ Integration**
- Port database logic to C++
- Use Unreal's database plugins
- Full control over data
- **Best for:** Complex server logic

### **Option 4: Hybrid Approach** (RECOMMENDED)
- Static data (items, quests) ? Data Tables
- Dynamic data (characters, inventory) ? REST API
- **Best for:** MMORPG-style games

---

## ?? Method 1: Data Tables (Quick Start)

### **Step 1: Export Data from SQL**

Run the export script:
```sql
-- In SSMS, execute:
Database\UnrealEngine5\ExportDataToUE5.sql
```

This generates JSON for:
- ? 430+ Items
- ? 72 Zones
- ? 26+ Enemies
- ? Quests
- ? Achievements
- ? Crafting recipes

### **Step 2: Create UE5 Data Table Structures**

In Unreal Engine 5:

#### **Create Item Structure (C++):**
```cpp
// ItemDataStruct.h
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemDataStruct.generated.h"

UENUM(BlueprintType)
enum class EItemRarity : uint8
{
    Common     UMETA(DisplayName = "Common"),
    Uncommon   UMETA(DisplayName = "Uncommon"),
    Rare       UMETA(DisplayName = "Rare"),
    Epic       UMETA(DisplayName = "Epic"),
    Legendary  UMETA(DisplayName = "Legendary")
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
    Weapon     UMETA(DisplayName = "Weapon"),
    Armor      UMETA(DisplayName = "Armor"),
    Consumable UMETA(DisplayName = "Consumable"),
    Material   UMETA(DisplayName = "Material"),
    Quest      UMETA(DisplayName = "Quest Item")
};

USTRUCT(BlueprintType)
struct FItemStats
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Damage = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Armor = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Strength = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Agility = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Intelligence = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Stamina = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AttackSpeed = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 FireDamage = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 FrostDamage = 0;
};

USTRUCT(BlueprintType)
struct FRPGItemData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    int32 ItemID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    EItemType Type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    EItemRarity Rarity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    int32 RequiredLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    int32 MaxStackSize;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    int32 VendorPrice;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    bool IsTradeable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FItemStats Stats;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    UTexture2D* Icon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    UStaticMesh* WorldMesh;
};
```

#### **Create Character Structure:**
```cpp
// CharacterDataStruct.h
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CharacterDataStruct.generated.h"

USTRUCT(BlueprintType)
struct FRPGRaceData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString RaceName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 BaseStrength;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 BaseAgility;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 BaseIntelligence;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 BaseStamina;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> RacialAbilities;
};

USTRUCT(BlueprintType)
struct FRPGClassData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ClassName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> Specializations;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> StartingAbilities;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 BaseHealth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 BaseMana;
};
```

#### **Create Enemy Structure:**
```cpp
// EnemyDataStruct.h
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "EnemyDataStruct.generated.h"

UENUM(BlueprintType)
enum class EEnemyRank : uint8
{
    Normal    UMETA(DisplayName = "Normal"),
    Elite     UMETA(DisplayName = "Elite"),
    Boss      UMETA(DisplayName = "Boss"),
    WorldBoss UMETA(DisplayName = "World Boss"),
    RaidBoss  UMETA(DisplayName = "Raid Boss")
};

USTRUCT(BlueprintType)
struct FRPGEnemyData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 EnemyID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Level;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Health;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Armor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MinDamage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxDamage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EEnemyRank Rank;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ExperienceReward;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<AActor> EnemyBlueprint;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    USkeletalMesh* Mesh;
};
```

### **Step 3: Import to UE5**

1. **Create Data Table:**
   - Content Browser ? Right Click ? Miscellaneous ? Data Table
   - Choose `FRPGItemData` as Row Structure
   - Name it `DT_Items`

2. **Import JSON:**
   - Open the Data Table
   - Click "Import" (or use CSV import)
   - Paste JSON from SQL export

3. **Repeat for:**
   - `DT_Zones`
   - `DT_Enemies`
   - `DT_Quests`
   - `DT_Races`
   - `DT_Classes`

### **Step 4: Blueprint Usage**

#### **Get Item by ID:**
```
Blueprint Node: Get Data Table Row
- Data Table: DT_Items
- Row Name: ItemID (as Name)
- Out Row: FRPGItemData struct
```

#### **Display Item:**
```cpp
// In Blueprint or C++
FRPGItemData* ItemData = ItemDataTable->FindRow<FRPGItemData>(FName(*FString::FromInt(ItemID)), "");
if (ItemData)
{
    UE_LOG(LogTemp, Warning, TEXT("Item: %s, Damage: %d"), *ItemData->Name, ItemData->Stats.Damage);
}
```

---

## ?? Method 2: REST API Backend (Multiplayer)

### **Step 1: Create C# Web API**

Create new ASP.NET Core Web API project:

```csharp
// Controllers/ItemsController.cs
using Microsoft.AspNetCore.Mvc;
using RPGMenuSystem.Database;

[ApiController]
[Route("api/[controller]")]
public class ItemsController : ControllerBase
{
    private readonly RpgDbContext _context;

    public ItemsController(RpgDbContext context)
    {
        _context = context;
    }

    [HttpGet]
    public async Task<ActionResult<IEnumerable<Item>>> GetItems()
    {
        return await _context.Items.ToListAsync();
    }

    [HttpGet("{id}")]
    public async Task<ActionResult<Item>> GetItem(int id)
    {
        var item = await _context.Items.FindAsync(id);
        if (item == null) return NotFound();
        return item;
    }

    [HttpGet("rarity/{rarity}")]
    public async Task<ActionResult<IEnumerable<Item>>> GetItemsByRarity(string rarity)
    {
        return await _context.Items
            .Where(i => i.Rarity == rarity)
            .ToListAsync();
    }
}

// Controllers/CharactersController.cs
[ApiController]
[Route("api/[controller]")]
public class CharactersController : ControllerBase
{
    private readonly DatabaseManager _dbManager;

    [HttpGet("{id}")]
    public async Task<ActionResult<Character>> GetCharacter(int id)
    {
        var character = await _dbManager.GetCharacterByIdAsync(id);
        return character == null ? NotFound() : Ok(character);
    }

    [HttpPost]
    public async Task<ActionResult<Character>> CreateCharacter([FromBody] CharacterCreateDto dto)
    {
        var character = await _dbManager.CreateCharacterAsync(
            dto.AccountId, dto.Name, dto.Race, dto.Class, dto.Specialization);
        return CreatedAtAction(nameof(GetCharacter), new { id = character.CharacterID }, character);
    }

    [HttpPut("{id}/inventory")]
    public async Task<IActionResult> UpdateInventory(int id, [FromBody] InventoryUpdateDto dto)
    {
        await _dbManager.AddItemToInventoryAsync(id, dto.ItemId, dto.Quantity);
        return NoContent();
    }
}
```

### **Step 2: UE5 HTTP Client**

#### **C++ HTTP Request:**
```cpp
// RPGHttpClient.h
#pragma once

#include "CoreMinimal.h"
#include "Http.h"
#include "Json.h"
#include "JsonUtilities.h"

class YOURPROJECT_API FRPGHttpClient
{
public:
    static void GetItems(TFunction<void(TArray<FRPGItemData>)> OnSuccess);
    static void GetCharacter(int32 CharacterID, TFunction<void(FRPGCharacterData)> OnSuccess);
    static void CreateCharacter(FString Name, FString Race, FString Class, 
                               TFunction<void(int32 CharacterID)> OnSuccess);

private:
    static const FString BaseURL;
    static void ProcessJsonResponse(FHttpResponsePtr Response, TFunction<void(FString)> OnSuccess);
};

// RPGHttpClient.cpp
const FString FRPGHttpClient::BaseURL = TEXT("http://localhost:5000/api");

void FRPGHttpClient::GetItems(TFunction<void(TArray<FRPGItemData>)> OnSuccess)
{
    TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
    Request->SetURL(BaseURL + TEXT("/items"));
    Request->SetVerb(TEXT("GET"));
    Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

    Request->OnProcessRequestComplete().BindLambda([OnSuccess](
        FHttpRequestPtr Request, 
        FHttpResponsePtr Response, 
        bool bWasSuccessful)
    {
        if (bWasSuccessful && Response.IsValid())
        {
            FString JsonString = Response->GetContentAsString();
            
            TArray<TSharedPtr<FJsonValue>> JsonArray;
            TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
            
            if (FJsonSerializer::Deserialize(Reader, JsonArray))
            {
                TArray<FRPGItemData> Items;
                for (const TSharedPtr<FJsonValue>& Value : JsonArray)
                {
                    const TSharedPtr<FJsonObject>* Object;
                    if (Value->TryGetObject(Object))
                    {
                        FRPGItemData Item;
                        Item.ItemID = (*Object)->GetIntegerField(TEXT("ItemID"));
                        Item.Name = (*Object)->GetStringField(TEXT("ItemName"));
                        // ... parse other fields
                        Items.Add(Item);
                    }
                }
                OnSuccess(Items);
            }
        }
    });

    Request->ProcessRequest();
}
```

#### **Blueprint HTTP Request:**
Create Blueprint Function Library:
```cpp
// RPGBlueprintLibrary.h
UCLASS()
class URPGBlueprintLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "RPG|Network")
    static void GetItemsFromServer(const FString& ServerURL, 
                                   const FOnItemsReceived& OnSuccess);

    UFUNCTION(BlueprintCallable, Category = "RPG|Network")
    static void CreateCharacterOnServer(const FString& ServerURL, 
                                        const FString& CharacterName,
                                        const FString& Race,
                                        const FString& Class,
                                        const FOnCharacterCreated& OnSuccess);
};
```

---

## ?? UE5 Project Structure

```
YourRPGProject/
??? Content/
?   ??? Data/
?   ?   ??? Items/
?   ?   ?   ??? DT_Items.uasset
?   ?   ?   ??? DT_Weapons.uasset
?   ?   ?   ??? DT_Armor.uasset
?   ?   ??? Characters/
?   ?   ?   ??? DT_Races.uasset
?   ?   ?   ??? DT_Classes.uasset
?   ?   ?   ??? DT_Specializations.uasset
?   ?   ??? World/
?   ?   ?   ??? DT_Zones.uasset
?   ?   ?   ??? DT_Enemies.uasset
?   ?   ??? Quests/
?   ?       ??? DT_Quests.uasset
?   ??? Blueprints/
?   ?   ??? Characters/
?   ?   ?   ??? BP_PlayerCharacter.uasset
?   ?   ?   ??? BP_CharacterCreation.uasset
?   ?   ??? Enemies/
?   ?   ?   ??? BP_EnemyBase.uasset
?   ?   ??? UI/
?   ?       ??? WBP_Inventory.uasset
?   ?       ??? WBP_CharacterSheet.uasset
?   ?       ??? WBP_QuestLog.uasset
?   ??? Maps/
?       ??? MainMenu.umap
?       ??? GameWorld.umap
??? Source/
    ??? YourProject/
        ??? RPGGameMode.h/cpp
        ??? RPGPlayerController.h/cpp
        ??? RPGCharacter.h/cpp
        ??? Systems/
            ??? InventoryComponent.h/cpp
            ??? QuestComponent.h/cpp
            ??? CombatComponent.h/cpp
```

---

## ?? Quick Setup Checklist

### ? **For Single-Player:**
1. Run `ExportDataToUE5.sql` in SSMS
2. Create Data Table structs in UE5
3. Import JSON to Data Tables
4. Create Blueprint systems to read data
5. Build game logic around data

### ? **For Multiplayer:**
1. Convert C# project to Web API
2. Deploy API to server
3. Create HTTP client in UE5
4. Use dedicated server architecture
5. Sync data with REST calls

---

## ?? Next Steps

See the following files:
- `UE5_DataExport.ps1` - Automated data export script
- `UE5_ProjectTemplate.zip` - Pre-configured UE5 project
- `UE5_BlueprintExamples.md` - Blueprint node examples
- `UE5_ServerSetup.md` - Multiplayer server guide

---

**Your 430+ items, 72 zones, and complete RPG system are ready for Unreal Engine 5!** ??
