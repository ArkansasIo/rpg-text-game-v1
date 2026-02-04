# ?? UNREAL ENGINE 5 BLUEPRINT STRUCTURE - COMPLETE FOLDER & FILE MANIFEST

## ?? Complete Folder Hierarchy

```
Content/
??? Blueprints/
?   ??? Character/
?   ?   ??? Players/
?   ?   ?   ??? BP_PlayerCharacter.uasset
?   ?   ?   ??? BP_PlayerCharacter_Male.uasset
?   ?   ?   ??? BP_PlayerCharacter_Female.uasset
?   ?   ?   ??? BP_PlayerAnimInstance.uasset
?   ?   ?   ??? BP_PlayerController.uasset
?   ?   ??? NPCs/
?   ?   ?   ??? BP_NPCCharacter_Base.uasset
?   ?   ?   ??? BP_Merchant.uasset
?   ?   ?   ??? BP_QuestGiver.uasset
?   ?   ?   ??? BP_Trainer.uasset
?   ?   ?   ??? BP_Guard.uasset
?   ?   ?   ??? BP_Innkeeper.uasset
?   ?   ??? Enemies/
?   ?       ??? BP_EnemyCharacter_Base.uasset
?   ?       ??? BP_Goblin_Warrior.uasset
?   ?       ??? BP_Goblin_Archer.uasset
?   ?       ??? BP_Orc_Shaman.uasset
?   ?       ??? BP_Dragon_Ancient.uasset
?   ?       ??? BP_Boss_LichKing.uasset
?   ?       ??? BP_Werewolf.uasset
?   ?       ??? BP_Vampire.uasset
?   ?       ??? BP_Necromancer.uasset
?   ?       ??? BP_EnemyAnimInstance.uasset
?   ?
?   ??? Items/
?   ?   ??? Equipment/
?   ?   ?   ??? Weapons/
?   ?   ?   ?   ??? BP_Sword_Base.uasset
?   ?   ?   ?   ??? BP_Sword_Iron.uasset
?   ?   ?   ?   ??? BP_Sword_Excalibur.uasset
?   ?   ?   ?   ??? BP_Axe_Base.uasset
?   ?   ?   ?   ??? BP_Bow_Base.uasset
?   ?   ?   ?   ??? BP_Staff_Base.uasset
?   ?   ?   ?   ??? BP_Dagger_Base.uasset
?   ?   ?   ?   ??? BP_Mace_Base.uasset
?   ?   ?   ??? Armor/
?   ?   ?       ??? BP_Armor_Base.uasset
?   ?   ?       ??? BP_Armor_Plate.uasset
?   ?   ?       ??? BP_Armor_Leather.uasset
?   ?   ?       ??? BP_Armor_Cloth.uasset
?   ?   ?       ??? BP_Helmet_Base.uasset
?   ?   ?       ??? BP_Chest_Plate.uasset
?   ?   ?       ??? BP_Legs_Plate.uasset
?   ?   ?       ??? BP_Boots_Base.uasset
?   ?   ??? Consumables/
?   ?   ?   ??? BP_HealthPotion.uasset
?   ?   ?   ??? BP_ManaPotion.uasset
?   ?   ?   ??? BP_StaminaPotion.uasset
?   ?   ?   ??? BP_Food_Bread.uasset
?   ?   ?   ??? BP_Food_Meat.uasset
?   ?   ?   ??? BP_Buff_Potion.uasset
?   ?   ?   ??? BP_Elixir_Rare.uasset
?   ?   ??? Materials/
?   ?   ?   ??? BP_Ore_Iron.uasset
?   ?   ?   ??? BP_Ore_Silver.uasset
?   ?   ?   ??? BP_Ore_Gold.uasset
?   ?   ?   ??? BP_Wood_Oak.uasset
?   ?   ?   ??? BP_Wood_Pine.uasset
?   ?   ?   ??? BP_Cloth_Cotton.uasset
?   ?   ?   ??? BP_Leather_Base.uasset
?   ?   ?   ??? BP_Herb_Moonflower.uasset
?   ?   ??? Gems/
?   ?   ?   ??? BP_Gem_Emerald.uasset
?   ?   ?   ??? BP_Gem_Ruby.uasset
?   ?   ?   ??? BP_Gem_Sapphire.uasset
?   ?   ?   ??? BP_Gem_Diamond.uasset
?   ?   ?   ??? BP_Gem_Rare.uasset
?   ?   ??? Quest Items/
?   ?       ??? BP_QuestItem_Base.uasset
?   ?       ??? BP_QuestItem_Scroll.uasset
?   ?       ??? BP_QuestItem_Key.uasset
?   ?       ??? BP_QuestItem_Artifact.uasset
?   ?       ??? BP_QuestItem_Crystal.uasset
?   ?
?   ??? UI/
?   ?   ??? MainMenu/
?   ?   ?   ??? WBP_MainMenu.uasset
?   ?   ?   ??? WBP_NewGame.uasset
?   ?   ?   ??? WBP_LoadGame.uasset
?   ?   ?   ??? WBP_Quit.uasset
?   ?   ??? CharacterCreation/
?   ?   ?   ??? WBP_CharacterCreation_Main.uasset
?   ?   ?   ??? WBP_CharacterCreation_Race.uasset
?   ?   ?   ??? WBP_CharacterCreation_Class.uasset
?   ?   ?   ??? WBP_CharacterCreation_Appearance.uasset
?   ?   ?   ??? WBP_CharacterCreation_Review.uasset
?   ?   ??? InGame/
?   ?   ?   ??? HUD/
?   ?   ?   ?   ??? WBP_MainHUD.uasset
?   ?   ?   ?   ??? WBP_HealthBar.uasset
?   ?   ?   ?   ??? WBP_ManaBar.uasset
?   ?   ?   ?   ??? WBP_StaminaBar.uasset
?   ?   ?   ?   ??? WBP_AbilityBar.uasset
?   ?   ?   ?   ??? WBP_AbilitySlot.uasset
?   ?   ?   ?   ??? WBP_StatusEffects.uasset
?   ?   ?   ?   ??? WBP_TargetInfo.uasset
?   ?   ?   ?   ??? WBP_Minimap.uasset
?   ?   ?   ?   ??? WBP_CompassBar.uasset
?   ?   ?   ?   ??? WBP_CombatLog.uasset
?   ?   ?   ?   ??? WBP_DamageNumbers.uasset
?   ?   ?   ?   ??? WBP_Notifications.uasset
?   ?   ?   ??? Menus/
?   ?   ?   ?   ??? WBP_PauseMenu.uasset
?   ?   ?   ?   ??? WBP_Inventory.uasset
?   ?   ?   ?   ??? WBP_CharacterSheet.uasset
?   ?   ?   ?   ??? WBP_QuestLog.uasset
?   ?   ?   ?   ??? WBP_MapUI.uasset
?   ?   ?   ?   ??? WBP_GuildUI.uasset
?   ?   ?   ?   ??? WBP_RaidUI.uasset
?   ?   ?   ?   ??? WBP_PartyUI.uasset
?   ?   ?   ?   ??? WBP_SocialUI.uasset
?   ?   ?   ?   ??? WBP_ShopUI.uasset
?   ?   ?   ?   ??? WBP_CraftingUI.uasset
?   ?   ?   ?   ??? WBP_TalentTree.uasset
?   ?   ?   ?   ??? WBP_CharacterStats.uasset
?   ?   ?   ??? Settings/
?   ?   ?       ??? WBP_SettingsMenu.uasset
?   ?   ?       ??? WBP_Settings_Graphics.uasset
?   ?   ?       ??? WBP_Settings_Audio.uasset
?   ?   ?       ??? WBP_Settings_Gameplay.uasset
?   ?   ?       ??? WBP_Settings_Accessibility.uasset
?   ?   ?       ??? WBP_Settings_Controls.uasset
?   ?   ?       ??? WBP_Settings_Keybinds.uasset
?   ?   ??? Dialogs/
?   ?   ?   ??? WBP_DialogBox_Base.uasset
?   ?   ?   ??? WBP_NPC_Dialog.uasset
?   ?   ?   ??? WBP_Merchant_Dialog.uasset
?   ?   ?   ??? WBP_Quest_Dialog.uasset
?   ?   ?   ??? WBP_Confirm_Dialog.uasset
?   ?   ?   ??? WBP_Choice_Dialog.uasset
?   ?   ??? Splash/
?   ?       ??? WBP_SplashScreen.uasset
?   ?       ??? WBP_LoadingScreen.uasset
?   ?
?   ??? Abilities/
?   ?   ??? Spells/
?   ?   ?   ??? Mage/
?   ?   ?   ?   ??? BP_Ability_Fireball.uasset
?   ?   ?   ?   ??? BP_Ability_IceShards.uasset
?   ?   ?   ?   ??? BP_Ability_Lightning.uasset
?   ?   ?   ?   ??? BP_Ability_Teleport.uasset
?   ?   ?   ?   ??? BP_Ability_TimeWarp.uasset
?   ?   ?   ??? Priest/
?   ?   ?   ?   ??? BP_Ability_HolyLight.uasset
?   ?   ?   ?   ??? BP_Ability_Heal.uasset
?   ?   ?   ?   ??? BP_Ability_Resurrection.uasset
?   ?   ?   ?   ??? BP_Ability_DivineShield.uasset
?   ?   ?   ??? Warlock/
?   ?   ?       ??? BP_Ability_Curse.uasset
?   ?   ?       ??? BP_Ability_ShadowBolt.uasset
?   ?   ?       ??? BP_Ability_Drain.uasset
?   ?   ?       ??? BP_Ability_Summon.uasset
?   ?   ??? Melee/
?   ?   ?   ??? Warrior/
?   ?   ?   ?   ??? BP_Ability_Slash.uasset
?   ?   ?   ?   ??? BP_Ability_PowerAttack.uasset
?   ?   ?   ?   ??? BP_Ability_Charge.uasset
?   ?   ?   ?   ??? BP_Ability_Whirlwind.uasset
?   ?   ?   ??? Rogue/
?   ?   ?   ?   ??? BP_Ability_Backstab.uasset
?   ?   ?   ?   ??? BP_Ability_Stealth.uasset
?   ?   ?   ?   ??? BP_Ability_Evasion.uasset
?   ?   ?   ?   ??? BP_Ability_Poison.uasset
?   ?   ?   ??? Paladin/
?   ?   ?       ??? BP_Ability_Smite.uasset
?   ?   ?       ??? BP_Ability_Shield.uasset
?   ?   ?       ??? BP_Ability_Judgment.uasset
?   ?   ?       ??? BP_Ability_HolyWrath.uasset
?   ?   ??? Abilities_Base/
?   ?       ??? BP_Ability_Base.uasset
?   ?       ??? BP_Ability_Projectile.uasset
?   ?       ??? BP_Ability_MeleeAttack.uasset
?   ?       ??? BP_Ability_Heal.uasset
?   ?       ??? BP_Ability_Buff.uasset
?   ?       ??? BP_Ability_Channel.uasset
?   ?
?   ??? Effects/
?   ?   ??? VFX/
?   ?   ?   ??? Combat/
?   ?   ?   ?   ??? BP_VFX_Fireball.uasset
?   ?   ?   ?   ??? BP_VFX_Lightning.uasset
?   ?   ?   ?   ??? BP_VFX_Heal.uasset
?   ?   ?   ?   ??? BP_VFX_Explosion.uasset
?   ?   ?   ?   ??? BP_VFX_Slash.uasset
?   ?   ?   ?   ??? BP_VFX_Shield.uasset
?   ?   ?   ?   ??? BP_VFX_ImpactHit.uasset
?   ?   ?   ??? Environmental/
?   ?   ?   ?   ??? BP_VFX_Rain.uasset
?   ?   ?   ?   ??? BP_VFX_Snow.uasset
?   ?   ?   ?   ??? BP_VFX_Wind.uasset
?   ?   ?   ?   ??? BP_VFX_Fog.uasset
?   ?   ?   ?   ??? BP_VFX_Fire.uasset
?   ?   ?   ??? Special/
?   ?   ?       ??? BP_VFX_LevelUp.uasset
?   ?   ?       ??? BP_VFX_Buff.uasset
?   ?   ?       ??? BP_VFX_Debuff.uasset
?   ?   ?       ??? BP_VFX_Portal.uasset
?   ?   ?       ??? BP_VFX_Teleport.uasset
?   ?   ??? Audio/
?   ?       ??? Combat/
?   ?       ?   ??? BP_Sound_Sword_Hit.uasset
?   ?       ?   ??? BP_Sound_Magic_Cast.uasset
?   ?       ?   ??? BP_Sound_Explosion.uasset
?   ?       ?   ??? BP_Sound_Heal.uasset
?   ?       ??? Ambient/
?   ?       ?   ??? BP_Music_MainMenu.uasset
?   ?       ?   ??? BP_Music_Exploration.uasset
?   ?       ?   ??? BP_Music_Combat.uasset
?   ?       ?   ??? BP_Music_Boss.uasset
?   ?       ?   ??? BP_Ambient_Forest.uasset
?   ?       ??? UI/
?   ?           ??? BP_Sound_UI_Click.uasset
?   ?           ??? BP_Sound_UI_Hover.uasset
?   ?           ??? BP_Sound_Notification.uasset
?   ?           ??? BP_Sound_Error.uasset
?   ?
?   ??? Interactables/
?   ?   ??? BP_Interactable_Base.uasset
?   ?   ??? Doors/
?   ?   ?   ??? BP_Door_Wooden.uasset
?   ?   ?   ??? BP_Door_Iron.uasset
?   ?   ?   ??? BP_Door_Magic.uasset
?   ?   ?   ??? BP_Door_Locked.uasset
?   ?   ??? Chests/
?   ?   ?   ??? BP_Chest_Wood.uasset
?   ?   ?   ??? BP_Chest_Metal.uasset
?   ?   ?   ??? BP_Chest_Treasure.uasset
?   ?   ?   ??? BP_Chest_Locked.uasset
?   ?   ??? Objects/
?   ?   ?   ??? BP_Barrel.uasset
?   ?   ?   ??? BP_Crate.uasset
?   ?   ?   ??? BP_Furniture.uasset
?   ?   ?   ??? BP_Statues.uasset
?   ?   ?   ??? BP_Books.uasset
?   ?   ??? Traps/
?   ?       ??? BP_Trap_Spike.uasset
?   ?       ??? BP_Trap_Fire.uasset
?   ?       ??? BP_Trap_Arrow.uasset
?   ?       ??? BP_Trap_Electric.uasset
?   ?
?   ??? Multiplayer/
?       ??? Social/
?       ?   ??? BP_PartyManager.uasset
?       ?   ??? BP_GuildManager.uasset
?       ?   ??? BP_RaidManager.uasset
?       ?   ??? BP_SocialSystem.uasset
?       ??? Chat/
?           ??? WBP_ChatWindow.uasset
?           ??? WBP_ChatMessage.uasset
?           ??? WBP_ChatInput.uasset
?
??? Maps/
?   ??? MainMenu/
?   ?   ??? L_MainMenu.umap
?   ??? LoadingScreen/
?   ?   ??? L_LoadingScreen.umap
?   ??? CharacterCreation/
?   ?   ??? L_CharacterCreation.umap
?   ??? Worlds/
?   ?   ??? Continents/
?   ?   ?   ??? L_Valorath.umap
?   ?   ?   ??? L_Lumeria.umap
?   ?   ?   ??? L_Mortalis.umap
?   ?   ?   ??? L_Kharanos.umap
?   ?   ?   ??? L_Aethral.umap
?   ?   ?   ??? L_Deepmoor.umap
?   ?   ?   ??? L_Celestia.umap
?   ?   ??? Cities/
?   ?   ?   ??? L_Thornhaven.umap
?   ?   ?   ??? L_Silverleaf_City.umap
?   ?   ?   ??? L_Ironforge.umap
?   ?   ?   ??? L_Amuntep.umap
?   ?   ?   ??? L_Heavenspire.umap
?   ?   ??? Zones/
?   ?   ?   ??? L_Whispering_Woods.umap
?   ?   ?   ??? L_Ancient_Oak_Grove.umap
?   ?   ?   ??? L_Crystal_Cave.umap
?   ?   ?   ??? L_Dark_Forest.umap
?   ?   ?   ??? L_Dragon_Mountains.umap
?   ?   ?   ??? L_Poisoned_Swamp.umap
?   ?   ?   ??? L_Lava_Chambers.umap
?   ?   ?   ??? L_Endless_Desert.umap
?   ?   ?   ??? L_Emerald_Vale.umap
?   ?   ?   ??? L_Shadowpine_Jungle.umap
?   ?   ?   ??? L_Frozen_Wastes.umap
?   ?   ?   ??? L_Moonlit_Glade.umap
?   ?   ?   ??? L_Underground_Caverns.umap
?   ?   ?   ??? L_Drow_Kingdom.umap
?   ?   ?   ??? L_Blackthorn_Citadel.umap
?   ?   ?   ??? L_Demonfire_Wastes.umap
?   ?   ??? Dungeons/
?   ?       ??? D_Goblin_Cave.umap
?   ?       ??? D_Dragon_Spire.umap
?   ?       ??? D_Lich_Tomb.umap
?   ?       ??? D_Demon_Citadel.umap
?   ?       ??? D_Dark_Temple.umap
?   ?       ??? D_Ancient_Crypt.umap
?   ?       ??? D_Fire_Mountain.umap
?   ?       ??? D_Shadow_Fortress.umap
?   ?       ??? D_Abyss_Portal.umap
?   ?
?   ??? Miscellaneous/
?       ??? L_Tutorial.umap
?       ??? L_PvP_Arena.umap
?       ??? L_Guild_Hall.umap
?       ??? L_Test_Level.umap
?
??? Characters/
?   ??? Meshes/
?   ?   ??? Player_Male.uasset
?   ?   ??? Player_Female.uasset
?   ?   ??? Goblin_Warrior.uasset
?   ?   ??? Orc_Shaman.uasset
?   ?   ??? Dragon_Ancient.uasset
?   ?   ??? Human_Guard.uasset
?   ?   ??? Elf_Archer.uasset
?   ?   ??? Werewolf_Beast.uasset
?   ??? Animations/
?   ?   ??? ABP_Player.uasset
?   ?   ??? ABP_Enemy.uasset
?   ?   ??? AM_Idle.uasset
?   ?   ??? AM_Walk.uasset
?   ?   ??? AM_Run.uasset
?   ?   ??? AM_Jump.uasset
?   ?   ??? AM_Attack.uasset
?   ?   ??? AM_Cast.uasset
?   ?   ??? AM_Die.uasset
?   ?   ??? AM_TakeHit.uasset
?   ?   ??? AM_Emote.uasset
?   ??? Materials/
?       ??? M_Skin_Human.uasset
?       ??? M_Armor_Plate.uasset
?       ??? M_Armor_Leather.uasset
?       ??? M_Weapon_Iron.uasset
?       ??? M_Weapon_Gold.uasset
?       ??? M_Eyes.uasset
?
??? Environment/
?   ??? Buildings/
?   ?   ??? BP_House_Wooden.uasset
?   ?   ??? BP_House_Stone.uasset
?   ?   ??? BP_Castle.uasset
?   ?   ??? BP_Tower.uasset
?   ?   ??? BP_Tavern.uasset
?   ?   ??? BP_Shop.uasset
?   ?   ??? BP_Temple.uasset
?   ?   ??? BP_Barracks.uasset
?   ??? Nature/
?   ?   ??? BP_Tree_Oak.uasset
?   ?   ??? BP_Tree_Pine.uasset
?   ?   ??? BP_Rock_Large.uasset
?   ?   ??? BP_Rock_Small.uasset
?   ?   ??? BP_Bush.uasset
?   ?   ??? BP_Grass.uasset
?   ?   ??? BP_Flower.uasset
?   ??? Terrain/
?   ?   ??? M_Grass.uasset
?   ?   ??? M_Stone.uasset
?   ?   ??? M_Sand.uasset
?   ?   ??? M_Snow.uasset
?   ?   ??? M_Mud.uasset
?   ?   ??? M_Water.uasset
?   ?   ??? M_Lava.uasset
?   ??? Lighting/
?       ??? BP_Sunlight.uasset
?       ??? BP_Moonlight.uasset
?       ??? BP_Campfire.uasset
?       ??? BP_Torch.uasset
?       ??? BP_MagicLight.uasset
?       ??? BP_Fog.uasset
?
??? Miscellaneous/
    ??? Managers/
    ?   ??? BP_GameManager.uasset
    ?   ??? BP_PlayerManager.uasset
    ?   ??? BP_InputManager.uasset
    ?   ??? BP_UIManager.uasset
    ?   ??? BP_SaveManager.uasset
    ?   ??? BP_DatabaseManager.uasset
    ?   ??? BP_AudioManager.uasset
    ??? Utilities/
        ??? BP_DebugVisualizer.uasset
        ??? BP_PerformanceMonitor.uasset
        ??? BP_ScreenshotCapture.uasset
```

