namespace RPGMenuSystem.Game;

/// <summary>
/// Comprehensive world definition for a medieval fantasy realm spanning an Earth-like planet.
/// The world "Aethermoor" is as large as World of Warcraft with 7 major continents.
/// </summary>
public static class WorldDefinition
{
    // ==================== WORLD STRUCTURE ====================
    // Aethermoor: A medieval fantasy world with magic, kingdoms, and ancient mysteries
    // Total Area: ~5.3 million square miles (Earth-like scale)
    // Population: ~50 million across all civilizations

    public const string WorldName = "Aethermoor";
    public const string WorldTheme = "Medieval Fantasy with Magic and Dungeons";

    public static List<Continent> GetAllContinents()
    {
        return new List<Continent>
        {
            GetNorthernContinents(),
            GetEasternContinents(),
            GetWesternContinents(),
            GetSouthernContinents(),
            GetCentralContinents(),
            GetUndergroundRealms(),
            GetSkyRealms()
        };
    }

    // ==================== CONTINENT 1: VALORATH (North) ====================
    private static Continent GetNorthernContinents()
    {
        return new Continent
        {
            Id = 1,
            Name = "Valorath",
            Description = "The frozen northern continent of eternal winter and ancient dwarven kingdoms",
            Area = 850000,
            Population = 2500000,
            Theme = "Frozen Peaks, Snow Valleys, Dwarven Mines",
            Regions = new List<Region>
            {
                // Region 1: Kingdom of Ironforge (Dwarven)
                new Region
                {
                    Id = 1,
                    Name = "Ironhammer Kingdom",
                    Description = "The greatest dwarven kingdom with underground cities",
                    RecommendedLevel = 1,
                    RegionType = "Underground City / Mountains",
                    BiomeType = BiomeType.Mountain,
                    Population = 500000,
                    GovernmentType = "Monarchy",
                    Ruler = "King Thorin Stonebeard",
                    CapitalCity = "Ironforge Citadel",
                    Zones = new List<ZoneDetail>
                    {
                        new ZoneDetail { ZoneId = 101, Name = "Stonekeep Entrance", Level = 1, Type = "Mountain", Description = "Majestic entrance to the dwarven kingdom" },
                        new ZoneDetail { ZoneId = 102, Name = "Deepdelve Mines", Level = 5, Type = "Underground", Description = "Ancient mining operations" },
                        new ZoneDetail { ZoneId = 103, Name = "Forgemaster's Cavern", Level = 8, Type = "Dungeon", Description = "Where legendary weapons are crafted" },
                        new ZoneDetail { ZoneId = 104, Name = "Molten Throne Room", Level = 12, Type = "Castle", Description = "Seat of dwarven power" }
                    }
                },
                // Region 2: Frozen Wastes
                new Region
                {
                    Id = 2,
                    Name = "Frostheim Wastes",
                    Description = "Endless icy plains home to frost giants and ice dragons",
                    RecommendedLevel = 15,
                    RegionType = "Tundra / Glacier",
                    BiomeType = BiomeType.Tundra,
                    Population = 100000,
                    GovernmentType = "Tribal",
                    Ruler = "Jarl Skaelgrym",
                    CapitalCity = "Icehammer Hold",
                    Zones = new List<ZoneDetail>
                    {
                        new ZoneDetail { ZoneId = 105, Name = "Eternal Snowfield", Level = 15, Type = "Plains", Description = "Endless white landscape" },
                        new ZoneDetail { ZoneId = 106, Name = "Glacial Abyss", Level = 20, Type = "Cave", Description = "Frozen caverns with ancient secrets" },
                        new ZoneDetail { ZoneId = 107, Name = "Frostbite Peak", Level = 25, Type = "Mountain", Description = "Home of the Ice Dragons" }
                    }
                },
                // Region 3: Dragon's Rest Mountains
                new Region
                {
                    Id = 3,
                    Name = "Drakespine Mountains",
                    Description = "Ancient dragon nesting grounds and mountain monasteries",
                    RecommendedLevel = 20,
                    RegionType = "Mountain Range",
                    BiomeType = BiomeType.Mountain,
                    Population = 250000,
                    GovernmentType = "Theocracy",
                    Ruler = "Grandmaster Elorah",
                    CapitalCity = "Skyward Monastery",
                    Zones = new List<ZoneDetail>
                    {
                        new ZoneDetail { ZoneId = 108, Name = "Eagle's Nest Pass", Level = 20, Type = "Mountain", Description = "Treacherous mountain passage" },
                        new ZoneDetail { ZoneId = 109, Name = "Dragonborn Sanctum", Level = 25, Type = "Temple", Description = "Sacred draconic temple" },
                        new ZoneDetail { ZoneId = 110, Name = "Chromatic Spire", Level = 30, Type = "Dungeon", Description = "Tower of corrupted dragons" }
                    }
                }
            }
        };
    }

