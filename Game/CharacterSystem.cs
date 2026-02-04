namespace RPGMenuSystem.Game;

public enum CharacterRace
{
    Human,
    Elf,
    Dwarf,
    Orc,
    Undead,
    Troll,
    Gnome,
    Tauren,
    Draenei,
    BloodElf,
    NightElf,
    Goblin
}

public enum CharacterClass
{
    Warrior,
    Mage,
    Rogue,
    Priest,
    Paladin,
    Warlock,
    Hunter,
    Shaman,
    Druid,
    DeathKnight,
    Monk,
    DemonHunter
}

public enum ClassSpecialization
{
    // Warrior
    WarriorArms,
    WarriorFury,
    WarriorProtection,
    
    // Mage
    MageFire,
    MageFrost,
    MageArcane,
    
    // Rogue
    RogueAssassination,
    RogueCombat,
    RogueSubtlety,
    
    // Priest
    PriestDiscipline,
    PriestHoly,
    PriestShadow,
    
    // Paladin
    PaladinHoly,
    PaladinProtection,
    PaladinRetribution,
    
    // Warlock
    WarlockAffliction,
    WarlockDemonology,
    WarlockDestruction,
    
    // Hunter
    HunterBeastMastery,
    HunterMarksmanship,
    HunterSurvival,
    
    // Shaman
    ShamanElemental,
    ShamanEnhancement,
    ShamanRestoration,
    
    // Druid
    DruidBalance,
    DruidFeral,
    DruidGuardian,
    DruidRestoration,
    
    // Death Knight
    DeathKnightBlood,
    DeathKnightFrost,
    DeathKnightUnholy,
    
    // Monk
    MonkBrewmaster,
    MonkMistweaver,
    MonkWindwalker,
    
    // Demon Hunter
    DemonHunterHavoc,
    DemonHunterVengeance
}

public class CharacterStats
{
    // Primary Stats
    public int Strength { get; set; }
    public int Agility { get; set; }
    public int Intelligence { get; set; }
    public int Stamina { get; set; }
    public int Spirit { get; set; }
    
    // Secondary Stats
    public int CriticalStrike { get; set; }
    public int Haste { get; set; }
    public int Mastery { get; set; }
    public int Versatility { get; set; }
    
    // Defensive Stats
    public int Armor { get; set; }
    public int DodgeRating { get; set; }
    public int ParryRating { get; set; }
    public int BlockRating { get; set; }
}

public class RaceInfo
{
    public CharacterRace Race { get; set; }
    public string Name { get; set; } = string.Empty;
    public string Description { get; set; } = string.Empty;
    public List<CharacterClass> AvailableClasses { get; set; } = new();
    public Dictionary<string, int> RacialBonuses { get; set; } = new();
    public List<string> RacialAbilities { get; set; } = new();
    