---

## ?? BLUEPRINT MASTER LIST BY CATEGORY

### CHARACTER BLUEPRINTS (9 total)

**Player Characters**
```
BP_PlayerCharacter              - Main player character base
BP_PlayerCharacter_Male         - Male player variant
BP_PlayerCharacter_Female       - Female player variant
BP_PlayerAnimInstance           - Player animation controller
BP_PlayerController             - Player input controller
```

**NPCs (6 total)**
```
BP_NPCCharacter_Base           - Base NPC class
BP_Merchant                    - Merchant/Shop keeper
BP_QuestGiver                  - Quest giver NPC
BP_Trainer                     - Class/Ability trainer
BP_Guard                       - Town guard/soldier
BP_Innkeeper                   - Inn/Tavern keeper
```

**Enemies (10+ total)**
```
BP_EnemyCharacter_Base         - Enemy base class
BP_Goblin_Warrior              - Common goblin warrior
BP_Goblin_Archer               - Ranged goblin
BP_Orc_Shaman                  - Orc spellcaster
BP_Dragon_Ancient              - Ancient dragon boss
BP_Boss_LichKing               - Final boss
BP_Werewolf                    - Werewolf enemy
BP_Vampire                     - Vampire enemy
BP_Necromancer                 - Necromancer enemy
BP_EnemyAnimInstance           - Enemy animation controller
```