    // ==================== CONTINENT 2: LUMERIA (East) ====================
    private static Continent GetEasternContinents()
    {
        return new Continent
        {
            Id = 2,
            Name = "Lumeria",
            Description = "The mystical eastern continent of ancient elven forests and arcane magic",
            Area = 920000,
            Population = 3000000,
            Theme = "Magical Forests, Elven Cities, Arcane Ruins",
            Regions = new List<Region>
            {
                // Region 1: Emerald Vale
                new Region
                {
                    Id = 4,
                    Name = "Emerald Vale",
                    Description = "The heart of elven civilization with ancient treeship cities",
                    RecommendedLevel = 8,
                    RegionType = "Old Growth Forest",
                    BiomeType = BiomeType.TemperateForest,
                    Population = 800000,
                    GovernmentType = "Monarchy",
                    Ruler = "Queen Aelindor Moonwhisper",
                    CapitalCity = "Silverleaf City",
                    Zones = new List<ZoneDetail>
                    {
                        new ZoneDetail { ZoneId = 111, Name = "Whispering Grove", Level = 8, Type = "Forest", Description = "Ancient elven sanctuary" },
                        new ZoneDetail { ZoneId = 112, Name = "Moonwell Glade", Level = 12, Type = "Forest", Description = "Sacred magical springs" },
                        new ZoneDetail { ZoneId = 113, Name = "Starfire Tower", Level = 16, Type = "Temple", Description = "Arcane research center" }
                    }
                },
                // Region 2: Shadowpine Jungle
                new Region
                {
                    Id = 5,
                    Name = "Shadowpine Jungle",
                    Description = "Dense rainforest with hidden druids and wild magic",
                    RecommendedLevel = 12,
                    RegionType = "Tropical Rainforest",
                    BiomeType = BiomeType.TropicalRainforest,
                    Population = 450000,
                    GovernmentType = "Druidic Council",
                    Ruler = "Archdruid Sylvanus",
                    CapitalCity = "Deepwood Grotto",
                    Zones = new List<ZoneDetail>
                    {
                        new ZoneDetail { ZoneId = 114, Name = "Canopy Pathways", Level = 12, Type = "Forest", Description = "Bridges through ancient trees" },
                        new ZoneDetail { ZoneId = 115, Name = "Primal Swamp", Level = 18, Type = "Swamp", Description = "Where nature's power runs wild" },
                        new ZoneDetail { ZoneId = 116, Name = "Bastion of the Wild", Level = 22, Type = "Dungeon", Description = "Corrupted druid stronghold" }
                    }
                },
                // Region 3: Arcane Isles
                new Region
                {
                    Id = 6,
                    Name = "Arcane Isles",
                    Description = "Magical archipelago of wizard towers and research facilities",
                    RecommendedLevel = 18,
                    RegionType = "Island Chain",
                    BiomeType = BiomeType.FloatingIslands,
                    Population = 350000,
                    GovernmentType = "Mage Council",
                    Ruler = "Archmagus Valdris",
                    CapitalCity = "Spellforge Academy",
                    Zones = new List<ZoneDetail>
                    {
                        new ZoneDetail { ZoneId = 117, Name = "Mage Academy Isle", Level = 18, Type = "Town", Description = "Premier magical university" },
                        new ZoneDetail { ZoneId = 118, Name = "Floating Sanctum", Level = 22, Type = "Sky Realm", Description = "Suspended magical libraries" },
                        new ZoneDetail { ZoneId = 119, Name = "Ley Node Nexus", Level = 28, Type = "Dungeon", Description = "Heart of magical power" }
                    }
                }
            }
        };
    }

