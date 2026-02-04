-- =============================================
-- CONTINUATION: 400+ ITEMS DATABASE PART 4
-- Shoulders, Boots, Gloves, Belts, Consumables, Materials, Quest Items
-- =============================================

USE RPGGame;
GO

-- =============================================
-- ARMOR - SHOULDERS (20 items)
-- =============================================

INSERT INTO Items (ItemName, Description, ItemType, Rarity, RequiredLevel, MaxStackSize, VendorPrice, IsTradeable, IsQuestItem, Stats, IconPath) VALUES
('Cloth Mantle', 'Simple shoulder covering', 'Armor', 'Common', 1, 1, 4, 1, 0, '{"Armor":"3","ArmorType":"Cloth","Slot":"Shoulders","Intelligence":"1"}', '/icons/armor/shoulder_cloth1.png'),
('Arcanist Mantle', 'Magical pauldrons', 'Armor', 'Epic', 40, 1, 1800, 1, 0, '{"Armor":"45","ArmorType":"Cloth","Slot":"Shoulders","Intelligence":"28","SpellPower":"42"}', '/icons/armor/shoulder_cloth2.png'),
('Prophecy Mantle', 'Divine shoulders', 'Armor', 'Legendary', 60, 1, 14000, 1, 0, '{"Armor":"72","ArmorType":"Cloth","Slot":"Shoulders","Intelligence":"52","SpellPower":"88"}', '/icons/armor/shoulder_cloth3.png'),
('Leather Spaulders', 'Basic protection', 'Armor', 'Common', 1, 1, 6, 1, 0, '{"Armor":"5","ArmorType":"Leather","Slot":"Shoulders","Agility":"2"}', '/icons/armor/shoulder_leather1.png'),
('Bloodfang Spaulders', 'Legendary rogue shoulders', 'Armor', 'Epic', 40, 1, 2000, 1, 0, '{"Armor":"65","ArmorType":"Leather","Slot":"Shoulders","Agility":"32","AttackPower":"45"}', '/icons/armor/shoulder_leather2.png'),
('Assassin''s Mantle', 'Perfect for stealth', 'Armor', 'Legendary', 60, 1, 16000, 1, 0, '{"Armor":"98","ArmorType":"Leather","Slot":"Shoulders","Agility":"58","CritChance":"4"}', '/icons/armor/shoulder_leather3.png'),
('Mail Pauldrons', 'Chainmail shoulders', 'Armor', 'Common', 1, 1, 8, 1, 0, '{"Armor":"8","ArmorType":"Mail","Slot":"Shoulders","Agility":"2","Stamina":"1"}', '/icons/armor/shoulder_mail1.png'),
('Dragonstalker Spaulders', 'Dragon scale pauldrons', 'Armor', 'Epic', 40, 1, 2400, 1, 0, '{"Armor":"88","ArmorType":"Mail","Slot":"Shoulders","Agility":"35","AttackPower":"58"}', '/icons/armor/shoulder_mail2.png'),
('Stormrage Pauldrons', 'Storm empowered', 'Armor', 'Legendary', 60, 1, 18000, 1, 0, '{"Armor":"132","ArmorType":"Mail","Slot":"Shoulders","Agility":"62","AllStats":"15"}', '/icons/armor/shoulder_mail3.png'),
('Iron Pauldrons', 'Heavy shoulder armor', 'Armor', 'Common', 1, 1, 12, 1, 0, '{"Armor":"12","ArmorType":"Plate","Slot":"Shoulders","Strength":"3","Stamina":"2"}', '/icons/armor/shoulder_plate1.png'),
('Valor Pauldrons', 'Courageous shoulders', 'Armor', 'Rare', 25, 1, 620, 1, 0, '{"Armor":"72","ArmorType":"Plate","Slot":"Shoulders","Strength":"24","Stamina":"18"}', '/icons/armor/shoulder_plate2.png'),
('Judgment Spaulders', 'Divine protection', 'Armor', 'Epic', 40, 1, 2800, 1, 0, '{"Armor":"122","ArmorType":"Plate","Slot":"Shoulders","Strength":"42","AllStats":"8"}', '/icons/armor/shoulder_plate3.png'),
('Pauldrons of Might', 'Ultimate warrior shoulders', 'Armor', 'Legendary', 60, 1, 22000, 1, 0, '{"Armor":"178","ArmorType":"Plate","Slot":"Shoulders","Strength":"72","Defense":"35"}', '/icons/armor/shoulder_plate4.png'),
('Dragon Scale Spaulders', 'Forged from dragon', 'Armor', 'Epic', 45, 1, 3200, 1, 0, '{"Armor":"95","ArmorType":"Mail","Slot":"Shoulders","Agility":"38","FireResistance":"25"}', '/icons/armor/shoulder_dragon.png'),
('Frozen Mantle', 'Ice eternal', 'Armor', 'Epic', 42, 1, 2900, 1, 0, '{"Armor":"108","ArmorType":"Plate","Slot":"Shoulders","Strength":"35","FrostResistance":"30"}', '/icons/armor/shoulder_frozen.png'),
('Shadow Spaulders', 'Hidden in darkness', 'Armor', 'Epic', 38, 1, 1800, 1, 0, '{"Armor":"58","ArmorType":"Leather","Slot":"Shoulders","Agility":"28","Stealth":"12"}', '/icons/armor/shoulder_shadow.png'),
('Phoenix Spaulders', 'Reborn from ashes', 'Armor', 'Legendary', 58, 1, 20000, 1, 0, '{"Armor":"165","ArmorType":"Plate","Slot":"Shoulders","Strength":"68","FireDamage":"35"}', '/icons/armor/shoulder_phoenix.png'),
('Netherwind Mantle', 'Void touched', 'Armor', 'Epic', 50, 1, 4500, 1, 0, '{"Armor":"62","ArmorType":"Cloth","Slot":"Shoulders","Intelligence":"48","ShadowDamage":"38"}', '/icons/armor/shoulder_nether.png'),
('Demonhide Spaulders', 'Demon skin armor', 'Armor', 'Epic', 48, 1, 4000, 1, 0, '{"Armor":"82","ArmorType":"Leather","Slot":"Shoulders","Agility":"45","DemonSlaying":"20"}', '/icons/armor/shoulder_demon.png'),
('Titansteel Shoulders', 'Unbreakable', 'Armor', 'Legendary', 60, 1, 24000, 1, 0, '{"Armor":"185","ArmorType":"Plate","Slot":"Shoulders","Strength":"78","Stamina":"58"}', '/icons/armor/shoulder_titan.png');

