namespace RPGMenuSystem.Game;

/// <summary>
/// Example usage and demonstrations of the Aethermoor World System
/// Shows how to integrate the world into your game
/// </summary>
public class WorldSystemExamples
{
    private AethermoorWorldSystem _world = new();

    /// <summary>
    /// Display complete world information
    /// </summary>
    public void DisplayWorldOverview()
    {
        Console.WriteLine("???????????????????????????????????????????????????????");
        Console.WriteLine($"Welcome to {_world.GetWorldName()}");
        Console.WriteLine("???????????????????????????????????????????????????????");
        Console.WriteLine();
        Console.WriteLine(_world.GetWorldDescription());
        Console.WriteLine();
        Console.WriteLine(_world.GetWorldStatistics());
    }

    /// <summary>
    /// Show all continents and their regions
    /// </summary>
    public void DisplayContinentsList()
    {
        Console.WriteLine("\n??? THE SEVEN CONTINENTS OF AETHERMOOR ???\n");
        
        foreach (var continent in _world.GetAllContinents())
        {
            Console.WriteLine($"?? {continent.Name}");
            Console.WriteLine($"   Theme: {continent.Theme}");
            Console.WriteLine($"   Population: {continent.Population:N0}");
            Console.WriteLine($"   Area: {continent.Area:N0} sq. miles");
            Console.WriteLine($"   Regions: {continent.Regions.Count}");
            
            foreach (var region in continent.Regions)
            {
                Console.WriteLine($"   ?? {region.Name} (Levels {region.RecommendedLevel}+)");
                Console.WriteLine($"      Ruler: {region.Ruler}");
                Console.WriteLine($"      Government: {region.GovernmentType}");
                Console.WriteLine($"      Capital: {region.CapitalCity}");
            }
            Console.WriteLine();
        }
    }

    /// <summary>
    /// Display faction relationships and alignments
    /// </summary>
    public void DisplayFactionWars()
    {
        Console.WriteLine("\n??? FACTION RELATIONSHIPS ???\n");
        
        var factions = _world.GetAllFactions();
        
        // Group by alignment
        var goodFactions = _world.GetFactionsByAlignment("Good");
        var evilFactions = _world.GetFactionsByAlignment("Evil");
        var neutralFactions = factions.Where(f => !f.Alignment.Contains("Good") && !f.Alignment.Contains("Evil")).ToList();
        
        Console.WriteLine($"?? GOOD FACTIONS ({goodFactions.Count})");
        foreach (var faction in goodFactions)
        {
            Console.WriteLine($"   {faction.Name} - {faction.Description}");
            Console.WriteLine($"      Leader: {faction.LeaderName}, {faction.LeaderTitle}");
            Console.WriteLine($"      Allies: {string.Join(", ", faction.Allies)}");
        }
        
        Console.WriteLine($"\n? EVIL FACTIONS ({evilFactions.Count})");
        foreach (var faction in evilFactions)
        {
            Console.WriteLine($"   {faction.Name} - {faction.Description}");
            Console.WriteLine($"      Leader: {faction.LeaderName}, {faction.LeaderTitle}");
            Console.WriteLine($"      Enemies: {string.Join(", ", faction.Enemies)}");
        }
        
        Console.WriteLine($"\n? NEUTRAL FACTIONS ({neutralFactions.Count})");
        foreach (var faction in neutralFactions)
        {
            Console.WriteLine($"   {faction.Name} - {faction.Description}");
            Console.WriteLine($"      Leader: {faction.LeaderName}, {faction.LeaderTitle}");
        }
    }

    /// <summary>
    /// Show major characters and their roles
    /// </summary>
    public void DisplayMajorCharacters()
    {
        Console.WriteLine("\n??? LEGENDARY CHARACTERS ???\n");
        
        var leaders = _world.GetLeadersByRank();
        
        Console.WriteLine("?? WORLD LEADERS (Sorted by Power)\n");
        for (int i = 0; i < Math.Min(10, leaders.Count); i++)
        {
            var character = leaders[i];
            Console.WriteLine($"{i + 1}. {character.GetFullTitle()}");
            Console.WriteLine($"   Race: {character.Race}");
            Console.WriteLine($"   Class: {character.Class}");
            Console.WriteLine($"   Level: {character.Level}");
            Console.WriteLine($"   Faction: {character.Faction}");
            Console.WriteLine($"   Location: {character.Location}");
            Console.WriteLine($"   Alignment: {character.Alignment}");
            Console.WriteLine($"   Bio: {character.Description}");
            Console.WriteLine();
        }
    }

