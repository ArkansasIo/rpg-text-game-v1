-- =============================================
-- CONTINUATION: 400+ ITEMS DATABASE PART 3
-- ARMOR - Helmets, Chest, Legs, Shoulders, Boots, Gloves, Belts
-- =============================================

USE RPGGame;
GO

-- =============================================
-- ARMOR - HELMETS (30 items)
-- =============================================

INSERT INTO Items (ItemName, Description, ItemType, Rarity, RequiredLevel, MaxStackSize, VendorPrice, IsTradeable, IsQuestItem, Stats, IconPath) VALUES
-- Cloth Helmets
('Linen Cap', 'Simple cloth headwear', 'Armor', 'Common', 1, 1, 5, 1, 0, '{"Armor":"2","ArmorType":"Cloth","Slot":"Head","Intelligence":"1"}', '/icons/armor/helm_cloth1.png'),
('Apprentice Hood', 'Basic mage hood', 'Armor', 'Common', 8, 1, 35, 1, 0, '{"Armor":"8","ArmorType":"Cloth","Slot":"Head","Intelligence":"4","Spirit":"2"}', '/icons/armor/helm_cloth2.png'),
('Silk Cowl', 'Fine silk material', 'Armor', 'Uncommon', 15, 1, 120, 1, 0, '{"Armor":"15","ArmorType":"Cloth","Slot":"Head","Intelligence":"8","SpellPower":"12"}', '/icons/armor/helm_cloth3.png'),
('Sorcerer''s Crown', 'Powerful magic focus', 'Armor', 'Rare', 25, 1, 480, 1, 0, '{"Armor":"28","ArmorType":"Cloth","Slot":"Head","Intelligence":"15","SpellPower":"25","Spirit":"10"}', '/icons/armor/helm_cloth4.png'),
('Arcanist Crown', 'Legendary mage helm', 'Armor', 'Epic', 40, 1, 1950, 1, 0, '{"Armor":"52","ArmorType":"Cloth","Slot":"Head","Intelligence":"28","SpellPower":"48","CritChance":"2"}', '/icons/armor/helm_cloth5.png'),
('Crown of Destruction', 'Ultimate caster helm', 'Armor', 'Legendary', 60, 1, 15000, 1, 0, '{"Armor":"88","ArmorType":"Cloth","Slot":"Head","Intelligence":"50","SpellPower":"95","AllStats":"12"}', '/icons/armor/helm_cloth6.png'),

-- Leather Helmets
('Leather Cap', 'Basic leather protection', 'Armor', 'Common', 1, 1, 8, 1, 0, '{"Armor":"5","ArmorType":"Leather","Slot":"Head","Agility":"2"}', '/icons/armor/helm_leather1.png'),
('Scout''s Hood', 'For reconnaissance', 'Armor', 'Common', 8, 1, 45, 1, 0, '{"Armor":"12","ArmorType":"Leather","Slot":"Head","Agility":"5","Stamina":"3"}', '/icons/armor/helm_leather2.png'),
('Rogue''s Mask', 'Conceals identity', 'Armor', 'Uncommon', 15, 1, 150, 1, 0, '{"Armor":"22","ArmorType":"Leather","Slot":"Head","Agility":"10","CritChance":"1"}', '/icons/armor/helm_leather3.png'),
('Shadowcraft Cap', 'Made for shadows', 'Armor', 'Rare', 25, 1, 550, 1, 0, '{"Armor":"38","ArmorType":"Leather","Slot":"Head","Agility":"18","Stamina":"12","CritChance":"2"}', '/icons/armor/helm_leather4.png'),
('Bloodfang Hood', 'Legendary rogue helm', 'Armor', 'Epic', 40, 1, 2200, 1, 0, '{"Armor":"68","ArmorType":"Leather","Slot":"Head","Agility":"32","Stamina":"22","AttackPower":"45"}', '/icons/armor/helm_leather5.png'),
('Crown of Madness', 'Drives enemies insane', 'Armor', 'Legendary', 60, 1, 18000, 1, 0, '{"Armor":"105","ArmorType":"Leather","Slot":"Head","Agility":"55","Stamina":"38","CritChance":"5"}', '/icons/armor/helm_leather6.png'),