-- =============================================
-- ARMOR - BOOTS (20 items)
-- =============================================

INSERT INTO Items (ItemName, Description, ItemType, Rarity, RequiredLevel, MaxStackSize, VendorPrice, IsTradeable, IsQuestItem, Stats, IconPath) VALUES
('Cloth Shoes', 'Basic footwear', 'Armor', 'Common', 1, 1, 3, 1, 0, '{"Armor":"2","ArmorType":"Cloth","Slot":"Feet","Intelligence":"1"}', '/icons/armor/boots_cloth1.png'),
('Arcanist Boots', 'Magical footwear', 'Armor', 'Epic', 40, 1, 1600, 1, 0, '{"Armor":"38","ArmorType":"Cloth","Slot":"Feet","Intelligence":"25","SpellPower":"38"}', '/icons/armor/boots_cloth2.png'),
('Boots of Prophecy', 'Divine footsteps', 'Armor', 'Legendary', 60, 1, 12000, 1, 0, '{"Armor":"62","ArmorType":"Cloth","Slot":"Feet","Intelligence":"48","SpellPower":"78"}', '/icons/armor/boots_cloth3.png'),
('Leather Boots', 'Supple leather', 'Armor', 'Common', 1, 1, 5, 1, 0, '{"Armor":"4","ArmorType":"Leather","Slot":"Feet","Agility":"2"}', '/icons/armor/boots_leather1.png'),
('Bloodfang Boots', 'Silent steps', 'Armor', 'Epic', 40, 1, 1800, 1, 0, '{"Armor":"55","ArmorType":"Leather","Slot":"Feet","Agility":"28","AttackPower":"42"}', '/icons/armor/boots_leather2.png'),
('Boots of the Assassin', 'Perfect stealth', 'Armor', 'Legendary', 60, 1, 14000, 1, 0, '{"Armor":"85","ArmorType":"Leather","Slot":"Feet","Agility":"52","MovementSpeed":"10%"}', '/icons/armor/boots_leather3.png'),
('Mail Sabatons', 'Chain footwear', 'Armor', 'Common', 1, 1, 7, 1, 0, '{"Armor":"6","ArmorType":"Mail","Slot":"Feet","Agility":"2","Stamina":"1"}', '/icons/armor/boots_mail1.png'),
('Dragonstalker Greaves', 'Dragon scale boots', 'Armor', 'Epic', 40, 1, 2200, 1, 0, '{"Armor":"75","ArmorType":"Mail","Slot":"Feet","Agility":"32","AttackPower":"52"}', '/icons/armor/boots_mail2.png'),
('Stormrage Boots', 'Storm blessed', 'Armor', 'Legendary', 60, 1, 16000, 1, 0, '{"Armor":"115","ArmorType":"Mail","Slot":"Feet","Agility":"58","AllStats":"12"}', '/icons/armor/boots_mail3.png'),
('Iron Boots', 'Heavy plate boots', 'Armor', 'Common', 1, 1, 10, 1, 0, '{"Armor":"10","ArmorType":"Plate","Slot":"Feet","Strength":"2","Stamina":"2"}', '/icons/armor/boots_plate1.png'),
('Boots of Valor', 'Steadfast protection', 'Armor', 'Rare', 25, 1, 550, 1, 0, '{"Armor":"62","ArmorType":"Plate","Slot":"Feet","Strength":"22","Stamina":"16"}', '/icons/armor/boots_plate2.png'),
('Judgment Sabatons', 'Divine protection', 'Armor', 'Epic', 40, 1, 2600, 1, 0, '{"Armor":"105","ArmorType":"Plate","Slot":"Feet","Strength":"38","AllStats":"7"}', '/icons/armor/boots_plate3.png'),
('Boots of Might', 'Ultimate warrior boots', 'Armor', 'Legendary', 60, 1, 20000, 1, 0, '{"Armor":"155","ArmorType":"Plate","Slot":"Feet","Strength":"65","Defense":"30"}', '/icons/armor/boots_plate4.png'),
('Dragonscale Boots', 'Dragon hide', 'Armor', 'Epic', 45, 1, 2800, 1, 0, '{"Armor":"82","ArmorType":"Mail","Slot":"Feet","Agility":"35","FireResistance":"20"}', '/icons/armor/boots_dragon.png'),
('Frozen Sabatons', 'Never slip', 'Armor', 'Epic', 42, 1, 2500, 1, 0, '{"Armor":"95","ArmorType":"Plate","Slot":"Feet","Strength":"32","FrostResistance":"25"}', '/icons/armor/boots_frozen.png'),
('Shadow Treads', 'Silent as death', 'Armor', 'Epic', 38, 1, 1600, 1, 0, '{"Armor":"48","ArmorType":"Leather","Slot":"Feet","Agility":"25","Stealth":"10"}', '/icons/armor/boots_shadow.png'),
('Phoenix Sabatons', 'Walk through fire', 'Armor', 'Legendary', 58, 1, 18000, 1, 0, '{"Armor":"145","ArmorType":"Plate","Slot":"Feet","Strength":"62","FireDamage":"30"}', '/icons/armor/boots_phoenix.png'),
('Netherwind Boots', 'Step into void', 'Armor', 'Epic', 50, 1, 4000, 1, 0, '{"Armor":"52","ArmorType":"Cloth","Slot":"Feet","Intelligence":"45","ShadowDamage":"32"}', '/icons/armor/boots_nether.png'),
('Windwalker Boots', 'Swift as wind', 'Armor', 'Rare', 30, 1, 950, 1, 0, '{"Armor":"42","ArmorType":"Leather","Slot":"Feet","Agility":"18","MovementSpeed":"8%"}', '/icons/armor/boots_wind.png'),
('Titansteel Warboots', 'Unstoppable march', 'Armor', 'Legendary', 60, 1, 22000, 1, 0, '{"Armor":"162","ArmorType":"Plate","Slot":"Feet","Strength":"72","Stamina":"52"}', '/icons/armor/boots_titan.png');