    public static List<RaceInfo> GetAllRaces()
    {
        return new List<RaceInfo>
        {
            new RaceInfo
            {
                Race = CharacterRace.Human,
                Name = "Human",
                Description = "Versatile and adaptable, humans excel in all areas",
                AvailableClasses = new List<CharacterClass> { CharacterClass.Warrior, CharacterClass.Mage, CharacterClass.Rogue, CharacterClass.Priest, CharacterClass.Paladin },
                RacialBonuses = new Dictionary<string, int> { { "Spirit", 5 }, { "Reputation", 10 } },
                RacialAbilities = new List<string> { "Every Man for Himself", "The Human Spirit" }
            },
            new RaceInfo
            {
                Race = CharacterRace.Elf,
                Name = "Elf",
                Description = "Ancient and wise, elves are masters of magic and archery",
                AvailableClasses = new List<CharacterClass> { CharacterClass.Mage, CharacterClass.Rogue, CharacterClass.Hunter, CharacterClass.Priest, CharacterClass.Druid },
                RacialBonuses = new Dictionary<string, int> { { "Agility", 5 }, { "Intelligence", 3 } },
                RacialAbilities = new List<string> { "Quickness", "Keen Senses" }
            },
            new RaceInfo
            {
                Race = CharacterRace.Dwarf,
                Name = "Dwarf",
                Description = "Hardy mountaineers, dwarves are tough and resilient",
                AvailableClasses = new List<CharacterClass> { CharacterClass.Warrior, CharacterClass.Paladin, CharacterClass.Hunter, CharacterClass.Priest, CharacterClass.Shaman },
                RacialBonuses = new Dictionary<string, int> { { "Stamina", 5 }, { "Frost Resistance", 10 } },
                RacialAbilities = new List<string> { "Stoneform", "Mace Specialization" }
            },
            new RaceInfo
            {
                Race = CharacterRace.Orc,
                Name = "Orc",
                Description = "Fierce warriors with unmatched strength",
                AvailableClasses = new List<CharacterClass> { CharacterClass.Warrior, CharacterClass.Hunter, CharacterClass.Shaman, CharacterClass.Warlock, CharacterClass.DeathKnight },
                RacialBonuses = new Dictionary<string, int> { { "Strength", 5 }, { "Attack Power", 10 } },
                RacialAbilities = new List<string> { "Blood Fury", "Hardiness" }
            },
            new RaceInfo
            {
                Race = CharacterRace.Undead,
                Name = "Undead",
                Description = "Risen from death, the undead are immune to fear",
                AvailableClasses = new List<CharacterClass> { CharacterClass.Warrior, CharacterClass.Rogue, CharacterClass.Priest, CharacterClass.Warlock, CharacterClass.Mage },
                RacialBonuses = new Dictionary<string, int> { { "Shadow Resistance", 10 } },
                RacialAbilities = new List<string> { "Will of the Forsaken", "Cannibalize" }
            },
            new RaceInfo
            {
                Race = CharacterRace.NightElf,
                Name = "Night Elf",
                Description = "Stealthy and agile, masters of the shadows",
                AvailableClasses = new List<CharacterClass> { CharacterClass.Druid, CharacterClass.Hunter, CharacterClass.Rogue, CharacterClass.Priest, CharacterClass.Warrior },
                RacialBonuses = new Dictionary<string, int> { { "Agility", 4 }, { "Nature Resistance", 10 } },
                RacialAbilities = new List<string> { "Shadowmeld", "Elusiveness" }
            },
            new RaceInfo
            {
                Race = CharacterRace.Tauren,
                Name = "Tauren",
                Description = "Noble and strong, connected to nature",
                AvailableClasses = new List<CharacterClass> { CharacterClass.Warrior, CharacterClass.Shaman, CharacterClass.Druid, CharacterClass.Hunter, CharacterClass.Paladin },
                RacialBonuses = new Dictionary<string, int> { { "Stamina", 5 }, { "Nature Resistance", 10 } },
                RacialAbilities = new List<string> { "War Stomp", "Endurance" }
            },
            new RaceInfo
            {
                Race = CharacterRace.Gnome,
                Name = "Gnome",
                Description = "Small but ingenious, masters of technology and magic",
                AvailableClasses = new List<CharacterClass> { CharacterClass.Mage, CharacterClass.Warlock, CharacterClass.Rogue, CharacterClass.Warrior, CharacterClass.Priest },
                RacialBonuses = new Dictionary<string, int> { { "Intelligence", 5 }, { "Arcane Resistance", 10 } },
                RacialAbilities = new List<string> { "Escape Artist", "Engineering Specialization" }
            }
        };
    }
}

public class ClassInfo
{
    public CharacterClass Class { get; set; }
    public string Name { get; set; } = string.Empty;
    public string Description { get; set; } = string.Empty;
    public string Role { get; set; } = string.Empty; // Tank, DPS, Healer
    public string PrimaryResource { get; set; } = string.Empty; // Mana, Rage, Energy, etc.
    public List<ClassSpecialization> Specializations { get; set; } = new();
    public Dictionary<string, int> StartingStats { get; set; } = new();
    