-- Mail Helmets
('Chainmail Coif', 'Basic chain protection', 'Armor', 'Common', 1, 1, 10, 1, 0, '{"Armor":"8","ArmorType":"Mail","Slot":"Head","Strength":"2","Agility":"1"}', '/icons/armor/helm_mail1.png'),
('Hunter''s Headguard', 'For tracking beasts', 'Armor', 'Common', 8, 1, 55, 1, 0, '{"Armor":"18","ArmorType":"Mail","Slot":"Head","Agility":"6","Stamina":"4"}', '/icons/armor/helm_mail2.png'),
('Beastmaster Helm', 'Controls wild creatures', 'Armor', 'Uncommon', 15, 1, 180, 1, 0, '{"Armor":"32","ArmorType":"Mail","Slot":"Head","Agility":"12","Stamina":"8","AttackPower":"15"}', '/icons/armor/helm_mail3.png'),
('Dragonstalker Helm', 'For hunting dragons', 'Armor', 'Rare', 25, 1, 620, 1, 0, '{"Armor":"55","ArmorType":"Mail","Slot":"Head","Agility":"20","Stamina":"15","AttackPower":"32"}', '/icons/armor/helm_mail4.png'),
('Crown of the Wild', 'Nature''s fury', 'Armor', 'Epic', 40, 1, 2500, 1, 0, '{"Armor":"92","ArmorType":"Mail","Slot":"Head","Agility":"35","Stamina":"28","AttackPower":"58"}', '/icons/armor/helm_mail5.png'),
('Stormrage Cover', 'Calls the storm', 'Armor', 'Legendary', 60, 1, 20000, 1, 0, '{"Armor":"138","ArmorType":"Mail","Slot":"Head","Agility":"58","Stamina":"45","AllStats":"15"}', '/icons/armor/helm_mail6.png'),

-- Plate Helmets
('Iron Helm', 'Solid iron construction', 'Armor', 'Common', 1, 1, 15, 1, 0, '{"Armor":"15","ArmorType":"Plate","Slot":"Head","Strength":"3","Stamina":"2"}', '/icons/armor/helm_plate1.png'),
('Warrior''s Helm', 'Battle-tested protection', 'Armor', 'Common', 8, 1, 75, 1, 0, '{"Armor":"28","ArmorType":"Plate","Slot":"Head","Strength":"7","Stamina":"5"}', '/icons/armor/helm_plate2.png'),
('Knight''s Helmet', 'Noble warrior''s helm', 'Armor', 'Uncommon', 15, 1, 220, 1, 0, '{"Armor":"48","ArmorType":"Plate","Slot":"Head","Strength":"14","Stamina":"10"}', '/icons/armor/helm_plate3.png'),
('Helm of Valor', 'Inspires courage', 'Armor', 'Rare', 25, 1, 720, 1, 0, '{"Armor":"82","ArmorType":"Plate","Slot":"Head","Strength":"24","Stamina":"18","Defense":"15"}', '/icons/armor/helm_plate4.png'),
('Judgment Crown', 'Divine judgment', 'Armor', 'Epic', 40, 1, 2800, 1, 0, '{"Armor":"135","ArmorType":"Plate","Slot":"Head","Strength":"40","Stamina":"32","AllStats":"8"}', '/icons/armor/helm_plate5.png'),
('Crown of Might', 'Ultimate warrior helm', 'Armor', 'Legendary', 60, 1, 25000, 1, 0, '{"Armor":"200","ArmorType":"Plate","Slot":"Head","Strength":"65","Stamina":"55","Defense":"35"}', '/icons/armor/helm_plate6.png'),

-- Special/Unique Helmets
('Dragon Scale Helm', 'Made from dragon scales', 'Armor', 'Epic', 45, 1, 3800, 1, 0, '{"Armor":"115","ArmorType":"Plate","Slot":"Head","Strength":"32","FireResistance":"25"}', '/icons/armor/helm_dragon.png'),
('Frozen Crown', 'Eternal ice', 'Armor', 'Epic', 42, 1, 3200, 1, 0, '{"Armor":"105","ArmorType":"Plate","Slot":"Head","Strength":"28","FrostResistance":"30"}', '/icons/armor/helm_frozen.png'),
('Shadow Hood', 'Invisible in darkness', 'Armor', 'Epic', 38, 1, 2400, 1, 0, '{"Armor":"55","ArmorType":"Leather","Slot":"Head","Agility":"28","Stealth":"20"}', '/icons/armor/helm_shadow.png'),
('Mindbreaker Hood', 'Shatters psyches', 'Armor', 'Legendary', 55, 1, 14000, 1, 0, '{"Armor":"75","ArmorType":"Cloth","Slot":"Head","Intelligence":"45","SpellPower":"75","MindControl":"True"}', '/icons/armor/helm_mind.png'),
('Demon Hunter Mask', 'For stalking demons', 'Armor', 'Epic', 48, 1, 5000, 1, 0, '{"Armor":"88","ArmorType":"Leather","Slot":"Head","Agility":"36","DemonSlaying":"30"}', '/icons/armor/helm_dh.png');

