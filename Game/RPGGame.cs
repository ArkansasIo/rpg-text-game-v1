using System;
using System.Collections.Generic;
using System.Linq;
using RPGMenuSystem.MenuSystem;
using RPGMenuSystem.SaveSystem;
using RPGMenuSystem.UI;
using RPGMenuSystem.Database;

namespace RPGMenuSystem.Game;

public class RPGGame
{
    private MenuManager _menuManager;
    private Player _player;
    private SaveManager _saveManager;
    private CombatSystem _combatSystem;
    private QuestManager _questManager;
    private ZoneManager _zoneManager;
    private bool _isNewGame;

    private DatabaseManager _databaseManager;
    private int _currentAccountId = 1; // Demo account ID
    private bool _useDatabaseMode = false;

    public RPGGame()
    {
        _menuManager = new MenuManager();
        _saveManager = new SaveManager();
        _combatSystem = new CombatSystem();
        _questManager = new QuestManager();
        _zoneManager = new ZoneManager();
        
        _player = new Player
        {
            Inventory = new List<Item>
            {
                new Item { Name = "Health Potion", Description = "Restores 50 HP", Value = 25 },
                new Item { Name = "Mana Potion", Description = "Restores 30 MP", Value = 20 }
            }
        };

        _player.Equipment.Weapon = new Equipment 
        { 
            Name = "Rusty Sword", 
            Description = "An old sword", 
            Slot = EquipmentSlot.Weapon, 
            Attack = 5, 
            Value = 10 
        };
    }

    public void SetDatabaseManager(DatabaseManager databaseManager)
    {
        _databaseManager = databaseManager;
        _useDatabaseMode = true;
        Console.WriteLine("? Database mode enabled");
    }

    public void Start()
    {
        // Show splash screen first
        SplashScreen.Show();

        // Show title screen
        TitleScreenChoice choice = TitleScreenChoice.None;
        var titleScreen = new TitleScreen((selectedChoice) =>
        {
            choice = selectedChoice;
            // Close the title screen
        });

        titleScreen.Show();

        // Handle player's choice
        switch (choice)
        {
            case TitleScreenChoice.NewGame:
                StartNewGame();
                break;
            case TitleScreenChoice.Continue:
                ContinueGame();
                break;
            case TitleScreenChoice.LoadGame:
                LoadGameFromTitle();
                break;
            case TitleScreenChoice.Settings:
                ShowSettings();
                Start(); // Return to title
                break;
            case TitleScreenChoice.Credits:
                ShowCredits();
                Start(); // Return to title
                break;
            case TitleScreenChoice.Exit:
                return;
        }
    }

    private void StartNewGame()
    {
        LoadingScreen.Show("Creating New Adventure...");
        Thread.Sleep(1000);
        _isNewGame = true;
        CreateMainMenu();
        Run();
    }

    private void ContinueGame()
    {
        var saves = _saveManager.GetAllSaves();
        if (saves.Count > 0)
        {
            var latestSave = saves.First();
            LoadingScreen.Show($"Loading {latestSave.SaveSlotName}...");
            Thread.Sleep(800);
            _player = _saveManager.LoadGame(latestSave.SaveSlotName) ?? _player;
            CreateMainMenu();
            Run();
        }
        else
        {
            Console.Clear();
            Console.WriteLine("\n\n\n                    No save data found. Starting new game...");
            Thread.Sleep(2000);
            StartNewGame();
        }
    }

    private void LoadGameFromTitle()
    {
        LoadingScreen.Show("Loading Save Data...");
        Thread.Sleep(500);
        CreateMainMenu();
        OpenLoadMenu();
        Run();
    }

    private void ShowSettings()
    {
        Console.Clear();
        Console.WriteLine("\n\n\n");
        Console.WriteLine("                              ??????????????????????????????");
        Console.WriteLine("                              ?         Settings           ?");
        Console.WriteLine("                              ??????????????????????????????");
        Console.WriteLine("\n                              Audio: ON");
        Console.WriteLine("                              Difficulty: Normal");
        Console.WriteLine("                              Controls: Standard");
        Console.WriteLine("\n\n                              Press any key to return...");
        Console.ReadKey(true);
    }

    private void ShowCredits()
    {
        Console.Clear();
        Console.ForegroundColor = ConsoleColor.Yellow;
        Console.WriteLine("\n\n\n");
        Console.WriteLine("                              ??????????????????????????????");
        Console.WriteLine("                              ?          Credits           ?");
        Console.WriteLine("                              ??????????????????????????????");
        Console.WriteLine();
        Console.WriteLine("                              Created with GitHub Copilot");
        Console.WriteLine("                              Designed for: RPG Enthusiasts");
        Console.WriteLine("                              Genre: Fantasy RPG");
        Console.WriteLine("                              Features: 72 Unique Zones");
        Console.WriteLine("                              ");
        Console.WriteLine("                              Special Thanks to:");
        Console.WriteLine("                              All RPG Fans Worldwide!");
        Console.ResetColor();
        Console.WriteLine("\n\n                              Press any key to return...");
        Console.ReadKey(true);
    }