### ITEM BLUEPRINTS (40+ total)

**Weapons (8)**
```
BP_Sword_Base, BP_Sword_Iron, BP_Sword_Excalibur
BP_Axe_Base, BP_Bow_Base, BP_Staff_Base
BP_Dagger_Base, BP_Mace_Base
```

**Armor (8)**
```
BP_Armor_Base, BP_Armor_Plate, BP_Armor_Leather, BP_Armor_Cloth
BP_Helmet_Base, BP_Chest_Plate, BP_Legs_Plate, BP_Boots_Base
```

**Consumables (7)**
```
BP_HealthPotion, BP_ManaPotion, BP_StaminaPotion
BP_Food_Bread, BP_Food_Meat, BP_Buff_Potion, BP_Elixir_Rare
```

**Materials (8)**
```
BP_Ore_Iron, BP_Ore_Silver, BP_Ore_Gold
BP_Wood_Oak, BP_Wood_Pine, BP_Cloth_Cotton
BP_Leather_Base, BP_Herb_Moonflower
```

**Gems (5)**
```
BP_Gem_Emerald, BP_Gem_Ruby, BP_Gem_Sapphire
BP_Gem_Diamond, BP_Gem_Rare
```

**Quest Items (5)**
```
BP_QuestItem_Base, BP_QuestItem_Scroll
BP_QuestItem_Key, BP_QuestItem_Artifact, BP_QuestItem_Crystal
```