-- =============================================
-- CONSUMABLES - POTIONS (30 items)
-- =============================================

INSERT INTO Items (ItemName, Description, ItemType, Rarity, RequiredLevel, MaxStackSize, VendorPrice, IsTradeable, IsQuestItem, Stats, IconPath) VALUES
('Minor Healing Potion', 'Restores 50 health', 'Consumable', 'Common', 1, 20, 5, 1, 0, '{"Effect":"Heal","Value":"50"}', '/icons/consumables/potion_health1.png'),
('Healing Potion', 'Restores 150 health', 'Consumable', 'Common', 10, 20, 15, 1, 0, '{"Effect":"Heal","Value":"150"}', '/icons/consumables/potion_health2.png'),
('Greater Healing Potion', 'Restores 350 health', 'Consumable', 'Uncommon', 20, 20, 35, 1, 0, '{"Effect":"Heal","Value":"350"}', '/icons/consumables/potion_health3.png'),
('Superior Healing Potion', 'Restores 700 health', 'Consumable', 'Uncommon', 30, 20, 75, 1, 0, '{"Effect":"Heal","Value":"700"}', '/icons/consumables/potion_health4.png'),
('Major Healing Potion', 'Restores 1500 health', 'Consumable', 'Rare', 40, 20, 180, 1, 0, '{"Effect":"Heal","Value":"1500"}', '/icons/consumables/potion_health5.png'),
('Ultimate Healing Potion', 'Restores 3500 health', 'Consumable', 'Rare', 50, 20, 420, 1, 0, '{"Effect":"Heal","Value":"3500"}', '/icons/consumables/potion_health6.png'),
('Minor Mana Potion', 'Restores 30 mana', 'Consumable', 'Common', 1, 20, 5, 1, 0, '{"Effect":"RestoreMana","Value":"30"}', '/icons/consumables/potion_mana1.png'),
('Mana Potion', 'Restores 100 mana', 'Consumable', 'Common', 10, 20, 15, 1, 0, '{"Effect":"RestoreMana","Value":"100"}', '/icons/consumables/potion_mana2.png'),
('Greater Mana Potion', 'Restores 250 mana', 'Consumable', 'Uncommon', 20, 20, 35, 1, 0, '{"Effect":"RestoreMana","Value":"250"}', '/icons/consumables/potion_mana3.png'),
('Superior Mana Potion', 'Restores 500 mana', 'Consumable', 'Uncommon', 30, 20, 75, 1, 0, '{"Effect":"RestoreMana","Value":"500"}', '/icons/consumables/potion_mana4.png'),
('Major Mana Potion', 'Restores 1200 mana', 'Consumable', 'Rare', 40, 20, 180, 1, 0, '{"Effect":"RestoreMana","Value":"1200"}', '/icons/consumables/potion_mana5.png'),
('Elixir of Strength', '+20 Strength for 1 hour', 'Consumable', 'Uncommon', 15, 20, 45, 1, 0, '{"Effect":"BuffStrength","Value":"20","Duration":"3600"}', '/icons/consumables/elixir_str.png'),
('Elixir of Agility', '+20 Agility for 1 hour', 'Consumable', 'Uncommon', 15, 20, 45, 1, 0, '{"Effect":"BuffAgility","Value":"20","Duration":"3600"}', '/icons/consumables/elixir_agi.png'),
('Elixir of Intelligence', '+20 Intelligence for 1 hour', 'Consumable', 'Uncommon', 15, 20, 45, 1, 0, '{"Effect":"BuffIntelligence","Value":"20","Duration":"3600"}', '/icons/consumables/elixir_int.png'),
('Flask of Titans', '+500 Health for 2 hours', 'Consumable', 'Rare', 40, 5, 350, 1, 0, '{"Effect":"BuffHealth","Value":"500","Duration":"7200"}', '/icons/consumables/flask_titan.png'),
('Flask of Supreme Power', '+100 Spell Power for 2 hours', 'Consumable', 'Rare', 40, 5, 350, 1, 0, '{"Effect":"BuffSpellPower","Value":"100","Duration":"7200"}', '/icons/consumables/flask_power.png'),
('Flask of the Winds', '+50 Agility for 2 hours', 'Consumable', 'Rare', 40, 5, 350, 1, 0, '{"Effect":"BuffAgility","Value":"50","Duration":"7200"}', '/icons/consumables/flask_wind.png'),
('Potion of Speed', '+50% Movement Speed for 30 sec', 'Consumable', 'Uncommon', 20, 20, 75, 1, 0, '{"Effect":"MovementSpeed","Value":"50","Duration":"30"}', '/icons/consumables/potion_speed.png'),
('Potion of Invisibility', 'Become invisible for 20 sec', 'Consumable', 'Rare', 30, 10, 280, 1, 0, '{"Effect":"Invisibility","Duration":"20"}', '/icons/consumables/potion_invis.png'),
('Fire Resistance Potion', '+50 Fire Resistance for 1 hour', 'Consumable', 'Uncommon', 25, 20, 85, 1, 0, '{"Effect":"FireResistance","Value":"50","Duration":"3600"}', '/icons/consumables/potion_fire_res.png'),
('Frost Resistance Potion', '+50 Frost Resistance for 1 hour', 'Consumable', 'Uncommon', 25, 20, 85, 1, 0, '{"Effect":"FrostResistance","Value":"50","Duration":"3600"}', '/icons/consumables/potion_frost_res.png'),
('Shadow Resistance Potion', '+50 Shadow Resistance for 1 hour', 'Consumable', 'Uncommon', 25, 20, 85, 1, 0, '{"Effect":"ShadowResistance","Value":"50","Duration":"3600"}', '/icons/consumables/potion_shadow_res.png'),
('Nature Resistance Potion', '+50 Nature Resistance for 1 hour', 'Consumable', 'Uncommon', 25, 20, 85, 1, 0, '{"Effect":"NatureResistance","Value":"50","Duration":"3600"}', '/icons/consumables/potion_nature_res.png'),
('Rage Potion', '+20 Rage instantly', 'Consumable', 'Uncommon', 20, 20, 55, 1, 0, '{"Effect":"GenerateRage","Value":"20"}', '/icons/consumables/potion_rage.png'),
('Energy Potion', '+40 Energy instantly', 'Consumable', 'Uncommon', 20, 20, 55, 1, 0, '{"Effect":"RestoreEnergy","Value":"40"}', '/icons/consumables/potion_energy.png'),
('Free Action Potion', 'Immune to stun/slow for 30 sec', 'Consumable', 'Rare', 35, 10, 220, 1, 0, '{"Effect":"FreeAction","Duration":"30"}', '/icons/consumables/potion_free.png'),
('Living Action Potion', 'Remove stun/slow effects', 'Consumable', 'Rare', 45, 10, 380, 1, 0, '{"Effect":"RemoveCC"}', '/icons/consumables/potion_living.png'),
('Mighty Rage Potion', '+45 Rage, +60 Strength for 20 sec', 'Consumable', 'Rare', 50, 10, 450, 1, 0, '{"Effect":"RageAndStrength","Rage":"45","Strength":"60","Duration":"20"}', '/icons/consumables/potion_mighty.png'),
('Potion of Wild Magic', 'Random magical effect', 'Consumable', 'Rare', 30, 5, 180, 1, 0, '{"Effect":"Random"}', '/icons/consumables/potion_wild.png'),
('Rejuvenation Potion', 'Heal 600 over 10 seconds', 'Consumable', 'Uncommon', 25, 20, 95, 1, 0, '{"Effect":"HealOverTime","Value":"600","Duration":"10"}', '/icons/consumables/potion_rejuv.png');

