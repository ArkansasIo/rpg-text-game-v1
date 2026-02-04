// RPGTypes.h
// Core enums and structs for RPG system

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "RPGTypes.generated.h"

// ==================== ENUMS ====================

UENUM(BlueprintType)
enum class ERPGRace : uint8
{
    Human       UMETA(DisplayName = "Human"),
    Dwarf       UMETA(DisplayName = "Dwarf"),
    Elf         UMETA(DisplayName = "Elf"),
    Orc         UMETA(DisplayName = "Orc"),
    Troll       UMETA(DisplayName = "Troll"),
    Undead      UMETA(DisplayName = "Undead"),
    NightElf    UMETA(DisplayName = "Night Elf"),
    Tauren      UMETA(DisplayName = "Tauren"),
    Gnome       UMETA(DisplayName = "Gnome"),
    BloodElf    UMETA(DisplayName = "Blood Elf"),
    Draenei     UMETA(DisplayName = "Draenei"),
    Worgen      UMETA(DisplayName = "Worgen")
};

UENUM(BlueprintType)
enum class ERPGClass : uint8
{
    Warrior     UMETA(DisplayName = "Warrior"),
    Mage        UMETA(DisplayName = "Mage"),
    Rogue       UMETA(DisplayName = "Rogue"),
    Priest      UMETA(DisplayName = "Priest"),
    Paladin     UMETA(DisplayName = "Paladin"),
    Hunter      UMETA(DisplayName = "Hunter"),
    Shaman      UMETA(DisplayName = "Shaman"),
    Warlock     UMETA(DisplayName = "Warlock"),
    Druid       UMETA(DisplayName = "Druid"),
    Monk        UMETA(DisplayName = "Monk"),
    DeathKnight UMETA(DisplayName = "Death Knight"),
    DemonHunter UMETA(DisplayName = "Demon Hunter")
};

UENUM(BlueprintType)
enum class EItemRarity : uint8
{
    Common      UMETA(DisplayName = "Common"),
    Uncommon    UMETA(DisplayName = "Uncommon"),
    Rare        UMETA(DisplayName = "Rare"),
    Epic        UMETA(DisplayName = "Epic"),
    Legendary   UMETA(DisplayName = "Legendary")
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
    Weapon      UMETA(DisplayName = "Weapon"),
    Armor       UMETA(DisplayName = "Armor"),
    Consumable  UMETA(DisplayName = "Consumable"),
    Material    UMETA(DisplayName = "Material"),
    Quest       UMETA(DisplayName = "Quest Item"),
    Container   UMETA(DisplayName = "Container"),
    Reagent     UMETA(DisplayName = "Reagent")
};

UENUM(BlueprintType)
enum class EEquipmentSlot : uint8
{
    Head        UMETA(DisplayName = "Head"),
    Neck        UMETA(DisplayName = "Neck"),
    Shoulders   UMETA(DisplayName = "Shoulders"),
    Back        UMETA(DisplayName = "Back"),
    Chest       UMETA(DisplayName = "Chest"),
    Shirt       UMETA(DisplayName = "Shirt"),
    Tabard      UMETA(DisplayName = "Tabard"),
    Wrist       UMETA(DisplayName = "Wrist"),
    Hands       UMETA(DisplayName = "Hands"),
    Waist       UMETA(DisplayName = "Waist"),
    Legs        UMETA(DisplayName = "Legs"),
    Feet        UMETA(DisplayName = "Feet"),
    Ring1       UMETA(DisplayName = "Ring 1"),
    Ring2       UMETA(DisplayName = "Ring 2"),
    Trinket1    UMETA(DisplayName = "Trinket 1"),
    Trinket2    UMETA(DisplayName = "Trinket 2"),
    MainHand    UMETA(DisplayName = "Main Hand"),
    OffHand     UMETA(DisplayName = "Off Hand"),
    Ranged      UMETA(DisplayName = "Ranged")
};

UENUM(BlueprintType)
enum class EAbilityType : uint8
{
    Instant     UMETA(DisplayName = "Instant"),
    Cast        UMETA(DisplayName = "Cast"),
    Channeled   UMETA(DisplayName = "Channeled"),
    Passive     UMETA(DisplayName = "Passive")
};

UENUM(BlueprintType)
enum class EQuestStatus : uint8
{
    Available   UMETA(DisplayName = "Available"),
    Active      UMETA(DisplayName = "Active"),
    Complete    UMETA(DisplayName = "Complete"),
    TurnedIn    UMETA(DisplayName = "Turned In"),
    Failed      UMETA(DisplayName = "Failed")
};

// ==================== STRUCTS ====================

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
    int32 Spirit = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AttackSpeed = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 SpellPower = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 CritRating = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 HasteRating = 0;
};

USTRUCT(BlueprintType)
struct FRPGItemData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    int32 ItemID = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    EItemType Type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    EItemRarity Rarity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    int32 RequiredLevel = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    int32 MaxStackSize = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    int32 VendorPrice = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    bool bIsTradeable = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    bool bIsQuestItem = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FItemStats Stats;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    UTexture2D* Icon = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    UStaticMesh* WorldMesh = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    TSubclassOf<AActor> DropActorClass;
};

USTRUCT(BlueprintType)
struct FInventorySlot
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FRPGItemData ItemData;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Quantity = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 SlotIndex = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsEmpty = true;
};

USTRUCT(BlueprintType)
struct FRPGAbilityData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 AbilityID = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString AbilityName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EAbilityType Type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Cooldown = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ManaCost = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float EnergyCost = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float RageCost = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CastTime = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Range = 30.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Damage = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Healing = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UTexture2D* Icon = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<AActor> ProjectileClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UParticleSystem* CastEffect = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UParticleSystem* HitEffect = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    USoundBase* CastSound = nullptr;
};

USTRUCT(BlueprintType)
struct FRPGQuestData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 QuestID = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString QuestName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString QuestType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 RequiredLevel = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsRepeatable = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int64 ExperienceReward = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int64 GoldReward = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FRPGItemData> RewardItems;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> Objectives;
};

USTRUCT(BlueprintType)
struct FRPGZoneData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ZoneID = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ZoneName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ZoneType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 RecommendedLevel = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MinLevel = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxLevel = 60;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsSanctuary = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UWorld> LevelAsset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector SpawnLocation;
};

USTRUCT(BlueprintType)
struct FRPGEnemyData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 EnemyID = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString EnemyName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString EnemyType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Level = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Health = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Armor = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MinDamage = 10;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxDamage = 15;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Rank;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int64 ExperienceReward = 100;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<AActor> EnemyBlueprint;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    USkeletalMesh* Mesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<int32> LootTableIDs;
};

USTRUCT(BlueprintType)
struct FGuildInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 GuildID = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString GuildName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString GuildTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 GuildLevel = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MemberCount = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString LeaderName;
};

USTRUCT(BlueprintType)
struct FPartyMemberInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString CharacterName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Level = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ERPGClass Class;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float HealthPercent = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ManaPercent = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsOnline = true;
};

// ==================== DELEGATES ====================

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChanged, float, NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLevelUp, int32, NewLevel, int32, TalentPoints);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnItemAdded, FRPGItemData, Item, int32, Quantity, int32, SlotIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestAccepted, int32, QuestID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestCompleted, int32, QuestID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGuildInvite, FString, GuildName, FString, InviterName);