    /// <summary>
    /// Display available artifacts and their locations
    /// </summary>
    public void DisplayLegendaryArtifacts()
    {
        Console.WriteLine("\n??? LEGENDARY ARTIFACTS ???\n");
        
        var artifacts = _world.GetAllArtifacts();
        
        foreach (var artifact in artifacts)
        {
            Console.WriteLine($"??  {artifact.Name}");
            Console.WriteLine($"    Type: {artifact.Type}");
            Console.WriteLine($"    Power Level: {artifact.PowerLevel}/100");
            Console.WriteLine($"    Required Level: {artifact.RequiredLevel}");
            Console.WriteLine($"    Location: {artifact.LocationZone}");
            Console.WriteLine($"    Description: {artifact.Description}");
            Console.WriteLine($"    Lore: {artifact.Lore}");
            Console.WriteLine();
        }
    }

    /// <summary>
    /// Display boss encounters
    /// </summary>
    public void DisplayBossEncounters()
    {
        Console.WriteLine("\n??? LEGENDARY BOSSES ???\n");
        
        var beasts = _world.GetAllLegendaryBeasts();
        
        foreach (var beast in beasts)
        {
            Console.WriteLine($"?? {beast.Name}");
            Console.WriteLine($"   Type: {beast.Type}");
            Console.WriteLine($"   Level: {beast.Level}");
            Console.WriteLine($"   Health: {beast.HealthPoints:N0} HP");
            Console.WriteLine($"   Location: {beast.Location}");
            Console.WriteLine($"   Description: {beast.Description}");
            Console.WriteLine($"   Loot Drops:");
            foreach (var loot in beast.LootTable)
            {
                Console.WriteLine($"      • {loot}");
            }
            Console.WriteLine();
        }
    }

    /// <summary>
    /// Get leveling path recommendations
    /// </summary>
    public void DisplayLevelingPath(int playerLevel)
    {
        Console.WriteLine($"\n??? RECOMMENDED ZONES FOR LEVEL {playerLevel} ???\n");
        
        var recommendedZones = _world.GetRecommendedPath(playerLevel);
        
        if (recommendedZones.Count > 0)
        {
            foreach (var zone in recommendedZones)
            {
                Console.WriteLine($"  • {zone}");
            }
        }
        else
        {
            Console.WriteLine("  No appropriate zones found for your level.");
        }
    }

    /// <summary>
    /// Show world lore and prophecies
    /// </summary>
    public void DisplayWorldLore()
    {
        Console.WriteLine("\n??? WORLD LORE & PROPHECIES ???\n");
        
        Console.WriteLine("?? THE CREATION MYTH");
        Console.WriteLine(_world.GetWorldLore("creation"));
        
        Console.WriteLine("\n?? THE ANCIENT PROPHECY");
        Console.WriteLine(_world.GetWorldLore("prophecy"));
        
        Console.WriteLine("\n?? CURSE OF THE LICH KING");
        Console.WriteLine(_world.GetWorldLore("lich"));
        
        Console.WriteLine("\n?? THE DEMON INCURSION");
        Console.WriteLine(_world.GetWorldLore("demons"));
    }

    /// <summary>
    /// Search characters by various criteria
    /// </summary>
    public void SearchCharacterExamples()
    {
        Console.WriteLine("\n??? CHARACTER SEARCH EXAMPLES ???\n");
        
        // Find all wizards
        var wizards = _world.GetCharactersByClass("Wizard");
        Console.WriteLine($"All Wizards ({wizards.Count}):");
        foreach (var wizard in wizards)
        {
            Console.WriteLine($"  • {wizard.Name} - Level {wizard.Level}");
        }
        
        Console.WriteLine();
        
        // Find all elves
        var elves = _world.GetCharactersByRace("Elf");
        Console.WriteLine($"All Elves ({elves.Count}):");
        foreach (var elf in elves)
        {
            Console.WriteLine($"  • {elf.Name} ({elf.Class}) - {elf.Faction}");
        }
        
        Console.WriteLine();
        
        // Find characters in a specific location
        var thornhavenChars = _world.GetCharactersByLocation("Thornhaven");
        Console.WriteLine($"Characters in Thornhaven ({thornhavenChars.Count}):");
        foreach (var character in thornhavenChars)
        {
            Console.WriteLine($"  • {character.GetFullTitle()} ({character.Class})");
        }
    }

