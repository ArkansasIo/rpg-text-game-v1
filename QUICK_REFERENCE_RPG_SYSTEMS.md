# ?? RPG Systems Quick Reference Guide

## ?? Get Started in 5 Minutes

### Step 1: Access the Systems Manager
```cpp
ARPGGameSystemsManager* GameSystems = Cast<ARPGGameSystemsManager>(GetWorld()->GetGameState());
```

### Step 2: Get Any System
```cpp
// Pick the system you need:
UCharacterProgressionSystem* Progression = GameSystems->GetProgressionSystem();
UCombatSystem* Combat = GameSystems->GetCombatSystem();
UInventorySystem* Inventory = GameSystems->GetInventorySystem();
UQuestSystem* Quests = GameSystems->GetQuestSystem();
UStatusEffectSystem* Effects = GameSystems->GetStatusEffectSystem();
```

### Step 3: Use Functions
```cpp
// Examples:
Progression->GainExperience(100);
Combat->TakeDamage(25.0f);
Inventory->AddGold(50);
Quests->AcceptQuest("quest_001");
Effects->ApplyEffect(PoisonEffect);
```

---

## ?? System Functions By Category

### ?? Character Progression
```cpp
// Level & XP
Progression->GainExperience(amount);
Progression->LevelUp();

// Stats
Progression->IncreaseStatByPoints(ECharacterStatType::Strength, 5);
Progression->GetTotalStats();

// Skills
Progression->LearnSkill(skillData);
Progression->UpgradeSkill("SkillName");
Progression->FindSkill("SkillName");
```

### ?? Combat
```cpp
// Combat State
Combat->StartCombat();
Combat->EndCombat();

// Damage
Combat->CalculateDamage(ECharacterStatType::Strength);
Combat->ApplyDefense(incomingDamage, damageType);

// Resources
Combat->TakeDamage(25.0f);
Combat->Heal(50.0f);
Combat->RegenerateResources(deltaTime);

// Actions
Combat->AttemptAbility("Fireball", manaCost);
Combat->AttemptDodge();
Combat->AttemptBlock();

// Status
Combat->IsAlive();
```

### ?? Inventory
```cpp
// Items
Inventory->AddItem(item);
Inventory->RemoveItem("itemID", quantity);
Inventory->FindItem("itemID");
Inventory->UseItem("itemID");
Inventory->DropItem("itemID", quantity);

// Equipment
Inventory->EquipItem("itemID", EEquipmentSlot::MainHand);
Inventory->UnequipItem(EEquipmentSlot::Head);
Inventory->GetEquippedItem(EEquipmentSlot::Chest);

// Bonuses
Inventory->CalculateTotalArmorBonus();
Inventory->CalculateTotalDamageBonus();

// Status
Inventory->GetCurrentInventoryWeight();
Inventory->IsInventoryFull();
Inventory->GetAvailableSlots();

// Currency
Inventory->AddGold(100);
Inventory->SpendGold(50);
Inventory->GetGold();

// Utility
Inventory->SortInventory();
Inventory->ClearInventory();
```

### ?? Quests
```cpp
// Quest Management
Quests->RegisterQuest(newQuest);
Quests->AcceptQuest("questID");
Quests->CompleteQuest("questID");
Quests->FailQuest("questID");
Quests->AbandonQuest("questID");

// Progress
Quests->UpdateQuestProgress("questID", "objectiveID", amount);
Quests->GetQuest("questID");

// Filtering
Quests->GetAvailableQuestsForLevel(playerLevel);
Quests->GetTotalCompletedQuests();

// Individual Quest
Quest->AcceptQuest();
Quest->UpdateObjective("objectiveID", amount);
Quest->CompleteQuest();
Quest->FailQuest();
Quest->AbandonQuest();
Quest->GetCompletionPercentage();
Quest->IsAllObjectivesComplete();
```

### ?? Status Effects
```cpp
// Apply & Remove
Effects->ApplyEffect(effect);
Effects->RemoveEffect("effectID");
Effects->RemoveEffectByType(EStatusEffectType::Poison);

// Updates
Effects->UpdateEffects(deltaTime); // Called by manager

// Query
Effects->GetEffect("effectID");
Effects->HasEffect(EStatusEffectType::Poison);
Effects->GetActiveEffectCount();
Effects->GetTotalStatModifier(EStatusEffectType::Buff);

// Utility
Effects->ClearAllEffects();
Effects->CleansPoison();
Effects->IsImmobilized();
Effects->IsSlowed();
```

