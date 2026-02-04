-- ============================================
-- RPG/MMORPG Database - SEED DATA
-- Sample Data for All Tables
-- ============================================

-- ============================================
-- ZONES
-- ============================================

SET IDENTITY_INSERT Zones ON;

INSERT INTO Zones (ZoneId, ZoneName, Description, ZoneType, BiomeType, RecommendedLevel, HasShop, HasInn, HasBank, HasAuctionHouse, HasFlightMaster) VALUES
(1, 'Greenleaf Village', 'A peaceful starting village', 1, 0, 1, 1, 1, 1, 0, 0),
(2, 'Whispering Woods', 'A quiet forest near the village', 2, 1, 2, 0, 0, 0, 0, 0),
(3, 'Stormwind City', 'The grand capital of the Alliance', 4, 0, 1, 1, 1, 1, 1, 1),
(4, 'Orgrimmar', 'The mighty fortress city of the Horde', 4, 3, 1, 1, 1, 1, 1, 1),
(5, 'Ironforge', 'The underground fortress of the dwarves', 13, 9, 1, 1, 1, 1, 1, 1),
(6, 'Blackrock Depths', 'Ancient dark iron dwarf city', 6, 9, 52, 0, 0, 0, 0, 0),
(7, 'Molten Core', 'A volcanic lair beneath Blackrock Mountain', 6, 10, 60, 0, 0, 0, 0, 0),
(8, 'Elwynn Forest', 'Peaceful starting zone for humans', 2, 1, 1, 0, 0, 0, 0, 0),
(9, 'Durotar', 'Harsh desert homeland of orcs', 7, 3, 1, 0, 0, 0, 0, 0);

SET IDENTITY_INSERT Zones OFF;

-- ============================================
-- ITEMS - WEAPONS
-- ============================================

SET IDENTITY_INSERT Items ON;

INSERT INTO Items (ItemId, ItemName, Description, ItemType, Quality, ItemLevel, RequiredLevel, MaxStack, Value, EquipmentSlot, WeaponType, StatsJson) VALUES
-- Weapons
(1, 'Rusty Sword', 'An old worn sword', 0, 0, 1, 1, 1, 5, 16, 0, '{"Attack": 5}'),
(2, 'Iron Sword', 'A sturdy iron blade', 0, 1, 10, 5, 1, 100, 16, 0, '{"Attack": 15, "Strength": 3}'),
(3, 'Steel Longsword', 'Well-crafted steel blade', 0, 2, 25, 15, 1, 500, 16, 0, '{"Attack": 35, "Strength": 8, "Stamina": 5}'),
(4, 'Flameblade', 'A sword wreathed in flames', 0, 3, 50, 40, 1, 5000, 16, 0, '{"Attack": 75, "Strength": 20, "FireDamage": 15}'),
(5, 'Thunderfury, Blessed Blade of the Windseeker', 'Legendary sword crackling with lightning', 0, 5, 80, 60, 1, 100000, 16, 0, '{"Attack": 150, "Strength": 50, "Agility": 30, "LightningDamage": 50}'),
(6, 'Simple Staff', 'A basic wooden staff', 0, 0, 1, 1, 1, 10, 16, 6, '{"MagicPower": 8}'),
(7, 'Arcane Staff', 'Staff channeling arcane energy', 0, 3, 40, 35, 1, 4000, 16, 6, '{"MagicPower": 60, "Intelligence": 25, "Stamina": 15}'),
(8, 'Hunter''s Bow', 'A well-crafted hunting bow', 0, 2, 30, 20, 1, 800, 18, 8, '{"Attack": 40, "Agility": 12, "CriticalStrike": 8}'),

-- Armor
(9, 'Cloth Robe', 'Basic cloth robe', 1, 0, 1, 1, 1, 10, 4, NULL, '{"Armor": 5, "Intelligence": 2}'),
(10, 'Leather Vest', 'Sturdy leather armor', 1, 1, 15, 10, 1, 150, 4, NULL, '{"Armor": 25, "Agility": 8, "Stamina": 10}'),
(11, 'Chainmail Armor', 'Heavy metal chain links', 1, 2, 35, 25, 1, 1500, 4, NULL, '{"Armor": 60, "Strength": 15, "Stamina": 20}'),
(12, 'Platemail of the Titan', 'Legendary plate armor', 1, 4, 70, 55, 1, 50000, 4, NULL, '{"Armor": 200, "Strength": 40, "Stamina": 60, "Defense": 30}'),