    /// <summary>
    /// Create a world lore book
    /// </summary>
    public string GenerateWorldLoreBook()
    {
        var sb = new System.Text.StringBuilder();
        
        sb.AppendLine("????????????????????????????????????????????");
        sb.AppendLine("     THE COMPLETE LORE OF AETHERMOOR");
        sb.AppendLine("????????????????????????????????????????????\n");
        
        // World overview
        sb.AppendLine("PART I: THE WORLD ITSELF");
        sb.AppendLine("?????????????????????????");
        sb.AppendLine($"World Name: {_world.GetWorldName()}");
        sb.AppendLine($"Theme: {_world.GetWorldTheme()}");
        var stats = _world.GetWorldStatistics();
        sb.AppendLine($"Continents: {stats.TotalContinents}");
        sb.AppendLine($"Regions: {stats.TotalRegions}");
        sb.AppendLine($"Total Population: {stats.TotalPopulation:N0}");
        
        // Factions
        sb.AppendLine("\n\nPART II: THE MAJOR POWERS");
        sb.AppendLine("??????????????????????????");
        foreach (var faction in _world.GetAllFactions())
        {
            sb.AppendLine($"\n{faction.Name}");
            sb.AppendLine($"Alignment: {faction.Alignment}");
            sb.AppendLine($"Leader: {faction.LeaderName}, {faction.LeaderTitle}");
            sb.AppendLine($"Purpose: {faction.Description}");
        }
        
        // Characters
        sb.AppendLine("\n\nPART III: LEGENDARY HEROES AND VILLAINS");
        sb.AppendLine("?????????????????????????????????????????");
        var topCharacters = _world.GetAllCharacters().OrderByDescending(c => c.Level).Take(10);
        foreach (var character in topCharacters)
        {
            sb.AppendLine($"\n{character.GetFullTitle()}");
            sb.AppendLine($"Race: {character.Race}");
            sb.AppendLine($"Class: {character.Class}");
            sb.AppendLine($"Level: {character.Level}");
            sb.AppendLine($"Alignment: {character.Alignment}");
            sb.AppendLine($"Faction: {character.Faction}");
            sb.AppendLine($"Description: {character.Description}");
        }
        
        // Artifacts
        sb.AppendLine("\n\nPART IV: ARTIFACTS OF POWER");
        sb.AppendLine("???????????????????????????");
        foreach (var artifact in _world.GetAllArtifacts())
        {
            sb.AppendLine($"\n{artifact.Name}");
            sb.AppendLine($"Type: {artifact.Type}");
            sb.AppendLine($"Power: {artifact.PowerLevel}/100");
            sb.AppendLine($"Lore: {artifact.Lore}");
            sb.AppendLine($"Location: {artifact.LocationZone}");
        }
        
        return sb.ToString();
    }

    /// <summary>
    /// Main demonstration - show all features
    /// </summary>
    public void RunFullDemonstration()
    {
        DisplayWorldOverview();
        DisplayContinentsList();
        DisplayFactionWars();
        DisplayMajorCharacters();
        DisplayLegendaryArtifacts();
        DisplayBossEncounters();
        DisplayLevelingPath(20);
        DisplayWorldLore();
        SearchCharacterExamples();
    }
}

/// <summary>
/// Quick reference for integrating world system into main game
/// </summary>
public class WorldSystemIntegration
{
    public static void InitializeWorldInGame(RPGGame game)
    {
        // Create world system instance
        var worldSystem = new AethermoorWorldSystem();
        
        // Store in game instance
        // game.World = worldSystem;
        
        // Initialize based on world data
        // 1. Load all zones from world definition
        // 2. Initialize NPC characters from character list
        // 3. Setup faction relationships
        // 4. Place legendary artifacts in dungeons
        // 5. Setup boss encounters with legendary beasts
        
        // Example: Get all zones and add to zone manager
        // var zones = worldSystem.GetAllContinents()
        //     .SelectMany(c => c.Regions)
        //     .SelectMany(r => r.Zones)
        //     .ToList();
        
        // foreach (var zone in zones)
        // {
        //     game.ZoneManager.AddZone(zone);
        // }
    }
}
