namespace RPGMenuSystem.Game;

public enum BiomeType
{
    GrasslandPlains,
    TemperateForest,
    TropicalRainforest,
    Desert,
    Tundra,
    Taiga,
    Savanna,
    Swamp,
    Marsh,
    Mountain,
    Volcano,
    FrozenWasteland,
    CrystalCaverns,
    MushroomGrove,
    DarkForest,
    CorruptedLands,
    FloatingIslands,
    Underwater,
    LavaFields,
    PoisonBog,
    Underground
}

public enum SettlementType
{
    SmallVillage,
    LargeVillage,
    Town,
    City,
    Capital,
    Outpost,
    FortifiedCity,
    TradingPost,
    MiningCamp,
    PortCity,
    UndergroundCity,
    FloatingCity,
    DesertOasis,
    MountainStronghold
}

public enum UndergroundZoneType
{
    ShallowCave,
    DeepCavern,
    CrystalMine,
    AncientRuins,
    Catacombs,
    Sewers,
    UndergroundLake,
    FungalGrove,
    DwarvenMines,
    AbandonedDungeon,
    LavaChambers,
    IceCaves,
    SpiderNest,
    TrollCave,
    DragonLair
}

public class Settlement
{
    public int Id { get; set; }
    public string Name { get; set; } = string.Empty;
    public SettlementType Type { get; set; }
    public string Description { get; set; } = string.Empty;
    public int Population { get; set; }
    public List<string> AvailableServices { get; set; } = new();
    public bool HasBank { get; set; }
    public bool HasAuctionHouse { get; set; }
    public bool HasInn { get; set; }
    public bool HasFlightMaster { get; set; }
    public bool HasTrainers { get; set; }
    public List<string> Shops { get; set; } = new();
    public string Faction { get; set; } = string.Empty;
    
    public static List<Settlement> GetMajorSettlements()
    {
        return new List<Settlement>
        {
            new Settlement { Id = 1, Name = "Stormwind", Type = SettlementType.Capital, Description = "The grand capital of the Alliance", Population = 50000, HasBank = true, HasAuctionHouse = true, HasInn = true, HasFlightMaster = true, HasTrainers = true, Shops = new List<string> { "General", "Weapon", "Armor", "Magic", "Alchemy", "Enchanting" }, Faction = "Alliance" },
            new Settlement { Id = 2, Name = "Orgrimmar", Type = SettlementType.Capital, Description = "The mighty fortress city of the Horde", Population = 45000, HasBank = true, HasAuctionHouse = true, HasInn = true, HasFlightMaster = true, HasTrainers = true, Shops = new List<string> { "General", "Weapon", "Armor", "Magic", "Alchemy", "Engineering" }, Faction = "Horde" },
            new Settlement { Id = 3, Name = "Ironforge", Type = SettlementType.UndergroundCity, Description = "The underground fortress of the dwarves", Population = 30000, HasBank = true, HasAuctionHouse = true, HasInn = true, HasFlightMaster = true, HasTrainers = true, Shops = new List<string> { "General", "Weapon", "Armor", "Mining", "Blacksmithing" }, Faction = "Alliance" },
            new Settlement { Id = 4, Name = "Undercity", Type = SettlementType.UndergroundCity, Description = "The dark undead capital beneath ruins", Population = 25000, HasBank = true, HasAuctionHouse = true, HasInn = true, HasFlightMaster = true, HasTrainers = true, Shops = new List<string> { "General", "Weapon", "Alchemy", "Tailoring" }, Faction = "Horde" },
            new Settlement { Id = 5, Name = "Darnassus", Type = SettlementType.Capital, Description = "The night elf tree city", Population = 20000, HasBank = true, HasAuctionHouse = true, HasInn = true, HasFlightMaster = true, HasTrainers = true, Shops = new List<string> { "General", "Weapon", "Armor", "Herbalism" }, Faction = "Alliance" },
            new Settlement { Id = 6, Name = "Thunder Bluff", Type = SettlementType.Capital, Description = "The tauren city on high plateaus", Population = 18000, HasBank = true, HasAuctionHouse = true, HasInn = true, HasFlightMaster = true, HasTrainers = true, Shops = new List<string> { "General", "Weapon", "Leatherworking" }, Faction = "Horde" },
            new Settlement { Id = 7, Name = "Goldshire", Type = SettlementType.SmallVillage, Description = "A peaceful human village", Population = 500, HasInn = true, Shops = new List<string> { "General" }, Faction = "Alliance" },
            new Settlement { Id = 8, Name = "Crossroads", Type = SettlementType.Outpost, Description = "A strategic horde outpost", Population = 300, HasInn = true, HasFlightMaster = true, Shops = new List<string> { "General" }, Faction = "Horde" },
            new Settlement { Id = 9, Name = "Booty Bay", Type = SettlementType.PortCity, Description = "A neutral goblin port city", Population = 5000, HasBank = true, HasAuctionHouse = true, HasInn = true, Shops = new List<string> { "General", "Black Market", "Exotic Goods" }, Faction = "Neutral" },
            new Settlement { Id = 10, Name = "Dalaran", Type = SettlementType.FloatingCity, Description = "The magical floating city", Population = 15000, HasBank = true, HasAuctionHouse = true, HasInn = true, HasFlightMaster = true, HasTrainers = true, Shops = new List<string> { "General", "Magic", "Enchanting", "Tailoring", "Jewelcrafting" }, Faction = "Neutral" }
        };
    }
}