-- Consumables
(13, 'Health Potion', 'Restores 50 HP', 2, 1, 1, 1, 20, 25, NULL, NULL, '{"HealAmount": 50}'),
(14, 'Mana Potion', 'Restores 30 MP', 2, 1, 1, 1, 20, 20, NULL, NULL, '{"ManaAmount": 30}'),
(15, 'Elixir of Strength', 'Increases Strength by 10 for 30 minutes', 2, 2, 20, 15, 5, 100, NULL, NULL, '{"Strength": 10, "Duration": 1800}'),
(16, 'Greater Healing Potion', 'Restores 150 HP', 2, 2, 30, 20, 20, 75, NULL, NULL, '{"HealAmount": 150}'),

-- Quest Items
(17, 'Ancient Artifact', 'A mysterious ancient relic', 3, 3, 1, 1, 1, 0, NULL, NULL, NULL),
(18, 'Dragon Scale', 'Scale from an ancient dragon', 3, 4, 60, 1, 1, 500, NULL, NULL, NULL),

-- Materials
(19, 'Copper Ore', 'Raw copper ore', 5, 0, 1, 1, 20, 5, NULL, NULL, NULL),
(20, 'Iron Ore', 'Raw iron ore', 5, 1, 10, 1, 20, 20, NULL, NULL, NULL),
(21, 'Mithril Ore', 'Rare mithril ore', 5, 2, 30, 1, 20, 100, NULL, NULL, NULL),
(22, 'Magic Herb', 'Herb with magical properties', 5, 1, 15, 1, 20, 30, NULL, NULL, NULL);

SET IDENTITY_INSERT Items OFF;

-- ============================================
-- WEAPONS DETAILS
-- ============================================

SET IDENTITY_INSERT Weapons ON;

INSERT INTO Weapons (WeaponId, ItemId, WeaponType, MinDamage, MaxDamage, AttackSpeed, Range) VALUES
(1, 1, 0, 3, 8, 2.0, 5.0),
(2, 2, 0, 12, 20, 2.2, 5.0),
(3, 3, 0, 30, 45, 2.4, 5.0),
(4, 4, 0, 65, 95, 2.6, 5.0),
(5, 5, 0, 135, 185, 1.8, 5.0),
(6, 6, 2, 5, 10, 3.0, 30.0),
(7, 7, 2, 50, 75, 2.8, 30.0),
(8, 8, 5, 35, 55, 2.0, 40.0);

SET IDENTITY_INSERT Weapons OFF;

-- ============================================
-- ARMOR DETAILS
-- ============================================

SET IDENTITY_INSERT Armor ON;

INSERT INTO Armor (ArmorId, ItemId, ArmorType, ArmorValue) VALUES
(1, 9, 0, 5),
(2, 10, 1, 25),
(3, 11, 2, 60),
(4, 12, 3, 200);

SET IDENTITY_INSERT Armor OFF;

-- ============================================
-- NPCS
-- ============================================

SET IDENTITY_INSERT NPCs ON;

INSERT INTO NPCs (NpcId, NpcName, Title, NpcType, Level, Health, ZoneId, PositionX, PositionY, PositionZ, IsVendor, IsQuestGiver, IsTrainer, GreetingText) VALUES
(1, 'Guard Williams', 'City Guard', 0, 10, 500, 1, 100.0, 0.0, 50.0, 0, 0, 0, 'Welcome to Greenleaf Village, traveler.'),
(2, 'Merchant Tom', 'General Goods', 0, 5, 100, 1, 110.0, 0.0, 55.0, 1, 0, 0, 'Looking for supplies? I have the best deals!'),
(3, 'Elder Sage', 'Village Elder', 1, 1, 50, 1, 105.0, 0.0, 60.0, 0, 1, 0, 'Ah, a new hero arrives! I have a task for you.'),
(4, 'Weapon Master Bran', 'Arms Trainer', 2, 50, 2000, 3, 200.0, 10.0, 150.0, 0, 0, 1, 'Ready to hone your combat skills?'),
(5, 'Mage Instructor Elena', 'Arcane Studies', 2, 45, 1500, 3, 180.0, 15.0, 160.0, 0, 0, 1, 'The arcane arts require dedication and practice.'),
(6, 'Banker Goldsworth', 'Bank Manager', 0, 30, 1000, 3, 190.0, 5.0, 140.0, 0, 0, 0, 1, 'Your valuables are safe with us.');