-- =============================================
-- CONSUMABLES - FOOD & BUFF ITEMS (20 items)
-- =============================================

INSERT INTO Items (ItemName, Description, ItemType, Rarity, RequiredLevel, MaxStackSize, VendorPrice, IsTradeable, IsQuestItem, Stats, IconPath) VALUES
('Bread', 'Restores 150 health over 15 sec', 'Consumable', 'Common', 1, 20, 2, 1, 0, '{"Effect":"FoodHeal","Value":"150","Duration":"15"}', '/icons/consumables/food_bread.png'),
('Cheese', 'Restores 200 health over 15 sec', 'Consumable', 'Common', 5, 20, 3, 1, 0, '{"Effect":"FoodHeal","Value":"200","Duration":"15"}', '/icons/consumables/food_cheese.png'),
('Roasted Meat', 'Restores 400 health over 20 sec', 'Consumable', 'Common', 15, 20, 8, 1, 0, '{"Effect":"FoodHeal","Value":"400","Duration":"20"}', '/icons/consumables/food_meat.png'),
('Cooked Fish', 'Restores 500 health over 20 sec', 'Consumable', 'Common', 20, 20, 12, 1, 0, '{"Effect":"FoodHeal","Value":"500","Duration":"20"}', '/icons/consumables/food_fish.png'),
('Hearty Stew', 'Restores 850 health over 25 sec', 'Consumable', 'Uncommon', 30, 20, 25, 1, 0, '{"Effect":"FoodHeal","Value":"850","Duration":"25"}', '/icons/consumables/food_stew.png'),
('Delicious Cake', 'Restores 1500 health over 30 sec', 'Consumable', 'Uncommon', 40, 20, 45, 1, 0, '{"Effect":"FoodHeal","Value":"1500","Duration":"30"}', '/icons/consumables/food_cake.png'),
('Feast', 'Restores 3000 health over 30 sec', 'Consumable', 'Rare', 50, 10, 180, 1, 0, '{"Effect":"FoodHeal","Value":"3000","Duration":"30"}', '/icons/consumables/food_feast.png'),
('Water', 'Restores 100 mana over 15 sec', 'Consumable', 'Common', 1, 20, 2, 1, 0, '{"Effect":"DrinkMana","Value":"100","Duration":"15"}', '/icons/consumables/drink_water.png'),
('Milk', 'Restores 200 mana over 15 sec', 'Consumable', 'Common', 5, 20, 3, 1, 0, '{"Effect":"DrinkMana","Value":"200","Duration":"15"}', '/icons/consumables/drink_milk.png'),
('Sweet Tea', 'Restores 400 mana over 20 sec', 'Consumable', 'Common', 15, 20, 8, 1, 0, '{"Effect":"DrinkMana","Value":"400","Duration":"20"}', '/icons/consumables/drink_tea.png'),
('Magical Juice', 'Restores 800 mana over 25 sec', 'Consumable', 'Uncommon', 30, 20, 25, 1, 0, '{"Effect":"DrinkMana","Value":"800","Duration":"25"}', '/icons/consumables/drink_juice.png'),
('Enchanted Wine', 'Restores 1500 mana over 30 sec', 'Consumable', 'Uncommon', 40, 20, 45, 1, 0, '{"Effect":"DrinkMana","Value":"1500","Duration":"30"}', '/icons/consumables/drink_wine.png'),
('Nightfin Soup', '+10 Spirit for 30 min', 'Consumable', 'Uncommon', 20, 20, 35, 1, 0, '{"Effect":"BuffSpirit","Value":"10","Duration":"1800"}', '/icons/consumables/food_soup.png'),
('Smoked Desert Dumplings', '+20 Strength for 30 min', 'Consumable', 'Uncommon', 35, 20, 65, 1, 0, '{"Effect":"FoodBuffStr","Value":"20","Duration":"1800"}', '/icons/consumables/food_dump.png'),
('Grilled Squid', '+10 Agility for 30 min', 'Consumable', 'Uncommon', 25, 20, 45, 1, 0, '{"Effect":"FoodBuffAgi","Value":"10","Duration":"1800"}', '/icons/consumables/food_squid.png'),
('Mageblood Potion', '+12 MP5 for 1 hour', 'Consumable', 'Rare', 40, 10, 180, 1, 0, '{"Effect":"ManaRegen","Value":"12","Duration":"3600"}', '/icons/consumables/food_mage.png'),
('Blessed Sunfruit', '+10 All Stats for 30 min', 'Consumable', 'Rare', 45, 10, 220, 1, 0, '{"Effect":"BuffAllStats","Value":"10","Duration":"1800"}', '/icons/consumables/food_sun.png'),
('Dragonbreath Chili', '+25 Fire Spell Damage for 30 min', 'Consumable', 'Rare', 35, 10, 120, 1, 0, '{"Effect":"FireSpellDamage","Value":"25","Duration":"1800"}', '/icons/consumables/food_chili.png'),
('Tender Wolf Steak', '+12 Stamina, +12 Spirit for 30 min', 'Consumable', 'Uncommon', 30, 20, 55, 1, 0, '{"Effect":"BuffStamSp","Stamina":"12","Spirit":"12","Duration":"1800"}', '/icons/consumables/food_wolf.png'),
('Runn Tum Tuber Surprise', '+10 Int, +10 Stam for 30 min', 'Consumable', 'Uncommon', 40, 20, 75, 1, 0, '{"Effect":"BuffIntStam","Intelligence":"10","Stamina":"10","Duration":"1800"}', '/icons/consumables/food_tuber.png');

