namespace RPGMenuSystem.Game;

/// <summary>
/// Master World System that integrates all fantasy world components
/// This is the central hub for accessing all world information
/// </summary>
public class AethermoorWorldSystem
{
    private List<Continent> _continents = new();
    private List<Faction> _factions = new();
    private List<NPCCharacter> _characters = new();
    private List<LegendaryEnemy> _legendaryBeasts = new();
    private List<Artifact> _artifacts = new();

    public AethermoorWorldSystem()
    {
        InitializeWorld();
    }

    private void InitializeWorld()
    {
        _continents = WorldDefinition.GetAllContinents();
        _factions = FantasyFactions.GetAllFactions();
        _characters = WorldCharacters.GetAllMajorCharacters();
        _legendaryBeasts = LegendaryBeasts.GetLegendaryEnemies();
        _artifacts = LegendaryArtifacts.GetLegendaryArtifacts();
    }

    // ==================== CONTINENT ACCESS ====================
    public List<Continent> GetAllContinents() => _continents;
    
    public Continent? GetContinentById(int id) => _continents.FirstOrDefault(c => c.Id == id);
    
    public Continent? GetContinentByName(string name) 
        => _continents.FirstOrDefault(c => c.Name.Equals(name, StringComparison.OrdinalIgnoreCase));
    
    public List<Region> GetRegionsByContinentId(int continentId)
    {
        var continent = GetContinentById(continentId);
        return continent?.Regions ?? new List<Region>();
    }

    public List<ZoneDetail> GetZonesByRegionId(int continentId, int regionId)
    {
        var continent = GetContinentById(continentId);
        var region = continent?.Regions.FirstOrDefault(r => r.Id == regionId);
        return region?.Zones ?? new List<ZoneDetail>();
    }

    // ==================== FACTION ACCESS ====================
    public List<Faction> GetAllFactions() => _factions;
    
    public Faction? GetFactionById(int id) => _factions.FirstOrDefault(f => f.FactionId == id);
    
    public Faction? GetFactionByName(string name)
        => _factions.FirstOrDefault(f => f.Name.Equals(name, StringComparison.OrdinalIgnoreCase));
    
    public List<Faction> GetFactionsByAlignment(string alignment)
        => _factions.Where(f => f.Alignment.Contains(alignment, StringComparison.OrdinalIgnoreCase)).ToList();
    
    public List<Faction> GetEnemyFactions(string factionName)
    {
        var faction = GetFactionByName(factionName);
        if (faction == null) return new List<Faction>();
        
        return _factions.Where(f => faction.Enemies.Contains(f.Name)).ToList();
    }
    
    public List<Faction> GetAlliedFactions(string factionName)
    {
        var faction = GetFactionByName(factionName);
        if (faction == null) return new List<Faction>();
        
        return _factions.Where(f => faction.Allies.Contains(f.Name)).ToList();
    }

    // ==================== CHARACTER ACCESS ====================
    public List<NPCCharacter> GetAllCharacters() => _characters;
    
    public NPCCharacter? GetCharacterById(int id) => _characters.FirstOrDefault(c => c.CharacterId == id);
    
    public NPCCharacter? GetCharacterByName(string name)
        => _characters.FirstOrDefault(c => c.Name.Equals(name, StringComparison.OrdinalIgnoreCase));
    
    public List<NPCCharacter> GetCharactersByFaction(string factionName)
        => _characters.Where(c => c.Faction.Equals(factionName, StringComparison.OrdinalIgnoreCase)).ToList();
    
    public List<NPCCharacter> GetCharactersByLocation(string location)
        => _characters.Where(c => c.Location.Contains(location, StringComparison.OrdinalIgnoreCase)).ToList();
    
    public List<NPCCharacter> GetCharactersByClass(string className)
        => _characters.Where(c => c.Class.Equals(className, StringComparison.OrdinalIgnoreCase)).ToList();
    
    public List<NPCCharacter> GetCharactersByRace(string raceName)
        => _characters.Where(c => c.Race.Equals(raceName, StringComparison.OrdinalIgnoreCase)).ToList();
    
    public List<NPCCharacter> GetLeadersByRank()
        => _characters.Where(c => c.Title.Contains("King") || c.Title.Contains("Queen") || 
           c.Title.Contains("Lord") || c.Title.Contains("Archmagus") || c.Title.Contains("Commander"))
           .OrderByDescending(c => c.Level).ToList();

    // ==================== ARTIFACT ACCESS ====================
    public List<Artifact> GetAllArtifacts() => _artifacts;
    
    public Artifact? GetArtifactById(int id) => _artifacts.FirstOrDefault(a => a.ArtifactId == id);
    
    public Artifact? GetArtifactByName(string name)
        => _artifacts.FirstOrDefault(a => a.Name.Equals(name, StringComparison.OrdinalIgnoreCase));
    
    public List<Artifact> GetArtifactsByLocation(string location)
        => _artifacts.Where(a => a.LocationZone.Equals(location, StringComparison.OrdinalIgnoreCase)).ToList();
    
    public List<Artifact> GetArtifactsByLevel(int minLevel)
        => _artifacts.Where(a => a.RequiredLevel >= minLevel).OrderBy(a => a.RequiredLevel).ToList();

