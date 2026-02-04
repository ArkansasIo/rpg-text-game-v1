namespace RPGMenuSystem.Game;

public class Zone
{
    public int Id { get; set; }
    public string Name { get; set; } = string.Empty;
    public string Description { get; set; } = string.Empty;
    public ZoneType Type { get; set; }
    public int RecommendedLevel { get; set; }
    public List<int> ConnectedZones { get; set; } = new();
    public bool IsDiscovered { get; set; }
    public List<string> Enemies { get; set; } = new();
    public bool HasShop { get; set; }
    public bool HasInn { get; set; }
}

public enum ZoneType
{
    Town,
    Village,
    Forest,
    Cave,
    Dungeon,
    Mountain,
    Desert,
    Plains,
    Swamp,
    Castle,
    Temple,
    Ruins,
    Ocean,
    Island,
    Volcano,
    IceLand,
    SkyRealm,
    Underground,
    Graveyard,
    BossArea
}

public class ZoneManager
{
    private List<Zone> _zones = new();
    private int _currentZoneId = 1;

    public Zone CurrentZone => _zones.FirstOrDefault(z => z.Id == _currentZoneId) ?? _zones[0];
    public List<Zone> DiscoveredZones => _zones.Where(z => z.IsDiscovered).ToList();

    public ZoneManager()
    {
        InitializeZones();
        _zones[0].IsDiscovered = true; // Starting zone
    }