SET IDENTITY_INSERT NPCs OFF;

-- ============================================
-- ENEMIES
-- ============================================

SET IDENTITY_INSERT Enemies ON;

INSERT INTO Enemies (EnemyId, EnemyName, EnemyType, EnemyRank, Level, Health, Mana, Attack, Defense, MagicPower, ExperienceReward, GoldReward, Description, AbilitiesJson) VALUES
(1, 'Forest Wolf', 0, 0, 5, 100, 0, 12, 3, 0, 50, 5, 'A common wolf found in forests', '["Bite", "Howl"]'),
(2, 'Cave Bear', 0, 0, 8, 200, 0, 18, 5, 0, 80, 10, 'A powerful bear dwelling in caves', '["Maul", "Swipe"]'),
(3, 'Bandit Thug', 1, 0, 10, 180, 0, 20, 5, 0, 100, 25, 'A common highway bandit', '["Backstab", "Throw Dagger"]'),
(4, 'Zombie', 2, 0, 12, 200, 0, 15, 3, 0, 90, 8, 'An undead shambling corpse', '["Infectious Bite"]'),
(5, 'Skeleton Warrior', 2, 0, 18, 300, 0, 28, 10, 0, 150, 20, 'Reanimated skeleton soldier', '["Bone Strike", "Shield Wall"]'),
(6, 'Dark Mage', 1, 1, 35, 800, 1000, 30, 15, 60, 600, 75, 'Evil sorcerer wielding dark magic', '["Shadow Bolt", "Fear", "Dark Shield"]'),
(7, 'Orc Warmaster', 1, 1, 40, 2000, 0, 80, 30, 0, 1500, 200, 'Elite orc warrior commander', '["Cleave", "Battle Shout", "Enrage"]'),
(8, 'Ancient Dragon', 10, 3, 65, 15000, 5000, 180, 80, 120, 8000, 2000, 'Massive ancient wyrm', '["Dragon Breath", "Tail Sweep", "Wing Storm", "Ancient Fury"]'),
(9, 'Lich King', 2, 4, 70, 100000, 20000, 200, 100, 150, 50000, 10000, 'Undead lord of the frozen wastes', '["Death Coil", "Army of the Dead", "Frostmourne Strike", "Soul Reaper"]'),
(10, 'Ragnaros the Firelord', 5, 5, 60, 150000, 0, 250, 150, 200, 100000, 50000, 'Elemental lord of fire', '["Lava Burst", "Flame Wave", "Submerge", "Wrath of Ragnaros"]');

SET IDENTITY_INSERT Enemies OFF;

-- ============================================
-- ENEMY LOOT TABLES
-- ============================================

SET IDENTITY_INSERT EnemyLootTable ON;

INSERT INTO EnemyLootTable (LootId, EnemyId, ItemId, DropChance, MinQuantity, MaxQuantity) VALUES
(1, 1, 13, 0.3, 1, 1),
(2, 2, 13, 0.4, 1, 2),
(3, 2, 10, 0.1, 1, 1),
(4, 3, 14, 0.25, 1, 1),
(5, 3, 2, 0.05, 1, 1),
(6, 7, 11, 0.15, 1, 1),
(7, 7, 3, 0.08, 1, 1),
(8, 8, 18, 0.8, 1, 3),
(9, 8, 4, 0.2, 1, 1),
(10, 10, 5, 0.05, 1, 1);

SET IDENTITY_INSERT EnemyLootTable OFF;

-- ============================================
-- DUNGEONS
-- ============================================

SET IDENTITY_INSERT Dungeons ON;