    // ==================== BEAST ACCESS ====================
    public List<LegendaryEnemy> GetAllLegendaryBeasts() => _legendaryBeasts;
    
    public LegendaryEnemy? GetBeastById(int id) => _legendaryBeasts.FirstOrDefault(b => b.BeastId == id);
    
    public LegendaryEnemy? GetBeastByName(string name)
        => _legendaryBeasts.FirstOrDefault(b => b.Name.Equals(name, StringComparison.OrdinalIgnoreCase));
    
    public List<LegendaryEnemy> GetBeastsByLevel(int minLevel)
        => _legendaryBeasts.Where(b => b.Level >= minLevel).OrderBy(b => b.Level).ToList();
    
    public List<LegendaryEnemy> GetDefeatedBeasts()
        => _legendaryBeasts.Where(b => b.IsDefeated).ToList();

    // ==================== WORLD STATISTICS ====================
    public WorldStatistics GetWorldStatistics()
    {
        return new WorldStatistics
        {
            TotalContinents = _continents.Count,
            TotalRegions = _continents.Sum(c => c.Regions.Count),
            TotalZones = _continents.Sum(c => c.Regions.Sum(r => r.Zones.Count)),
            TotalPopulation = _continents.Sum(c => c.Population),
            TotalFactions = _factions.Count,
            TotalCharacters = _characters.Count,
            TotalArtifacts = _artifacts.Count,
            TotalLegendaryBeasts = _legendaryBeasts.Count,
            AverageCharacterLevel = _characters.Count > 0 ? _characters.Average(c => c.Level) : 0,
            HighestLevelCharacter = _characters.Count > 0 ? _characters.Max(c => c.Level) : 0
        };
    }

    // ==================== LORE & FLAVOR ====================
    public string GetWorldLore(string loreType)
    {
        return loreType switch
        {
            "creation" => WorldLore.CreationMyth,
            "prophecy" => WorldLore.AncientProphecy,
            "lich" => WorldLore.CurseOfTheLichKing,
            "demons" => WorldLore.TheDemonIncursion,
            _ => "Unknown lore type"
        };
    }

    // ==================== WORLD INFORMATION ====================
    public string GetWorldName() => WorldDefinition.WorldName;
    
    public string GetWorldTheme() => WorldDefinition.WorldTheme;
    
    public string GetWorldDescription()
    {
        return $@"
Welcome to {WorldDefinition.WorldName}

A vast medieval fantasy world spanning across {_continents.Count} major continents with over 
{_continents.Sum(c => c.Regions.Count)} regions and hundreds of distinct zones. This Earth-sized world 
rivals World of Warcraft in scope and is filled with kingdoms, factions, powerful artifacts, 
and legendary beasts awaiting brave adventurers.

Total Population: {_continents.Sum(c => c.Population):N0}
Total Factions: {_factions.Count}
Major Characters: {_characters.Count}
Legendary Artifacts: {_artifacts.Count}
Legendary Bosses: {_legendaryBeasts.Count}
        ";
    }

    // ==================== TRAVEL & NAVIGATION ====================
    public bool CanTravelBetweenZones(int fromZoneId, int toZoneId)
    {
        foreach (var continent in _continents)
        {
            foreach (var region in continent.Regions)
            {
                var fromZone = region.Zones.FirstOrDefault(z => z.ZoneId == fromZoneId);
                if (fromZone != null)
                {
                    var toZone = region.Zones.FirstOrDefault(z => z.ZoneId == toZoneId);
                    if (toZone != null)
                        return true;
                }
            }
        }
        return false;
    }

    public List<string> GetRecommendedPath(int playerLevel)
    {
        var recommendedZones = new List<string>();
        
        foreach (var continent in _continents)
        {
            foreach (var region in continent.Regions)
            {
                var appropriateZones = region.Zones
                    .Where(z => z.Level <= playerLevel && z.Level >= playerLevel - 5)
                    .OrderBy(z => z.Level);
                
                recommendedZones.AddRange(appropriateZones.Select(z => $"{z.Name} (Level {z.Level})"));
            }
        }
        
        return recommendedZones.Take(10).ToList();
    }
}

public class WorldStatistics
{
    public int TotalContinents { get; set; }
    public int TotalRegions { get; set; }
    public int TotalZones { get; set; }
    public int TotalPopulation { get; set; }
    public int TotalFactions { get; set; }
    public int TotalCharacters { get; set; }
    public int TotalArtifacts { get; set; }
    public int TotalLegendaryBeasts { get; set; }
    public double AverageCharacterLevel { get; set; }
    public int HighestLevelCharacter { get; set; }

    public override string ToString()
    {
        return $@"
========== AETHERMOOR WORLD STATISTICS ==========
Continents: {TotalContinents}
Regions: {TotalRegions}
Zones: {TotalZones}
Total Population: {TotalPopulation:N0}
Factions: {TotalFactions}
Major Characters: {TotalCharacters}
Legendary Artifacts: {TotalArtifacts}
Legendary Bosses: {TotalLegendaryBeasts}
Average Character Level: {AverageCharacterLevel:F1}
Highest Level Character: {HighestLevelCharacter}
================================================
        ";
    }
}