-- =============================================
-- ARMOR - CHEST PIECES (30 items)
-- =============================================

INSERT INTO Items (ItemName, Description, ItemType, Rarity, RequiredLevel, MaxStackSize, VendorPrice, IsTradeable, IsQuestItem, Stats, IconPath) VALUES
-- Cloth Chest
('Linen Robe', 'Simple cloth robe', 'Armor', 'Common', 1, 1, 8, 1, 0, '{"Armor":"5","ArmorType":"Cloth","Slot":"Chest","Intelligence":"2","Spirit":"1"}', '/icons/armor/chest_cloth1.png'),
('Apprentice Robe', 'Basic mage attire', 'Armor', 'Common', 8, 1, 50, 1, 0, '{"Armor":"15","ArmorType":"Cloth","Slot":"Chest","Intelligence":"6","Spirit":"4","SpellPower":"5"}', '/icons/armor/chest_cloth2.png'),
('Silk Robe', 'Luxurious silk', 'Armor', 'Uncommon', 15, 1, 180, 1, 0, '{"Armor":"28","ArmorType":"Cloth","Slot":"Chest","Intelligence":"12","Spirit":"8","SpellPower":"18"}', '/icons/armor/chest_cloth3.png'),
('Sorcerer''s Robes', 'Powerful magic vestments', 'Armor', 'Rare', 25, 1, 680, 1, 0, '{"Armor":"52","ArmorType":"Cloth","Slot":"Chest","Intelligence":"22","Spirit":"15","SpellPower":"38"}', '/icons/armor/chest_cloth4.png'),
('Arcanist Robes', 'Legendary mage robes', 'Armor', 'Epic', 40, 1, 2800, 1, 0, '{"Armor":"95","ArmorType":"Cloth","Slot":"Chest","Intelligence":"42","Spirit":"28","SpellPower":"72"}', '/icons/armor/chest_cloth5.png'),
('Robes of the Void', 'Woven from darkness', 'Armor', 'Legendary', 60, 1, 22000, 1, 0, '{"Armor":"155","ArmorType":"Cloth","Slot":"Chest","Intelligence":"75","SpellPower":"140","AllStats":"18"}', '/icons/armor/chest_cloth6.png'),

-- Leather Chest
('Leather Vest', 'Basic leather armor', 'Armor', 'Common', 1, 1, 12, 1, 0, '{"Armor":"10","ArmorType":"Leather","Slot":"Chest","Agility":"3","Stamina":"2"}', '/icons/armor/chest_leather1.png'),
('Scout''s Tunic', 'Light and flexible', 'Armor', 'Common', 8, 1, 65, 1, 0, '{"Armor":"22","ArmorType":"Leather","Slot":"Chest","Agility":"8","Stamina":"5"}', '/icons/armor/chest_leather2.png'),
('Rogue''s Vest', 'For stealth operations', 'Armor', 'Uncommon', 15, 1, 220, 1, 0, '{"Armor":"42","ArmorType":"Leather","Slot":"Chest","Agility":"15","Stamina":"10","CritChance":"1"}', '/icons/armor/chest_leather3.png'),
('Shadowcraft Tunic', 'Blends with shadows', 'Armor', 'Rare', 25, 1, 780, 1, 0, '{"Armor":"72","ArmorType":"Leather","Slot":"Chest","Agility":"28","Stamina":"18","CritChance":"2"}', '/icons/armor/chest_leather4.png'),
('Bloodfang Chestpiece', 'Legendary assassin armor', 'Armor', 'Epic', 40, 1, 3200, 1, 0, '{"Armor":"125","ArmorType":"Leather","Slot":"Chest","Agility":"48","Stamina":"35","AttackPower":"68"}', '/icons/armor/chest_leather5.png'),
('Tunic of Assassination', 'Perfect stealth suit', 'Armor', 'Legendary', 60, 1, 26000, 1, 0, '{"Armor":"192","ArmorType":"Leather","Slot":"Chest","Agility":"82","Stamina":"58","CritChance":"6"}', '/icons/armor/chest_leather6.png'),