public class BiomeZone
{
    public int Id { get; set; }
    public string Name { get; set; } = string.Empty;
    public BiomeType Biome { get; set; }
    public string Description { get; set; } = string.Empty;
    public int RecommendedLevel { get; set; }
    public List<string> CommonEnemies { get; set; } = new();
    public List<string> RareEnemies { get; set; } = new();
    public List<string> Resources { get; set; } = new();
    public string WeatherEffect { get; set; } = string.Empty;
    
    public static List<BiomeZone> GetBiomeZones()
    {
        return new List<BiomeZone>
        {
            new BiomeZone { Id = 1, Name = "Elwynn Forest", Biome = BiomeType.TemperateForest, Description = "A peaceful forest with rolling hills", RecommendedLevel = 1, CommonEnemies = new List<string> { "Wolf", "Bear", "Kobold" }, Resources = new List<string> { "Herbs", "Copper" }, WeatherEffect = "Sunny" },
            new BiomeZone { Id = 2, Name = "Durotar", Biome = BiomeType.Desert, Description = "A harsh desert homeland", RecommendedLevel = 1, CommonEnemies = new List<string> { "Scorpion", "Boar", "Raptor" }, Resources = new List<string> { "Copper", "Cactus" }, WeatherEffect = "Hot" },
            new BiomeZone { Id = 3, Name = "Dun Morogh", Biome = BiomeType.Tundra, Description = "A frozen mountainous region", RecommendedLevel = 1, CommonEnemies = new List<string> { "Ice Troll", "Yeti", "Wendigo" }, Resources = new List<string> { "Copper", "Ice Moss" }, WeatherEffect = "Snowy" },
            new BiomeZone { Id = 4, Name = "Mulgore", Biome = BiomeType.GrasslandPlains, Description = "Vast grasslands and open skies", RecommendedLevel = 1, CommonEnemies = new List<string> { "Plainstrider", "Cougar", "Quillboar" }, Resources = new List<string> { "Herbs", "Leather" }, WeatherEffect = "Clear" },
            new BiomeZone { Id = 5, Name = "Teldrassil", Biome = BiomeType.TemperateForest, Description = "The great world tree", RecommendedLevel = 1, CommonEnemies = new List<string> { "Spider", "Owl", "Satyr" }, Resources = new List<string> { "Moonwell Water", "Nightsaber Fang" }, WeatherEffect = "Moonlight" },
            new BiomeZone { Id = 6, Name = "Tirisfal Glades", Biome = BiomeType.CorruptedLands, Description = "Corrupted lands of the undead", RecommendedLevel = 1, CommonEnemies = new List<string> { "Zombie", "Skeleton", "Ghoul" }, Resources = new List<string> { "Grave Moss", "Undead Essence" }, WeatherEffect = "Gloomy" },
            new BiomeZone { Id = 7, Name = "Swamp of Sorrows", Biome = BiomeType.Swamp, Description = "A dark and dangerous swampland", RecommendedLevel = 35, CommonEnemies = new List<string> { "Crocolisk", "Murloc", "Swamp Walker" }, RareEnemies = new List<string> { "Swamp Dragon" }, Resources = new List<string> { "Swamp Herb", "Fishing Spots" }, WeatherEffect = "Foggy" },
            new BiomeZone { Id = 8, Name = "Tanaris", Biome = BiomeType.Desert, Description = "An endless sea of sand", RecommendedLevel = 40, CommonEnemies = new List<string> { "Sandworm", "Scarab", "Wastewander Bandit" }, RareEnemies = new List<string> { "Sand Drake" }, Resources = new List<string> { "Thorium", "Silk" }, WeatherEffect = "Sandstorm" },
            new BiomeZone { Id = 9, Name = "Winterspring", Biome = BiomeType.FrozenWasteland, Description = "A permanently frozen wilderness", RecommendedLevel = 55, CommonEnemies = new List<string> { "Frostmaul Giant", "Chimera", "Ice Thistle" }, RareEnemies = new List<string> { "Azuregos" }, Resources = new List<string> { "Winterfall Firewater", "Thorium" }, WeatherEffect = "Blizzard" },
            new BiomeZone { Id = 10, Name = "Un'Goro Crater", Biome = BiomeType.TropicalRainforest, Description = "A prehistoric jungle crater", RecommendedLevel = 48, CommonEnemies = new List<string> { "Devilsaur", "Pterrordax", "Ooze" }, RareEnemies = new List<string> { "King Mosh" }, Resources = new List<string> { "Un'Goro Soil", "Rare Herbs" }, WeatherEffect = "Humid" }
        };
    }
}