    private void CreateMainMenu()
    {
        var mainMenu = new Menu
        {
            Title = "Main Menu",
            Items = new List<MenuItem>
            {
                new MenuItem { Text = "Character", OnSelect = () => OpenCharacterMenu() },
                new MenuItem { Text = "Inventory", OnSelect = () => OpenInventoryMenu() },
                new MenuItem { Text = "Equipment", OnSelect = () => OpenEquipmentMenu() },
                new MenuItem { Text = "Skills", OnSelect = () => OpenSkillsMenu() },
                new MenuItem { Text = "Quest Log", OnSelect = () => OpenQuestLogMenu() },
                new MenuItem { Text = "World Map", OnSelect = () => OpenWorldMapMenu() },
                new MenuItem { Text = "Explore", OnSelect = () => OpenExploreMenu() },
                new MenuItem { Text = "Shop", OnSelect = () => OpenShopSelectionMenu() },
                new MenuItem { Text = "Save/Load", OnSelect = () => OpenSaveLoadMenu() },
                new MenuItem { Text = "Settings", OnSelect = () => OpenSettingsMenu() },
                new MenuItem { Text = "Exit Game", OnSelect = () => ExitGame() }
            }
        };

        _menuManager.OpenMenu(mainMenu);
    }

    private void OpenWorldMapMenu()
    {
        var mapMenu = new Menu
        {
            Title = $"World Map - Current Zone: {_zoneManager.CurrentZone.Name}",
            Items = new List<MenuItem>()
        };

        mapMenu.Items.Add(new MenuItem { Text = $"Current: {_zoneManager.CurrentZone.Name} (Lv.{_zoneManager.CurrentZone.RecommendedLevel})", IsEnabled = false });
        mapMenu.Items.Add(new MenuItem { Text = $"Description: {_zoneManager.CurrentZone.Description}", IsEnabled = false });
        mapMenu.Items.Add(new MenuItem { Text = $"Type: {_zoneManager.CurrentZone.Type}", IsEnabled = false });
        mapMenu.Items.Add(new MenuItem { Text = "--- Connected Zones ---", IsEnabled = false });

        var connectedZones = _zoneManager.GetConnectedZones();
        foreach (var zone in connectedZones)
        {
            string displayText = zone.IsDiscovered 
                ? $"? {zone.Name} (Lv.{zone.RecommendedLevel}) - {zone.Type}"
                : $"? ??? (Undiscovered)";
                
            mapMenu.Items.Add(new MenuItem 
            { 
                Text = displayText, 
                OnSelect = () => TravelToZone(zone),
                IsEnabled = zone.IsDiscovered
            });
        }

        mapMenu.Items.Add(new MenuItem { Text = "View All Discovered Zones", OnSelect = () => ShowDiscoveredZones() });
        mapMenu.Items.Add(new MenuItem { Text = "Back", OnSelect = () => _menuManager.CloseCurrentMenu() });

        _menuManager.OpenMenu(mapMenu);
    }

    private void ShowDiscoveredZones()
    {
        var discoveredMenu = new Menu
        {
            Title = $"Discovered Zones ({_zoneManager.DiscoveredZones.Count}/72)",
            Items = new List<MenuItem>()
        };

        var zonesByType = _zoneManager.DiscoveredZones.GroupBy(z => z.Type);

        foreach (var group in zonesByType.OrderBy(g => g.Key))
        {
            discoveredMenu.Items.Add(new MenuItem { Text = $"=== {group.Key} ===", IsEnabled = false });
            
            foreach (var zone in group.OrderBy(z => z.RecommendedLevel))
            {
                discoveredMenu.Items.Add(new MenuItem 
                { 
                    Text = $"  {zone.Name} (Lv.{zone.RecommendedLevel})",
                    IsEnabled = false
                });
            }
        }

        discoveredMenu.Items.Add(new MenuItem { Text = "Back", OnSelect = () => _menuManager.CloseCurrentMenu() });

        _menuManager.OpenMenu(discoveredMenu);
    }

    private void TravelToZone(Zone targetZone)
    {
        string currentZoneName = _zoneManager.CurrentZone.Name;
        
        if (_zoneManager.TravelToZone(targetZone.Id))
        {
            _menuManager.CloseCurrentMenu();
            LoadingScreen.ShowZoneTransition(currentZoneName, targetZone.Name);
            ShowMessage($"Arrived at {targetZone.Name}!\n\n{targetZone.Description}");
        }
        else
        {
            ShowMessage("Cannot travel to that zone!");
        }
    }