---

## ?? Status Effect Types

```cpp
EStatusEffectType::Poison          // Damage over time
EStatusEffectType::Burn            // Burning damage
EStatusEffectType::Freeze          // Slow/immobilize
EStatusEffectType::Stun            // Immobilize
EStatusEffectType::Bleed           // Bleed damage
EStatusEffectType::Curse           // Stat reduction
EStatusEffectType::Buff            // Stat increase
EStatusEffectType::Debuff          // Stat decrease
EStatusEffectType::Regeneration    // Healing over time
EStatusEffectType::Shield          // Damage reduction
```

---

## ?? Common Stat Types

```cpp
ECharacterStatType::Strength       // Physical damage
ECharacterStatType::Intelligence   // Magic damage
ECharacterStatType::Vitality       // Health
ECharacterStatType::Endurance      // Stamina
ECharacterStatType::Defense        // Armor
ECharacterStatType::Dexterity      // Attack speed
```

---

## ?? Item Types

```cpp
EItemType::Weapon
EItemType::Armor
EItemType::Consumable
EItemType::Miscellaneous
EItemType::Equipment
```

---

## ?? Item Rarity

```cpp
EItemRarity::Common        // White
EItemRarity::Uncommon      // Green
EItemRarity::Rare          // Blue
EItemRarity::Epic          // Purple
EItemRarity::Legendary     // Orange/Gold
```

---

## ??? Equipment Slots

```cpp
EEquipmentSlot::Head
EEquipmentSlot::Chest
EEquipmentSlot::Legs
EEquipmentSlot::Feet
EEquipmentSlot::MainHand
EEquipmentSlot::OffHand
EEquipmentSlot::Accessory1
EEquipmentSlot::Accessory2
```

---

## ?? Quest Types

```cpp
EQuestType::Kill          // Defeat enemies
EQuestType::Collect       // Gather items
EQuestType::Explore       // Visit locations
EQuestType::Rescue        // Save NPCs
EQuestType::Escort        // Guard NPCs
EQuestType::Defend        // Protect area
EQuestType::Puzzle        // Solve puzzle
EQuestType::Custom        // Custom quest
```

---

## ?? Quest Status

```cpp
EQuestStatus::Unaccepted     // Not started
EQuestStatus::Active         // In progress
EQuestStatus::InProgress     // Objectives updating
EQuestStatus::ReadyToTurnIn  // Can complete
EQuestStatus::Completed      // Finished
EQuestStatus::Failed         // Quest failed
EQuestStatus::Abandoned      // Abandoned by player
```

---

## ?? Event Binding Examples

### In C++
```cpp
// Bind event to function
Progression->OnLevelUp.AddDynamic(this, &AMyCharacter::OnLevelUp);
Combat->OnDamageDealt.AddDynamic(this, &AMyCharacter::OnTakeDamage);
Inventory->OnItemAdded.AddDynamic(this, &AMyCharacter::OnItemPickup);
Quests->OnQuestCompleted.AddDynamic(this, &AMyCharacter::OnQuestDone);

// Event handler
void AMyCharacter::OnLevelUp(int32 NewLevel, int32 SkillPoints)
{
    // Handle level up
}
```

### In Blueprint
1. Get System Manager (Cast to ARPGGameSystemsManager)
2. Get desired system (Get Progression System, etc.)
3. Drag system into event graph
4. Right-click ? Bind Event ? Select event
5. Connect to your nodes

---

## ?? Create Structures

### Create a Skill
```cpp
FSkillData Fireball;
Fireball.SkillName = "Fireball";
Fireball.SkillDescription = "Launch a fireball";
Fireball.SkillLevel = 1;
Fireball.MaxSkillLevel = 10;
Fireball.ManaCost = 25.0f;
Fireball.Cooldown = 5.0f;
Progression->LearnSkill(Fireball);
```

### Create an Item
```cpp
FInventoryItem Sword;
Sword.ItemID = "iron_sword";
Sword.ItemName = "Iron Sword";
Sword.ItemType = EItemType::Equipment;
Sword.Rarity = EItemRarity::Uncommon;
Sword.Weight = 5.0f;
Sword.SellValue = 100;
Sword.bStackable = false;
Inventory->AddItem(Sword);
```