### UI BLUEPRINTS (60+ total)

**Main Menu (4)**
```
WBP_MainMenu, WBP_NewGame
WBP_LoadGame, WBP_Quit
```

**Character Creation (5)**
```
WBP_CharacterCreation_Main
WBP_CharacterCreation_Race
WBP_CharacterCreation_Class
WBP_CharacterCreation_Appearance
WBP_CharacterCreation_Review
```

**In-Game HUD (13)**
```
WBP_MainHUD, WBP_HealthBar, WBP_ManaBar, WBP_StaminaBar
WBP_AbilityBar, WBP_AbilitySlot, WBP_StatusEffects
WBP_TargetInfo, WBP_Minimap, WBP_CompassBar
WBP_CombatLog, WBP_DamageNumbers, WBP_Notifications
```

**In-Game Menus (13)**
```
WBP_PauseMenu, WBP_Inventory, WBP_CharacterSheet
WBP_QuestLog, WBP_MapUI, WBP_GuildUI, WBP_RaidUI
WBP_PartyUI, WBP_SocialUI, WBP_ShopUI, WBP_CraftingUI
WBP_TalentTree, WBP_CharacterStats
```

**Settings (6)**
```
WBP_SettingsMenu, WBP_Settings_Graphics
WBP_Settings_Audio, WBP_Settings_Gameplay
WBP_Settings_Accessibility, WBP_Settings_Controls
WBP_Settings_Keybinds
```