    private void OpenCharacterMenu()
    {
        var characterMenu = new Menu
        {
            Title = "Character Stats",
            Items = new List<MenuItem>
            {
                new MenuItem { Text = $"Name: {_player.Name}", IsEnabled = false },
                new MenuItem { Text = $"Level: {_player.Level}", IsEnabled = false },
                new MenuItem { Text = $"Experience: {_player.Experience}/{_player.ExperienceToNextLevel}", IsEnabled = false },
                new MenuItem { Text = $"Health: {_player.Health}/{_player.MaxHealth}", IsEnabled = false },
                new MenuItem { Text = $"Mana: {_player.Mana}/{_player.MaxMana}", IsEnabled = false },
                new MenuItem { Text = $"Attack: {_player.GetTotalAttack()} ({_player.BaseAttack} + {_player.Equipment.GetTotalAttack()})", IsEnabled = false },
                new MenuItem { Text = $"Defense: {_player.GetTotalDefense()} ({_player.BaseDefense} + {_player.Equipment.GetTotalDefense()})", IsEnabled = false },
                new MenuItem { Text = $"Magic Power: {_player.GetTotalMagicPower()} ({_player.BaseMagicPower} + {_player.Equipment.GetTotalMagicPower()})", IsEnabled = false },
                new MenuItem { Text = $"Gold: {_player.Gold}", IsEnabled = false },
                new MenuItem { Text = $"Current Zone: {_zoneManager.CurrentZone.Name}", IsEnabled = false },
                new MenuItem { Text = $"Zones Discovered: {_zoneManager.DiscoveredZones.Count}/72", IsEnabled = false },
                new MenuItem { Text = "Back", OnSelect = () => _menuManager.CloseCurrentMenu() }
            }
        };

        _menuManager.OpenMenu(characterMenu);
    }

    private void OpenEquipmentMenu()
    {
        var equipmentMenu = new Menu
        {
            Title = "Equipment",
            Items = new List<MenuItem>
            {
                new MenuItem { Text = $"Weapon: {_player.Equipment.Weapon?.Name ?? "[Empty]"}", OnSelect = () => ManageEquipmentSlot(EquipmentSlot.Weapon) },
                new MenuItem { Text = $"Armor: {_player.Equipment.Armor?.Name ?? "[Empty]"}", OnSelect = () => ManageEquipmentSlot(EquipmentSlot.Armor) },
                new MenuItem { Text = $"Helmet: {_player.Equipment.Helmet?.Name ?? "[Empty]"}", OnSelect = () => ManageEquipmentSlot(EquipmentSlot.Helmet) },
                new MenuItem { Text = $"Boots: {_player.Equipment.Boots?.Name ?? "[Empty]"}", OnSelect = () => ManageEquipmentSlot(EquipmentSlot.Boots) },
                new MenuItem { Text = $"Accessory: {_player.Equipment.Accessory?.Name ?? "[Empty]"}", OnSelect = () => ManageEquipmentSlot(EquipmentSlot.Accessory) },
                new MenuItem { Text = "Back", OnSelect = () => _menuManager.CloseCurrentMenu() }
            }
        };

        _menuManager.OpenMenu(equipmentMenu);
    }

    private void ManageEquipmentSlot(EquipmentSlot slot)
    {
        var slotMenu = new Menu
        {
            Title = $"Manage {slot}",
            Items = new List<MenuItem>()
        };

        var currentEquipment = _player.Equipment.GetEquipmentInSlot(slot);
        if (currentEquipment != null)
        {
            slotMenu.Items.Add(new MenuItem 
            { 
                Text = $"[Equipped] {currentEquipment.Name} (Atk:{currentEquipment.Attack} Def:{currentEquipment.Defense} Mag:{currentEquipment.MagicPower})", 
                IsEnabled = false 
            });
            slotMenu.Items.Add(new MenuItem { Text = "Unequip", OnSelect = () => { _player.UnequipItem(slot); _menuManager.CloseCurrentMenu(); } });
        }
        else
        {
            slotMenu.Items.Add(new MenuItem { Text = "[Empty Slot]", IsEnabled = false });
        }

        slotMenu.Items.Add(new MenuItem { Text = "Back", OnSelect = () => _menuManager.CloseCurrentMenu() });

        _menuManager.OpenMenu(slotMenu);
    }

