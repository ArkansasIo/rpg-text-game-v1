-- =============================================
-- CONTINUATION: 400+ ITEMS DATABASE PART 2
-- Axes, Maces, Bows, Staves, Armor, Consumables
-- =============================================

USE RPGGame;
GO

-- =============================================
-- WEAPONS - AXES (20 items)
-- =============================================

INSERT INTO Items (ItemName, Description, ItemType, Rarity, RequiredLevel, MaxStackSize, VendorPrice, IsTradeable, IsQuestItem, Stats, IconPath) VALUES
('Woodcutter''s Axe', 'Simple tool turned weapon', 'Weapon', 'Common', 1, 1, 8, 1, 0, '{"Damage":"4-8","AttackSpeed":"2.2","WeaponType":"Axe"}', '/icons/weapons/axe_wood.png'),
('Battle Axe', 'Sturdy iron axe', 'Weapon', 'Common', 10, 1, 75, 1, 0, '{"Damage":"14-22","AttackSpeed":"2.4","Strength":"5","WeaponType":"Axe"}', '/icons/weapons/axe_battle.png'),
('Berserker Axe', 'Fuels rage in battle', 'Weapon', 'Uncommon', 18, 1, 320, 1, 0, '{"Damage":"28-40","AttackSpeed":"2.3","Strength":"9","CritChance":"2","WeaponType":"Axe"}', '/icons/weapons/axe_berserk.png'),
('Skullsplitter', 'Cleaves through bone', 'Weapon', 'Rare', 25, 1, 720, 1, 0, '{"Damage":"42-58","AttackSpeed":"2.4","Strength":"12","CritDamage":"15","WeaponType":"Axe"}', '/icons/weapons/axe_skull.png'),
('Orcish Waraxe', 'Traditional orc weapon', 'Weapon', 'Rare', 30, 1, 1100, 1, 0, '{"Damage":"52-70","AttackSpeed":"2.5","Strength":"15","WeaponType":"Axe"}', '/icons/weapons/axe_orc.png'),
('Bonecrusher', 'Shatters enemy defenses', 'Weapon', 'Epic', 35, 1, 1900, 1, 0, '{"Damage":"65-87","AttackSpeed":"2.4","Strength":"19","ArmorBreak":"20","WeaponType":"Axe"}', '/icons/weapons/axe_bone.png'),
('Doomseeker', 'Seeks ultimate battle', 'Weapon', 'Epic', 42, 1, 3100, 1, 0, '{"Damage":"82-108","AttackSpeed":"2.5","Strength":"24","Lifesteal":"3","WeaponType":"Axe"}', '/icons/weapons/axe_doom.png'),
('Thunderstrike Axe', 'Crashes like thunder', 'Weapon', 'Epic', 48, 1, 5200, 1, 0, '{"Damage":"98-125","AttackSpeed":"2.4","Strength":"30","LightningDamage":"30","WeaponType":"Axe"}', '/icons/weapons/axe_thunder.png'),
('Hellreaver', 'Forged in the underworld', 'Weapon', 'Legendary', 55, 1, 15000, 1, 0, '{"Damage":"130-165","AttackSpeed":"2.5","Strength":"42","FireDamage":"50","WeaponType":"Axe"}', '/icons/weapons/axe_hell.png'),
('Gorehowl Axe', 'Legendary battle axe', 'Weapon', 'Legendary', 60, 1, 30000, 1, 0, '{"Damage":"165-205","AttackSpeed":"2.4","Strength":"55","CritChance":"5","WeaponType":"Axe"}', '/icons/weapons/axe_gorehowl.png'),
('Frostbite Cleaver', 'Frozen solid', 'Weapon', 'Rare', 28, 1, 920, 1, 0, '{"Damage":"48-66","AttackSpeed":"2.3","Strength":"14","FrostDamage":"20","WeaponType":"Axe"}', '/icons/weapons/axe_frost.png'),
('Decapitator', 'Removes heads cleanly', 'Weapon', 'Epic', 40, 1, 2800, 1, 0, '{"Damage":"75-100","AttackSpeed":"2.4","Strength":"22","ExecuteChance":"3","WeaponType":"Axe"}', '/icons/weapons/axe_decap.png'),
('Earthshatter', 'Splits the ground', 'Weapon', 'Epic', 45, 1, 4000, 1, 0, '{"Damage":"88-115","AttackSpeed":"2.5","Strength":"27","AreaDamage":"True","WeaponType":"Axe"}', '/icons/weapons/axe_earth.png'),
('Stormfury Axe', 'Channels storm energy', 'Weapon', 'Legendary', 52, 1, 12000, 1, 0, '{"Damage":"118-150","AttackSpeed":"2.4","Strength":"38","NatureDamage":"45","WeaponType":"Axe"}', '/icons/weapons/axe_storm.png'),
('Demon''s Bane', 'Scourge of demons', 'Weapon', 'Epic', 38, 1, 2400, 1, 0, '{"Damage":"70-94","AttackSpeed":"2.3","Strength":"20","DemonSlaying":"35","WeaponType":"Axe"}', '/icons/weapons/axe_demon.png'),
('Bloodaxe', 'Drinks enemy blood', 'Weapon', 'Rare', 32, 1, 1400, 1, 0, '{"Damage":"58-78","AttackSpeed":"2.4","Strength":"16","LifeSteal":"2","WeaponType":"Axe"}', '/icons/weapons/axe_blood.png'),
('Dragonbone Cleaver', 'Made from dragon remains', 'Weapon', 'Legendary', 58, 1, 18000, 1, 0, '{"Damage":"145-180","AttackSpeed":"2.5","Strength":"48","DragonSlaying":"50","WeaponType":"Axe"}', '/icons/weapons/axe_dragon.png'),
('Hand of Justice', 'Righteous fury', 'Weapon', 'Epic', 50, 1, 7500, 1, 0, '{"Damage":"105-135","AttackSpeed":"2.4","Strength":"32","HolyDamage":"35","WeaponType":"Axe"}', '/icons/weapons/axe_justice.png'),
('Skullforge Reaver', 'Crafted by dwarven master', 'Weapon', 'Legendary', 60, 1, 28000, 1, 0, '{"Damage":"160-200","AttackSpeed":"2.4","Strength":"52","AllStats":"15","WeaponType":"Axe"}', '/icons/weapons/axe_skull2.png'),
('Infinity Cleaver', 'Never dulls', 'Weapon', 'Legendary', 60, 1, 35000, 1, 0, '{"Damage":"175-215","AttackSpeed":"2.3","Strength":"58","Indestructible":"True","WeaponType":"Axe"}', '/icons/weapons/axe_infinity.png');