**Dialogs (6)**
```
WBP_DialogBox_Base, WBP_NPC_Dialog
WBP_Merchant_Dialog, WBP_Quest_Dialog
WBP_Confirm_Dialog, WBP_Choice_Dialog
```

**Splash/Loading (2)**
```
WBP_SplashScreen, WBP_LoadingScreen
```

### ABILITY BLUEPRINTS (20+ total)

**Mage Spells (5)**
```
BP_Ability_Fireball, BP_Ability_IceShards
BP_Ability_Lightning, BP_Ability_Teleport
BP_Ability_TimeWarp
```

**Priest Spells (4)**
```
BP_Ability_HolyLight, BP_Ability_Heal
BP_Ability_Resurrection, BP_Ability_DivineShield
```

**Warlock Spells (4)**
```
BP_Ability_Curse, BP_Ability_ShadowBolt
BP_Ability_Drain, BP_Ability_Summon
```

**Warrior Abilities (4)**
```
BP_Ability_Slash, BP_Ability_PowerAttack
BP_Ability_Charge, BP_Ability_Whirlwind
```

**Rogue Abilities (4)**
```
BP_Ability_Backstab, BP_Ability_Stealth
BP_Ability_Evasion, BP_Ability_Poison
```

**Paladin Abilities (4)**
```
BP_Ability_Smite, BP_Ability_Shield
BP_Ability_Judgment, BP_Ability_HolyWrath
```