public class UndergroundZone
{
    public int Id { get; set; }
    public string Name { get; set; } = string.Empty;
    public UndergroundZoneType Type { get; set; }
    public string Description { get; set; } = string.Empty;
    public int RecommendedLevel { get; set; }
    public int Depth { get; set; } // Meters underground
    public List<string> Enemies { get; set; } = new();
    public List<string> Treasures { get; set; } = new();
    public bool HasWater { get; set; }
    public string LightLevel { get; set; } = string.Empty;
    
    public static List<UndergroundZone> GetUndergroundZones()
    {
        return new List<UndergroundZone>
        {
            new UndergroundZone { Id = 1, Name = "The Deeprun Tram", Type = UndergroundZoneType.ShallowCave, Description = "Underground tram connecting cities", RecommendedLevel = 1, Depth = 100, Enemies = new List<string> { "Rat" }, LightLevel = "Lit" },
            new UndergroundZone { Id = 2, Name = "Blackrock Depths", Type = UndergroundZoneType.DwarvenMines, Description = "Ancient dark iron dwarf city", RecommendedLevel = 52, Depth = 1000, Enemies = new List<string> { "Dark Iron Dwarf", "Fire Elemental", "Lava Spawn" }, Treasures = new List<string> { "Dark Iron Ore", "Fire Ruby" }, HasWater = true, LightLevel = "Dim" },
            new UndergroundZone { Id = 3, Name = "Uldaman", Type = UndergroundZoneType.AncientRuins, Description = "Ancient titan vault", RecommendedLevel = 40, Depth = 500, Enemies = new List<string> { "Stone Guardian", "Trogg", "Earthen" }, Treasures = new List<string> { "Ancient Artifacts", "Titan Relics" }, LightLevel = "Dark" },
            new UndergroundZone { Id = 4, Name = "Wailing Caverns", Type = UndergroundZoneType.DeepCavern, Description = "Twisted underground cavern", RecommendedLevel = 17, Depth = 200, Enemies = new List<string> { "Druid of the Fang", "Deviate Raptor", "Serpent" }, HasWater = true, LightLevel = "Dim" },
            new UndergroundZone { Id = 5, Name = "Maraudon", Type = UndergroundZoneType.DeepCavern, Description = "Underground temple of earth", RecommendedLevel = 46, Depth = 800, Enemies = new List<string> { "Earth Elemental", "Satyr", "Ancient" }, Treasures = new List<string> { "Nature Gems", "Earth Essence" }, HasWater = true, LightLevel = "Dark" },
            new UndergroundZone { Id = 6, Name = "Crystal Depths", Type = UndergroundZoneType.CrystalMine, Description = "Glowing crystal caves", RecommendedLevel = 30, Depth = 400, Enemies = new List<string> { "Crystal Golem", "Crystal Spider" }, Treasures = new List<string> { "Magic Crystals", "Gems" }, LightLevel = "Glowing" },
            new UndergroundZone { Id = 7, Name = "The Underbog", Type = UndergroundZoneType.UndergroundLake, Description = "Murky underground lake system", RecommendedLevel = 62, Depth = 300, Enemies = new List<string> { "Bog Giant", "Naga", "Murloc" }, HasWater = true, LightLevel = "Very Dark" },
            new UndergroundZone { Id = 8, Name = "Ahn'Qiraj Lower", Type = UndergroundZoneType.AncientRuins, Description = "Ancient qiraji ruins", RecommendedLevel = 60, Depth = 600, Enemies = new List<string> { "Qiraji Warrior", "Anubisath", "Scarab" }, Treasures = new List<string> { "Qiraji Artifacts", "Ancient Scarabs" }, LightLevel = "Dim" }
        };
    }
}