INSERT INTO Dungeons (DungeonId, DungeonName, DungeonType, Description, MinLevel, MaxLevel, MinPlayers, MaxPlayers, EstimatedTime, LocationZoneId) VALUES
(1, 'The Deadmines', 0, 'Abandoned mine taken over by bandits', 15, 21, 5, 5, 30, 1),
(2, 'Blackrock Depths', 0, 'Ancient dark iron dwarf city deep underground', 52, 60, 5, 5, 90, 6),
(3, 'Molten Core', 1, 'Volcanic lair of Ragnaros the Firelord', 60, 60, 20, 40, 180, 7),
(4, 'Icecrown Citadel', 1, 'Fortress of the Lich King', 70, 70, 10, 25, 240, 9);

SET IDENTITY_INSERT Dungeons OFF;

-- ============================================
-- DUNGEON BOSSES
-- ============================================

SET IDENTITY_INSERT DungeonBosses ON;

INSERT INTO DungeonBosses (BossId, DungeonId, EnemyId, BossOrder, IsRaidBoss) VALUES
(1, 1, 3, 1, 0),
(2, 1, 7, 2, 0),
(3, 2, 6, 1, 0),
(4, 2, 8, 2, 0),
(5, 3, 10, 1, 1),
(6, 4, 9, 1, 1);

SET IDENTITY_INSERT DungeonBosses OFF;

-- ============================================
-- QUESTS
-- ============================================

SET IDENTITY_INSERT Quests ON;

INSERT INTO Quests (QuestId, QuestName, Description, QuestType, RequiredLevel, ExperienceReward, GoldReward, QuestGiverNpcId, IsRepeatable) VALUES
(1, 'Welcome to Greenleaf', 'Speak with Guard Williams to learn about the village.', 0, 1, 100, 0, 3, 0),
(2, 'Wolf Problem', 'The wolves have been attacking villagers. Kill 10 Forest Wolves.', 1, 3, 500, 50, 3, 0),
(3, 'Gather Herbs', 'Collect 10 Magic Herbs for the village healer.', 1, 5, 400, 30, 3, 0),
(4, 'Clear the Mine', 'Enter the Deadmines and defeat the Bandit Leader.', 0, 15, 2000, 500, 3, 0),
(5, 'Dragon Threat', 'An Ancient Dragon has been terrorizing the land. Defeat it!', 0, 60, 10000, 5000, 3, 0),
(6, 'Daily Fishing', 'Catch 5 fish from any water source.', 2, 10, 200, 20, 2, 1);

SET IDENTITY_INSERT Quests OFF;

-- ============================================
-- QUEST OBJECTIVES
-- ============================================

SET IDENTITY_INSERT QuestObjectives ON;

INSERT INTO QuestObjectives (ObjectiveId, QuestId, ObjectiveType, Description, TargetId, RequiredCount) VALUES
(1, 1, 2, 'Speak with Guard Williams', 1, 1),
(2, 2, 0, 'Kill Forest Wolves', 1, 10),
(3, 3, 1, 'Collect Magic Herbs', 22, 10),
(4, 4, 0, 'Defeat Bandit Leader', 3, 1),
(5, 5, 0, 'Slay the Ancient Dragon', 8, 1);

SET IDENTITY_INSERT QuestObjectives OFF;

-- ============================================
-- PROFESSIONS
-- ============================================

SET IDENTITY_INSERT Professions ON;

INSERT INTO Professions (ProfessionId, ProfessionName, ProfessionType, Description, MaxSkill) VALUES
(1, 'Blacksmithing', 1, 'Craft weapons and armor from metal', 300),
(2, 'Alchemy', 1, 'Create potions and elixirs', 300),
(3, 'Enchanting', 1, 'Add magical properties to equipment', 300),
(4, 'Herbalism', 0, 'Gather herbs from plants', 300),
(5, 'Mining', 0, 'Extract ore from mineral deposits', 300),
(6, 'Skinning', 0, 'Harvest leather from beasts', 300),
(7, 'Tailoring', 1, 'Create cloth armor', 300),
(8, 'Leatherworking', 1, 'Craft leather armor', 300),
(9, 'Engineering', 1, 'Build gadgets and explosives', 300),
(10, 'Jewelcrafting', 1, 'Cut gems and craft jewelry', 300),
(11, 'Cooking', 2, 'Prepare food that provides buffs', 300),
(12, 'Fishing', 2, 'Catch fish from water', 300);

