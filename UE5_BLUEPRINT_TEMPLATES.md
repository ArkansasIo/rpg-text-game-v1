# ?? UNREAL ENGINE 5 BLUEPRINT TEMPLATES - COMPLETE IMPLEMENTATION

## ??? BLUEPRINT NAMING CONVENTIONS

### Prefix Standards
```
BP_    = Blueprint Class
WBP_   = Widget Blueprint
ABP_   = Animation Blueprint
AM_    = Animation Montage
M_     = Material
MI_    = Material Instance
PS_    = Particle System
BUS_   = Blueprint Function Library
D_     = Dungeon/Dialog Map
L_     = Level/Location Map
```

### Naming Examples
```
BP_PlayerCharacter        - Character blueprint
WBP_MainMenu             - UI widget blueprint
ABP_Player               - Animation blueprint
PS_Explosion             - Particle system
M_Armor_Plate            - Material
D_Dragon_Spire           - Dungeon map
L_Thornhaven             - Level map
```

---

## ?? DETAILED BLUEPRINT TEMPLATES

### 1. PLAYER CHARACTER BLUEPRINT (BP_PlayerCharacter)

**Components to Include:**
```
- Capsule Component (Root)
- Skeletal Mesh (Character Model)
- Camera (Third-person camera)
- Spring Arm (Camera distance)
- Weapon Attachment Point
- Health Component
- Inventory Component
- Ability Component
- Status Effects Component
```

**Key Variables:**
```cpp
// Player Stats
float Health;              // Current health
float MaxHealth = 100.0f;  // Max health points
float Mana;                // Current mana
float MaxMana = 50.0f;     // Max mana points
float Stamina;             // Current stamina
float MaxStamina = 100.0f; // Max stamina points

// Experience & Leveling
int32 Level = 1;           // Current level
int32 Experience = 0;      // Current XP
int32 NextLevelXP = 1000;  // XP needed for next level

// Combat
float AttackSpeed = 1.0f;  // Attack speed multiplier
float CriticalChance = 0.15f; // 15% crit chance
float DamageMultiplier = 1.0f;

// Attributes
int32 Strength = 10;       // Physical damage
int32 Intelligence = 10;   // Magical damage
int32 Dexterity = 10;      // Evasion/accuracy
int32 Vitality = 10;       // Health/resistance
int32 Wisdom = 10;         // Mana/willpower
int32 Luck = 5;            // Crit/loot chance

// Equipment
class AWeapon* CurrentWeapon;
class AArmor* EquippedArmor[10]; // Head, chest, legs, etc.
```

**Key Functions:**
```cpp
void TakeDamage(float Damage, class ACharacter* Attacker);
void Heal(float HealAmount);
void UseMana(float Amount);
void GainExperience(int32 XPAmount);
void LevelUp();
void EquipItem(class AItem* Item);
void UnequipItem(class AItem* Item);
void CastAbility(int32 AbilitySlot);
void Jump();
void Die();
void Respawn();
void ApplyStatusEffect(FStatusEffect Effect);
void RemoveStatusEffect(FName EffectName);
```

**Event Graph Setup:**
```
Event BeginPlay
?? Initialize Health/Mana/Stamina
?? Setup Input Component
?? Setup Inventory
?? Setup Abilities
?? Setup HUD

Event Tick
?? Regenerate Health (if not in combat)
?? Regenerate Mana
?? Regenerate Stamina
?? Update Status Effects
?? Update HUD

Input Events (W, A, S, D, Space, E, etc.)
?? Move character
?? Jump
?? Attack
?? Cast ability
?? Interact
```

---

### 2. ENEMY CHARACTER BLUEPRINT (BP_EnemyCharacter_Base)

**Components:**
```
- Capsule Component (Root)
- Skeletal Mesh
- AI Controller
- Sight Radius Component
- Patrol Points
- Combat Range Indicator
```