-- =============================================
-- MATERIALS - CRAFTING (50 items)
-- =============================================

INSERT INTO Items (ItemName, Description, ItemType, Rarity, RequiredLevel, MaxStackSize, VendorPrice, IsTradeable, IsQuestItem, Stats, IconPath) VALUES
('Copper Ore', 'Basic mining material', 'Material', 'Common', 1, 20, 1, 1, 0, '{"Type":"Ore","Tier":"1"}', '/icons/materials/ore_copper.png'),
('Tin Ore', 'Common ore', 'Material', 'Common', 5, 20, 2, 1, 0, '{"Type":"Ore","Tier":"1"}', '/icons/materials/ore_tin.png'),
('Iron Ore', 'Sturdy metal', 'Material', 'Common', 15, 20, 5, 1, 0, '{"Type":"Ore","Tier":"2"}', '/icons/materials/ore_iron.png'),
('Gold Ore', 'Precious metal', 'Material', 'Uncommon', 20, 20, 15, 1, 0, '{"Type":"Ore","Tier":"2"}', '/icons/materials/ore_gold.png'),
('Mithril Ore', 'Rare strong ore', 'Material', 'Uncommon', 30, 20, 25, 1, 0, '{"Type":"Ore","Tier":"3"}', '/icons/materials/ore_mithril.png'),
('Thorium Ore', 'Dense ore', 'Material', 'Uncommon', 40, 20, 45, 1, 0, '{"Type":"Ore","Tier":"4"}', '/icons/materials/ore_thorium.png'),
('Adamantite Ore', 'Extremely hard', 'Material', 'Rare', 50, 20, 85, 1, 0, '{"Type":"Ore","Tier":"5"}', '/icons/materials/ore_adamant.png'),
('Titansteel Bar', 'Strongest metal', 'Material', 'Rare', 60, 10, 180, 1, 0, '{"Type":"Bar","Tier":"6"}', '/icons/materials/bar_titan.png'),
('Linen Cloth', 'Basic cloth', 'Material', 'Common', 1, 20, 1, 1, 0, '{"Type":"Cloth","Tier":"1"}', '/icons/materials/cloth_linen.png'),
('Wool Cloth', 'Warm fabric', 'Material', 'Common', 10, 20, 3, 1, 0, '{"Type":"Cloth","Tier":"1"}', '/icons/materials/cloth_wool.png'),
('Silk Cloth', 'Fine fabric', 'Material', 'Common', 20, 20, 8, 1, 0, '{"Type":"Cloth","Tier":"2"}', '/icons/materials/cloth_silk.png'),
('Mageweave Cloth', 'Magical fabric', 'Material', 'Uncommon', 30, 20, 18, 1, 0, '{"Type":"Cloth","Tier":"3"}', '/icons/materials/cloth_mage.png'),
('Runecloth', 'Runed fabric', 'Material', 'Uncommon', 40, 20, 35, 1, 0, '{"Type":"Cloth","Tier":"4"}', '/icons/materials/cloth_rune.png'),
('Netherweave Cloth', 'Void fabric', 'Material', 'Rare', 50, 20, 65, 1, 0, '{"Type":"Cloth","Tier":"5"}', '/icons/materials/cloth_nether.png'),
('Light Leather', 'Basic hide', 'Material', 'Common', 1, 20, 2, 1, 0, '{"Type":"Leather","Tier":"1"}', '/icons/materials/leather_light.png'),
('Medium Leather', 'Tougher hide', 'Material', 'Common', 10, 20, 5, 1, 0, '{"Type":"Leather","Tier":"2"}', '/icons/materials/leather_medium.png'),
('Heavy Leather', 'Thick hide', 'Material', 'Common', 20, 20, 12, 1, 0, '{"Type":"Leather","Tier":"3"}', '/icons/materials/leather_heavy.png'),
('Thick Leather', 'Very durable', 'Material', 'Uncommon', 30, 20, 25, 1, 0, '{"Type":"Leather","Tier":"4"}', '/icons/materials/leather_thick.png'),
('Rugged Leather', 'Extremely tough', 'Material', 'Uncommon', 40, 20, 45, 1, 0, '{"Type":"Leather","Tier":"5"}', '/icons/materials/leather_rugged.png'),
('Dragonscale', 'Dragon hide', 'Material', 'Rare', 50, 10, 120, 1, 0, '{"Type":"Leather","Tier":"6"}', '/icons/materials/leather_dragon.png'),
('Strange Dust', 'Magical residue', 'Material', 'Common', 1, 20, 3, 1, 0, '{"Type":"Enchanting","Tier":"1"}', '/icons/materials/ench_dust1.png'),
('Soul Dust', 'Spirit essence', 'Material', 'Common', 15, 20, 8, 1, 0, '{"Type":"Enchanting","Tier":"2"}', '/icons/materials/ench_dust2.png'),
('Vision Dust', 'Dreamlike powder', 'Material', 'Uncommon', 30, 20, 22, 1, 0, '{"Type":"Enchanting","Tier":"3"}', '/icons/materials/ench_dust3.png'),
('Dream Dust', 'Ethereal essence', 'Material', 'Uncommon', 45, 20, 48, 1, 0, '{"Type":"Enchanting","Tier":"4"}', '/icons/materials/ench_dust4.png'),
('Arcane Dust', 'Pure magic', 'Material', 'Rare', 60, 20, 85, 1, 0, '{"Type":"Enchanting","Tier":"5"}', '/icons/materials/ench_dust5.png'),
('Lesser Magic Essence', 'Weak magic', 'Material', 'Common', 1, 20, 5, 1, 0, '{"Type":"Essence","Tier":"1"}', '/icons/materials/essence1.png'),
('Greater Magic Essence', 'Moderate magic', 'Material', 'Uncommon', 20, 20, 18, 1, 0, '{"Type":"Essence","Tier":"2"}', '/icons/materials/essence2.png'),
('Eternal Essence', 'Lasting magic', 'Material', 'Rare', 40, 20, 55, 1, 0, '{"Type":"Essence","Tier":"3"}', '/icons/materials/essence3.png'),
('Large Brilliant Shard', 'Powerful crystal', 'Material', 'Rare', 50, 10, 180, 1, 0, '{"Type":"Shard","Tier":"4"}', '/icons/materials/shard1.png'),
('Nexus Crystal', 'Legendary essence', 'Material', 'Epic', 60, 5, 450, 1, 0, '{"Type":"Crystal","Tier":"5"}', '/icons/materials/crystal1.png'),
('Peacebloom', 'Common herb', 'Material', 'Common', 1, 20, 2, 1, 0, '{"Type":"Herb","Tier":"1"}', '/icons/materials/herb_peace.png'),
('Silverleaf', 'Shiny herb', 'Material', 'Common', 5, 20, 3, 1, 0, '{"Type":"Herb","Tier":"1"}', '/icons/materials/herb_silver.png'),
('Mageroyal', 'Magical plant', 'Material', 'Common', 15, 20, 8, 1, 0, '{"Type":"Herb","Tier":"2"}', '/icons/materials/herb_mage.png'),
('Kingsblood', 'Royal herb', 'Material', 'Uncommon', 25, 20, 18, 1, 0, '{"Type":"Herb","Tier":"3"}', '/icons/materials/herb_king.png'),
('Sungrass', 'Solar powered', 'Material', 'Uncommon', 35, 20, 32, 1, 0, '{"Type":"Herb","Tier":"4"}', '/icons/materials/herb_sun.png'),
('Golden Sansam', 'Precious plant', 'Material', 'Rare', 45, 20, 65, 1, 0, '{"Type":"Herb","Tier":"5"}', '/icons/materials/herb_golden.png'),
('Dreamfoil', 'Causes visions', 'Material', 'Rare', 50, 20, 95, 1, 0, '{"Type":"Herb","Tier":"5"}', '/icons/materials/herb_dream.png'),
('Black Lotus', 'Extremely rare', 'Material', 'Epic', 60, 5, 500, 1, 0, '{"Type":"Herb","Tier":"6"}', '/icons/materials/herb_lotus.png'),
('Rough Stone', 'Basic stone', 'Material', 'Common', 1, 20, 1, 1, 0, '{"Type":"Stone","Tier":"1"}', '/icons/materials/stone_rough.png'),
('Heavy Stone', 'Dense rock', 'Material', 'Common', 20, 20, 5, 1, 0, '{"Type":"Stone","Tier":"2"}', '/icons/materials/stone_heavy.png'),
('Solid Stone', 'Very dense', 'Material', 'Uncommon', 40, 20, 18, 1, 0, '{"Type":"Stone","Tier":"3"}', '/icons/materials/stone_solid.png'),
('Dense Stone', 'Extremely heavy', 'Material', 'Rare', 55, 20, 45, 1, 0, '{"Type":"Stone","Tier":"4"}', '/icons/materials/stone_dense.png'),
('Elemental Fire', 'Burning essence', 'Material', 'Uncommon', 30, 10, 35, 1, 0, '{"Type":"Elemental","Element":"Fire"}', '/icons/materials/elem_fire.png'),
('Elemental Water', 'Liquid essence', 'Material', 'Uncommon', 30, 10, 35, 1, 0, '{"Type":"Elemental","Element":"Water"}', '/icons/materials/elem_water.png'),
('Elemental Earth', 'Solid essence', 'Material', 'Uncommon', 30, 10, 35, 1, 0, '{"Type":"Elemental","Element":"Earth"}', '/icons/materials/elem_earth.png'),
('Elemental Air', 'Wind essence', 'Material', 'Uncommon', 30, 10, 35, 1, 0, '{"Type":"Elemental","Element":"Air"}', '/icons/materials/elem_air.png'),
('Heart of Fire', 'Molten core', 'Material', 'Rare', 50, 5, 180, 1, 0, '{"Type":"Elemental","Element":"Fire","Tier":"Epic"}', '/icons/materials/heart_fire.png'),
('Eye of Shadow', 'Dark essence', 'Material', 'Epic', 60, 1, 1000, 1, 0, '{"Type":"Rare","Special":"True"}', '/icons/materials/eye_shadow.png'),
('Arcanite Bar', 'Transmuted metal', 'Material', 'Rare', 50, 10, 220, 1, 0, '{"Type":"Bar","Tier":"6","Magical":"True"}', '/icons/materials/bar_arcane.png'),
('Pristine Diamond', 'Perfect gem', 'Material', 'Rare', 40, 10, 350, 1, 0, '{"Type":"Gem","Quality":"Perfect"}', '/icons/materials/gem_diamond.png');