    private void OpenInventoryMenu()
    {
        var inventoryMenu = new Menu
        {
            Title = $"Inventory ({_player.Inventory.Count} items)",
            Items = new List<MenuItem>()
        };

        if (_player.Inventory.Count == 0)
        {
            inventoryMenu.Items.Add(new MenuItem { Text = "Inventory is empty", IsEnabled = false });
        }
        else
        {
            foreach (var item in _player.Inventory)
            {
                inventoryMenu.Items.Add(new MenuItem
                {
                    Text = $"{item.Name} - {item.Description} (Value: {item.Value}g)",
                    OnSelect = () => UseOrManageItem(item)
                });
            }
        }

        inventoryMenu.Items.Add(new MenuItem { Text = "Back", OnSelect = () => _menuManager.CloseCurrentMenu() });

        _menuManager.OpenMenu(inventoryMenu);
    }

    private void UseOrManageItem(Item item)
    {
        if (_player.UseItem(item))
        {
            ShowMessage($"Used {item.Name}!");
        }
        else
        {
            ShowMessage($"Cannot use {item.Name} right now.");
        }
    }

    private void OpenSkillsMenu()
    {
        var skillsMenu = new Menu
        {
            Title = "Skills",
            Items = new List<MenuItem>
            {
                new MenuItem { Text = $"Fireball (10 MP) - Magic Attack", OnSelect = () => ShowMessage("Fireball learned! Use in combat.") },
                new MenuItem { Text = $"Heal (15 MP) - Restore HP", OnSelect = () => CastHeal() },
                new MenuItem { Text = $"Lightning Strike (20 MP) - Powerful Attack", OnSelect = () => ShowMessage("Lightning Strike learned! Use in combat."), IsEnabled = _player.Level >= 5 },
                new MenuItem { Text = $"Meditation (0 MP) - Restore MP", OnSelect = () => CastMeditation() },
                new MenuItem { Text = "Back", OnSelect = () => _menuManager.CloseCurrentMenu() }
            }
        };

        _menuManager.OpenMenu(skillsMenu);
    }

    private void CastHeal()
    {
        if (_player.Mana >= 15)
        {
            _player.Mana -= 15;
            int healAmount = 30 + _player.GetTotalMagicPower();
            _player.Health = Math.Min(_player.MaxHealth, _player.Health + healAmount);
            ShowMessage($"You cast Heal! Restored {healAmount} HP!");
        }
        else
        {
            ShowMessage("Not enough mana!");
        }
    }

    private void CastMeditation()
    {
        int manaRestored = 20;
        _player.Mana = Math.Min(_player.MaxMana, _player.Mana + manaRestored);
        ShowMessage($"You meditate and restore {manaRestored} MP!");
    }

    private void OpenQuestLogMenu()
    {
        var questMenu = new Menu
        {
            Title = "Quest Log",
            Items = new List<MenuItem>()
        };

        var activeQuests = _questManager.GetActiveQuests();
        var completedQuests = _questManager.GetCompletedQuests();
        var availableQuests = _questManager.GetAvailableQuests();

        if (activeQuests.Count > 0)
        {
            questMenu.Items.Add(new MenuItem { Text = "=== Active Quests ===", IsEnabled = false });
            foreach (var quest in activeQuests)
            {
                questMenu.Items.Add(new MenuItem 
                { 
                    Text = $"[Active] {quest.Name}", 
                    OnSelect = () => ShowQuestDetails(quest) 
                });
            }
        }

        if (availableQuests.Count > 0)
        {
            questMenu.Items.Add(new MenuItem { Text = "=== Available Quests ===", IsEnabled = false });
            foreach (var quest in availableQuests)
            {
                questMenu.Items.Add(new MenuItem 
                { 
                    Text = $"[New] {quest.Name}", 
                    OnSelect = () => ShowQuestDetails(quest) 
                });
            }
        }

        if (completedQuests.Count > 0)
        {
            questMenu.Items.Add(new MenuItem { Text = "=== Completed Quests ===", IsEnabled = false });
            foreach (var quest in completedQuests)
            {
                questMenu.Items.Add(new MenuItem 
                { 
                    Text = $"[Completed] {quest.Name}", 
                    OnSelect = () => ShowQuestDetails(quest) 
                });
            }
        }

        questMenu.Items.Add(new MenuItem { Text = "Back", OnSelect = () => _menuManager.CloseCurrentMenu() });

        _menuManager.OpenMenu(questMenu);
    }