-- Mail Chest
('Chainmail Hauberk', 'Linked metal rings', 'Armor', 'Common', 1, 1, 15, 1, 0, '{"Armor":"15","ArmorType":"Mail","Slot":"Chest","Strength":"3","Agility":"2"}', '/icons/armor/chest_mail1.png'),
('Hunter''s Chestguard', 'Protects vital organs', 'Armor', 'Common', 8, 1, 80, 1, 0, '{"Armor":"32","ArmorType":"Mail","Slot":"Chest","Agility":"9","Stamina":"6"}', '/icons/armor/chest_mail2.png'),
('Beastmaster Vest', 'Tanned beast hide', 'Armor', 'Uncommon', 15, 1, 260, 1, 0, '{"Armor":"58","ArmorType":"Mail","Slot":"Chest","Agility":"18","Stamina":"12","AttackPower":"22"}', '/icons/armor/chest_mail3.png'),
('Dragonstalker Breastplate', 'Dragon scale mail', 'Armor', 'Rare', 25, 1, 880, 1, 0, '{"Armor":"98","ArmorType":"Mail","Slot":"Chest","Agility":"32","Stamina":"22","AttackPower":"48"}', '/icons/armor/chest_mail4.png'),
('Vest of the Wild', 'Nature''s armor', 'Armor', 'Epic', 40, 1, 3600, 1, 0, '{"Armor":"165","ArmorType":"Mail","Slot":"Chest","Agility":"52","Stamina":"42","AttackPower":"85"}', '/icons/armor/chest_mail5.png'),
('Stormrage Chestguard', 'Storm-blessed mail', 'Armor', 'Legendary', 60, 1, 28000, 1, 0, '{"Armor":"245","ArmorType":"Mail","Slot":"Chest","Agility":"88","Stamina":"68","AllStats":"22"}', '/icons/armor/chest_mail6.png'),

-- Plate Chest
('Iron Breastplate', 'Solid iron plate', 'Armor', 'Common', 1, 1, 20, 1, 0, '{"Armor":"25","ArmorType":"Plate","Slot":"Chest","Strength":"4","Stamina":"3"}', '/icons/armor/chest_plate1.png'),
('Warrior''s Chestplate', 'Battle-forged armor', 'Armor', 'Common', 8, 1, 110, 1, 0, '{"Armor":"48","ArmorType":"Plate","Slot":"Chest","Strength":"10","Stamina":"8"}', '/icons/armor/chest_plate2.png'),
('Knight''s Breastplate', 'Noble protection', 'Armor', 'Uncommon', 15, 1, 320, 1, 0, '{"Armor":"88","ArmorType":"Plate","Slot":"Chest","Strength":"20","Stamina":"15"}', '/icons/armor/chest_plate3.png'),
('Breastplate of Valor', 'Inspires allies', 'Armor', 'Rare', 25, 1, 1000, 1, 0, '{"Armor":"145","ArmorType":"Plate","Slot":"Chest","Strength":"36","Stamina":"28","Defense":"22"}', '/icons/armor/chest_plate4.png'),
('Judgment Breastplate', 'Divine protection', 'Armor', 'Epic', 40, 1, 4000, 1, 0, '{"Armor":"240","ArmorType":"Plate","Slot":"Chest","Strength":"60","Stamina":"48","AllStats":"12"}', '/icons/armor/chest_plate5.png'),
('Chestplate of Might', 'Ultimate warrior armor', 'Armor', 'Legendary', 60, 1, 35000, 1, 0, '{"Armor":"355","ArmorType":"Plate","Slot":"Chest","Strength":"98","Stamina":"82","Defense":"52"}', '/icons/armor/chest_plate6.png'),