-- =============================================
-- QUEST ITEMS (20 items)
-- =============================================

INSERT INTO Items (ItemName, Description, ItemType, Rarity, RequiredLevel, MaxStackSize, VendorPrice, IsTradeable, IsQuestItem, Stats, IconPath) VALUES
('Hero''s Call', 'Summons you to adventure', 'Quest', 'Uncommon', 1, 1, 0, 0, 1, '{"QuestID":"1"}', '/icons/quest/call.png'),
('Ancient Tome', 'Contains forbidden knowledge', 'Quest', 'Rare', 20, 1, 0, 0, 1, '{"QuestID":"15"}', '/icons/quest/tome.png'),
('Dragon Scale Fragment', 'Piece of ancient dragon', 'Quest', 'Rare', 30, 1, 0, 0, 1, '{"QuestID":"25"}', '/icons/quest/scale.png'),
('Cursed Amulet', 'Radiates dark magic', 'Quest', 'Epic', 40, 1, 0, 0, 1, '{"QuestID":"40"}', '/icons/quest/amulet.png'),
('Sacred Relic', 'Holy artifact', 'Quest', 'Epic', 45, 1, 0, 0, 1, '{"QuestID":"45"}', '/icons/quest/relic.png'),
('Demon Heart', 'Still beating', 'Quest', 'Rare', 35, 1, 0, 0, 1, '{"QuestID":"35"}', '/icons/quest/heart.png'),
('Crystal Shard', 'Glows with power', 'Quest', 'Uncommon', 25, 1, 0, 0, 1, '{"QuestID":"20"}', '/icons/quest/crystal.png'),
('Lost Letter', 'Urgent message', 'Quest', 'Common', 10, 1, 0, 0, 1, '{"QuestID":"5"}', '/icons/quest/letter.png'),
('Bandit Leader''s Head', 'Proof of victory', 'Quest', 'Uncommon', 15, 1, 0, 0, 1, '{"QuestID":"12"}', '/icons/quest/head.png'),
('Ancient Key', 'Opens forgotten doors', 'Quest', 'Rare', 30, 1, 0, 0, 1, '{"QuestID":"28"}', '/icons/quest/key.png'),
('Phoenix Feather', 'Legendary material', 'Quest', 'Epic', 50, 1, 0, 0, 1, '{"QuestID":"50"}', '/icons/quest/feather.png'),
('Sealed Scroll', 'Do not open', 'Quest', 'Uncommon', 20, 1, 0, 0, 1, '{"QuestID":"18"}', '/icons/quest/scroll.png'),
('Corrupted Blood Sample', 'Diseased specimen', 'Quest', 'Rare', 35, 1, 0, 0, 1, '{"QuestID":"33"}', '/icons/quest/blood.png'),
('Enchanted Gem', 'Pulsing with magic', 'Quest', 'Epic', 55, 1, 0, 0, 1, '{"QuestID":"55"}', '/icons/quest/gem.png'),
('Wolf Pelt', 'For the hunter', 'Quest', 'Common', 5, 10, 0, 0, 1, '{"QuestID":"3"}', '/icons/quest/pelt.png'),
('Rare Mushroom', 'Alchemist needs this', 'Quest', 'Uncommon', 18, 1, 0, 0, 1, '{"QuestID":"16"}', '/icons/quest/mushroom.png'),
('Stolen Plans', 'Enemy secrets', 'Quest', 'Rare', 28, 1, 0, 0, 1, '{"QuestID":"26"}', '/icons/quest/plans.png'),
('Royal Seal', 'King''s authority', 'Quest', 'Epic', 48, 1, 0, 0, 1, '{"QuestID":"48"}', '/icons/quest/seal.png'),
('Soulstone', 'Trapped spirit', 'Quest', 'Legendary', 60, 1, 0, 0, 1, '{"QuestID":"60"}', '/icons/quest/soul.png'),
('Legendary Artifact', 'World-changing item', 'Quest', 'Legendary', 60, 1, 0, 0, 1, '{"QuestID":"100"}', '/icons/quest/artifact.png');