**Key Variables:**
```cpp
// AI Settings
float SightRadius = 1000.0f;        // How far enemy can see
float PeripheralVision = 90.0f;     // Cone of vision
float AttackRange = 200.0f;          // Melee range
float CombatDistance = 500.0f;       // Follow distance

// Enemy Stats
float Health;
float MaxHealth = 50.0f;
float Damage = 10.0f;
float AttackSpeed = 1.0f;
int32 EnemyLevel = 1;
int32 RewardXP = 100;
float RewardGoldMin = 5.0f;
float RewardGoldMax = 15.0f;

// AI State
enum EAIState { Idle, Patrol, Alert, Combat, Dying };
EAIState CurrentState = Idle;

// Behavior
TArray<FVector> PatrolPoints;
int32 CurrentPatrolIndex = 0;
class ACharacter* CurrentTarget;
bool bCanAttack = true;
float AttackCooldown = 1.5f;
```

**AI Behavior Tree Setup:**
```
Root Selector
?? Sequence (If Dying)
?  ?? Play Death Animation
?? Sequence (If In Combat)
?  ?? Check Target Valid
?  ?? Move to Attack Range
?  ?? Face Target
?  ?? Attack (if cooldown ready)
?  ?? Cast Abilities
?? Sequence (If Alerted)
?  ?? Move to last known location
?  ?? Search (cone around)
?? Sequence (If Has Target)
?  ?? Move to target
?  ?? Set Combat State
?? Sequence (Default)
   ?? Patrol Route
   ?? Look for targets
```

**Key Functions:**
```cpp
void TakeDamage(float Damage, AActor* Attacker);
void Die();
void OnTargetSpotted(APawn* Target);
void OnTargetLost();
void MoveToTarget();
void AttackTarget();
void Patrol();
void Search();
void PlayDeathAnimation();
void DropLoot();
void ApplyDamageToPlayer();
bool CanAttack() const;
void UpdateAIState();
```

---

### 3. MAIN HUD WIDGET (WBP_MainHUD)

**Canvas Structure:**
```
Canvas Panel (Root, full screen)
??? PlayerInfo Panel (Top-Left)
?   ?? Portrait Image
?   ?? Character Name Text
?   ?? Level Text
?   ?? HealthBar (Progress Bar)
?   ?  ?? Health Text (75/100)
?   ?? ManaBar (Progress Bar)
?   ?  ?? Mana Text (45/100)
?   ?? StaminaBar (Progress Bar)
?      ?? Stamina Text (80/100)
?
??? TargetInfo Panel (Center-Top)
?   ?? Target Portrait
?   ?? Target Name
?   ?? Target Level
?   ?? Target HealthBar
?
??? AbilityBar (Bottom-Center)
?   ?? Slot 1 (Q) - Ability Icon + Cooldown
?   ?? Slot 2 (W) - Ability Icon + Cooldown
?   ?? Slot 3 (E) - Ability Icon + Cooldown
?   ?? Slot 4 (R) - Ability Icon + Cooldown
?   ?? Slot 5 (1) - Ability Icon + Cooldown
?   ?? Slot 6 (2) - Ability Icon + Cooldown
?   ?? Slot 7 (3) - Ability Icon + Cooldown
?   ?? Slot 8 (4) - Ability Icon + Cooldown
?   ?? Slot 9 (5) - Ability Icon + Cooldown
?   ?? Slot 10 (6) - Ability Icon + Cooldown
?   ?? Slot 11 (7) - Ability Icon + Cooldown
?
??? StatusEffects Panel (Top-Right)
?   ?? Horizontal scroll of buff/debuff icons
?
??? Minimap (Bottom-Right)
?   ?? Map Image (256x256)
?   ?? Player Marker (center)
?   ?? Enemy Markers (red dots)
?   ?? NPC Markers (yellow dots)
?   ?? POI Markers (blue dots)
?
??? CombatLog (Center-Bottom)
?   ?? Scrollable text area
?   ?? Color-coded messages
?   ?? Timestamp for each entry
?
??? DamageNumbers (Free floating)
?   ?? Floating text above enemies
?
??? Crosshair (Center)
?   ?? Reticle image
?
??? Compass (Top-Center)
?   ?? Cardinal directions
?
??? Notifications (Top-Right corner)
?   ?? Quest updated, level up, etc.
?
??? Hotkeys Display (Top-Left corner)
    ?? I=Inventory, C=Character, Q=Quest, etc.
```

