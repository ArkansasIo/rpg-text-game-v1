namespace RPGMenuSystem.SaveSystem;

public class SaveData
{
    public string PlayerName { get; set; } = string.Empty;
    public int Level { get; set; }
    public int Health { get; set; }
    public int MaxHealth { get; set; }
    public int Mana { get; set; }
    public int MaxMana { get; set; }
    public int Gold { get; set; }
    public List<ItemData> Inventory { get; set; } = new();
    public DateTime SavedAt { get; set; }
    public string SaveSlotName { get; set; } = string.Empty;
}

public class ItemData
{
    public string Name { get; set; } = string.Empty;
    public string Description { get; set; } = string.Empty;
    public int Value { get; set; }
}
