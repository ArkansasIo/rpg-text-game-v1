namespace RPGMenuSystem.Game;

public class Shop
{
    public string Name { get; set; } = string.Empty;
    public List<Item> ItemsForSale { get; set; } = new();
    public List<Equipment> EquipmentForSale { get; set; } = new();

    public static Shop CreateGeneralShop()
    {
        return new Shop
        {
            Name = "General Store",
            ItemsForSale = new List<Item>
            {
                new Item { Name = "Health Potion", Description = "Restores 50 HP", Value = 25 },
                new Item { Name = "Mana Potion", Description = "Restores 30 MP", Value = 20 },
                new Item { Name = "Antidote", Description = "Cures poison", Value = 15 },
                new Item { Name = "Elixir", Description = "Restores HP and MP", Value = 50 }
            }
        };
    }

    public static Shop CreateWeaponShop()
    {
        return new Shop
        {
            Name = "Weapon Shop",
            EquipmentForSale = new List<Equipment>
            {
                new Equipment { Name = "Iron Sword", Description = "A sturdy iron blade", Slot = EquipmentSlot.Weapon, Attack = 15, Value = 100 },
                new Equipment { Name = "Steel Sword", Description = "A well-crafted steel blade", Slot = EquipmentSlot.Weapon, Attack = 25, Value = 250 },
                new Equipment { Name = "Magic Staff", Description = "Channels magical energy", Slot = EquipmentSlot.Weapon, Attack = 10, MagicPower = 20, Value = 200 },
                new Equipment { Name = "Dagger", Description = "Fast and deadly", Slot = EquipmentSlot.Weapon, Attack = 12, Value = 80 }
            }
        };
    }

    public static Shop CreateArmorShop()
    {
        return new Shop
        {
            Name = "Armor Shop",
            EquipmentForSale = new List<Equipment>
            {
                new Equipment { Name = "Leather Armor", Description = "Basic protection", Slot = EquipmentSlot.Armor, Defense = 10, Value = 150 },
                new Equipment { Name = "Chainmail", Description = "Sturdy metal armor", Slot = EquipmentSlot.Armor, Defense = 20, Value = 350 },
                new Equipment { Name = "Iron Helmet", Description = "Protects your head", Slot = EquipmentSlot.Helmet, Defense = 5, Value = 100 },
                new Equipment { Name = "Steel Boots", Description = "Reinforced footwear", Slot = EquipmentSlot.Boots, Defense = 8, Value = 120 },
                new Equipment { Name = "Magic Ring", Description = "Enhances magic power", Slot = EquipmentSlot.Accessory, MagicPower = 15, Value = 300 }
            }
        };
    }
}
