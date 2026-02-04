namespace RPGMenuSystem.Game;

/// <summary>
/// Complete fantasy faction system for Aethermoor world
/// Defines all major powers, their relationships, and allegiances
/// </summary>
public static class FantasyFactions
{
    public static List<Faction> GetAllFactions()
    {
        return new List<Faction>
        {
            // ==================== GOOD ALIGNED ====================
            
            new Faction
            {
                FactionId = 1,
                Name = "The Silver Alliance",
                Alignment = "Good",
                Description = "Union of free kingdoms fighting against darkness",
                LeaderName = "King Aldarin Stormborn",
                LeaderTitle = "High King",
                Headquarters = "Thornhaven, Valorian Kingdom",
                Members = new List<string> { "Humans", "Elves", "Dwarves", "Gnomes", "Halflings" },
                Colors = new List<string> { "Silver", "Blue", "Gold" },
                Enemies = new List<string> { "Shadowlands Coalition", "Demonfire Empire", "Undead Armies" },
                Allies = new List<string> { "The Celestial Order", "Ranger's Council" },
                ReputationReward = 50
            },
            new Faction
            {
                FactionId = 2,
                Name = "The Celestial Order",
                Alignment = "Good",
                Description = "Divine agents of the heavens defending against evil",
                LeaderName = "Archangel Uriel",
                LeaderTitle = "Divine Commander",
                Headquarters = "Heavenspire, Celestia",
                Members = new List<string> { "Angels", "Celestials", "Holy Paladins", "Divine Monks" },
                Colors = new List<string> { "Gold", "White", "Light Blue" },
                Enemies = new List<string> { "Demonic Forces", "Abyssal Creatures", "Corrupted Souls" },
                Allies = new List<string> { "The Silver Alliance", "Druidic Circle" },
                ReputationReward = 100
            },
            new Faction
            {
                FactionId = 3,
                Name = "Druidic Circle",
                Alignment = "Good",
                Description = "Guardians of nature and balance across Aethermoor",
                LeaderName = "Archdruid Sylvanus",
                LeaderTitle = "Circle Head",
                Headquarters = "Deepwood Grotto, Shadowpine Jungle",
                Members = new List<string> { "Druids", "Rangers", "Nature Shamans", "Wilderness Keepers" },
                Colors = new List<string> { "Green", "Brown", "Emerald" },
                Enemies = new List<string> { "Demonfire Empire", "Shadowlands Coalition" },
                Allies = new List<string> { "The Silver Alliance", "The Celestial Order" },
                ReputationReward = 75
            },
            
            // ==================== NEUTRAL ALIGNED ====================
            
            new Faction
            {
                FactionId = 4,
                Name = "Merchant's Confluence",
                Alignment = "Neutral",
                Description = "Traders and merchants united for commerce and profit",
                LeaderName = "High Merchant Lord Cassius",
                LeaderTitle = "Lord of Trade",
                Headquarters = "Goldport, Merchant's Confluence",
                Members = new List<string> { "Merchants", "Traders", "Goblins", "Gnomes", "Humans" },
                Colors = new List<string> { "Gold", "Green", "Purple" },
                Enemies = new List<string> { },
                Allies = new List<string> { "The Silver Alliance", "Shadowlands Coalition" },
                ReputationReward = 40
            },
            new Faction
            {
                FactionId = 5,
                Name = "Mage Council",
                Alignment = "Neutral",
                Description = "Organization of powerful wizards pursuing magical knowledge",
                LeaderName = "Archmagus Valdris",
                LeaderTitle = "Master of Magic",
                Headquarters = "Spellforge Academy, Arcane Isles",
                Members = new List<string> { "Wizards", "Sorcerers", "Enchanters", "Arcane Scholars" },
                Colors = new List<string> { "Purple", "Blue", "White" },
                Enemies = new List<string> { },
                Allies = new List<string> { "All Factions (for knowledge)" },
                ReputationReward = 60
            },
            new Faction
            {
                FactionId = 6,
                Name = "Dwarven Clans",
                Alignment = "Neutral Good",
                Description = "Proud dwarven kingdoms united by honor and clan tradition",
                LeaderName = "King Thorin Stonebeard",
                LeaderTitle = "High King of the Dwarves",
                Headquarters = "Ironforge Citadel, Ironhammer Kingdom",
                Members = new List<string> { "Dwarves", "Mountain Shepherds" },
                Colors = new List<string> { "Bronze", "Steel", "Brown" },
                Enemies = new List<string> { "Drow Empire", "Goblin Hordes" },
                Allies = new List<string> { "The Silver Alliance", "Elven Courts" },
                ReputationReward = 70
            },
            new Faction
            {
                FactionId = 7,
                Name = "Ranger's Council",
                Alignment = "Good",
                Description = "Elite warriors protecting the wild places of Aethermoor",
                LeaderName = "Ranger Captain Thorne",
                LeaderTitle = "Council Warden",
                Headquarters = "Sentinel Keep, Northmark Frontier",
                Members = new List<string> { "Rangers", "Scouts", "Hunters", "Beast Masters" },
                Colors = new List<string> { "Green", "Brown", "Silver" },
                Enemies = new List<string> { "Monster Hordes", "Dark Forces" },
                Allies = new List<string> { "The Silver Alliance", "Druidic Circle" },
                ReputationReward = 80
            },
            
            // ==================== EVIL ALIGNED ====================
            
            new Faction
            {
                FactionId = 8,
                Name = "Shadowlands Coalition",
                Alignment = "Evil",
                Description = "Undead and dark forces spreading corruption and death",
                LeaderName = "The Lich King Morthos",
                LeaderTitle = "Master of Death",
                Headquarters = "Blackthorn Citadel, The Shadowlands",
                Members = new List<string> { "Undead", "Dark Necromancers", "Death Knights", "Cultists" },
                Colors = new List<string> { "Black", "Purple", "Gray" },
                Enemies = new List<string> { "The Silver Alliance", "The Celestial Order", "All Living Beings" },
                Allies = new List<string> { "Demonfire Empire" },
                ReputationReward = -100
            },
            new Faction
            {
                FactionId = 9,
                Name = "Demonfire Empire",
                Alignment = "Chaotic Evil",
                Description = "Demonic forces of the abyss seeking to corrupt the world",
                LeaderName = "Archfiend Baltazar",
                LeaderTitle = "Lord of Flames",
                Headquarters = "Infernus, Demonfire Wastes",
                Members = new List<string> { "Demons", "Hellfire Cultists", "Corrupted Mortals", "Fire Elementals" },
                Colors = new List<string> { "Red", "Black", "Orange" },
                Enemies = new List<string> { "The Silver Alliance", "The Celestial Order", "All Good Beings" },
                Allies = new List<string> { "Shadowlands Coalition" },
                ReputationReward = -150
            },
            new Faction
            {
                FactionId = 10,
                Name = "Drow Empire",
                Alignment = "Neutral Evil",
                Description = "Dark elven civilization ruling the Underdark with tyranny",
                LeaderName = "Matriarch Lolth's Chosen",
                LeaderTitle = "Spider Queen's Voice",
                Headquarters = "Menzoberranzan, Underdark Abyss",
                Members = new List<string> { "Dark Elves", "Drow Soldiers", "Spider Cultists" },
                Colors = new List<string> { "Purple", "Black", "Silver" },
                Enemies = new List<string> { "Dwarven Clans", "Surface Elves", "The Silver Alliance" },
                Allies = new List<string> { "Evil Underdark Races" },
                ReputationReward = -80
            },
            new Faction
            {
                FactionId = 11,
                Name = "Goblin Hordes",
                Alignment = "Chaotic Neutral",
                Description = "Raiding goblin clans interested only in plunder and chaos",
                LeaderName = "Warlord Grakthak",
                LeaderTitle = "Chief of Clans",
                Headquarters = "Grakthak's Fortress, Various Goblin Settlements",
                Members = new List<string> { "Goblins", "Goblin Shamans", "Goblin Warriors" },
                Colors = new List<string> { "Green", "Red", "Yellow" },
                Enemies = new List<string> { "Dwarves", "Elves", "Civilized Kingdoms" },
                Allies = new List<string> { "Neutral Traders (sometimes)" },
                ReputationReward = -50
            },
            new Faction
            {
                FactionId = 12,
                Name = "Elven Courts",
                Alignment = "Good",
                Description = "Ancient and proud elven kingdoms of magic and wisdom",
                LeaderName = "Queen Aelindor Moonwhisper",
                LeaderTitle = "High Queen",
                Headquarters = "Silverleaf City, Emerald Vale",
                Members = new List<string> { "High Elves", "Wood Elves", "Moon Elves", "Star Elves" },
                Colors = new List<string> { "Silver", "Green", "Gold" },
                Enemies = new List<string> { "Drow Empire", "Demonfire Empire", "Goblin Hordes" },
                Allies = new List<string> { "The Silver Alliance", "Druidic Circle", "Dwarven Clans" },
                ReputationReward = 85
            },
            new Faction
            {
                FactionId = 13,
                Name = "Order of the Tempest",
                Alignment = "Neutral",
                Description = "Storm giants and sky dwellers maintaining order above the clouds",
                LeaderName = "Storm Lord Tempestus",
                LeaderTitle = "Lord of Thunder",
                Headquarters = "Stormhaven, Storm Islands",
                Members = new List<string> { "Storm Giants", "Air Elementals", "Storm Shamans", "Sky Knights" },
                Colors = new List<string> { "White", "Blue", "Gray" },
                Enemies = new List<string> { },
                Allies = new List<string> { "The Celestial Order" },
                ReputationReward = 65
            }
        };
    }
}