**Base Abilities (6)**
```
BP_Ability_Base, BP_Ability_Projectile
BP_Ability_MeleeAttack, BP_Ability_Heal
BP_Ability_Buff, BP_Ability_Channel
```

### EFFECTS BLUEPRINTS (25+ total)

**Combat VFX (7)**
```
BP_VFX_Fireball, BP_VFX_Lightning, BP_VFX_Heal
BP_VFX_Explosion, BP_VFX_Slash, BP_VFX_Shield
BP_VFX_ImpactHit
```

**Environmental VFX (5)**
```
BP_VFX_Rain, BP_VFX_Snow, BP_VFX_Wind
BP_VFX_Fog, BP_VFX_Fire
```

**Special VFX (5)**
```
BP_VFX_LevelUp, BP_VFX_Buff, BP_VFX_Debuff
BP_VFX_Portal, BP_VFX_Teleport
```

**Audio - Combat (4)**
```
BP_Sound_Sword_Hit, BP_Sound_Magic_Cast
BP_Sound_Explosion, BP_Sound_Heal
```

**Audio - Ambient (5)**
```
BP_Music_MainMenu, BP_Music_Exploration
BP_Music_Combat, BP_Music_Boss, BP_Ambient_Forest
```

**Audio - UI (4)**
```
BP_Sound_UI_Click, BP_Sound_UI_Hover
BP_Sound_Notification, BP_Sound_Error
```

