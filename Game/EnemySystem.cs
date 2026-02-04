namespace RPGMenuSystem.Game;

public enum EnemyType
{
    Beast,
    Humanoid,
    Undead,
    Demon,
    Elemental,
    Dragon,
    Giant,
    Aberration,
    Mechanical,
    Critter,
    Dragonkin
}

public enum EnemyRank
{
    Normal,
    Elite,
    RareElite,
    Boss,
    WorldBoss,
    RaidBoss
}

public class EnemyTemplate
{
    public int Id { get; set; }
    public string Name { get; set; } = string.Empty;
    public EnemyType Type { get; set; }
    public EnemyRank Rank { get; set; }
    public int Level { get; set; }
    public int Health { get; set; }
    public int Mana { get; set; }
    public int Attack { get; set; }
    public int Defense { get; set; }
    public int MagicPower { get; set; }
    public List<string> Abilities { get; set; } = new();
    public List<string> Resistances { get; set; } = new();
    public List<string> Weaknesses { get; set; } = new();
    public int XPReward { get; set; }
    public int GoldReward { get; set; }
    public List<AdvancedItem> LootTable { get; set; } = new();
    public float DropRate { get; set; } = 0.3f;
    public string Description { get; set; } = string.Empty;
    
    public static List<EnemyTemplate> GetEnemyTemplates()
    {
        return new List<EnemyTemplate>
        {
            // Beasts
            new EnemyTemplate { Id = 1, Name = "Wolf", Type = EnemyType.Beast, Rank = EnemyRank.Normal, Level = 5, Health = 100, Attack = 12, Defense = 3, XPReward = 50, GoldReward = 5, Abilities = new List<string> { "Bite", "Howl" } },
            new EnemyTemplate { Id = 2, Name = "Bear", Type = EnemyType.Beast, Rank = EnemyRank.Normal, Level = 8, Health = 200, Attack = 18, Defense = 5, XPReward = 80, GoldReward = 10, Abilities = new List<string> { "Maul", "Swipe" } },
            new EnemyTemplate { Id = 3, Name = "Raptor", Type = EnemyType.Beast, Rank = EnemyRank.Normal, Level = 15, Health = 250, Attack = 25, Defense = 7, XPReward = 120, GoldReward = 15, Abilities = new List<string> { "Rend", "Pounce" } },
            new EnemyTemplate { Id = 4, Name = "Elder Bear", Type = EnemyType.Beast, Rank = EnemyRank.Elite, Level = 20, Health = 800, Attack = 40, Defense = 15, XPReward = 500, GoldReward = 50, Abilities = new List<string> { "Crushing Blow", "Roar", "Enrage" } },
            
            // Humanoids
            new EnemyTemplate { Id = 5, Name = "Bandit", Type = EnemyType.Humanoid, Rank = EnemyRank.Normal, Level = 10, Health = 180, Attack = 20, Defense = 5, XPReward = 100, GoldReward = 25, Abilities = new List<string> { "Backstab", "Throw Dagger" } },
            new EnemyTemplate { Id = 6, Name = "Orc Warrior", Type = EnemyType.Humanoid, Rank = EnemyRank.Normal, Level = 25, Health = 500, Attack = 45, Defense = 20, XPReward = 250, GoldReward = 40, Abilities = new List<string> { "Cleave", "Shield Bash" } },
            new EnemyTemplate { Id = 7, Name = "Dark Mage", Type = EnemyType.Humanoid, Rank = EnemyRank.Elite, Level = 35, Health = 800, Mana = 1000, Attack = 30, MagicPower = 60, Defense = 15, XPReward = 600, GoldReward = 75, Abilities = new List<string> { "Fireball", "Frost Nova", "Blink" } },
            new EnemyTemplate { Id = 8, Name = "Bandit Lord", Type = EnemyType.Humanoid, Rank = EnemyRank.RareElite, Level = 40, Health = 2000, Attack = 80, Defense = 30, XPReward = 1500, GoldReward = 200, Abilities = new List<string> { "Dual Strike", "Poison Blade", "Shadow Step" } },
            
            // Undead
            new EnemyTemplate { Id = 9, Name = "Zombie", Type = EnemyType.Undead, Rank = EnemyRank.Normal, Level = 12, Health = 200, Attack = 15, Defense = 3, XPReward = 90, GoldReward = 8, Abilities = new List<string> { "Infectious Bite" }, Weaknesses = new List<string> { "Holy" } },
            new EnemyTemplate { Id = 10, Name = "Skeleton Warrior", Type = EnemyType.Undead, Rank = EnemyRank.Normal, Level = 18, Health = 300, Attack = 28, Defense = 10, XPReward = 150, GoldReward = 20, Abilities = new List<string> { "Bone Strike", "Shield Wall" }, Weaknesses = new List<string> { "Holy", "Blunt" } },
            new EnemyTemplate { Id = 11, Name = "Lich", Type = EnemyType.Undead, Rank = EnemyRank.Elite, Level = 50, Health = 3000, Mana = 2000, MagicPower = 90, Defense = 25, XPReward = 2000, GoldReward = 300, Abilities = new List<string> { "Death Coil", "Frost Nova", "Raise Dead", "Phylactery" }, Weaknesses = new List<string> { "Holy" } },
            new EnemyTemplate { Id = 12, Name = "Vampire Lord", Type = EnemyType.Undead, Rank = EnemyRank.Boss, Level = 60, Health = 10000, Attack = 150, Defense = 50, XPReward = 5000, GoldReward = 1000, Abilities = new List<string> { "Life Drain", "Blood Frenzy", "Bat Form", "Hypnotize" }, Weaknesses = new List<string> { "Holy", "Fire" } },
            
            // Demons
            new EnemyTemplate { Id = 13, Name = "Imp", Type = EnemyType.Demon, Rank = EnemyRank.Normal, Level = 20, Health = 250, Mana = 300, MagicPower = 35, Defense = 5, XPReward = 180, GoldReward = 30, Abilities = new List<string> { "Firebolt", "Phase Shift" } },
            new EnemyTemplate { Id = 14, Name = "Felguard", Type = EnemyType.Demon, Rank = EnemyRank.Elite, Level = 45, Health = 2500, Attack = 85, Defense = 35, XPReward = 1800, GoldReward = 250, Abilities = new List<string> { "Fel Cleave", "Demonic Charge", "Intimidate" } },
            new EnemyTemplate { Id = 15, Name = "Pit Lord", Type = EnemyType.Demon, Rank = EnemyRank.RareElite, Level = 55, Health = 8000, Attack = 120, Defense = 40, XPReward = 4000, GoldReward = 800, Abilities = new List<string> { "Doom", "Rain of Fire", "Howl of Terror" } },
            new EnemyTemplate { Id = 16, Name = "Demon Lord Kazzak", Type = EnemyType.Demon, Rank = EnemyRank.WorldBoss, Level = 70, Health = 50000, Attack = 250, MagicPower = 150, Defense = 100, XPReward = 20000, GoldReward = 5000, Abilities = new List<string> { "Shadow Bolt Volley", "Mark of Kazzak", "Twisted Reflection", "Capture Soul" } },
            
            // Elementals
            new EnemyTemplate { Id = 17, Name = "Fire Elemental", Type = EnemyType.Elemental, Rank = EnemyRank.Normal, Level = 30, Health = 600, MagicPower = 50, Defense = 10, XPReward = 350, GoldReward = 45, Abilities = new List<string> { "Flame Burst", "Immolate" }, Resistances = new List<string> { "Fire" }, Weaknesses = new List<string> { "Water", "Frost" } },
            new EnemyTemplate { Id = 18, Name = "Water Elemental", Type = EnemyType.Elemental, Rank = EnemyRank.Normal, Level = 30, Health = 600, MagicPower = 50, Defense = 10, XPReward = 350, GoldReward = 45, Abilities = new List<string> { "Water Bolt", "Freeze" }, Resistances = new List<string> { "Frost", "Water" }, Weaknesses = new List<string> { "Lightning" } },
            new EnemyTemplate { Id = 19, Name = "Storm Elemental", Type = EnemyType.Elemental, Rank = EnemyRank.Elite, Level = 50, Health = 3500, MagicPower = 100, Defense = 30, XPReward = 2200, GoldReward = 350, Abilities = new List<string> { "Chain Lightning", "Thunderstorm", "Static Charge" }, Resistances = new List<string> { "Lightning" } },
            
            // Dragons
            new EnemyTemplate { Id = 20, Name = "Whelp", Type = EnemyType.Dragonkin, Rank = EnemyRank.Normal, Level = 35, Health = 800, Attack = 55, Defense = 20, XPReward = 500, GoldReward = 60, Abilities = new List<string> { "Flame Breath", "Wing Buffet" } },
            new EnemyTemplate { Id = 21, Name = "Drake", Type = EnemyType.Dragonkin, Rank = EnemyRank.Elite, Level = 50, Health = 4000, Attack = 100, MagicPower = 70, Defense = 50, XPReward = 2500, GoldReward = 400, Abilities = new List<string> { "Dragon Breath", "Tail Swipe", "Fly" } },
            new EnemyTemplate { Id = 22, Name = "Ancient Dragon", Type = EnemyType.Dragonkin, Rank = EnemyRank.Boss, Level = 65, Health = 15000, Attack = 180, MagicPower = 120, Defense = 80, XPReward = 8000, GoldReward = 2000, Abilities = new List<string> { "Inferno Breath", "Wing Storm", "Dragon Fear", "Ancient Fury" } },
            new EnemyTemplate { Id = 23, Name = "Onyxia", Type = EnemyType.Dragonkin, Rank = EnemyRank.RaidBoss, Level = 60, Health = 100000, Attack = 200, MagicPower = 150, Defense = 100, XPReward = 50000, GoldReward = 10000, Abilities = new List<string> { "Deep Breath", "Tail Sweep", "Fear", "Fireball", "Phase Shift" }, Description = "A massive black dragon" },
            
            // Giants
            new EnemyTemplate { Id = 24, Name = "Hill Giant", Type = EnemyType.Giant, Rank = EnemyRank.Elite, Level = 40, Health = 3000, Attack = 90, Defense = 25, XPReward = 1500, GoldReward = 200, Abilities = new List<string> { "Boulder Throw", "Ground Slam" } },
            new EnemyTemplate { Id = 25, Name = "Frost Giant", Type = EnemyType.Giant, Rank = EnemyRank.Elite, Level = 55, Health = 6000, Attack = 120, Defense = 40, XPReward = 3500, GoldReward = 600, Abilities = new List<string> { "Ice Boulder", "Frost Aura", "Stomp" }, Resistances = new List<string> { "Frost" } },
            new EnemyTemplate { Id = 26, Name = "Fire Giant King", Type = EnemyType.Giant, Rank = EnemyRank.Boss, Level = 65, Health = 20000, Attack = 180, Defense = 60, XPReward = 10000, GoldReward = 3000, Abilities = new List<string> { "Molten Strike", "Inferno", "Volcanic Eruption", "Flame Shield" }, Resistances = new List<string> { "Fire" } }
        };
    }
}