    // ==================== CONTINENT 3: MORTALIS (West) ====================
    private static Continent GetWesternContinents()
    {
        return new Continent
        {
            Id = 3,
            Name = "Mortalis",
            Description = "The western continent of human kingdoms, commerce, and political intrigue",
            Area = 880000,
            Population = 4500000,
            Theme = "Human Kingdoms, Trading Routes, Castles",
            Regions = new List<Region>
            {
                // Region 1: Kingdom of Valorian
                new Region
                {
                    Id = 7,
                    Name = "Valorian Kingdom",
                    Description = "The greatest human kingdom with vast territories",
                    RecommendedLevel = 1,
                    RegionType = "Mixed Terrain",
                    BiomeType = BiomeType.GrasslandPlains,
                    Population = 1500000,
                    GovernmentType = "Monarchy",
                    Ruler = "King Aldarin Stormborn",
                    CapitalCity = "Thornhaven",
                    Zones = new List<ZoneDetail>
                    {
                        new ZoneDetail { ZoneId = 120, Name = "Thornhaven Plaza", Level = 1, Type = "City", Description = "Capital city of Valorian" },
                        new ZoneDetail { ZoneId = 121, Name = "Royal Castle Valdemere", Level = 5, Type = "Castle", Description = "Home of the king" },
                        new ZoneDetail { ZoneId = 122, Name = "Farmland Vales", Level = 3, Type = "Plains", Description = "Fertile agricultural lands" },
                        new ZoneDetail { ZoneId = 123, Name = "Dark Forest of Mal'thir", Level = 10, Type = "Forest", Description = "Dangerous woods at kingdom's edge" }
                    }
                },
                // Region 2: Trade Federation
                new Region
                {
                    Id = 8,
                    Name = "Merchant's Confluence",
                    Description = "Free cities united by commerce and trade",
                    RecommendedLevel = 8,
                    RegionType = "Merchant Cities",
                    BiomeType = BiomeType.GrasslandPlains,
                    Population = 1200000,
                    GovernmentType = "Merchant Republic",
                    Ruler = "High Merchant Lord Cassius",
                    CapitalCity = "Goldport",
                    Zones = new List<ZoneDetail>
                    {
                        new ZoneDetail { ZoneId = 124, Name = "Goldport Harbor", Level = 8, Type = "Port City", Description = "Busiest trading port" },
                        new ZoneDetail { ZoneId = 125, Name = "Silvermarrow Market", Level = 6, Type = "Town", Description = "Great trading hub" },
                        new ZoneDetail { ZoneId = 126, Name = "Caravan Routes", Level = 5, Type = "Plains", Description = "Merchant roads crossing continent" }
                    }
                },
                // Region 3: Ranger's Frontier
                new Region
                {
                    Id = 9,
                    Name = "The Northmark Frontier",
                    Description = "Wild frontier lands home to rangers and adventurers",
                    RecommendedLevel = 15,
                    RegionType = "Wilderness",
                    BiomeType = BiomeType.Taiga,
                    Population = 300000,
                    GovernmentType = "Ranger Order",
                    Ruler = "Ranger Captain Thorne",
                    CapitalCity = "Sentinel Keep",
                    Zones = new List<ZoneDetail>
                    {
                        new ZoneDetail { ZoneId = 127, Name = "Sentinel Keep Outpost", Level = 15, Type = "Outpost", Description = "Frontier defense post" },
                        new ZoneDetail { ZoneId = 128, Name = "Wildwood Expanse", Level = 18, Type = "Forest", Description = "Untamed wilderness" },
                        new ZoneDetail { ZoneId = 129, Name = "Beast Hollows", Level = 22, Type = "Cave", Description = "Lair of dangerous creatures" }
                    }
                }
            }
        };
    }