SET IDENTITY_INSERT Professions OFF;

-- ============================================
-- RECIPES
-- ============================================

SET IDENTITY_INSERT Recipes ON;

INSERT INTO Recipes (RecipeId, RecipeName, ProfessionId, RequiredSkill, CraftedItemId, CraftedQuantity, CraftTime) VALUES
(1, 'Iron Sword', 1, 50, 2, 1, 10),
(2, 'Steel Longsword', 1, 150, 3, 1, 20),
(3, 'Health Potion', 2, 1, 13, 1, 3),
(4, 'Greater Healing Potion', 2, 150, 16, 1, 5),
(5, 'Elixir of Strength', 2, 100, 15, 1, 8);

SET IDENTITY_INSERT Recipes OFF;

-- ============================================
-- RECIPE MATERIALS
-- ============================================

SET IDENTITY_INSERT RecipeMaterials ON;

INSERT INTO RecipeMaterials (MaterialId, RecipeId, ItemId, Quantity) VALUES
(1, 1, 20, 8),
(2, 2, 21, 10),
(3, 3, 22, 1),
(4, 4, 22, 3),
(5, 5, 22, 2);

SET IDENTITY_INSERT RecipeMaterials OFF;

-- ============================================
-- ACHIEVEMENTS
-- ============================================

SET IDENTITY_INSERT Achievements ON;

INSERT INTO Achievements (AchievementId, AchievementName, Description, Category, Points) VALUES
(1, 'First Kill', 'Defeat your first enemy', 0, 10),
(2, 'Level 10', 'Reach level 10', 1, 10),
(3, 'Level 50', 'Reach level 50', 1, 50),
(4, 'Level 60', 'Reach maximum level', 1, 100),
(5, 'Explorer', 'Discover 20 zones', 2, 25),
(6, 'World Explorer', 'Discover all 72 zones', 2, 100),
(7, 'Dungeon Master', 'Complete 10 dungeons', 0, 50),
(8, 'Raid Leader', 'Complete your first raid', 0, 100),
(9, 'Wealthy', 'Accumulate 10,000 gold', 3, 30),
(10, 'Legendary', 'Obtain a legendary item', 4, 150),
(11, 'Dragon Slayer', 'Defeat an ancient dragon', 0, 100),
(12, 'Fully Equipped', 'Have epic item in every equipment slot', 4, 75),
(13, 'Master Crafter', 'Reach 300 skill in any profession', 5, 50),
(14, 'Arena Champion', 'Reach 2000 Arena rating', 6, 100);

SET IDENTITY_INSERT Achievements OFF;

-- ============================================
-- FACTIONS
-- ============================================

SET IDENTITY_INSERT Factions ON;

INSERT INTO Factions (FactionId, FactionName, Description, IsHostile) VALUES
(1, 'Alliance', 'The noble Alliance of humans, dwarves, and elves', 0),
(2, 'Horde', 'The mighty Horde of orcs, trolls, and undead', 0),
(3, 'Argent Dawn', 'Crusaders against the undead scourge', 0),
(4, 'Cenarion Circle', 'Druids protecting nature', 0),
(5, 'Defias Brotherhood', 'Bandit organization', 1),
(6, 'Scourge', 'Undead army of the Lich King', 1);

SET IDENTITY_INSERT Factions OFF;

-- ============================================
-- MOUNTS
-- ============================================

SET IDENTITY_INSERT Mounts ON;

INSERT INTO Mounts (MountId, MountName, MountType, SpeedBonus, RequiredLevel, CanFly, Description) VALUES
(1, 'Brown Horse', 0, 60, 20, 0, 'A reliable brown horse'),
(2, 'Black Stallion', 0, 100, 40, 0, 'A fast and majestic black horse'),
(3, 'Wind Rider', 1, 150, 60, 1, 'A swift flying mount'),
(4, 'Gryphon', 1, 150, 60, 1, 'Majestic flying gryphon'),
(5, 'Sea Turtle', 2, 100, 30, 0, 'Aquatic mount for underwater travel'),
(6, 'Spectral Tiger', 0, 100, 1, 0, 'Rare ethereal tiger mount');