-- =============================================
-- WEAPONS - MACES & HAMMERS (20 items)
-- =============================================

INSERT INTO Items (ItemName, Description, ItemType, Rarity, RequiredLevel, MaxStackSize, VendorPrice, IsTradeable, IsQuestItem, Stats, IconPath) VALUES
('Wooden Club', 'Primitive but effective', 'Weapon', 'Common', 1, 1, 5, 1, 0, '{"Damage":"3-6","AttackSpeed":"2.0","WeaponType":"Mace"}', '/icons/weapons/mace_wood.png'),
('Iron Mace', 'Solid iron construction', 'Weapon', 'Common', 8, 1, 55, 1, 0, '{"Damage":"11-18","AttackSpeed":"2.2","Strength":"4","WeaponType":"Mace"}', '/icons/weapons/mace_iron.png'),
('Warhammer', 'Crushes armor', 'Weapon', 'Uncommon', 15, 1, 200, 1, 0, '{"Damage":"22-35","AttackSpeed":"2.4","Strength":"7","ArmorBreak":"10","WeaponType":"Mace"}', '/icons/weapons/mace_war.png'),
('Spiked Mace', 'Brutally spiked head', 'Weapon', 'Uncommon', 20, 1, 420, 1, 0, '{"Damage":"32-48","AttackSpeed":"2.2","Strength":"9","BleedDamage":"15","WeaponType":"Mace"}', '/icons/weapons/mace_spike.png'),
('Hammer of Justice', 'Righteous weapon', 'Weapon', 'Rare', 25, 1, 720, 1, 0, '{"Damage":"42-62","AttackSpeed":"2.3","Strength":"12","HolyDamage":"20","WeaponType":"Mace"}', '/icons/weapons/mace_justice.png'),
('Blessed Mace', 'Consecrated by priests', 'Weapon', 'Rare', 28, 1, 920, 1, 0, '{"Damage":"48-68","AttackSpeed":"2.2","Intelligence":"10","HolyDamage":"22","WeaponType":"Mace"}', '/icons/weapons/mace_blessed.png'),
('Skullbasher', 'Concussive strikes', 'Weapon', 'Epic', 32, 1, 1650, 1, 0, '{"Damage":"62-85","AttackSpeed":"2.3","Strength":"17","StunChance":"5","WeaponType":"Mace"}', '/icons/weapons/mace_skull.png'),
('Ironfoe', 'Legendary dwarven hammer', 'Weapon', 'Epic', 38, 1, 2500, 1, 0, '{"Damage":"75-102","AttackSpeed":"2.4","Strength":"21","ExtraAttack":"10%","WeaponType":"Mace"}', '/icons/weapons/mace_iron.png'),
('Sulfuron Hammer', 'Forged in molten core', 'Weapon', 'Legendary', 50, 1, 10000, 1, 0, '{"Damage":"115-152","AttackSpeed":"2.5","Strength":"35","FireDamage":"50","WeaponType":"Mace"}', '/icons/weapons/mace_sulfuron.png'),
('Hand of Ragnaros', 'Ultimate fire hammer', 'Weapon', 'Legendary', 60, 1, 35000, 1, 0, '{"Damage":"180-230","AttackSpeed":"2.6","Strength":"60","FireDamage":"80","WeaponType":"Mace"}', '/icons/weapons/mace_rag.png'),
('Frostbrand Mace', 'Freezing cold', 'Weapon', 'Rare', 30, 1, 1150, 1, 0, '{"Damage":"52-72","AttackSpeed":"2.2","Strength":"14","FrostDamage":"18","WeaponType":"Mace"}', '/icons/weapons/mace_frost.png'),
('Lightbringer', 'Channels divine light', 'Weapon', 'Epic', 40, 1, 2850, 1, 0, '{"Damage":"78-108","AttackSpeed":"2.3","Intelligence":"18","HolyDamage":"30","WeaponType":"Mace"}', '/icons/weapons/mace_light.png'),
('Earthshaker', 'Causes tremors', 'Weapon', 'Epic', 45, 1, 4100, 1, 0, '{"Damage":"92-122","AttackSpeed":"2.5","Strength":"26","AreaStun":"True","WeaponType":"Mace"}', '/icons/weapons/mace_earth.png'),
('Thunderfury Hammer', 'Blessed by storm gods', 'Weapon', 'Legendary', 55, 1, 16000, 1, 0, '{"Damage":"135-172","AttackSpeed":"2.4","Strength":"44","LightningDamage":"55","WeaponType":"Mace"}', '/icons/weapons/mace_thunder.png'),
('Doomhammer Replica', 'Copy of legendary weapon', 'Weapon', 'Epic', 42, 1, 3200, 1, 0, '{"Damage":"82-112","AttackSpeed":"2.4","Strength":"23","AllResistances":"10","WeaponType":"Mace"}', '/icons/weapons/mace_doom.png'),
('Judgment', 'Divine retribution', 'Weapon', 'Legendary', 52, 1, 12000, 1, 0, '{"Damage":"122-158","AttackSpeed":"2.3","Strength":"38","HolyDamage":"45","WeaponType":"Mace"}', '/icons/weapons/mace_judgment.png'),
('Bonereaver''s Edge', 'Legendary mace', 'Weapon', 'Epic', 48, 1, 5500, 1, 0, '{"Damage":"98-128","AttackSpeed":"2.4","Strength":"29","CritChance":"3","WeaponType":"Mace"}', '/icons/weapons/mace_bone.png'),
('Crusher of Kings', 'Topples monarchs', 'Weapon', 'Legendary', 58, 1, 19000, 1, 0, '{"Damage":"148-188","AttackSpeed":"2.5","Strength":"48","ArmorBreak":"40","WeaponType":"Mace"}', '/icons/weapons/mace_king.png'),
('Obsidian Warhammer', 'Carved from volcanic rock', 'Weapon', 'Rare', 35, 1, 1950, 1, 0, '{"Damage":"68-92","AttackSpeed":"2.4","Strength":"18","FireDamage":"25","WeaponType":"Mace"}', '/icons/weapons/mace_obsidian.png'),
('Worldbreaker Hammer', 'Shatters reality', 'Weapon', 'Legendary', 60, 1, 40000, 1, 0, '{"Damage":"190-240","AttackSpeed":"2.6","Strength":"65","AllDamage":"25","WeaponType":"Mace"}', '/icons/weapons/mace_world.png');