    public static List<ClassInfo> GetAllClasses()
    {
        return new List<ClassInfo>
        {
            new ClassInfo
            {
                Class = CharacterClass.Warrior,
                Name = "Warrior",
                Description = "A master of weapons and armor, using rage to fuel devastating attacks",
                Role = "Tank / DPS",
                PrimaryResource = "Rage",
                Specializations = new List<ClassSpecialization> { ClassSpecialization.WarriorArms, ClassSpecialization.WarriorFury, ClassSpecialization.WarriorProtection },
                StartingStats = new Dictionary<string, int> { { "Strength", 25 }, { "Stamina", 20 }, { "Armor", 15 } }
            },
            new ClassInfo
            {
                Class = CharacterClass.Mage,
                Name = "Mage",
                Description = "Wielder of arcane magic, capable of devastating elemental spells",
                Role = "DPS",
                PrimaryResource = "Mana",
                Specializations = new List<ClassSpecialization> { ClassSpecialization.MageFire, ClassSpecialization.MageFrost, ClassSpecialization.MageArcane },
                StartingStats = new Dictionary<string, int> { { "Intelligence", 25 }, { "Stamina", 15 }, { "Spirit", 20 } }
            },
            new ClassInfo
            {
                Class = CharacterClass.Rogue,
                Name = "Rogue",
                Description = "Master of stealth and precision, striking from the shadows",
                Role = "DPS",
                PrimaryResource = "Energy",
                Specializations = new List<ClassSpecialization> { ClassSpecialization.RogueAssassination, ClassSpecialization.RogueCombat, ClassSpecialization.RogueSubtlety },
                StartingStats = new Dictionary<string, int> { { "Agility", 25 }, { "Stamina", 18 }, { "Strength", 15 } }
            },
            new ClassInfo
            {
                Class = CharacterClass.Priest,
                Name = "Priest",
                Description = "Holy champion or shadow master, healing allies or destroying foes",
                Role = "Healer / DPS",
                PrimaryResource = "Mana",
                Specializations = new List<ClassSpecialization> { ClassSpecialization.PriestDiscipline, ClassSpecialization.PriestHoly, ClassSpecialization.PriestShadow },
                StartingStats = new Dictionary<string, int> { { "Intelligence", 23 }, { "Spirit", 22 }, { "Stamina", 15 } }
            },
            new ClassInfo
            {
                Class = CharacterClass.Paladin,
                Name = "Paladin",
                Description = "Holy warrior combining martial prowess with divine magic",
                Role = "Tank / Healer / DPS",
                PrimaryResource = "Mana / Holy Power",
                Specializations = new List<ClassSpecialization> { ClassSpecialization.PaladinHoly, ClassSpecialization.PaladinProtection, ClassSpecialization.PaladinRetribution },
                StartingStats = new Dictionary<string, int> { { "Strength", 22 }, { "Stamina", 20 }, { "Intelligence", 18 } }
            },
            new ClassInfo
            {
                Class = CharacterClass.Warlock,
                Name = "Warlock",
                Description = "Master of demonic magic and dark powers",
                Role = "DPS",
                PrimaryResource = "Mana / Soul Shards",
                Specializations = new List<ClassSpecialization> { ClassSpecialization.WarlockAffliction, ClassSpecialization.WarlockDemonology, ClassSpecialization.WarlockDestruction },
                StartingStats = new Dictionary<string, int> { { "Intelligence", 24 }, { "Stamina", 17 }, { "Spirit", 19 } }
            },
            new ClassInfo
            {
                Class = CharacterClass.Hunter,
                Name = "Hunter",
                Description = "Master of ranged combat and beast companions",
                Role = "DPS",
                PrimaryResource = "Focus",
                Specializations = new List<ClassSpecialization> { ClassSpecialization.HunterBeastMastery, ClassSpecialization.HunterMarksmanship, ClassSpecialization.HunterSurvival },
                StartingStats = new Dictionary<string, int> { { "Agility", 24 }, { "Stamina", 18 }, { "Strength", 16 } }
            },
            new ClassInfo
            {
                Class = CharacterClass.Shaman,
                Name = "Shaman",
                Description = "Wielder of elemental forces and spiritual power",
                Role = "Healer / DPS",
                PrimaryResource = "Mana",
                Specializations = new List<ClassSpecialization> { ClassSpecialization.ShamanElemental, ClassSpecialization.ShamanEnhancement, ClassSpecialization.ShamanRestoration },
                StartingStats = new Dictionary<string, int> { { "Intelligence", 22 }, { "Agility", 20 }, { "Stamina", 18 } }
            },
            new ClassInfo
            {
                Class = CharacterClass.Druid,
                Name = "Druid",
                Description = "Shapeshifter capable of adapting to any role",
                Role = "Tank / Healer / DPS",
                PrimaryResource = "Mana / Rage / Energy",
                Specializations = new List<ClassSpecialization> { ClassSpecialization.DruidBalance, ClassSpecialization.DruidFeral, ClassSpecialization.DruidGuardian, ClassSpecialization.DruidRestoration },
                StartingStats = new Dictionary<string, int> { { "Intelligence", 20 }, { "Agility", 20 }, { "Stamina", 20 } }
            },
            new ClassInfo
            {
                Class = CharacterClass.DeathKnight,
                Name = "Death Knight",
                Description = "Undead warrior wielding dark magic and runic power",
                Role = "Tank / DPS",
                PrimaryResource = "Runic Power",
                Specializations = new List<ClassSpecialization> { ClassSpecialization.DeathKnightBlood, ClassSpecialization.DeathKnightFrost, ClassSpecialization.DeathKnightUnholy },
                StartingStats = new Dictionary<string, int> { { "Strength", 26 }, { "Stamina", 22 }, { "Intelligence", 15 } }
            },
            new ClassInfo
            {
                Class = CharacterClass.Monk,
                Name = "Monk",
                Description = "Master of martial arts and ancient techniques",
                Role = "Tank / Healer / DPS",
                PrimaryResource = "Energy / Chi",
                Specializations = new List<ClassSpecialization> { ClassSpecialization.MonkBrewmaster, ClassSpecialization.MonkMistweaver, ClassSpecialization.MonkWindwalker },
                StartingStats = new Dictionary<string, int> { { "Agility", 23 }, { "Stamina", 19 }, { "Intelligence", 18 } }
            },
            new ClassInfo
            {
                Class = CharacterClass.DemonHunter,
                Name = "Demon Hunter",
                Description = "Fel-powered warrior sacrificing everything to hunt demons",
                Role = "Tank / DPS",
                PrimaryResource = "Fury",
                Specializations = new List<ClassSpecialization> { ClassSpecialization.DemonHunterHavoc, ClassSpecialization.DemonHunterVengeance },
                StartingStats = new Dictionary<string, int> { { "Agility", 26 }, { "Stamina", 20 }, { "Strength", 16 } }
            }
        };
    }
}
