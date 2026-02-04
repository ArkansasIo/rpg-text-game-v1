namespace RPGMenuSystem.Game;

public enum EquipmentSlotType
{
    Head,
    Neck,
    Shoulders,
    Back,
    Chest,
    Shirt,
    Tabard,
    Wrist,
    Hands,
    Waist,
    Legs,
    Feet,
    Finger1,
    Finger2,
    Trinket1,
    Trinket2,
    MainHand,
    OffHand,
    Ranged
}

public enum ItemQuality
{
    Poor,       // Gray
    Common,     // White
    Uncommon,   // Green
    Rare,       // Blue
    Epic,       // Purple
    Legendary,  // Orange
    Artifact,   // Gold
    Heirloom    // Light Blue
}

public enum ItemType
{
    Weapon,
    Armor,
    Consumable,
    Quest,
    Reagent,
    Container,
    Misc,
    Gem,
    Enchant
}

public enum WeaponType
{
    Sword,
    Axe,
    Mace,
    Dagger,
    Fist,
    Staff,
    Polearm,
    Bow,
    Crossbow,
    Gun,
    Wand,
    Shield
}

public enum ArmorType
{
    Cloth,
    Leather,
    Mail,
    Plate,
    Shield
}

public class AdvancedItem
{
    public int Id { get; set; }
    public string Name { get; set; } = string.Empty;
    public string Description { get; set; } = string.Empty;
    public ItemQuality Quality { get; set; }
    public ItemType Type { get; set; }
    public int Value { get; set; }
    public int RequiredLevel { get; set; }
    public int ItemLevel { get; set; }
    public bool Soulbound { get; set; }
    public bool Unique { get; set; }
    public int MaxStack { get; set; } = 1;
    public int CurrentStack { get; set; } = 1;
    
    // Equipment specific
    public EquipmentSlotType? EquipmentSlot { get; set; }
    public WeaponType? WeaponType { get; set; }
    public ArmorType? ArmorType { get; set; }
    
    // Stats
    public Dictionary<string, int> Stats { get; set; } = new();
    
    // Socket/Gem system
    public int Sockets { get; set; }
    public List<AdvancedItem> SocketedGems { get; set; } = new();
    
    // Enchantment
    public string? EnchantName { get; set; }
    public Dictionary<string, int> EnchantStats { get; set; } = new();
    
    public string GetQualityColorCode()
    {
        return Quality switch
        {
            ItemQuality.Poor => "Gray",
            ItemQuality.Common => "White",
            ItemQuality.Uncommon => "Green",
            ItemQuality.Rare => "Blue",
            ItemQuality.Epic => "Magenta",
            ItemQuality.Legendary => "DarkYellow",
            ItemQuality.Artifact => "Yellow",
            ItemQuality.Heirloom => "Cyan",
            _ => "White"
        };
    }
}

public class AdvancedEquipment
{
    private Dictionary<EquipmentSlotType, AdvancedItem?> _equippedItems = new();

    public AdvancedEquipment()
    {
        // Initialize all slots
        foreach (EquipmentSlotType slot in Enum.GetValues(typeof(EquipmentSlotType)))
        {
            _equippedItems[slot] = null;
        }
    }

    public AdvancedItem? GetEquipment(EquipmentSlotType slot)
    {
        return _equippedItems.ContainsKey(slot) ? _equippedItems[slot] : null;
    }

    public void SetEquipment(EquipmentSlotType slot, AdvancedItem? item)
    {
        _equippedItems[slot] = item;
    }

    public Dictionary<string, int> GetTotalStats()
    {
        var totalStats = new Dictionary<string, int>();

        foreach (var item in _equippedItems.Values)
        {
            if (item != null)
            {
                foreach (var stat in item.Stats)
                {
                    if (!totalStats.ContainsKey(stat.Key))
                        totalStats[stat.Key] = 0;
                    totalStats[stat.Key] += stat.Value;
                }

                // Add enchant stats
                foreach (var stat in item.EnchantStats)
                {
                    if (!totalStats.ContainsKey(stat.Key))
                        totalStats[stat.Key] = 0;
                    totalStats[stat.Key] += stat.Value;
                }

                // Add socketed gem stats
                foreach (var gem in item.SocketedGems)
                {
                    foreach (var stat in gem.Stats)
                    {
                        if (!totalStats.ContainsKey(stat.Key))
                            totalStats[stat.Key] = 0;
                        totalStats[stat.Key] += stat.Value;
                    }
                }
            }
        }

        return totalStats;
    }