    // ==================== CONTINENT 4: KHARANOS (South) ====================
    private static Continent GetSouthernContinents()
    {
        return new Continent
        {
            Id = 4,
            Name = "Kharanos",
            Description = "The southern desert continent of ancient civilizations and buried treasures",
            Area = 950000,
            Population = 2000000,
            Theme = "Deserts, Tombs, Ancient Ruins",
            Regions = new List<Region>
            {
                // Region 1: Scarab Dynasty
                new Region
                {
                    Id = 10,
                    Name = "Scarab Dynasty",
                    Description = "Ancient Egyptian-inspired civilization with pyramids and tombs",
                    RecommendedLevel = 18,
                    RegionType = "Desert",
                    BiomeType = BiomeType.Desert,
                    Population = 800000,
                    GovernmentType = "Divine Monarchy",
                    Ruler = "Pharaoh Amenhotep",
                    CapitalCity = "Amuntep",
                    Zones = new List<ZoneDetail>
                    {
                        new ZoneDetail { ZoneId = 130, Name = "Amuntep City", Level = 18, Type = "City", Description = "Grand pharaoh capital" },
                        new ZoneDetail { ZoneId = 131, Name = "Valley of Kings", Level = 22, Type = "Ruins", Description = "Ancient royal tombs" },
                        new ZoneDetail { ZoneId = 132, Name = "The Great Pyramid of Khen", Level = 26, Type = "Dungeon", Description = "Massive ancient structure" }
                    }
                },
                // Region 2: Endless Dunes
                new Region
                {
                    Id = 11,
                    Name = "Endless Dunes",
                    Description = "Vast golden deserts with oasis settlements",
                    RecommendedLevel = 15,
                    RegionType = "Desert Wasteland",
                    BiomeType = BiomeType.Desert,
                    Population = 500000,
                    GovernmentType = "Nomadic Tribes",
                    Ruler = "Sheikh Abubakar",
                    CapitalCity = "Oasis Prime",
                    Zones = new List<ZoneDetail>
                    {
                        new ZoneDetail { ZoneId = 133, Name = "Oasis Prime", Level = 15, Type = "Town", Description = "Largest desert oasis" },
                        new ZoneDetail { ZoneId = 134, Name = "Sunscorch Wastes", Level = 19, Type = "Desert", Description = "Hottest desert regions" },
                        new ZoneDetail { ZoneId = 135, Name = "Mirage Canyons", Level = 23, Type = "Caves", Description = "Hidden canyon systems" }
                    }
                },
                // Region 3: Jungles of Lusatia
                new Region
                {
                    Id = 12,
                    Name = "Lusatian Jungles",
                    Description = "Tropical jungles with lost civilizations",
                    RecommendedLevel = 20,
                    RegionType = "Jungle",
                    BiomeType = BiomeType.TropicalRainforest,
                    Population = 400000,
                    GovernmentType = "Tribal Council",
                    Ruler = "Shaman Kaida",
                    CapitalCity = "Serpent Temple",
                    Zones = new List<ZoneDetail>
                    {
                        new ZoneDetail { ZoneId = 136, Name = "Serpent Temple", Level = 20, Type = "Temple", Description = "Vast ancient temple complex" },
                        new ZoneDetail { ZoneId = 137, Name = "Curse Jungle", Level = 24, Type = "Forest", Description = "Dangerous overgrown wilderness" },
                        new ZoneDetail { ZoneId = 138, Name = "Lost City of Azurheim", Level = 28, Type = "Ruins", Description = "Sunken civilization ruins" }
                    }
                }
            }
        };
    }

    // ==================== CONTINENT 5: AETHRAL (Central) ====================
    private static Continent GetCentralContinents()
    {
        return new Continent
        {
            Id = 5,
            Name = "Aethral",
            Description = "The central continent where great powers collide and ancient evils stir",
            Area = 1000000,
            Population = 3500000,
            Theme = "Contested Lands, Dark Magic, Battlefields",
            Regions = new List<Region>
            {
                // Region 1: Shadowlands
                new Region
                {
                    Id = 13,
                    Name = "The Shadowlands",
                    Description = "Corrupted lands where darkness reigns supreme",
                    RecommendedLevel = 25,
                    RegionType = "Dark Badlands",
                    BiomeType = BiomeType.CorruptedLands,
                    Population = 1000000,
                    GovernmentType = "Necratic Tyranny",
                    Ruler = "The Lich King Morthos",
                    CapitalCity = "Blackthorn Citadel",
                    Zones = new List<ZoneDetail>
                    {
                        new ZoneDetail { ZoneId = 139, Name = "Blackthorn Citadel", Level = 25, Type = "Castle", Description = "Seat of undeath" },
                        new ZoneDetail { ZoneId = 140, Name = "Plaguelands", Level = 28, Type = "Corrupted", Description = "Disease-ridden wasteland" },
                        new ZoneDetail { ZoneId = 141, Name = "Eternal Darkness", Level = 32, Type = "Dungeon", Description = "Ultimate evil lair" }
                    }
                },
                // Region 2: Demonfire Wastes
                new Region
                {
                    Id = 14,
                    Name = "Demonfire Wastes",
                    Description = "Hell-touched lands of lava and demonic corruption",
                    RecommendedLevel = 22,
                    RegionType = "Volcanic Wasteland",
                    BiomeType = BiomeType.Volcano,
                    Population = 250000,
                    GovernmentType = "Demonic Hierarchy",
                    Ruler = "Archfiend Baltazar",
                    CapitalCity = "Infernus",
                    Zones = new List<ZoneDetail>
                    {
                        new ZoneDetail { ZoneId = 142, Name = "Infernus City", Level = 22, Type = "City", Description = "Demon stronghold" },
                        new ZoneDetail { ZoneId = 143, Name = "Brimstone Fields", Level = 25, Type = "Volcano", Description = "Burning hellscape" },
                        new ZoneDetail { ZoneId = 144, Name = "Abyssal Throne", Level = 30, Type = "Dungeon", Description = "Demon lord's domain" }
                    }
                },
                // Region 3: Contested Badlands
                new Region
                {
                    Id = 15,
                    Name = "Contested Badlands",
                    Description = "Battleground between multiple factions",
                    RecommendedLevel = 16,
                    RegionType = "Rocky Badlands",
                    BiomeType = BiomeType.GrasslandPlains,
                    Population = 800000,
                    GovernmentType = "Multi-Faction",
                    Ruler = "Various Warlords",
                    CapitalCity = "Warforge Keep",
                    Zones = new List<ZoneDetail>
                    {
                        new ZoneDetail { ZoneId = 145, Name = "Warforge Keep", Level = 16, Type = "Fortress", Description = "Neutral stronghold" },
                        new ZoneDetail { ZoneId = 146, Name = "Blood Fields", Level = 20, Type = "Plains", Description = "Constant battle zone" },
                        new ZoneDetail { ZoneId = 147, Name = "Warlord's Bastion", Level = 24, Type = "Dungeon", Description = "Tyrant's stronghold" }
                    }
                }
            }
        };
    }