### Create a Quest
```cpp
UQuest* Quest = NewObject<UQuest>();
Quest->QuestID = "first_quest";
Quest->QuestTitle = "Defeat Goblins";
Quest->QuestType = EQuestType::Kill;
Quest->RecommendedLevel = 1;

FQuestObjective Objective;
Objective.ObjectiveID = "kill_goblins";
Objective.ObjectiveDescription = "Kill 10 goblins";
Objective.TargetCount = 10;
Quest->Objectives.Add(Objective);

Quest->QuestReward.ExperienceReward = 500;
Quest->QuestReward.GoldReward = 200;

Quests->RegisterQuest(Quest);
```

### Create an Effect
```cpp
FStatusEffect Poison;
Poison.EffectID = "poison_001";
Poison.EffectType = EStatusEffectType::Poison;
Poison.EffectName = "Poison";
Poison.Duration = 30.0f;
Poison.TickInterval = 1.0f;
Poison.TickDamage = 5.0f;
Poison.bCanStack = true;
Poison.MaxStacks = 5;
Effects->ApplyEffect(Poison);
```

---

## ?? Global Settings

```cpp
// In RPGGameSystemsManager
GameSystems->GlobalDifficultyMultiplier = 1.5f;  // Hard mode
GameSystems->bEnablePvP = true;
GameSystems->bEnablePermaDeath = false;
GameSystems->MaxPlayersInParty = 4;
```

---

## ?? Common Patterns

### Level Up Flow
```cpp
Progression->GainExperience(100);
// Automatically triggers OnLevelUp if threshold reached
// OnLevelUp gives skill points
// Player allocates points
Progression->IncreaseStatByPoints(ECharacterStatType::Strength, 5);
```

### Combat Flow
```cpp
Combat->StartCombat();
float Damage = Combat->CalculateDamage(ECharacterStatType::Strength);
float FinalDamage = Combat->ApplyDefense(Damage, ECharacterStatType::Strength);
Combat->TakeDamage(FinalDamage);

// Apply status effect
FStatusEffect Burn;
Burn.EffectType = EStatusEffectType::Burn;
Effects->ApplyEffect(Burn);

Combat->EndCombat();
```

### Quest Flow
```cpp
Quests->AcceptQuest("quest_001");

// During gameplay
Quests->UpdateQuestProgress("quest_001", "kill_enemies", 1);

// Check completion
UQuest* Quest = Quests->GetQuest("quest_001");
if (Quest->IsAllObjectivesComplete())
{
    Quests->CompleteQuest("quest_001");
    // Rewards are given to player
}
```

### Inventory Flow
```cpp
Inventory->AddItem(LootItem);
Inventory->AddGold(50);

if (!Inventory->IsInventoryFull())
{
    // Can pick up more
}

Inventory->EquipItem("sword_id", EEquipmentSlot::MainHand);
float DamageBonus = Inventory->CalculateTotalDamageBonus();
```

---

## ?? Documentation Links

- **Full Documentation:** `UnrealEngine5/RPG_SYSTEMS_COMPLETE_DOCUMENTATION.md`
- **Implementation Summary:** `RPG_SYSTEMS_IMPLEMENTATION_COMPLETE.md`
- **System Files:** `UnrealEngine5/Source/RPGProject/Systems/`

---

## ? Checklist for Game Development

- [ ] Access systems from character
- [ ] Bind events to UI
- [ ] Create item database
- [ ] Design enemy stats
- [ ] Create quest content
- [ ] Implement loot drops
- [ ] Add ability effects
- [ ] Create NPC questgivers
- [ ] Implement save/load
- [ ] Balance difficulty
- [ ] Add VFX/SFX
- [ ] Playtest extensively

---

## ?? Pro Tips

1. **Always check if pointer is valid** before using systems
2. **Bind events early** in BeginPlay
3. **Use enums** instead of strings for safety
4. **Test all edge cases** (full inventory, no mana, etc.)
5. **Monitor performance** with complex effect stacking
6. **Document your changes** when extending systems
7. **Use Blueprint children** for variation
8. **Playtest frequently** to balance difficulty

---

## ?? You're Ready!

You have everything needed to build a complete RPG. Start creating content and enjoy! ???

For detailed information on any system, refer to `RPG_SYSTEMS_COMPLETE_DOCUMENTATION.md`