-- Summary
PRINT '================================================';
PRINT '400+ ITEMS DATABASE INSERTION COMPLETE!';
PRINT '================================================';
PRINT 'Total Items by Category:';
PRINT '- One-Handed Swords: 50';
PRINT '- Two-Handed Swords: 30';
PRINT '- Daggers: 25';
PRINT '- Axes: 20';
PRINT '- Maces & Hammers: 20';
PRINT '- Bows: 20';
PRINT '- Staves: 20';
PRINT '- Helmets: 30';
PRINT '- Chest Armor: 30';
PRINT '- Leg Armor: 25';
PRINT '- Shoulders: 20';
PRINT '- Boots: 20';
PRINT '- Potions: 30';
PRINT '- Food & Buffs: 20';
PRINT '- Crafting Materials: 50';
PRINT '- Quest Items: 20';
PRINT '================================================';
PRINT 'GRAND TOTAL: 430+ UNIQUE ITEMS!';
PRINT '================================================';
PRINT '';
PRINT 'All items include:';
PRINT '? Names and descriptions';
PRINT '? Item types and rarities';
PRINT '? Level requirements';
PRINT '? Stats in JSON format';
PRINT '? Vendor prices';
PRINT '? Stack sizes';
PRINT '? Trade flags';
PRINT '================================================';

GO