**Key Variables:**
```cpp
// References
class APlayerCharacter* PlayerCharacter;
APawn* CurrentTarget;

// UI Elements
float UpdateRate = 0.1f;        // Update every 0.1 seconds
bool bShowAllElements = true;
float HUDOpacity = 1.0f;

// Damage Numbers
TArray<FVector> FloatingDamagePositions;
TArray<FString> FloatingDamageTexts;
TArray<FLinearColor> FloatingDamageColors;
TArray<float> FloatingDamageLifeTimes;
```

**Key Functions:**
```cpp
void UpdatePlayerHealth(float Health, float MaxHealth);
void UpdatePlayerMana(float Mana, float MaxMana);
void UpdatePlayerStamina(float Stamina, float MaxStamina);
void UpdateTargetInfo(APawn* Target);
void ClearTargetInfo();
void UpdateAbilityCooldown(int32 SlotIndex, float Cooldown, float MaxCooldown);
void ShowDamageNumber(float Damage, FVector Position, bool bCritical = false);
void ShowHealingNumber(float Healing, FVector Position);
void ShowCombatMessage(FString Message, FLinearColor Color = FLinearColor::White);
void UpdateMinimap(TArray<FVector> EnemyPositions, TArray<FVector> NPCPositions);
void AddStatusEffect(FName EffectName, float Duration, UTexture2D* Icon);
void RemoveStatusEffect(FName EffectName);
void ToggleHUDVisibility();
void SetHUDMode(EHUDDisplayMode Mode);
```

**Event Graph:**
```
Event Construct
?? Get Player Character
?? Setup Timer for Updates
?? Initialize all UI elements

Event Tick (0.1s interval)
?? Update Health Bar
?? Update Mana Bar
?? Update Stamina Bar
?? Update Ability Cooldowns
?? Update Status Effects
?? Update Minimap
?? Update Floating Damage Numbers
?? Update Combat Log

Input Events
?? I Key ? Show/Hide Inventory
?? C Key ? Show/Hide Character Sheet
?? Q Key ? Show/Hide Quest Log
?? M Key ? Show/Hide Map
?? H Key ? Toggle HUD Visibility
?? Tab Key ? Toggle Minimap
```

---

### 4. INVENTORY WIDGET (WBP_Inventory)

**UI Layout:**
```
Window (Inventory)
??? Header
?   ?? Title: "Inventory"
?   ?? Close Button
??? Left Panel (Inventory Grid)
?   ?? Grid Size: 8x10 (80 slots)
?   ?? Drag/Drop enabled
?   ?? Item tooltips
?   ?? Item quantities
??? Right Panel (Item Details)
?   ?? Item Icon (large)
?   ?? Item Name
?   ?? Item Description
?   ?? Item Stats
?   ?  ?? Damage: +15
?   ?  ?? Armor: +10
?   ?  ?? Health: +50
?   ?  ?? Special: Lifesteal 5%
?   ?? Item Quality (color-coded)
?   ?? Item Rarity
?   ?? Equip Button
?   ?? Drop Button
?   ?? Use Button
??? Bottom Panel
?   ?? Total Slots: 45/80
?   ?? Total Weight: 125/200 lbs
?   ?? Gold: 5,250
?   ?? Sort By dropdown (Name, Type, Rarity)
??? Tabs
    ?? All Items
    ?? Weapons
    ?? Armor
    ?? Consumables
    ?? Materials
    ?? Quest Items
    ?? Junk
```

**Key Variables:**
```cpp
// Inventory Data
TArray<FInventoryItem> InventoryItems;  // Actual items
TMap<int32, UItemWidget*> SlotWidgets;  // UI references

// Inventory Settings
int32 MaxSlots = 80;
float MaxWeight = 200.0f;
float CurrentWeight = 0.0f;

// Filtering
EInventoryFilter CurrentFilter = EInventoryFilter::AllItems;

// Selection
FInventoryItem SelectedItem;
int32 SelectedSlot = -1;
```

**Item Struct:**
```cpp
struct FInventoryItem
{
    int32 ItemID;
    FString ItemName;
    FString Description;
    EItemType Type;  // Weapon, Armor, Consumable, etc.
    EItemRarity Rarity;  // Common, Uncommon, Rare, Epic, Legendary
    int32 Quantity = 1;
    float Weight = 0.5f;
    int32 SellPrice = 0;
    float Durability = 100.0f;
    FItemStats Stats;
    UTexture2D* Icon;
    bool bIsQuestItem = false;
    bool bIsEquipped = false;
};
```