    private void ShowQuestDetails(Quest quest)
    {
        var detailsMenu = new Menu
        {
            Title = quest.Name,
            Items = new List<MenuItem>
            {
                new MenuItem { Text = $"Status: {quest.Status}", IsEnabled = false },
                new MenuItem { Text = $"Description: {quest.Description}", IsEnabled = false },
                new MenuItem { Text = $"Reward: {quest.RewardGold}g, {quest.RewardXP} XP", IsEnabled = false },
                new MenuItem { Text = "--- Objectives ---", IsEnabled = false }
            }
        };

        foreach (var objective in quest.Objectives)
        {
            string status = objective.IsCompleted ? "[?]" : "[ ]";
            detailsMenu.Items.Add(new MenuItem 
            { 
                Text = $"{status} {objective.Description} ({objective.CurrentProgress}/{objective.RequiredProgress})", 
                IsEnabled = false 
            });
        }

        if (quest.Status == QuestStatus.Available)
        {
            detailsMenu.Items.Add(new MenuItem 
            { 
                Text = "Accept Quest", 
                OnSelect = () => { _questManager.AcceptQuest(quest.Id); _menuManager.CloseCurrentMenu(); ShowMessage($"Quest '{quest.Name}' accepted!"); } 
            });
        }

        detailsMenu.Items.Add(new MenuItem { Text = "Back", OnSelect = () => _menuManager.CloseCurrentMenu() });

        _menuManager.OpenMenu(detailsMenu);
    }

    private void OpenExploreMenu()
    {
        var currentZone = _zoneManager.CurrentZone;
        
        var exploreMenu = new Menu
        {
            Title = $"Explore - {currentZone.Name}",
            Items = new List<MenuItem>()
        };

        if (currentZone.Enemies.Count > 0)
        {
            exploreMenu.Items.Add(new MenuItem { Text = "Search for enemies", OnSelect = () => StartCombat() });
        }
        
        exploreMenu.Items.Add(new MenuItem { Text = "Rest at camp (Restore HP/MP)", OnSelect = () => Rest() });
        exploreMenu.Items.Add(new MenuItem { Text = "Search for treasure", OnSelect = () => SearchTreasure() });
        
        if (currentZone.HasInn)
        {
            exploreMenu.Items.Add(new MenuItem { Text = "Visit Inn (Full Restore + Save)", OnSelect = () => VisitInn() });
        }
        
        exploreMenu.Items.Add(new MenuItem { Text = "Back", OnSelect = () => _menuManager.CloseCurrentMenu() });

        _menuManager.OpenMenu(exploreMenu);
    }

    private void VisitInn()
    {
        _player.Health = _player.MaxHealth;
        _player.Mana = _player.MaxMana;
        LoadingScreen.ShowSavingScreen();
        _saveManager.SaveGame(_player, "Auto Save");
        ShowMessage("Rested at the inn. HP and MP fully restored!\nGame automatically saved!");
    }

    private void StartCombat()
    {
        var enemy = _combatSystem.GenerateRandomEnemy();
        ShowMessage($"A wild {enemy.Name} appeared!");
        OpenCombatMenu();
    }

    private void OpenCombatMenu()
    {
        if (_combatSystem.CurrentEnemy == null)
        {
            _menuManager.CloseCurrentMenu();
            return;
        }

        var enemy = _combatSystem.CurrentEnemy;
        var combatMenu = new Menu
        {
            Title = $"Battle: {enemy.Name} (HP: {enemy.Health}/{enemy.MaxHealth})",
            Items = new List<MenuItem>
            {
                new MenuItem { Text = $"Player HP: {_player.Health}/{_player.MaxHealth} | MP: {_player.Mana}/{_player.MaxMana}", IsEnabled = false },
                new MenuItem { Text = "Attack", OnSelect = () => ExecuteCombatAction(() => _combatSystem.PlayerAttack(_player)) },
                new MenuItem { Text = "Defend", OnSelect = () => ExecuteCombatAction(() => _combatSystem.PlayerDefend(_player)) },
                new MenuItem { Text = "Use Item", OnSelect = () => OpenCombatItemMenu() },
                new MenuItem { Text = "Cast Fireball (10 MP)", OnSelect = () => CastFireball(), IsEnabled = _player.Mana >= 10 },
                new MenuItem { Text = "Flee", OnSelect = () => ExecuteCombatAction(() => _combatSystem.PlayerFlee()) }
            }
        };

        _menuManager.OpenMenu(combatMenu);
    }