-- =============================================
-- WEAPONS - BOWS (20 items)
-- =============================================

INSERT INTO Items (ItemName, Description, ItemType, Rarity, RequiredLevel, MaxStackSize, VendorPrice, IsTradeable, IsQuestItem, Stats, IconPath) VALUES
('Hunting Bow', 'Simple hunting tool', 'Weapon', 'Common', 1, 1, 10, 1, 0, '{"Damage":"3-7","AttackSpeed":"2.5","WeaponType":"Bow"}', '/icons/weapons/bow_hunt.png'),
('Shortbow', 'Compact and quick', 'Weapon', 'Common', 8, 1, 60, 1, 0, '{"Damage":"12-20","AttackSpeed":"2.3","Agility":"4","WeaponType":"Bow"}', '/icons/weapons/bow_short.png'),
('Longbow', 'Powerful long range', 'Weapon', 'Uncommon', 15, 1, 210, 1, 0, '{"Damage":"25-38","AttackSpeed":"2.6","Agility":"7","WeaponType":"Bow"}', '/icons/weapons/bow_long.png'),
('Elven Bow', 'Crafted with elven grace', 'Weapon', 'Rare', 22, 1, 560, 1, 0, '{"Damage":"38-55","AttackSpeed":"2.4","Agility":"11","CritChance":"2","WeaponType":"Bow"}', '/icons/weapons/bow_elf.png'),
('Eagle Eye', 'Perfect accuracy', 'Weapon', 'Rare', 28, 1, 950, 1, 0, '{"Damage":"48-68","AttackSpeed":"2.5","Agility":"14","RangeDamage":"10","WeaponType":"Bow"}', '/icons/weapons/bow_eagle.png'),
('Windrunner', 'Swift as the wind', 'Weapon', 'Epic', 35, 1, 1950, 1, 0, '{"Damage":"68-92","AttackSpeed":"2.3","Agility":"19","AttackSpeed":"8%","WeaponType":"Bow"}', '/icons/weapons/bow_wind.png'),
('Dragonslayer Bow', 'Pierce dragon scales', 'Weapon', 'Epic', 40, 1, 2900, 1, 0, '{"Damage":"82-110","AttackSpeed":"2.5","Agility":"23","DragonSlaying":"30","WeaponType":"Bow"}', '/icons/weapons/bow_dragon.png'),
('Rhok''delar', 'Ancient hunter''s bow', 'Weapon', 'Legendary', 50, 1, 9500, 1, 0, '{"Damage":"115-148","AttackSpeed":"2.4","Agility":"36","AllStats":"12","WeaponType":"Bow"}', '/icons/weapons/bow_rhok.png'),
('Thori''dal', 'Legendary elven bow', 'Weapon', 'Legendary', 60, 1, 28000, 1, 0, '{"Damage":"165-210","AttackSpeed":"2.5","Agility":"55","NoAmmoRequired":"True","WeaponType":"Bow"}', '/icons/weapons/bow_thoridal.png'),
('Compound Bow', 'Mechanically enhanced', 'Weapon', 'Uncommon', 18, 1, 320, 1, 0, '{"Damage":"28-42","AttackSpeed":"2.4","Agility":"8","WeaponType":"Bow"}', '/icons/weapons/bow_compound.png'),
('Sniper''s Bow', 'Long range precision', 'Weapon', 'Epic', 38, 1, 2500, 1, 0, '{"Damage":"75-102","AttackSpeed":"2.6","Agility":"21","CritChance":"4","WeaponType":"Bow"}', '/icons/weapons/bow_sniper.png'),
('Venom Striker', 'Poison tipped', 'Weapon', 'Rare', 30, 1, 1150, 1, 0, '{"Damage":"52-72","AttackSpeed":"2.4","Agility":"15","PoisonDamage":"20","WeaponType":"Bow"}', '/icons/weapons/bow_venom.png'),
('Phoenix Bow', 'Arrows of flame', 'Weapon', 'Epic', 45, 1, 4200, 1, 0, '{"Damage":"92-122","AttackSpeed":"2.5","Agility":"27","FireDamage":"35","WeaponType":"Bow"}', '/icons/weapons/bow_phoenix.png'),
('Frostwind Bow', 'Ice arrows', 'Weapon', 'Rare', 32, 1, 1450, 1, 0, '{"Damage":"58-78","AttackSpeed":"2.4","Agility":"16","FrostDamage":"22","WeaponType":"Bow"}', '/icons/weapons/bow_frost.png'),
('Heartseeker Bow', 'Never misses vital spots', 'Weapon', 'Legendary', 55, 1, 15000, 1, 0, '{"Damage":"138-175","AttackSpeed":"2.4","Agility":"45","CritDamage":"35","WeaponType":"Bow"}', '/icons/weapons/bow_heart.png'),
('Stormrage', 'Summons lightning', 'Weapon', 'Epic', 42, 1, 3300, 1, 0, '{"Damage":"85-115","AttackSpeed":"2.5","Agility":"24","LightningDamage":"28","WeaponType":"Bow"}', '/icons/weapons/bow_storm.png'),
('Bone Bow', 'Made from demon bones', 'Weapon', 'Rare', 26, 1, 780, 1, 0, '{"Damage":"42-60","AttackSpeed":"2.4","Agility":"12","ShadowDamage":"15","WeaponType":"Bow"}', '/icons/weapons/bow_bone.png'),
('Ancient Recurve', 'Timeless design', 'Weapon', 'Epic', 48, 1, 5600, 1, 0, '{"Damage":"102-135","AttackSpeed":"2.4","Agility":"30","Durability":"200","WeaponType":"Bow"}', '/icons/weapons/bow_recurve.png'),
('Sunfury Bow', 'Radiant solar energy', 'Weapon', 'Legendary', 58, 1, 19000, 1, 0, '{"Damage":"152-192","AttackSpeed":"2.5","Agility":"50","HolyDamage":"50","WeaponType":"Bow"}', '/icons/weapons/bow_sun.png'),
('Infinity Bow', 'Unlimited potential', 'Weapon', 'Legendary', 60, 1, 32000, 1, 0, '{"Damage":"175-220","AttackSpeed":"2.3","Agility":"58","Multishot":"True","WeaponType":"Bow"}', '/icons/weapons/bow_infinity.png');