    // ==================== CONTINENT 6: DEEPMOOR (Underground Realms) ====================
    private static Continent GetUndergroundRealms()
    {
        return new Continent
        {
            Id = 6,
            Name = "Deepmoor",
            Description = "The vast underground network of caverns, mines, and subterranean kingdoms",
            Area = 650000,
            Population = 1500000,
            Theme = "Underground Cities, Crystal Caverns, Mysterious Depths",
            Regions = new List<Region>
            {
                // Region 1: Khaz-Modan (Dwarven Networks)
                new Region
                {
                    Id = 16,
                    Name = "Khaz-Modan",
                    Description = "Interconnected dwarven cities beneath the world",
                    RecommendedLevel = 10,
                    RegionType = "Underground Network",
                    BiomeType = BiomeType.Mountain,
                    Population = 700000,
                    GovernmentType = "Dwarven Clans",
                    Ruler = "Grand Council of Clans",
                    CapitalCity = "Ironforge Underground",
                    Zones = new List<ZoneDetail>
                    {
                        new ZoneDetail { ZoneId = 148, Name = "Main Trade Tunnels", Level = 10, Type = "Underground", Description = "Major dwarven highways" },
                        new ZoneDetail { ZoneId = 149, Name = "Crystal Caverns", Level = 14, Type = "Cavern", Description = "Gem mining operations" },
                        new ZoneDetail { ZoneId = 150, Name = "Deepforge Sanctuary", Level = 18, Type = "Sacred Site", Description = "Ancient dwarven temple" }
                    }
                },
                // Region 2: Underdark Abyss
                new Region
                {
                    Id = 17,
                    Name = "Underdark Abyss",
                    Description = "Darkest depths where the Drow rule supreme",
                    RecommendedLevel = 20,
                    RegionType = "Deep Underground",
                    BiomeType = BiomeType.Underground,
                    Population = 450000,
                    GovernmentType = "Matriarchal Theocracy",
                    Ruler = "Matriarch Lolth's Chosen",
                    CapitalCity = "Menzoberranzan",
                    Zones = new List<ZoneDetail>
                    {
                        new ZoneDetail { ZoneId = 151, Name = "Menzoberranzan", Level = 20, Type = "City", Description = "Dark elven metropolis" },
                        new ZoneDetail { ZoneId = 152, Name = "Spider Warrens", Level = 23, Type = "Cavern", Description = "Drow breeding grounds" },
                        new ZoneDetail { ZoneId = 153, Name = "Yochlol's Lair", Level = 28, Type = "Dungeon", Description = "Demon queen's throne" }
                    }
                },
                // Region 3: Fungal Depths
                new Region
                {
                    Id = 18,
                    Name = "Fungal Depths",
                    Description = "Bioluminescent caverns filled with otherworldly lifeforms",
                    RecommendedLevel = 15,
                    RegionType = "Biological Caverns",
                    BiomeType = BiomeType.Underground,
                    Population = 350000,
                    GovernmentType = "Hive Mind",
                    Ruler = "The Collective",
                    CapitalCity = "Spore Collective",
                    Zones = new List<ZoneDetail>
                    {
                        new ZoneDetail { ZoneId = 154, Name = "Spore Collective", Level = 15, Type = "Cavern", Description = "Fungal intelligence hub" },
                        new ZoneDetail { ZoneId = 155, Name = "Biolume Gardens", Level = 19, Type = "Cavern", Description = "Glowing organism farms" },
                        new ZoneDetail { ZoneId = 156, Name = "The Myconid Throne", Level = 24, Type = "Dungeon", Description = "Ancient fungal structure" }
                    }
                }
            }
        };
    }