**Key Functions:**
```cpp
void AddItemToInventory(FInventoryItem Item, int32 Quantity = 1);
void RemoveItemFromInventory(int32 SlotIndex, int32 Quantity = 1);
void EquipItem(int32 SlotIndex);
void UnequipItem(int32 SlotIndex);
void UseConsumable(int32 SlotIndex);
void DropItem(int32 SlotIndex);
void SortInventory(ESortMethod Method);
void FilterInventory(EInventoryFilter Filter);
void RefreshDisplay();
void ShowItemTooltip(FInventoryItem Item);
void HideItemTooltip();
float CalculateTotalWeight();
bool HasSpace(FInventoryItem Item) const;
void SwapItems(int32 Slot1, int32 Slot2);
```

---

### 5. ABILITY BLUEPRINT (BP_Ability_Base)

**Components:**
```
- Ability Data Asset reference
- Cooldown Timer
- Mana Cost
- Cast Time
```

**Key Variables:**
```cpp
// Ability Info
FName AbilityName = "Default Ability";
FString AbilityDescription = "";
int32 AbilityLevel = 1;
UTexture2D* AbilityIcon;

// Costs
float ManaCost = 20.0f;
float StaminaCost = 0.0f;
int32 HealthCost = 0;

// Cooldown
float CooldownDuration = 5.0f;
float CurrentCooldown = 0.0f;
bool bIsOnCooldown = false;

// Casting
float CastTime = 0.5f;
bool bIsCasting = false;
bool bIsChanneled = false;
float ChannelDuration = 0.0f;

// Effects
float Damage = 0.0f;
float Healing = 0.0f;
float DamageRadius = 0.0f;
class AAbilityEffect* AbilityEffect;

// Targeting
enum ETargetType { Self, SingleTarget, AOE, Cone, Line };
ETargetType TargetType = SingleTarget;
float Range = 1000.0f;

// Keybind
FKey AbilityKey = EKeys::Q;
int32 AbilitySlot = 0;
```

**Key Functions:**
```cpp
void CastAbility(ACharacter* Caster, AActor* Target = nullptr);
void ExecuteAbility(ACharacter* Caster, AActor* Target);
void ApplyEffects(ACharacter* Caster, AActor* Target);
void OnAbilityCast();
void OnAbilityHit(AActor* HitActor);
void OnAbilityEnd();
void StartCooldown();
void UpdateCooldown(float DeltaTime);
void ResetCooldown();
bool CanCastAbility(ACharacter* Caster) const;
bool HasEnoughResources(ACharacter* Caster) const;
void ConsumeResources(ACharacter* Caster);
void RefundResources(ACharacter* Caster);
```

---

### 6. QUEST BLUEPRINT (BP_Quest_Base)

**Quest Variables:**
```cpp
// Quest Info
int32 QuestID = 0;
FString QuestName = "Quest Name";
FString QuestDescription = "Description";
FString QuestObjective = "Objective";

// Quest Type
enum EQuestType { Kill, Collect, Deliver, Explore, Talk, Dungeon };
EQuestType Type = Kill;

// Requirements
int32 MinLevel = 1;
int32 MaxLevel = 99;
TArray<FName> RequiredFactions;
TArray<int32> RequiredQuests;  // Prerequisites

// Progress
struct FQuestObjective
{
    FString Description;
    int32 TargetCount = 1;
    int32 CurrentCount = 0;
    bool bCompleted = false;
};
TArray<FQuestObjective> Objectives;

// Rewards
int32 RewardXP = 100;
float RewardGold = 50.0f;
TArray<FInventoryItem> RewardItems;
TArray<FName> RewardFactionRep;  // Faction reputation gains

// Quest Giver
ACharacter* QuestGiver;
ACharacter* QuestTurnIn;

// State
enum EQuestState { Available, Accepted, InProgress, Completed, Abandoned };
EQuestState State = Available;

bool bIsRepeatable = false;
int32 TimeLimit = 0;  // In minutes (0 = no limit)
```

---

### 7. MAIN MENU WIDGET (WBP_MainMenu)

