namespace RPGMenuSystem.Game;

public class Equipment
{
    public string Name { get; set; } = string.Empty;
    public string Description { get; set; } = string.Empty;
    public EquipmentSlot Slot { get; set; }
    public int Attack { get; set; }
    public int Defense { get; set; }
    public int MagicPower { get; set; }
    public int Value { get; set; }
}

public enum EquipmentSlot
{
    Weapon,
    Armor,
    Helmet,
    Boots,
    Accessory
}

public class PlayerEquipment
{
    public Equipment? Weapon { get; set; }
    public Equipment? Armor { get; set; }
    public Equipment? Helmet { get; set; }
    public Equipment? Boots { get; set; }
    public Equipment? Accessory { get; set; }

    public int GetTotalAttack()
    {
        int total = 0;
        if (Weapon != null) total += Weapon.Attack;
        if (Armor != null) total += Armor.Attack;
        if (Helmet != null) total += Helmet.Attack;
        if (Boots != null) total += Boots.Attack;
        if (Accessory != null) total += Accessory.Attack;
        return total;
    }

    public int GetTotalDefense()
    {
        int total = 0;
        if (Weapon != null) total += Weapon.Defense;
        if (Armor != null) total += Armor.Defense;
        if (Helmet != null) total += Helmet.Defense;
        if (Boots != null) total += Boots.Defense;
        if (Accessory != null) total += Accessory.Defense;
        return total;
    }

    public int GetTotalMagicPower()
    {
        int total = 0;
        if (Weapon != null) total += Weapon.MagicPower;
        if (Armor != null) total += Armor.MagicPower;
        if (Helmet != null) total += Helmet.MagicPower;
        if (Boots != null) total += Boots.MagicPower;
        if (Accessory != null) total += Accessory.MagicPower;
        return total;
    }

    public Equipment? GetEquipmentInSlot(EquipmentSlot slot)
    {
        return slot switch
        {
            EquipmentSlot.Weapon => Weapon,
            EquipmentSlot.Armor => Armor,
            EquipmentSlot.Helmet => Helmet,
            EquipmentSlot.Boots => Boots,
            EquipmentSlot.Accessory => Accessory,
            _ => null
        };
    }

    public void SetEquipmentInSlot(EquipmentSlot slot, Equipment? equipment)
    {
        switch (slot)
        {
            case EquipmentSlot.Weapon:
                Weapon = equipment;
                break;
            case EquipmentSlot.Armor:
                Armor = equipment;
                break;
            case EquipmentSlot.Helmet:
                Helmet = equipment;
                break;
            case EquipmentSlot.Boots:
                Boots = equipment;
                break;
            case EquipmentSlot.Accessory:
                Accessory = equipment;
                break;
        }
    }
}