    private void CastFireball()
    {
        if (_combatSystem.CurrentEnemy == null) return;

        _player.Mana -= 10;
        int damage = _player.GetTotalMagicPower() + 15;
        int actualDamage = _combatSystem.CurrentEnemy.TakeDamage(damage);
        
        string message = $"You cast Fireball for {actualDamage} damage!";

        if (!_combatSystem.CurrentEnemy.IsAlive)
        {
            _player.GainExperience(_combatSystem.CurrentEnemy.XPReward);
            _player.Gold += _combatSystem.CurrentEnemy.GoldReward;
            message += $"\n{_combatSystem.CurrentEnemy.Name} defeated! Gained {_combatSystem.CurrentEnemy.XPReward} XP and {_combatSystem.CurrentEnemy.GoldReward} gold!";
            _combatSystem.EndCombat();
            _menuManager.CloseCurrentMenu();
        }
        else
        {
            int enemyDamage = _combatSystem.CurrentEnemy.AttackPlayer();
            int playerDamage = _player.TakeDamage(enemyDamage);
            message += $"\n{_combatSystem.CurrentEnemy.Name} attacks for {playerDamage} damage!";

            if (!_player.IsAlive)
            {
                message += "\nYou have been defeated!";
                _player.Health = _player.MaxHealth / 2;
                _player.Mana = _player.MaxMana / 2;
                _combatSystem.EndCombat();
                _menuManager.CloseCurrentMenu();
            }
        }

        ShowMessage(message);
    }

    private void OpenCombatItemMenu()
    {
        var itemMenu = new Menu
        {
            Title = "Use Item in Combat",
            Items = new List<MenuItem>()
        };

        var usableItems = _player.Inventory.Where(i => i.Name.Contains("Potion") || i.Name.Contains("Elixir")).ToList();

        if (usableItems.Count == 0)
        {
            itemMenu.Items.Add(new MenuItem { Text = "No usable items", IsEnabled = false });
        }
        else
        {
            foreach (var item in usableItems)
            {
                itemMenu.Items.Add(new MenuItem 
                { 
                    Text = item.Name, 
                    OnSelect = () => UseCombatItem(item) 
                });
            }
        }

        itemMenu.Items.Add(new MenuItem { Text = "Back", OnSelect = () => _menuManager.CloseCurrentMenu() });

        _menuManager.OpenMenu(itemMenu);
    }

    private void UseCombatItem(Item item)
    {
        _player.UseItem(item);
        _menuManager.CloseCurrentMenu();
        
        if (_combatSystem.CurrentEnemy != null && _combatSystem.CurrentEnemy.IsAlive)
        {
            int enemyDamage = _combatSystem.CurrentEnemy.AttackPlayer();
            int playerDamage = _player.TakeDamage(enemyDamage);
            ShowMessage($"Used {item.Name}!\n{_combatSystem.CurrentEnemy.Name} attacks for {playerDamage} damage!");
        }
    }

    private void ExecuteCombatAction(Func<CombatResult> action)
    {
        var result = action();
        
        if (result.CombatEnded)
        {
            _combatSystem.EndCombat();
            _menuManager.CloseCurrentMenu();
        }

        ShowMessage(result.Message);
    }

    private void Rest()
    {
        _player.Health = _player.MaxHealth;
        _player.Mana = _player.MaxMana;
        ShowMessage("You rest at camp. HP and MP fully restored!");
    }

    private void SearchTreasure()
    {
        Random rand = new Random();
        int chance = rand.Next(100);

        if (chance < 40)
        {
            int goldFound = rand.Next(20, 100);
            _player.Gold += goldFound;
            ShowMessage($"You found a treasure chest containing {goldFound} gold!");
        }
        else if (chance < 60)
        {
            var items = new[] 
            { 
                new Item { Name = "Health Potion", Description = "Restores 50 HP", Value = 25 },
                new Item { Name = "Mana Potion", Description = "Restores 30 MP", Value = 20 }
            };
            var foundItem = items[rand.Next(items.Length)];
            _player.Inventory.Add(foundItem);
            ShowMessage($"You found {foundItem.Name}!");
        }
        else
        {
            ShowMessage("You searched but found nothing...");
        }
    }

    private void OpenShopSelectionMenu()
    {
        if (!_zoneManager.CurrentZone.HasShop)
        {
            ShowMessage("There are no shops in this zone!");
            return;
        }

        var shopMenu = new Menu
        {
            Title = "Select Shop",
            Items = new List<MenuItem>
            {
                new MenuItem { Text = "General Store", OnSelect = () => OpenShop(Shop.CreateGeneralShop()) },
                new MenuItem { Text = "Weapon Shop", OnSelect = () => OpenShop(Shop.CreateWeaponShop()) },
                new MenuItem { Text = "Armor Shop", OnSelect = () => OpenShop(Shop.CreateArmorShop()) },
                new MenuItem { Text = "Back", OnSelect = () => _menuManager.CloseCurrentMenu() }
            }
        };

        _menuManager.OpenMenu(shopMenu);
    }