-- =============================================
-- WEAPONS - STAVES (20 items)
-- =============================================

INSERT INTO Items (ItemName, Description, ItemType, Rarity, RequiredLevel, MaxStackSize, VendorPrice, IsTradeable, IsQuestItem, Stats, IconPath) VALUES
('Apprentice Staff', 'Basic training staff', 'Weapon', 'Common', 1, 1, 12, 1, 0, '{"Damage":"4-8","AttackSpeed":"2.8","Intelligence":"2","WeaponType":"Staff"}', '/icons/weapons/staff_apprentice.png'),
('Oak Staff', 'Simple oak wood', 'Weapon', 'Common', 8, 1, 65, 1, 0, '{"Damage":"13-21","AttackSpeed":"2.9","Intelligence":"5","SpellPower":"8","WeaponType":"Staff"}', '/icons/weapons/staff_oak.png'),
('Mage''s Staff', 'Focus for spellcasting', 'Weapon', 'Uncommon', 15, 1, 220, 1, 0, '{"Damage":"24-38","AttackSpeed":"2.8","Intelligence":"9","SpellPower":"18","WeaponType":"Staff"}', '/icons/weapons/staff_mage.png'),
('Runed Staff', 'Carved with mystic runes', 'Weapon', 'Rare', 22, 1, 580, 1, 0, '{"Damage":"36-54","AttackSpeed":"2.9","Intelligence":"13","SpellPower":"32","WeaponType":"Staff"}', '/icons/weapons/staff_rune.png'),
('Staff of Flames', 'Crackles with fire', 'Weapon', 'Rare', 28, 1, 950, 1, 0, '{"Damage":"46-66","AttackSpeed":"2.8","Intelligence":"16","FireDamage":"25","SpellPower":"42","WeaponType":"Staff"}', '/icons/weapons/staff_flame.png'),
('Frostfire Staff', 'Fire and ice combined', 'Weapon', 'Epic', 35, 1, 2000, 1, 0, '{"Damage":"65-90","AttackSpeed":"2.9","Intelligence":"22","FireDamage":"20","FrostDamage":"20","WeaponType":"Staff"}', '/icons/weapons/staff_frost.png'),
('Archmage Staff', 'Wielded by archmages', 'Weapon', 'Epic', 40, 1, 2950, 1, 0, '{"Damage":"80-108","AttackSpeed":"2.8","Intelligence":"27","SpellPower":"68","WeaponType":"Staff"}', '/icons/weapons/staff_arch.png'),
('Staff of Dominion', 'Control the elements', 'Weapon', 'Legendary', 50, 1, 10000, 1, 0, '{"Damage":"118-152","AttackSpeed":"2.9","Intelligence":"40","SpellPower":"95","AllStats":"10","WeaponType":"Staff"}', '/icons/weapons/staff_dom.png'),
('Atiesh', 'Legendary staff of the guardian', 'Weapon', 'Legendary', 60, 1, 35000, 1, 0, '{"Damage":"175-225","AttackSpeed":"2.8","Intelligence":"65","SpellPower":"150","WeaponType":"Staff"}', '/icons/weapons/staff_atiesh.png'),
('Shadow Staff', 'Imbued with darkness', 'Weapon', 'Rare', 30, 1, 1200, 1, 0, '{"Damage":"52-72","AttackSpeed":"2.9","Intelligence":"17","ShadowDamage":"28","WeaponType":"Staff"}', '/icons/weapons/staff_shadow.png'),
('Staff of Nature', 'Channels primal forces', 'Weapon', 'Epic', 38, 1, 2600, 1, 0, '{"Damage":"75-102","AttackSpeed":"2.8","Intelligence":"25","NatureDamage":"32","WeaponType":"Staff"}', '/icons/weapons/staff_nature.png'),
('Lightning Rod', 'Pure electrical power', 'Weapon', 'Epic', 42, 1, 3400, 1, 0, '{"Damage":"85-115","AttackSpeed":"2.9","Intelligence":"28","LightningDamage":"38","WeaponType":"Staff"}', '/icons/weapons/staff_light.png'),
('Benediction', 'Holy healing staff', 'Weapon', 'Legendary', 52, 1, 12000, 1, 0, '{"Damage":"125-160","AttackSpeed":"2.8","Intelligence":"42","HealingPower":"85","WeaponType":"Staff"}', '/icons/weapons/staff_bene.png'),
('Anathema', 'Cursed shadow staff', 'Weapon', 'Legendary', 52, 1, 12000, 1, 0, '{"Damage":"125-160","AttackSpeed":"2.8","Intelligence":"42","ShadowDamage":"75","WeaponType":"Staff"}', '/icons/weapons/staff_anath.png'),
('Crystal Staff', 'Pure arcane crystal', 'Weapon', 'Epic', 45, 1, 4300, 1, 0, '{"Damage":"92-122","AttackSpeed":"2.8","Intelligence":"30","ArcaneDamage":"42","WeaponType":"Staff"}', '/icons/weapons/staff_crystal.png'),
('Netherwind Staff', 'From the void', 'Weapon', 'Legendary', 55, 1, 16000, 1, 0, '{"Damage":"142-180","AttackSpeed":"2.9","Intelligence":"48","VoidDamage":"65","WeaponType":"Staff"}', '/icons/weapons/staff_nether.png'),
('Druid''s Branch', 'Living wood staff', 'Weapon', 'Rare', 25, 1, 720, 1, 0, '{"Damage":"40-58","AttackSpeed":"2.8","Intelligence":"14","NatureDamage":"20","WeaponType":"Staff"}', '/icons/weapons/staff_druid.png'),
('Pyromancer''s Staff', 'Master of flames', 'Weapon', 'Epic', 48, 1, 5800, 1, 0, '{"Damage":"102-135","AttackSpeed":"2.9","Intelligence":"32","FireDamage":"55","WeaponType":"Staff"}', '/icons/weapons/staff_pyro.png'),
('Staff of Eternity', 'Timeless power', 'Weapon', 'Legendary', 58, 1, 20000, 1, 0, '{"Damage":"158-198","AttackSpeed":"2.8","Intelligence":"55","AllSpellDamage":"10%","WeaponType":"Staff"}', '/icons/weapons/staff_eternity.png'),
('Infinity Staff', 'Limitless magical power', 'Weapon', 'Legendary', 60, 1, 38000, 1, 0, '{"Damage":"180-230","AttackSpeed":"2.8","Intelligence":"70","SpellPower":"180","ManaCostReduction":"20%","WeaponType":"Staff"}', '/icons/weapons/staff_infinity.png');