**UI Layout:**
```
Canvas Panel (Full Screen)
??? Background Image
??? Logo/Title
??? Menu Buttons Panel (Center)
?   ?? "New Game" Button
?   ?? "Load Game" Button
?   ?? "Settings" Button
?   ?? "Credits" Button
?   ?? "Quit Game" Button
??? Version Text (Bottom-Right)
??? Music (Background)
```

**Key Functions:**
```cpp
void OnNewGameClicked();
void OnLoadGameClicked();
void OnSettingsClicked();
void OnCreditsClicked();
void OnQuitClicked();
void StartGame();
void NavigateMenu(bool bUp);
void SelectMenuItem();
void PlayMenuMusic();
```

---

### 8. CHARACTER CREATION WIDGET (WBP_CharacterCreation)

**Steps:**
```
1. Race Selection
   - Human
   - Elf
   - Dwarf
   - Orc
   - Goblin
   - Dragonborn

2. Class Selection
   - Warrior
   - Mage
   - Priest
   - Rogue
   - Paladin
   - Ranger

3. Appearance
   - Face customization
   - Hair style/color
   - Skin color
   - Body type
   - Scars/Tattoos

4. Review
   - Summary of character
   - Stats preview
   - Confirm button
```

---

### 9. SETTINGS MENU (WBP_SettingsMenu)

**Tabs:**
```
1. Graphics
   - Quality Level (Low/Medium/High/Ultra)
   - Resolution Selector
   - Fullscreen toggle
   - VSync toggle
   - Anti-aliasing
   - Shadows Quality
   - Render Distance

2. Audio
   - Master Volume Slider
   - Music Volume Slider
   - SFX Volume Slider
   - Voice Volume Slider
   - Ambient Volume Slider
   - Subtitle toggle

3. Gameplay
   - Difficulty (Easy/Normal/Hard/Legendary)
   - Mouse Sensitivity
   - Gamepad Sensitivity
   - Invert Mouse Y
   - Invert Gamepad Y
   - Camera Distance

4. Accessibility
   - Colorblind Mode
   - UI Scale
   - High Contrast
   - Font Size
   - Subtitle Size
```

---

### 10. NPC MERCHANT BLUEPRINT (BP_Merchant)

**Components:**
```
- Skeletal Mesh (NPC model)
- Interaction Component
- Shop Inventory System
```

**Key Variables:**
```cpp
// Shop Info
FString ShopName = "General Store";
TArray<FInventoryItem> ShopInventory;
int32 MaxShopSlots = 50;

// Pricing
float PriceMarkup = 1.2f;  // 20% markup
float BuybackPercentage = 0.75f;  // Buy items for 75% of sell price

// Behavior
bool bIsOpen = false;
FTime OpenTime;
FTime CloseTime;
TArray<FName> AcceptedCurrencies;

// Dialogue
FString GreetingText = "Welcome to my shop!";
FString GoodbyeText = "Come again soon!";
```

**Key Functions:**
```cpp
void OpenShop(ACharacter* Customer);
void CloseShop();
void SellItem(FInventoryItem Item);
void BuyItem(FInventoryItem Item, int32 Quantity);
void UpdateInventory();
void RestockInventory();
void CalculatePrice(FInventoryItem Item, bool bSelling);
void PlayTradingSFX();
```

---

## ?? BLUEPRINT QUICK REFERENCE

### Most Important Blueprints to Create First:

**Week 1 Priority:**
```
1. BP_PlayerCharacter      - Player controller
2. WBP_MainHUD             - Main game HUD
3. WBP_MainMenu            - Main menu
4. BP_GameManager          - Game state management
5. BP_InputManager         - Input handling
```

**Week 2 Priority:**
```
6. BP_EnemyCharacter_Base  - Enemy AI
7. WBP_Inventory           - Inventory system
8. BP_Ability_Base         - Ability system
9. WBP_CharacterCreation   - Character creation
10. L_MainMenu             - Main menu level
```

**Week 3 Priority:**
```
11. All weapon/armor items
12. All ability types
13. All NPC types
14. Guild/Party systems
15. Quest system
```

**Week 4+ Priority:**
```
16. All maps/levels
17. All VFX/Audio
18. Settings menu
19. Advanced features
20. Polish & optimization
```

---

This comprehensive guide gives you everything needed to create all 287 blueprints for your complete 3D MMORPG!