    // ==================== CONTINENT 7: CELESTIA (Sky Realms) ====================
    private static Continent GetSkyRealms()
    {
        return new Continent
        {
            Id = 7,
            Name = "Celestia",
            Description = "The floating sky islands and cloud cities suspended above the world",
            Area = 450000,
            Population = 1000000,
            Theme = "Floating Islands, Sky Cities, Celestial Magic",
            Regions = new List<Region>
            {
                // Region 1: Aethermere Sky
                new Region
                {
                    Id = 19,
                    Name = "Aethermere Sky",
                    Description = "Ancient sky kingdoms of angels and celestials",
                    RecommendedLevel = 24,
                    RegionType = "Floating Islands",
                    BiomeType = BiomeType.FloatingIslands,
                    Population = 500000,
                    GovernmentType = "Divine Monarchy",
                    Ruler = "Archangel Uriel",
                    CapitalCity = "Heavenspire",
                    Zones = new List<ZoneDetail>
                    {
                        new ZoneDetail { ZoneId = 157, Name = "Heavenspire City", Level = 24, Type = "Sky City", Description = "Divine city of angels" },
                        new ZoneDetail { ZoneId = 158, Name = "Cloud Sanctuaries", Level = 27, Type = "Sky", Description = "Holy sanctuaries above clouds" },
                        new ZoneDetail { ZoneId = 159, Name = "The Golden Thrones", Level = 31, Type = "Dungeon", Description = "Celestial divine seat" }
                    }
                },
                // Region 2: Storm Islands
                new Region
                {
                    Id = 20,
                    Name = "Storm Islands",
                    Description = "Tempestuous islands ruled by storm giants and air elementals",
                    RecommendedLevel = 20,
                    RegionType = "Storm Islands",
                    BiomeType = BiomeType.FloatingIslands,
                    Population = 300000,
                    GovernmentType = "Elemental Hierarchy",
                    Ruler = "Storm Lord Tempestus",
                    CapitalCity = "Stormhaven",
                    Zones = new List<ZoneDetail>
                    {
                        new ZoneDetail { ZoneId = 160, Name = "Stormhaven", Level = 20, Type = "Sky City", Description = "Storm giant capital" },
                        new ZoneDetail { ZoneId = 161, Name = "Lightning Peaks", Level = 23, Type = "Mountain", Description = "Electric storm mountains" },
                        new ZoneDetail { ZoneId = 162, Name = "The Eye of the Maelstrom", Level = 28, Type = "Dungeon", Description = "Eternal storm core" }
                    }
                }
            }
        };
    }
}

// ==================== SUPPORTING CLASSES ====================

public class Continent
{
    public int Id { get; set; }
    public string Name { get; set; } = string.Empty;
    public string Description { get; set; } = string.Empty;
    public int Area { get; set; } // Square miles
    public int Population { get; set; }
    public string Theme { get; set; } = string.Empty;
    public List<Region> Regions { get; set; } = new();
}

public class Region
{
    public int Id { get; set; }
    public string Name { get; set; } = string.Empty;
    public string Description { get; set; } = string.Empty;
    public int RecommendedLevel { get; set; }
    public string RegionType { get; set; } = string.Empty;
    public BiomeType BiomeType { get; set; }
    public int Population { get; set; }
    public string GovernmentType { get; set; } = string.Empty;
    public string Ruler { get; set; } = string.Empty;
    public string CapitalCity { get; set; } = string.Empty;
    public List<ZoneDetail> Zones { get; set; } = new();
}

public class ZoneDetail
{
    public int ZoneId { get; set; }
    public string Name { get; set; } = string.Empty;
    public int Level { get; set; }
    public string Type { get; set; } = string.Empty;
    public string Description { get; set; } = string.Empty;
}