public class EnemyInstance
{
    public EnemyTemplate Template { get; set; } = null!;
    public int CurrentHealth { get; set; }
    public int CurrentMana { get; set; }
    public bool IsAlive => CurrentHealth > 0;
    public List<string> ActiveBuffs { get; set; } = new();
    public List<string> ActiveDebuffs { get; set; } = new();
    
    public EnemyInstance(EnemyTemplate template)
    {
        Template = template;
        CurrentHealth = template.Health;
        CurrentMana = template.Mana;
    }
    
    public int TakeDamage(int damage, string damageType = "Physical")
    {
        // Apply resistances/weaknesses
        if (Template.Resistances.Contains(damageType))
        {
            damage = (int)(damage * 0.5f);
        }
        if (Template.Weaknesses.Contains(damageType))
        {
            damage = (int)(damage * 1.5f);
        }
        
        int actualDamage = Math.Max(1, damage - Template.Defense);
        CurrentHealth = Math.Max(0, CurrentHealth - actualDamage);
        return actualDamage;
    }
    
    public void Heal(int amount)
    {
        CurrentHealth = Math.Min(Template.Health, CurrentHealth + amount);
    }
    
    public List<AdvancedItem> GenerateLoot()
    {
        var loot = new List<AdvancedItem>();
        Random rand = new Random();
        
        if (rand.NextDouble() < Template.DropRate)
        {
            foreach (var item in Template.LootTable)
            {
                if (rand.NextDouble() < 0.3) // 30% chance per item
                {
                    loot.Add(item);
                }
            }
        }
        
        return loot;
    }
}