    private void OpenShop(Shop shop)
    {
        var shopMenu = new Menu
        {
            Title = $"{shop.Name} (Gold: {_player.Gold}g)",
            Items = new List<MenuItem>()
        };

        foreach (var item in shop.ItemsForSale)
        {
            shopMenu.Items.Add(new MenuItem 
            { 
                Text = $"{item.Name} - {item.Value}g", 
                OnSelect = () => BuyItem(item),
                IsEnabled = _player.Gold >= item.Value
            });
        }

        foreach (var equipment in shop.EquipmentForSale)
        {
            shopMenu.Items.Add(new MenuItem 
            { 
                Text = $"{equipment.Name} (Atk:{equipment.Attack} Def:{equipment.Defense} Mag:{equipment.MagicPower}) - {equipment.Value}g", 
                OnSelect = () => BuyEquipment(equipment),
                IsEnabled = _player.Gold >= equipment.Value
            });
        }

        shopMenu.Items.Add(new MenuItem { Text = "Sell Items", OnSelect = () => OpenSellMenu() });
        shopMenu.Items.Add(new MenuItem { Text = "Back", OnSelect = () => _menuManager.CloseCurrentMenu() });

        _menuManager.OpenMenu(shopMenu);
    }

    private void BuyItem(Item item)
    {
        if (_player.Gold >= item.Value)
        {
            _player.Gold -= item.Value;
            _player.Inventory.Add(item);
            ShowMessage($"Purchased {item.Name} for {item.Value}g!");
        }
        else
        {
            ShowMessage("Not enough gold!");
        }
    }

    private void BuyEquipment(Equipment equipment)
    {
        if (_player.Gold >= equipment.Value)
        {
            _player.Gold -= equipment.Value;
            _player.Inventory.Add(new Item 
            { 
                Name = equipment.Name, 
                Description = equipment.Description, 
                Value = equipment.Value 
            });
            ShowMessage($"Purchased {equipment.Name} for {equipment.Value}g! Check inventory to equip.");
        }
        else
        {
            ShowMessage("Not enough gold!");
        }
    }

    private void OpenSellMenu()
    {
        var sellMenu = new Menu
        {
            Title = "Sell Items",
            Items = new List<MenuItem>()
        };

        if (_player.Inventory.Count == 0)
        {
            sellMenu.Items.Add(new MenuItem { Text = "Nothing to sell", IsEnabled = false });
        }
        else
        {
            foreach (var item in _player.Inventory)
            {
                int sellPrice = item.Value / 2;
                sellMenu.Items.Add(new MenuItem 
                { 
                    Text = $"{item.Name} - Sell for {sellPrice}g", 
                    OnSelect = () => SellItem(item, sellPrice) 
                });
            }
        }

        sellMenu.Items.Add(new MenuItem { Text = "Back", OnSelect = () => _menuManager.CloseCurrentMenu() });

        _menuManager.OpenMenu(sellMenu);
    }

    private void SellItem(Item item, int price)
    {
        _player.Gold += price;
        _player.Inventory.Remove(item);
        ShowMessage($"Sold {item.Name} for {price}g!");
    }

    private void OpenSaveLoadMenu()
    {
        var saveLoadMenu = new Menu
        {
            Title = "Save/Load Game",
            Items = new List<MenuItem>
            {
                new MenuItem { Text = "Save Game", OnSelect = () => OpenSaveMenu() },
                new MenuItem { Text = "Load Game", OnSelect = () => OpenLoadMenu() },
                new MenuItem { Text = "Delete Save", OnSelect = () => OpenDeleteMenu() },
                new MenuItem { Text = "Back", OnSelect = () => _menuManager.CloseCurrentMenu() }
            }
        };

        _menuManager.OpenMenu(saveLoadMenu);
    }

    private void OpenSaveMenu()
    {
        var saveMenu = new Menu
        {
            Title = "Save Game - Select Slot",
            Items = new List<MenuItem>()
        };

        var existingSaves = _saveManager.GetAllSaves();
        var slotNames = new[] { "Slot 1", "Slot 2", "Slot 3", "Quick Save" };

        foreach (var slotName in slotNames)
        {
            var existingSave = existingSaves.FirstOrDefault(s => s.SaveSlotName == slotName);
            string displayText = slotName;

            if (existingSave != null)
            {
                displayText += $" - {existingSave.PlayerName} Lv.{existingSave.Level} ({existingSave.SavedAt:g})";
            }
            else
            {
                displayText += " - [Empty]";
            }

            string capturedSlotName = slotName;
            saveMenu.Items.Add(new MenuItem
            {
                Text = displayText,
                OnSelect = () => SaveGame(capturedSlotName)
            });
        }

        saveMenu.Items.Add(new MenuItem { Text = "Back", OnSelect = () => _menuManager.CloseCurrentMenu() });

        _menuManager.OpenMenu(saveMenu);
    }