### INTERACTABLE BLUEPRINTS (15+ total)

**Base**
```
BP_Interactable_Base
```

**Doors (4)**
```
BP_Door_Wooden, BP_Door_Iron
BP_Door_Magic, BP_Door_Locked
```

**Chests (4)**
```
BP_Chest_Wood, BP_Chest_Metal
BP_Chest_Treasure, BP_Chest_Locked
```

**Objects (5)**
```
BP_Barrel, BP_Crate, BP_Furniture
BP_Statues, BP_Books
```

**Traps (4)**
```
BP_Trap_Spike, BP_Trap_Fire
BP_Trap_Arrow, BP_Trap_Electric
```

### MULTIPLAYER BLUEPRINTS (7 total)

**Social Systems (4)**
```
BP_PartyManager, BP_GuildManager
BP_RaidManager, BP_SocialSystem
```

**Chat (3)**
```
WBP_ChatWindow, WBP_ChatMessage
WBP_ChatInput
```

### MAP BLUEPRINTS (40+ total)

**Main Areas (3)**
```
L_MainMenu, L_LoadingScreen, L_CharacterCreation
```

**Continents (7)**
```
L_Valorath, L_Lumeria, L_Mortalis, L_Kharanos
L_Aethral, L_Deepmoor, L_Celestia
```