SET IDENTITY_INSERT Mounts OFF;

-- ============================================
-- PETS
-- ============================================

SET IDENTITY_INSERT Pets ON;

INSERT INTO Pets (PetId, PetName, PetType, Species, BaseHealth, BaseAttack, BaseDefense) VALUES
(1, 'Wolf Pup', 0, 1, 100, 15, 5),
(2, 'Rabbit', 2, 2, 50, 5, 2),
(3, 'Hawk', 0, 3, 80, 20, 3),
(4, 'Black Cat', 2, 4, 60, 8, 4),
(5, 'Mini Dragon', 1, 5, 150, 25, 10);

SET IDENTITY_INSERT Pets OFF;

-- ============================================
-- COMPANIONS
-- ============================================

SET IDENTITY_INSERT Companions ON;

INSERT INTO Companions (CompanionId, CompanionName, Class, Race, BaseLevel, BaseHealth, BaseAttack, BaseDefense, BaseMagicPower, BackgroundStory) VALUES
(1, 'Lyra Swiftblade', 2, 1, 10, 200, 20, 10, 5, 'A rogue elf seeking redemption for her past.'),
(2, 'Thorgrim Ironhammer', 0, 2, 15, 400, 35, 25, 0, 'A dwarven warrior with unmatched strength.'),
(3, 'Elara Moonwhisper', 1, 10, 12, 150, 8, 5, 40, 'A night elf mage studying ancient arcane secrets.'),
(4, 'Gorak the Fierce', 0, 3, 20, 500, 45, 20, 0, 'An orc warrior seeking honor in battle.');

SET IDENTITY_INSERT Companions OFF;

-- ============================================
-- STATUS EFFECTS
-- ============================================

SET IDENTITY_INSERT StatusEffects ON;

INSERT INTO StatusEffects (EffectId, EffectName, Description, EffectType, CCType, Duration, TickInterval, MaxStacks, IsDispellable, StatModifiersJson, DamagePerTick, HealPerTick) VALUES
(1, 'Poison', 'Takes damage over time', 2, NULL, 15.0, 3.0, 5, 1, NULL, 10, 0),
(2, 'Regeneration', 'Restores health over time', 3, NULL, 15.0, 5.0, 1, 1, NULL, 0, 15),
(3, 'Haste', 'Increased attack and cast speed', 0, NULL, 30.0, NULL, 1, 1, '{"Haste": 20}', 0, 0),
(4, 'Stunned', 'Cannot move or act', 4, 1, 5.0, NULL, 1, 0, NULL, 0, 0),
(5, 'Slow', 'Movement speed reduced', 1, 8, 10.0, NULL, 1, 1, '{"MovementSpeed": -30}', 0, 0),
(6, 'Shield', 'Absorbs damage', 0, NULL, 30.0, NULL, 1, 0, '{"Shield": 100}', 0, 0),
(7, 'Strength Buff', 'Strength increased', 0, NULL, 60.0, NULL, 1, 1, '{"Strength": 20}', 0, 0),
(8, 'Bleed', 'Bleeding wound', 2, NULL, 12.0, 2.0, 3, 1, NULL, 15, 0);

SET IDENTITY_INSERT StatusEffects OFF;

-- ============================================
-- WORLD EVENTS
-- ============================================

SET IDENTITY_INSERT WorldEvents ON;

INSERT INTO WorldEvents (EventId, EventName, Description, EventType, Duration, StartTime, IsActive) VALUES
(1, 'Harvest Festival', 'Celebration with bonus rewards and activities', 0, 604800, DATEADD(day, 30, GETDATE()), 0),
(2, 'Winter Veil', 'Winter celebration with special quests', 0, 1209600, DATEADD(day, 60, GETDATE()), 0),
(3, 'Meteor Shower', 'Meteors rain from the sky with valuable materials', 1, 3600, NULL, 0),
(4, 'Dragon Attack', 'A dragon attacks major cities', 2, 7200, NULL, 0);

SET IDENTITY_INSERT WorldEvents OFF;

PRINT 'Seed data inserted successfully!';