    private void OpenLoadMenu()
    {
        var loadMenu = new Menu
        {
            Title = "Load Game - Select Slot",
            Items = new List<MenuItem>()
        };

        var existingSaves = _saveManager.GetAllSaves();

        if (existingSaves.Count == 0)
        {
            loadMenu.Items.Add(new MenuItem { Text = "No saves found", IsEnabled = false });
        }
        else
        {
            foreach (var save in existingSaves)
            {
                string displayText = $"{save.SaveSlotName} - {save.PlayerName} Lv.{save.Level} ({save.SavedAt:g})";
                string capturedSlotName = save.SaveSlotName;

                loadMenu.Items.Add(new MenuItem
                {
                    Text = displayText,
                    OnSelect = () => LoadGame(capturedSlotName)
                });
            }
        }

        loadMenu.Items.Add(new MenuItem { Text = "Back", OnSelect = () => _menuManager.CloseCurrentMenu() });

        _menuManager.OpenMenu(loadMenu);
    }

    private void OpenDeleteMenu()
    {
        var deleteMenu = new Menu
        {
            Title = "Delete Save - Select Slot",
            Items = new List<MenuItem>()
        };

        var existingSaves = _saveManager.GetAllSaves();

        if (existingSaves.Count == 0)
        {
            deleteMenu.Items.Add(new MenuItem { Text = "No saves to delete", IsEnabled = false });
        }
        else
        {
            foreach (var save in existingSaves)
            {
                string displayText = $"{save.SaveSlotName} - {save.PlayerName} Lv.{save.Level}";
                string capturedSlotName = save.SaveSlotName;

                deleteMenu.Items.Add(new MenuItem
                {
                    Text = displayText,
                    OnSelect = () => ConfirmDeleteSave(capturedSlotName)
                });
            }
        }

        deleteMenu.Items.Add(new MenuItem { Text = "Back", OnSelect = () => _menuManager.CloseCurrentMenu() });

        _menuManager.OpenMenu(deleteMenu);
    }

    private void SaveGame(string slotName)
    {
        LoadingScreen.ShowSavingScreen();
        bool success = _saveManager.SaveGame(_player, slotName);
        string message = success
            ? $"Game saved successfully to {slotName}!"
            : "Failed to save game.";

        ShowMessage(message);
    }

    private void LoadGame(string slotName)
    {
        LoadingScreen.Show($"Loading {slotName}...");
        Thread.Sleep(1000);
        
        var loadedPlayer = _saveManager.LoadGame(slotName);

        if (loadedPlayer != null)
        {
            _player = loadedPlayer;
            ShowMessage($"Game loaded successfully from {slotName}!");
        }
        else
        {
            ShowMessage("Failed to load game.");
        }
    }

    private void ConfirmDeleteSave(string slotName)
    {
        var confirmMenu = new Menu
        {
            Title = $"Delete {slotName}?",
            Items = new List<MenuItem>
            {
                new MenuItem { Text = "Yes, delete this save", OnSelect = () => DeleteSave(slotName) },
                new MenuItem { Text = "No, cancel", OnSelect = () => _menuManager.CloseCurrentMenu() }
            }
        };

        _menuManager.OpenMenu(confirmMenu);
    }

    private void DeleteSave(string slotName)
    {
        bool success = _saveManager.DeleteSave(slotName);
        _menuManager.CloseCurrentMenu();

        string message = success
            ? $"Save '{slotName}' deleted successfully!"
            : "Failed to delete save.";

        ShowMessage(message);
    }

    private void OpenSettingsMenu()
    {
        var settingsMenu = new Menu
        {
            Title = "Settings",
            Items = new List<MenuItem>
            {
                new MenuItem { Text = "Audio Settings", OnSelect = () => ShowMessage("Audio settings not implemented") },
                new MenuItem { Text = "Video Settings", OnSelect = () => ShowMessage("Video settings not implemented") },
                new MenuItem { Text = "Controls", OnSelect = () => ShowMessage("Controls settings not implemented") },
                new MenuItem { Text = "Back", OnSelect = () => _menuManager.CloseCurrentMenu() }
            }
        };

        _menuManager.OpenMenu(settingsMenu);
    }

    private void ShowMessage(string message)
    {
        var messageMenu = new Menu
        {
            Title = "Message",
            Items = new List<MenuItem>
            {
                new MenuItem { Text = message, IsEnabled = false },
                new MenuItem { Text = "OK", OnSelect = () => _menuManager.CloseCurrentMenu() }
            }
        };

        _menuManager.OpenMenu(messageMenu);
    }

    private void ExitGame()
    {
        _menuManager.CloseAllMenus();
    }

    public void Run()
    {
        while (_menuManager.CurrentMenu != null)
        {
            _menuManager.Render();
            var key = Console.ReadKey(true).Key;
            _menuManager.HandleInput(key);
        }

        Console.Clear();
        Console.WriteLine("Thanks for playing!");
    }
}