**Major Cities (5)**
```
L_Thornhaven, L_Silverleaf_City, L_Ironforge
L_Amuntep, L_Heavenspire
```

**Zones (16)**
```
L_Whispering_Woods, L_Ancient_Oak_Grove, L_Crystal_Cave
L_Dark_Forest, L_Dragon_Mountains, L_Poisoned_Swamp
L_Lava_Chambers, L_Endless_Desert, L_Emerald_Vale
L_Shadowpine_Jungle, L_Frozen_Wastes, L_Moonlit_Glade
L_Underground_Caverns, L_Drow_Kingdom, L_Blackthorn_Citadel
L_Demonfire_Wastes
```

**Dungeons (9)**
```
D_Goblin_Cave, D_Dragon_Spire, D_Lich_Tomb
D_Demon_Citadel, D_Dark_Temple, D_Ancient_Crypt
D_Fire_Mountain, D_Shadow_Fortress, D_Abyss_Portal
```

**Miscellaneous (4)**
```
L_Tutorial, L_PvP_Arena, L_Guild_Hall, L_Test_Level
```

### ENVIRONMENT BLUEPRINTS (25+ total)

**Buildings (8)**
```
BP_House_Wooden, BP_House_Stone, BP_Castle, BP_Tower
BP_Tavern, BP_Shop, BP_Temple, BP_Barracks
```

**Nature (7)**
```
BP_Tree_Oak, BP_Tree_Pine, BP_Rock_Large, BP_Rock_Small
BP_Bush, BP_Grass, BP_Flower
```

**Terrain Materials (7)**
```
M_Grass, M_Stone, M_Sand, M_Snow
M_Mud, M_Water, M_Lava
```

**Lighting (6)**
```
BP_Sunlight, BP_Moonlight, BP_Campfire, BP_Torch
BP_MagicLight, BP_Fog
```

### MANAGER BLUEPRINTS (7 total)

```
BP_GameManager, BP_PlayerManager, BP_InputManager
BP_UIManager, BP_SaveManager, BP_DatabaseManager
BP_AudioManager
```

### UTILITY BLUEPRINTS (3 total)

```
BP_DebugVisualizer, BP_PerformanceMonitor
BP_ScreenshotCapture
```

---

## ?? TOTAL BLUEPRINT COUNT

```
Character Blueprints:          25
Item Blueprints:               45
UI Blueprints:                 65
Ability Blueprints:            30
Effects Blueprints:            25
Interactable Blueprints:       15
Multiplayer Blueprints:         7
Map/Level Blueprints:          40
Environment Blueprints:        25
Manager Blueprints:             7
Utility Blueprints:             3
????????????????????????????????
TOTAL BLUEPRINTS:             287
```

---

## ?? BLUEPRINT CREATION PRIORITY

### Phase 1: Essential Systems (Week 1-2)
```
Priority 1:
- BP_PlayerCharacter
- BP_MainHUD
- WBP_MainMenu
- BP_GameManager
- BP_InputManager
```

### Phase 2: Core Gameplay (Week 2-3)
```
Priority 2:
- BP_EnemyCharacter_Base
- BP_Ability_Base
- WBP_Inventory
- BP_InteractableBase
- All Weapon/Armor Blueprints
```

### Phase 3: Content (Week 3-4)
```
Priority 3:
- Specific Enemy Types
- Specific Abilities
- All Map Blueprints
- All NPC Types
```

### Phase 4: Polish (Week 4-5)
```
Priority 4:
- VFX/Audio Blueprints
- Settings Blueprints
- Utility Blueprints
- All remaining UI elements
```

---

## ?? SAVE FILE STRUCTURE

Each blueprint saves as `.uasset` file containing:
- Blueprint Class definition
- Components
- Event graphs
- Functions
- Variables
- Material instances
- Animation references

---

## ?? NEXT STEPS

1. **Create Folder Structure** - Use provided hierarchy
2. **Create Base Classes** - Start with BP_PlayerCharacter, BP_EnemyCharacter_Base
3. **Populate Content** - Fill folders systematically
4. **Test Systems** - Verify each blueprint works
5. **Optimize** - Remove unused assets
6. **Package** - Prepare for distribution

---

This comprehensive blueprint structure provides everything needed for a complete 3D MMORPG!