    private void InitializeZones()
    {
        // Starter Zones (1-10)
        _zones.Add(new Zone { Id = 1, Name = "Greenleaf Village", Description = "A peaceful starting village", Type = ZoneType.Village, RecommendedLevel = 1, HasShop = true, HasInn = true, ConnectedZones = new List<int> { 2, 3 }, Enemies = new List<string> { "Slime", "Rat" } });
        _zones.Add(new Zone { Id = 2, Name = "Whispering Woods", Description = "A quiet forest near the village", Type = ZoneType.Forest, RecommendedLevel = 2, ConnectedZones = new List<int> { 1, 4, 5 }, Enemies = new List<string> { "Wolf", "Goblin" } });
        _zones.Add(new Zone { Id = 3, Name = "Sunny Plains", Description = "Wide open grasslands", Type = ZoneType.Plains, RecommendedLevel = 2, ConnectedZones = new List<int> { 1, 6 }, Enemies = new List<string> { "Boar", "Bandit" } });
        _zones.Add(new Zone { Id = 4, Name = "Ancient Oak Grove", Description = "Home to massive ancient trees", Type = ZoneType.Forest, RecommendedLevel = 3, ConnectedZones = new List<int> { 2, 7 }, Enemies = new List<string> { "Treant", "Spider" } });
        _zones.Add(new Zone { Id = 5, Name = "Crystal Cave", Description = "A cave filled with glowing crystals", Type = ZoneType.Cave, RecommendedLevel = 4, ConnectedZones = new List<int> { 2, 8 }, Enemies = new List<string> { "Bat", "Crystal Golem" } });
        _zones.Add(new Zone { Id = 6, Name = "Riverside Town", Description = "A bustling town by the river", Type = ZoneType.Town, RecommendedLevel = 3, HasShop = true, HasInn = true, ConnectedZones = new List<int> { 3, 9, 10 }, Enemies = new List<string>() });
        _zones.Add(new Zone { Id = 7, Name = "Moonlit Glade", Description = "A magical clearing in the forest", Type = ZoneType.Forest, RecommendedLevel = 5, ConnectedZones = new List<int> { 4, 11 }, Enemies = new List<string> { "Fairy", "Unicorn" } });
        _zones.Add(new Zone { Id = 8, Name = "Deep Caverns", Description = "Dark and dangerous underground passages", Type = ZoneType.Cave, RecommendedLevel = 6, ConnectedZones = new List<int> { 5, 12 }, Enemies = new List<string> { "Cave Troll", "Dark Elf" } });
        _zones.Add(new Zone { Id = 9, Name = "Farmer's Fields", Description = "Peaceful farmland", Type = ZoneType.Plains, RecommendedLevel = 3, ConnectedZones = new List<int> { 6, 13 }, Enemies = new List<string> { "Scarecrow", "Wild Dog" } });
        _zones.Add(new Zone { Id = 10, Name = "Old Bridge", Description = "An ancient stone bridge", Type = ZoneType.Plains, RecommendedLevel = 4, ConnectedZones = new List<int> { 6, 14 }, Enemies = new List<string> { "Troll", "Bandit" } });

        // Mid-Level Zones (11-30)
        _zones.Add(new Zone { Id = 11, Name = "Silverwood Forest", Description = "A mystical silver-leafed forest", Type = ZoneType.Forest, RecommendedLevel = 7, ConnectedZones = new List<int> { 7, 15, 16 }, Enemies = new List<string> { "Dryad", "Forest Spirit" } });
        _zones.Add(new Zone { Id = 12, Name = "Underground Lake", Description = "A vast subterranean water body", Type = ZoneType.Underground, RecommendedLevel = 8, ConnectedZones = new List<int> { 8, 17 }, Enemies = new List<string> { "Merfolk", "Giant Fish" } });
        _zones.Add(new Zone { Id = 13, Name = "Windmill Hill", Description = "Rolling hills with old windmills", Type = ZoneType.Plains, RecommendedLevel = 6, ConnectedZones = new List<int> { 9, 18 }, Enemies = new List<string> { "Harpy", "Wind Elemental" } });
        _zones.Add(new Zone { Id = 14, Name = "Bandit Camp", Description = "A dangerous outlaw hideout", Type = ZoneType.Plains, RecommendedLevel = 8, ConnectedZones = new List<int> { 10, 19 }, Enemies = new List<string> { "Bandit Chief", "Rogue" } });
        _zones.Add(new Zone { Id = 15, Name = "Moonstone City", Description = "A grand magical city", Type = ZoneType.Town, RecommendedLevel = 10, HasShop = true, HasInn = true, ConnectedZones = new List<int> { 11, 20, 21 }, Enemies = new List<string>() });
        _zones.Add(new Zone { Id = 16, Name = "Enchanted Garden", Description = "A garden of magical plants", Type = ZoneType.Forest, RecommendedLevel = 9, ConnectedZones = new List<int> { 11, 22 }, Enemies = new List<string> { "Plant Monster", "Sprite" } });
        _zones.Add(new Zone { Id = 17, Name = "Forgotten Mines", Description = "Abandoned mining tunnels", Type = ZoneType.Underground, RecommendedLevel = 10, ConnectedZones = new List<int> { 12, 23 }, Enemies = new List<string> { "Miner Zombie", "Rock Golem" } });
        _zones.Add(new Zone { Id = 18, Name = "Sky Bridges", Description = "Ancient bridges in the clouds", Type = ZoneType.SkyRealm, RecommendedLevel = 11, ConnectedZones = new List<int> { 13, 24 }, Enemies = new List<string> { "Sky Serpent", "Cloud Giant" } });
        _zones.Add(new Zone { Id = 19, Name = "Dusty Crossroads", Description = "Where many paths meet", Type = ZoneType.Plains, RecommendedLevel = 9, ConnectedZones = new List<int> { 14, 25, 26 }, Enemies = new List<string> { "Merchant Guard", "Highwayman" } });
        _zones.Add(new Zone { Id = 20, Name = "Royal Palace", Description = "The king's magnificent palace", Type = ZoneType.Castle, RecommendedLevel = 12, ConnectedZones = new List<int> { 15, 27 }, Enemies = new List<string>() });
        _zones.Add(new Zone { Id = 21, Name = "Magic Academy", Description = "School for aspiring mages", Type = ZoneType.Town, RecommendedLevel = 11, HasShop = true, ConnectedZones = new List<int> { 15, 28 }, Enemies = new List<string>() });
        _zones.Add(new Zone { Id = 22, Name = "Poison Swamp", Description = "A toxic and dangerous marshland", Type = ZoneType.Swamp, RecommendedLevel = 12, ConnectedZones = new List<int> { 16, 29 }, Enemies = new List<string> { "Swamp Beast", "Poison Frog" } });
        _zones.Add(new Zone { Id = 23, Name = "Lava Chambers", Description = "Scorching hot underground lava flows", Type = ZoneType.Underground, RecommendedLevel = 13, ConnectedZones = new List<int> { 17, 30 }, Enemies = new List<string> { "Fire Elemental", "Lava Beast" } });
        _zones.Add(new Zone { Id = 24, Name = "Floating Islands", Description = "Islands suspended in the sky", Type = ZoneType.SkyRealm, RecommendedLevel = 14, ConnectedZones = new List<int> { 18, 31 }, Enemies = new List<string> { "Wyvern", "Air Elemental" } });
        _zones.Add(new Zone { Id = 25, Name = "Desert Oasis", Description = "A life-giving oasis in the sand", Type = ZoneType.Desert, RecommendedLevel = 13, HasInn = true, ConnectedZones = new List<int> { 19, 32 }, Enemies = new List<string> { "Scorpion", "Sand Wurm" } });
        _zones.Add(new Zone { Id = 26, Name = "Haunted Graveyard", Description = "Where the dead don't rest", Type = ZoneType.Graveyard, RecommendedLevel = 14, ConnectedZones = new List<int> { 19, 33 }, Enemies = new List<string> { "Zombie", "Ghost" } });
        _zones.Add(new Zone { Id = 27, Name = "Throne Room", Description = "The heart of the kingdom", Type = ZoneType.Castle, RecommendedLevel = 15, ConnectedZones = new List<int> { 20, 34 }, Enemies = new List<string>() });
        _zones.Add(new Zone { Id = 28, Name = "Astral Observatory", Description = "Study the stars and cosmos", Type = ZoneType.SkyRealm, RecommendedLevel = 15, ConnectedZones = new List<int> { 21, 35 }, Enemies = new List<string> { "Star Guardian" } });
        _zones.Add(new Zone { Id = 29, Name = "Murky Depths", Description = "The darkest part of the swamp", Type = ZoneType.Swamp, RecommendedLevel = 16, ConnectedZones = new List<int> { 22, 36 }, Enemies = new List<string> { "Hydra", "Lizardman" } });
        _zones.Add(new Zone { Id = 30, Name = "Magma Core", Description = "The source of underground heat", Type = ZoneType.Volcano, RecommendedLevel = 17, ConnectedZones = new List<int> { 23, 37 }, Enemies = new List<string> { "Magma Dragon", "Fire Giant" } });

        // High-Level Zones (31-50)
        _zones.Add(new Zone { Id = 31, Name = "Storm Peak", Description = "A mountain wreathed in eternal storms", Type = ZoneType.Mountain, RecommendedLevel = 18, ConnectedZones = new List<int> { 24, 38 }, Enemies = new List<string> { "Storm Dragon", "Lightning Elemental" } });
        _zones.Add(new Zone { Id = 32, Name = "Endless Dunes", Description = "Vast stretches of desert", Type = ZoneType.Desert, RecommendedLevel = 17, ConnectedZones = new List<int> { 25, 39 }, Enemies = new List<string> { "Sand Drake", "Desert Nomad" } });
        _zones.Add(new Zone { Id = 33, Name = "Crypt of the Fallen", Description = "Ancient burial chambers", Type = ZoneType.Graveyard, RecommendedLevel = 18, ConnectedZones = new List<int> { 26, 40 }, Enemies = new List<string> { "Lich", "Death Knight" } });
        _zones.Add(new Zone { Id = 34, Name = "Secret Passage", Description = "Hidden tunnels beneath the castle", Type = ZoneType.Underground, RecommendedLevel = 19, ConnectedZones = new List<int> { 27, 41 }, Enemies = new List<string> { "Assassin", "Shadow Beast" } });
        _zones.Add(new Zone { Id = 35, Name = "Celestial Gardens", Description = "Gardens floating among the stars", Type = ZoneType.SkyRealm, RecommendedLevel = 20, ConnectedZones = new List<int> { 28, 42 }, Enemies = new List<string> { "Angel", "Celestial Guardian" } });
        _zones.Add(new Zone { Id = 36, Name = "Blackwater Bay", Description = "Dark waters hide ancient secrets", Type = ZoneType.Swamp, RecommendedLevel = 19, ConnectedZones = new List<int> { 29, 43 }, Enemies = new List<string> { "Kraken", "Sea Witch" } });
        _zones.Add(new Zone { Id = 37, Name = "Volcano Summit", Description = "The peak of an active volcano", Type = ZoneType.Volcano, RecommendedLevel = 21, ConnectedZones = new List<int> { 30, 44 }, Enemies = new List<string> { "Inferno Titan", "Phoenix" } });
        _zones.Add(new Zone { Id = 38, Name = "Thunder Keep", Description = "Fortress built into a storm mountain", Type = ZoneType.Castle, RecommendedLevel = 22, ConnectedZones = new List<int> { 31, 45 }, Enemies = new List<string> { "Storm Knight", "Thunder Bird" } });
        _zones.Add(new Zone { Id = 39, Name = "Mirage City", Description = "A city that appears and disappears", Type = ZoneType.Desert, RecommendedLevel = 21, HasShop = true, HasInn = true, ConnectedZones = new List<int> { 32, 46 }, Enemies = new List<string>() });
        _zones.Add(new Zone { Id = 40, Name = "Necropolis", Description = "City of the dead", Type = ZoneType.Graveyard, RecommendedLevel = 23, ConnectedZones = new List<int> { 33, 47 }, Enemies = new List<string> { "Bone Dragon", "Vampire Lord" } });
        _zones.Add(new Zone { Id = 41, Name = "Dark Fortress", Description = "An evil stronghold", Type = ZoneType.Castle, RecommendedLevel = 24, ConnectedZones = new List<int> { 34, 48 }, Enemies = new List<string> { "Dark Knight", "Demon" } });
        _zones.Add(new Zone { Id = 42, Name = "Star Temple", Description = "Ancient temple among the stars", Type = ZoneType.Temple, RecommendedLevel = 25, ConnectedZones = new List<int> { 35, 49 }, Enemies = new List<string> { "Starborn", "Cosmic Entity" } });
        _zones.Add(new Zone { Id = 43, Name = "Abyssal Trench", Description = "The deepest part of the ocean", Type = ZoneType.Ocean, RecommendedLevel = 24, ConnectedZones = new List<int> { 36, 50 }, Enemies = new List<string> { "Deep One", "Leviathan" } });
        _zones.Add(new Zone { Id = 44, Name = "Infernal Pit", Description = "Gateway to the underworld", Type = ZoneType.Volcano, RecommendedLevel = 26, ConnectedZones = new List<int> { 37, 51 }, Enemies = new List<string> { "Demon Lord", "Hellhound" } });
        _zones.Add(new Zone { Id = 45, Name = "Skyfortress", Description = "Legendary flying fortress", Type = ZoneType.SkyRealm, RecommendedLevel = 27, ConnectedZones = new List<int> { 38, 52 }, Enemies = new List<string> { "Sky Titan", "Griffin" } });
        _zones.Add(new Zone { Id = 46, Name = "Sandstorm Wastes", Description = "Endless sandstorms block vision", Type = ZoneType.Desert, RecommendedLevel = 26, ConnectedZones = new List<int> { 39, 53 }, Enemies = new List<string> { "Sand Demon", "Dust Devil" } });
        _zones.Add(new Zone { Id = 47, Name = "Soul Harvesting Chamber", Description = "Where souls are collected", Type = ZoneType.Graveyard, RecommendedLevel = 28, ConnectedZones = new List<int> { 40, 54 }, Enemies = new List<string> { "Soul Reaper", "Wraith King" } });
        _zones.Add(new Zone { Id = 48, Name = "Demon King's Hall", Description = "Throne room of evil", Type = ZoneType.Castle, RecommendedLevel = 29, ConnectedZones = new List<int> { 41, 55 }, Enemies = new List<string> { "Demon King" } });
        _zones.Add(new Zone { Id = 49, Name = "Constellation Chamber", Description = "Where stars are born", Type = ZoneType.SkyRealm, RecommendedLevel = 30, ConnectedZones = new List<int> { 42, 56 }, Enemies = new List<string> { "Star Dragon", "Nova Entity" } });
        _zones.Add(new Zone { Id = 50, Name = "Poseidon's Palace", Description = "Underwater palace of the sea god", Type = ZoneType.Ocean, RecommendedLevel = 30, ConnectedZones = new List<int> { 43, 57 }, Enemies = new List<string> { "Poseidon", "Sea Serpent" } });

        // Legendary Zones (51-72)
        _zones.Add(new Zone { Id = 51, Name = "Nine Hells", Description = "The deepest layer of hell", Type = ZoneType.BossArea, RecommendedLevel = 32, ConnectedZones = new List<int> { 44, 58 }, Enemies = new List<string> { "Archdevil", "Pit Fiend" } });
        _zones.Add(new Zone { Id = 52, Name = "Heaven's Gate", Description = "Entrance to the divine realm", Type = ZoneType.Temple, RecommendedLevel = 33, ConnectedZones = new List<int> { 45, 59 }, Enemies = new List<string> { "Archangel", "Seraphim" } });
        _zones.Add(new Zone { Id = 53, Name = "Pyramid of Eternity", Description = "Ancient pyramid of untold power", Type = ZoneType.Ruins, RecommendedLevel = 34, ConnectedZones = new List<int> { 46, 60 }, Enemies = new List<string> { "Pharaoh", "Mummy Lord" } });
        _zones.Add(new Zone { Id = 54, Name = "Void Nexus", Description = "Where reality breaks down", Type = ZoneType.BossArea, RecommendedLevel = 35, ConnectedZones = new List<int> { 47, 61 }, Enemies = new List<string> { "Void Dragon", "Entropy Beast" } });
        _zones.Add(new Zone { Id = 55, Name = "Pandemonium", Description = "Realm of chaos and madness", Type = ZoneType.BossArea, RecommendedLevel = 36, ConnectedZones = new List<int> { 48, 62 }, Enemies = new List<string> { "Chaos Lord", "Madness Incarnate" } });
        _zones.Add(new Zone { Id = 56, Name = "Astral Throne", Description = "Seat of cosmic power", Type = ZoneType.Temple, RecommendedLevel = 37, ConnectedZones = new List<int> { 49, 63 }, Enemies = new List<string> { "Cosmic Guardian", "Stellar Deity" } });
        _zones.Add(new Zone { Id = 57, Name = "Atlantis Depths", Description = "Lost city beneath the waves", Type = ZoneType.Ruins, RecommendedLevel = 38, HasShop = true, ConnectedZones = new List<int> { 50, 64 }, Enemies = new List<string> { "Atlantean Warrior", "Ancient Kraken" } });
        _zones.Add(new Zone { Id = 58, Name = "Inferno Core", Description = "The heart of all fire", Type = ZoneType.BossArea, RecommendedLevel = 39, ConnectedZones = new List<int> { 51, 65 }, Enemies = new List<string> { "Inferno Dragon", "Fire God" } });
        _zones.Add(new Zone { Id = 59, Name = "Divine Sanctum", Description = "Holy place of the gods", Type = ZoneType.Temple, RecommendedLevel = 40, ConnectedZones = new List<int> { 52, 66 }, Enemies = new List<string> { "Divine Champion", "Holy Dragon" } });
        _zones.Add(new Zone { Id = 60, Name = "Time's End", Description = "Where time itself stops", Type = ZoneType.BossArea, RecommendedLevel = 41, ConnectedZones = new List<int> { 53, 67 }, Enemies = new List<string> { "Time Keeper", "Temporal Dragon" } });
        _zones.Add(new Zone { Id = 61, Name = "Oblivion's Edge", Description = "The boundary of existence", Type = ZoneType.BossArea, RecommendedLevel = 42, ConnectedZones = new List<int> { 54, 68 }, Enemies = new List<string> { "Oblivion Beast", "Nothingness" } });
        _zones.Add(new Zone { Id = 62, Name = "Nightmare Realm", Description = "Dimension of living nightmares", Type = ZoneType.BossArea, RecommendedLevel = 43, ConnectedZones = new List<int> { 55, 69 }, Enemies = new List<string> { "Nightmare King", "Fear Incarnate" } });
        _zones.Add(new Zone { Id = 63, Name = "Cosmic Pinnacle", Description = "Peak of all creation", Type = ZoneType.SkyRealm, RecommendedLevel = 44, ConnectedZones = new List<int> { 56, 70 }, Enemies = new List<string> { "Reality Warden", "Universe Guardian" } });
        _zones.Add(new Zone { Id = 64, Name = "Forgotten Temple", Description = "Temple of an ancient civilization", Type = ZoneType.Ruins, RecommendedLevel = 45, ConnectedZones = new List<int> { 57, 71 }, Enemies = new List<string> { "Ancient God", "Titan" } });
        _zones.Add(new Zone { Id = 65, Name = "Dragon's Lair", Description = "Home of the elder dragons", Type = ZoneType.BossArea, RecommendedLevel = 46, ConnectedZones = new List<int> { 58, 72 }, Enemies = new List<string> { "Elder Dragon", "Dragon God" } });
        _zones.Add(new Zone { Id = 66, Name = "Paradise Lost", Description = "Fallen paradise realm", Type = ZoneType.Temple, RecommendedLevel = 47, ConnectedZones = new List<int> { 59, 72 }, Enemies = new List<string> { "Fallen Angel", "Corrupted Saint" } });
        _zones.Add(new Zone { Id = 67, Name = "Eternity's Prison", Description = "Where immortals are trapped", Type = ZoneType.BossArea, RecommendedLevel = 48, ConnectedZones = new List<int> { 60, 72 }, Enemies = new List<string> { "Imprisoned God", "Eternal Warden" } });
        _zones.Add(new Zone { Id = 68, Name = "Shattered Reality", Description = "Where dimensions collide", Type = ZoneType.BossArea, RecommendedLevel = 49, ConnectedZones = new List<int> { 61, 72 }, Enemies = new List<string> { "Reality Breaker", "Dimension Lord" } });
        _zones.Add(new Zone { Id = 69, Name = "Abyss of Despair", Description = "Deepest darkness exists here", Type = ZoneType.BossArea, RecommendedLevel = 50, ConnectedZones = new List<int> { 62, 72 }, Enemies = new List<string> { "Despair Incarnate", "Abyss Dragon" } });
        _zones.Add(new Zone { Id = 70, Name = "Genesis Chamber", Description = "Where all creation began", Type = ZoneType.Temple, RecommendedLevel = 52, ConnectedZones = new List<int> { 63, 72 }, Enemies = new List<string> { "Primordial Being", "Creator's Avatar" } });
        _zones.Add(new Zone { Id = 71, Name = "Ruins of the First Age", Description = "Remnants of the first civilization", Type = ZoneType.Ruins, RecommendedLevel = 54, ConnectedZones = new List<int> { 64, 72 }, Enemies = new List<string> { "Ancient One", "Primordial Titan" } });
        
        // Final Boss Zone
        _zones.Add(new Zone 
        { 
            Id = 72, 
            Name = "The Infinite Throne", 
            Description = "The center of all 72 realms where the Supreme Being resides", 
            Type = ZoneType.BossArea, 
            RecommendedLevel = 60, 
            ConnectedZones = new List<int> { 65, 66, 67, 68, 69, 70, 71 }, 
            Enemies = new List<string> { "Supreme Dragon God", "Reality Emperor", "Infinity Sovereign" },
            HasShop = false,
            HasInn = false
        });
    }

    public bool TravelToZone(int zoneId)
    {
        var targetZone = _zones.FirstOrDefault(z => z.Id == zoneId);
        if (targetZone == null) return false;

        if (!CurrentZone.ConnectedZones.Contains(zoneId))
            return false;

        _currentZoneId = zoneId;
        targetZone.IsDiscovered = true;
        return true;
    }

    public List<Zone> GetConnectedZones()
    {
        return _zones.Where(z => CurrentZone.ConnectedZones.Contains(z.Id)).ToList();
    }

    public Zone? GetZone(int id)
    {
        return _zones.FirstOrDefault(z => z.Id == id);
    }

    public List<Zone> GetAllZones()
    {
        return _zones;
    }
}