public class Faction
{
    public int FactionId { get; set; }
    public string Name { get; set; } = string.Empty;
    public string Alignment { get; set; } = string.Empty;  // Good/Evil/Neutral/LawfulChaotic
    public string Description { get; set; } = string.Empty;
    public string LeaderName { get; set; } = string.Empty;
    public string LeaderTitle { get; set; } = string.Empty;
    public string Headquarters { get; set; } = string.Empty;
    public List<string> Members { get; set; } = new();
    public List<string> Colors { get; set; } = new();
    public List<string> Enemies { get; set; } = new();
    public List<string> Allies { get; set; } = new();
    public int ReputationReward { get; set; }
    public int Reputation { get; set; } = 0;  // Player reputation with faction
    
    public bool IsAtWarWith(string factionName)
    {
        return Enemies.Contains(factionName);
    }
    
    public bool IsAlliedWith(string factionName)
    {
        return Allies.Contains(factionName);
    }
}

// ==================== LEGENDARY ITEMS & ARTIFACTS ====================

public static class LegendaryArtifacts
{
    public static List<Artifact> GetLegendaryArtifacts()
    {
        return new List<Artifact>
        {
            new Artifact
            {
                ArtifactId = 1,
                Name = "Excalibur",
                Type = "Legendary Sword",
                Description = "The holy blade of kings, infused with celestial light",
                PowerLevel = 100,
                LocationZone = "Royal Castle Valdemere",
                RequiredLevel = 40,
                Lore = "Forged by the Celestial Order to combat darkness"
            },
            new Artifact
            {
                ArtifactId = 2,
                Name = "Frostmourne",
                Type = "Legendary Axe",
                Description = "Cursed weapon of the Lich King, freezing everything it touches",
                PowerLevel = 95,
                LocationZone = "Blackthorn Citadel",
                RequiredLevel = 45,
                Lore = "Created from the cold of the Underdark itself"
            },
            new Artifact
            {
                ArtifactId = 3,
                Name = "Crown of Eternal Wisdom",
                Type = "Legendary Crown",
                Description = "Grants knowledge of all magics and ancient secrets",
                PowerLevel = 90,
                LocationZone = "Spellforge Academy",
                RequiredLevel = 35,
                Lore = "Worn by the greatest mages of Aethermoor"
            },
            new Artifact
            {
                ArtifactId = 4,
                Name = "Dragonsoul Armor",
                Type = "Legendary Armor Set",
                Description = "Impervious to damage, forged from dragon hide",
                PowerLevel = 92,
                LocationZone = "Chromatic Spire",
                RequiredLevel = 38,
                Lore = "Created from defeated ancient dragons"
            },
            new Artifact
            {
                ArtifactId = 5,
                Name = "The Amulet of Aethermoor",
                Type = "Legendary Amulet",
                Description = "Mysterious artifact said to hold the power to reshape the world",
                PowerLevel = 100,
                LocationZone = "Unknown",
                RequiredLevel = 50,
                Lore = "Origin unknown, sought by all major powers"
            }
        };
    }
}