    public int GetItemLevel()
    {
        int totalItemLevel = 0;
        int count = 0;

        foreach (var item in _equippedItems.Values)
        {
            if (item != null)
            {
                totalItemLevel += item.ItemLevel;
                count++;
            }
        }

        return count > 0 ? totalItemLevel / count : 0;
    }
}

public class GridInventory
{
    public int Rows { get; private set; }
    public int Columns { get; private set; }
    public AdvancedItem?[,] Grid { get; private set; }

    public GridInventory(int rows, int columns)
    {
        Rows = rows;
        Columns = columns;
        Grid = new AdvancedItem?[rows, columns];
    }

    public bool AddItem(AdvancedItem item)
    {
        // Try to stack with existing items first
        if (item.MaxStack > 1)
        {
            for (int r = 0; r < Rows; r++)
            {
                for (int c = 0; c < Columns; c++)
                {
                    var existingItem = Grid[r, c];
                    if (existingItem != null && existingItem.Id == item.Id && existingItem.CurrentStack < existingItem.MaxStack)
                    {
                        int spaceLeft = existingItem.MaxStack - existingItem.CurrentStack;
                        int toAdd = Math.Min(spaceLeft, item.CurrentStack);
                        existingItem.CurrentStack += toAdd;
                        item.CurrentStack -= toAdd;

                        if (item.CurrentStack == 0)
                            return true;
                    }
                }
            }
        }

        // Find empty slot
        for (int r = 0; r < Rows; r++)
        {
            for (int c = 0; c < Columns; c++)
            {
                if (Grid[r, c] == null)
                {
                    Grid[r, c] = item;
                    return true;
                }
            }
        }

        return false; // Inventory full
    }

    public bool RemoveItem(int row, int col)
    {
        if (row >= 0 && row < Rows && col >= 0 && col < Columns)
        {
            Grid[row, col] = null;
            return true;
        }
        return false;
    }

    public AdvancedItem? GetItem(int row, int col)
    {
        if (row >= 0 && row < Rows && col >= 0 && col < Columns)
        {
            return Grid[row, col];
        }
        return null;
    }

    public bool MoveItem(int fromRow, int fromCol, int toRow, int toCol)
    {
        var item = GetItem(fromRow, fromCol);
        if (item == null) return false;

        var targetItem = GetItem(toRow, toCol);
        
        // Swap items
        Grid[toRow, toCol] = item;
        Grid[fromRow, fromCol] = targetItem;
        
        return true;
    }

    public int GetFreeSlots()
    {
        int count = 0;
        for (int r = 0; r < Rows; r++)
        {
            for (int c = 0; c < Columns; c++)
            {
                if (Grid[r, c] == null)
                    count++;
            }
        }
        return count;
    }

    public List<AdvancedItem> GetAllItems()
    {
        var items = new List<AdvancedItem>();
        for (int r = 0; r < Rows; r++)
        {
            for (int c = 0; c < Columns; c++)
            {
                if (Grid[r, c] != null)
                    items.Add(Grid[r, c]!);
            }
        }
        return items;
    }
}

public class BankSystem
{
    public GridInventory MainBank { get; private set; }
    public List<GridInventory> BankTabs { get; private set; }
    public int Gold { get; set; }

    public BankSystem()
    {
        MainBank = new GridInventory(7, 7); // 49 slots
        BankTabs = new List<GridInventory>();
        
        // Start with 3 tabs, can be expanded
        for (int i = 0; i < 3; i++)
        {
            BankTabs.Add(new GridInventory(7, 7));
        }
    }

    public bool DepositItem(AdvancedItem item, int tabIndex = -1)
    {
        if (tabIndex == -1)
        {
            return MainBank.AddItem(item);
        }
        else if (tabIndex >= 0 && tabIndex < BankTabs.Count)
        {
            return BankTabs[tabIndex].AddItem(item);
        }
        return false;
    }

    public bool DepositGold(int amount)
    {
        Gold += amount;
        return true;
    }

    public bool WithdrawGold(int amount)
    {
        if (Gold >= amount)
        {
            Gold -= amount;
            return true;
        }
        return false;
    }

    public void PurchaseBankTab()
    {
        BankTabs.Add(new GridInventory(7, 7));
    }

    public int GetTotalSlots()
    {
        int total = MainBank.Rows * MainBank.Columns;
        foreach (var tab in BankTabs)
        {
            total += tab.Rows * tab.Columns;
        }
        return total;
    }
}