-- Special Chest Pieces
('Dragonhide Vest', 'Made from dragon leather', 'Armor', 'Epic', 45, 1, 5200, 1, 0, '{"Armor":"145","ArmorType":"Leather","Slot":"Chest","Agility":"48","FireResistance":"35"}', '/icons/armor/chest_dragon.png'),
('Frozen Chestguard', 'Never melts', 'Armor', 'Epic', 42, 1, 4500, 1, 0, '{"Armor":"185","ArmorType":"Mail","Slot":"Chest","Strength":"42","FrostResistance":"40"}', '/icons/armor/chest_frozen.png'),
('Demon Skin Vest', 'Cursed demon hide', 'Armor', 'Epic', 48, 1, 6500, 1, 0, '{"Armor":"135","ArmorType":"Leather","Slot":"Chest","Agility":"55","ShadowResistance":"30"}', '/icons/armor/chest_demon.png'),
('Robes of Eternity', 'Timeless vestments', 'Armor', 'Legendary', 55, 1, 18000, 1, 0, '{"Armor":"125","ArmorType":"Cloth","Slot":"Chest","Intelligence":"68","SpellPower":"115"}', '/icons/armor/chest_eternity.png'),
('Phoenix Plate', 'Reborn from ashes', 'Armor', 'Legendary', 58, 1, 32000, 1, 0, '{"Armor":"325","ArmorType":"Plate","Slot":"Chest","Strength":"88","Resurrection":"True"}', '/icons/armor/chest_phoenix.png');

-- =============================================
-- ARMOR - LEGS (25 items)
-- =============================================

INSERT INTO Items (ItemName, Description, ItemType, Rarity, RequiredLevel, MaxStackSize, VendorPrice, IsTradeable, IsQuestItem, Stats, IconPath) VALUES
-- Cloth Legs
('Linen Pants', 'Simple cloth leggings', 'Armor', 'Common', 1, 1, 6, 1, 0, '{"Armor":"4","ArmorType":"Cloth","Slot":"Legs","Intelligence":"2"}', '/icons/armor/legs_cloth1.png'),
('Silk Leggings', 'Fine silk material', 'Armor', 'Uncommon', 15, 1, 150, 1, 0, '{"Armor":"22","ArmorType":"Cloth","Slot":"Legs","Intelligence":"10","SpellPower":"15"}', '/icons/armor/legs_cloth2.png'),
('Arcanist Leggings', 'Powerful magic pants', 'Armor', 'Epic', 40, 1, 2400, 1, 0, '{"Armor":"75","ArmorType":"Cloth","Slot":"Legs","Intelligence":"38","SpellPower":"62"}', '/icons/armor/legs_cloth3.png'),
('Pants of Prophecy', 'Legendary mage legs', 'Armor', 'Legendary', 60, 1, 18000, 1, 0, '{"Armor":"125","ArmorType":"Cloth","Slot":"Legs","Intelligence":"65","SpellPower":"120"}', '/icons/armor/legs_cloth4.png'),

-- Leather Legs
('Leather Pants', 'Basic protection', 'Armor', 'Common', 1, 1, 10, 1, 0, '{"Armor":"8","ArmorType":"Leather","Slot":"Legs","Agility":"3"}', '/icons/armor/legs_leather1.png'),
('Rogue''s Leggings', 'Flexible and light', 'Armor', 'Uncommon', 15, 1, 180, 1, 0, '{"Armor":"35","ArmorType":"Leather","Slot":"Legs","Agility":"12","CritChance":"1"}', '/icons/armor/legs_leather2.png'),
('Bloodfang Pants', 'Legendary rogue legs', 'Armor', 'Epic', 40, 1, 2800, 1, 0, '{"Armor":"105","ArmorType":"Leather","Slot":"Legs","Agility":"42","AttackPower":"58"}', '/icons/armor/legs_leather3.png'),
('Leggings of the Assassin', 'Perfect stealth', 'Armor', 'Legendary', 60, 1, 22000, 1, 0, '{"Armor":"162","ArmorType":"Leather","Slot":"Legs","Agility":"72","CritChance":"5"}', '/icons/armor/legs_leather4.png'),

-- Mail Legs
('Chainmail Leggings', 'Linked rings', 'Armor', 'Common', 1, 1, 12, 1, 0, '{"Armor":"12","ArmorType":"Mail","Slot":"Legs","Agility":"3","Stamina":"2"}', '/icons/armor/legs_mail1.png'),
('Hunter''s Leggings', 'For long journeys', 'Armor', 'Uncommon', 15, 1, 220, 1, 0, '{"Armor":"48","ArmorType":"Mail","Slot":"Legs","Agility":"15","AttackPower":"18"}', '/icons/armor/legs_mail2.png'),
('Dragonstalker Legguards', 'Dragon scale legs', 'Armor', 'Epic', 40, 1, 3200, 1, 0, '{"Armor":"138","ArmorType":"Mail","Slot":"Legs","Agility":"45","AttackPower":"72"}', '/icons/armor/legs_mail3.png'),
('Stormrage Legguards', 'Storm blessed', 'Armor', 'Legendary', 60, 1, 24000, 1, 0, '{"Armor":"205","ArmorType":"Mail","Slot":"Legs","Agility":"78","AllStats":"18"}', '/icons/armor/legs_mail4.png'),