public class Artifact
{
    public int ArtifactId { get; set; }
    public string Name { get; set; } = string.Empty;
    public string Type { get; set; } = string.Empty;
    public string Description { get; set; } = string.Empty;
    public int PowerLevel { get; set; }
    public string LocationZone { get; set; } = string.Empty;
    public int RequiredLevel { get; set; }
    public string Lore { get; set; } = string.Empty;
}

// ==================== WORLD LORE & PROPHECIES ====================

public static class WorldLore
{
    public const string CreationMyth = @"
In the beginning, there was only void and chaos. The Celestial Order created structure 
from nothingness, molding the world of Aethermoor from divine essence. They created 
the races to be stewards of creation, but pride and greed corrupted many.
    ";
    
    public const string AncientProphecy = @"
'When stars align and darkness falls,
A champion shall heed the ancient calls.
The chosen one shall bridge the divide,
And with their strength, the world provide.
But beware the power within their core,
For they may become that which they deplore.'
    ";
    
    public const string CurseOfTheLichKing = @"
Morthos, once a great mage, sought immortality through forbidden necromancy.
He was cursed, transformed into an undead tyrant, forever spreading his corruption.
His goal: to turn all of Aethermoor into a lifeless kingdom of death.
    ";
    
    public const string TheDemonIncursion = @"
The seal containing the demonic realms weakens with each passing age.
Archfiend Baltazar gathers his forces, seeking to break through and consume
the world of the living in an eternal inferno of chaos and destruction.
    ";
}