-- Plate Legs
('Iron Legplates', 'Heavy iron', 'Armor', 'Common', 1, 1, 18, 1, 0, '{"Armor":"20","ArmorType":"Plate","Slot":"Legs","Strength":"4","Stamina":"3"}', '/icons/armor/legs_plate1.png'),
('Knight''s Legguards', 'Noble armor', 'Armor', 'Uncommon', 15, 1, 280, 1, 0, '{"Armor":"72","ArmorType":"Plate","Slot":"Legs","Strength":"18","Stamina":"12"}', '/icons/armor/legs_plate2.png'),
('Legplates of Valor', 'Courageous protection', 'Armor', 'Rare', 25, 1, 850, 1, 0, '{"Armor":"120","ArmorType":"Plate","Slot":"Legs","Strength":"32","Stamina":"24"}', '/icons/armor/legs_plate3.png'),
('Judgment Legplates', 'Divine armor', 'Armor', 'Epic', 40, 1, 3500, 1, 0, '{"Armor":"200","ArmorType":"Plate","Slot":"Legs","Strength":"52","Stamina":"42"}', '/icons/armor/legs_plate4.png'),
('Legplates of Might', 'Ultimate warrior legs', 'Armor', 'Legendary', 60, 1, 30000, 1, 0, '{"Armor":"295","ArmorType":"Plate","Slot":"Legs","Strength":"88","Defense":"45"}', '/icons/armor/legs_plate5.png'),

-- Special Legs
('Dragon Scale Leggings', 'Made from scales', 'Armor', 'Epic', 45, 1, 4500, 1, 0, '{"Armor":"165","ArmorType":"Mail","Slot":"Legs","Agility":"48","FireResistance":"30"}', '/icons/armor/legs_dragon.png'),
('Frozen Legguards', 'Ice never melts', 'Armor', 'Epic', 42, 1, 4000, 1, 0, '{"Armor":"155","ArmorType":"Plate","Slot":"Legs","Strength":"42","FrostResistance":"35"}', '/icons/armor/legs_frozen.png'),
('Shadow Pants', 'Invisible in darkness', 'Armor', 'Epic', 38, 1, 2200, 1, 0, '{"Armor":"88","ArmorType":"Leather","Slot":"Legs","Agility":"35","Stealth":"15"}', '/icons/armor/legs_shadow.png'),
('Eternal Legwraps', 'Timeless protection', 'Armor', 'Legendary', 55, 1, 16000, 1, 0, '{"Armor":"105","ArmorType":"Cloth","Slot":"Legs","Intelligence":"60","SpellPower":"95"}', '/icons/armor/legs_eternal.png'),
('Phoenix Legguards', 'Reborn from flame', 'Armor', 'Legendary', 58, 1, 28000, 1, 0, '{"Armor":"275","ArmorType":"Plate","Slot":"Legs","Strength":"78","FireDamage":"40"}', '/icons/armor/legs_phoenix.png'),
('Demon Hunter Leggings', 'Bane of demons', 'Armor', 'Epic', 48, 1, 5500, 1, 0, '{"Armor":"115","ArmorType":"Leather","Slot":"Legs","Agility":"52","DemonSlaying":"25"}', '/icons/armor/legs_dh.png'),
('Netherweave Pants', 'Woven from void', 'Armor', 'Epic', 50, 1, 6200, 1, 0, '{"Armor":"95","ArmorType":"Cloth","Slot":"Legs","Intelligence":"55","ShadowDamage":"45"}', '/icons/armor/legs_nether.png'),
('Titansteel Legguards', 'Unbreakable metal', 'Armor', 'Legendary', 60, 1, 32000, 1, 0, '{"Armor":"305","ArmorType":"Plate","Slot":"Legs","Strength":"92","Stamina":"75"}', '/icons/armor/legs_titan.png');

