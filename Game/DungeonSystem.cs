namespace RPGMenuSystem.Game;

public enum DungeonDifficulty
{
    Normal,
    Heroic,
    Mythic,
    MythicPlus
}

public enum DungeonType
{
    StandardDungeon,
    Raid,
    Trial,
    Challenge,
    Scenario,
    WorldBoss
}

public class Dungeon
{
    public int Id { get; set; }
    public string Name { get; set; } = string.Empty;
    public DungeonType Type { get; set; }
    public string Description { get; set; } = string.Empty;
    public int MinLevel { get; set; }
    public int MaxLevel { get; set; }
    public int MinPlayers { get; set; }
    public int MaxPlayers { get; set; }
    public List<DungeonDifficulty> AvailableDifficulties { get; set; } = new();
    public List<DungeonBoss> Bosses { get; set; } = new();
    public List<string> Rewards { get; set; } = new();
    public int EstimatedTime { get; set; } // in minutes
    public string Location { get; set; } = string.Empty;
    
    public static List<Dungeon> GetDungeons()
    {
        return new List<Dungeon>
        {
            // Low Level Dungeons
            new Dungeon
            {
                Id = 1,
                Name = "The Deadmines",
                Type = DungeonType.StandardDungeon,
                Description = "An abandoned mine taken over by the Defias Brotherhood",
                MinLevel = 15,
                MaxLevel = 21,
                MinPlayers = 5,
                MaxPlayers = 5,
                AvailableDifficulties = new List<DungeonDifficulty> { DungeonDifficulty.Normal, DungeonDifficulty.Heroic },
                Bosses = new List<DungeonBoss>
                {
                    new DungeonBoss { Name = "Rhahk'Zor", Level = 17 },
                    new DungeonBoss { Name = "Sneed", Level = 18 },
                    new DungeonBoss { Name = "Gilnid", Level = 19 },
                    new DungeonBoss { Name = "Mr. Smite", Level = 20 },
                    new DungeonBoss { Name = "Edwin VanCleef", Level = 21 }
                },
                Rewards = new List<string> { "Rare Weapons", "Armor", "Gold" },
                EstimatedTime = 30,
                Location = "Westfall"
            },
            new Dungeon
            {
                Id = 2,
                Name = "Wailing Caverns",
                Type = DungeonType.StandardDungeon,
                Description = "A corrupted underground cavern",
                MinLevel = 15,
                MaxLevel = 25,
                MinPlayers = 5,
                MaxPlayers = 5,
                AvailableDifficulties = new List<DungeonDifficulty> { DungeonDifficulty.Normal, DungeonDifficulty.Heroic },
                Bosses = new List<DungeonBoss>
                {
                    new DungeonBoss { Name = "Lady Anacondra", Level = 18 },
                    new DungeonBoss { Name = "Lord Pythas", Level = 19 },
                    new DungeonBoss { Name = "Lord Cobrahn", Level = 20 },
                    new DungeonBoss { Name = "Mutanus the Devourer", Level = 22 }
                },
                Rewards = new List<string> { "Druid Gear", "Leather Armor" },
                EstimatedTime = 45,
                Location = "The Barrens"
            },
            
            // Mid Level Dungeons
            new Dungeon
            {
                Id = 3,
                Name = "Scarlet Monastery",
                Type = DungeonType.StandardDungeon,
                Description = "A cathedral overtaken by zealous crusaders",
                MinLevel = 30,
                MaxLevel = 45,
                MinPlayers = 5,
                MaxPlayers = 5,
                AvailableDifficulties = new List<DungeonDifficulty> { DungeonDifficulty.Normal, DungeonDifficulty.Heroic },
                Bosses = new List<DungeonBoss>
                {
                    new DungeonBoss { Name = "Interrogator Vishas", Level = 32 },
                    new DungeonBoss { Name = "High Inquisitor Whitemane", Level = 34 },
                    new DungeonBoss { Name = "Scarlet Commander Mograine", Level = 34 },
                    new DungeonBoss { Name = "Herod", Level = 36 }
                },
                Rewards = new List<string> { "Plate Armor", "Rare Weapons", "Tabards" },
                EstimatedTime = 40,
                Location = "Tirisfal Glades"
            },
            
            // High Level Dungeons
            new Dungeon
            {
                Id = 4,
                Name = "Stratholme",
                Type = DungeonType.StandardDungeon,
                Description = "A city plagued by the undead scourge",
                MinLevel = 55,
                MaxLevel = 60,
                MinPlayers = 5,
                MaxPlayers = 5,
                AvailableDifficulties = new List<DungeonDifficulty> { DungeonDifficulty.Normal, DungeonDifficulty.Heroic },
                Bosses = new List<DungeonBoss>
                {
                    new DungeonBoss { Name = "The Unforgiven", Level = 57 },
                    new DungeonBoss { Name = "Baroness Anastari", Level = 58 },
                    new DungeonBoss { Name = "Maleki the Pallid", Level = 58 },
                    new DungeonBoss { Name = "Baron Rivendare", Level = 60 }
                },
                Rewards = new List<string> { "Epic Mounts", "Tier 0.5 Gear", "Runecloth" },
                EstimatedTime = 60,
                Location = "Eastern Plaguelands"
            },
            
            // Raids
            new Dungeon
            {
                Id = 5,
                Name = "Molten Core",
                Type = DungeonType.Raid,
                Description = "A volcanic lair beneath Blackrock Mountain",
                MinLevel = 60,
                MaxLevel = 60,
                MinPlayers = 20,
                MaxPlayers = 40,
                AvailableDifficulties = new List<DungeonDifficulty> { DungeonDifficulty.Normal },
                Bosses = new List<DungeonBoss>
                {
                    new DungeonBoss { Name = "Lucifron", Level = 60 },
                    new DungeonBoss { Name = "Magmadar", Level = 60 },
                    new DungeonBoss { Name = "Gehennas", Level = 60 },
                    new DungeonBoss { Name = "Garr", Level = 60 },
                    new DungeonBoss { Name = "Baron Geddon", Level = 60 },
                    new DungeonBoss { Name = "Shazzrah", Level = 60 },
                    new DungeonBoss { Name = "Sulfuron Harbinger", Level = 60 },
                    new DungeonBoss { Name = "Golemagg the Incinerator", Level = 60 },
                    new DungeonBoss { Name = "Majordomo Executus", Level = 60 },
                    new DungeonBoss { Name = "Ragnaros the Firelord", Level = 60, IsRaidBoss = true }
                },
                Rewards = new List<string> { "Tier 1 Armor", "Legendary Weapons", "Sulfuras" },
                EstimatedTime = 180,
                Location = "Blackrock Mountain"
            },
            new Dungeon
            {
                Id = 6,
                Name = "Blackwing Lair",
                Type = DungeonType.Raid,
                Description = "The lair of the black dragon Nefarian",
                MinLevel = 60,
                MaxLevel = 60,
                MinPlayers = 40,
                MaxPlayers = 40,
                AvailableDifficulties = new List<DungeonDifficulty> { DungeonDifficulty.Normal },
                Bosses = new List<DungeonBoss>
                {
                    new DungeonBoss { Name = "Razorgore the Untamed", Level = 60 },
                    new DungeonBoss { Name = "Vaelastrasz the Corrupt", Level = 60 },
                    new DungeonBoss { Name = "Broodlord Lashlayer", Level = 60 },
                    new DungeonBoss { Name = "Firemaw", Level = 60 },
                    new DungeonBoss { Name = "Ebonroc", Level = 60 },
                    new DungeonBoss { Name = "Flamegor", Level = 60 },
                    new DungeonBoss { Name = "Chromaggus", Level = 60 },
                    new DungeonBoss { Name = "Nefarian", Level = 60, IsRaidBoss = true }
                },
                Rewards = new List<string> { "Tier 2 Armor", "Dragon Weapons", "Legendary Materials" },
                EstimatedTime = 240,
                Location = "Blackrock Mountain"
            },
            
            // Trials/Challenge Dungeons
            new Dungeon
            {
                Id = 7,
                Name = "Trial of the Crusader",
                Type = DungeonType.Trial,
                Description = "Prove yourself in the Argent Tournament",
                MinLevel = 80,
                MaxLevel = 80,
                MinPlayers = 10,
                MaxPlayers = 25,
                AvailableDifficulties = new List<DungeonDifficulty> { DungeonDifficulty.Normal, DungeonDifficulty.Heroic },
                Bosses = new List<DungeonBoss>
                {
                    new DungeonBoss { Name = "The Beasts of Northrend", Level = 80 },
                    new DungeonBoss { Name = "Lord Jaraxxus", Level = 80 },
                    new DungeonBoss { Name = "Faction Champions", Level = 80 },
                    new DungeonBoss { Name = "The Twin Val'kyr", Level = 80 },
                    new DungeonBoss { Name = "Anub'arak", Level = 80, IsRaidBoss = true }
                },
                Rewards = new List<string> { "Tier 9 Armor", "Tribute Chest Items" },
                EstimatedTime = 90,
                Location = "Icecrown"
            },
            new Dungeon
            {
                Id = 8,
                Name = "The Maw of Souls",
                Type = DungeonType.Challenge,
                Description = "Navigate the cursed ship through the afterlife",
                MinLevel = 110,
                MaxLevel = 110,
                MinPlayers = 5,
                MaxPlayers = 5,
                AvailableDifficulties = new List<DungeonDifficulty> { DungeonDifficulty.Normal, DungeonDifficulty.Heroic, DungeonDifficulty.Mythic, DungeonDifficulty.MythicPlus },
                Bosses = new List<DungeonBoss>
                {
                    new DungeonBoss { Name = "Ymiron the Fallen King", Level = 110 },
                    new DungeonBoss { Name = "Harbaron", Level = 110 },
                    new DungeonBoss { Name = "Helya", Level = 110, IsRaidBoss = true }
                },
                Rewards = new List<string> { "Mythic+ Gear", "Artifact Power" },
                EstimatedTime = 25,
                Location = "Helheim"
            }
        };
    }
}

public class DungeonBoss
{
    public string Name { get; set; } = string.Empty;
    public int Level { get; set; }
    public int Health { get; set; }
    public bool IsRaidBoss { get; set; }
    public List<string> Abilities { get; set; } = new();
    public List<AdvancedItem> LootTable { get; set; } = new();
}

public class DungeonInstance
{
    public Dungeon Dungeon { get; set; } = null!;
    public DungeonDifficulty Difficulty { get; set; }
    public List<Player> Party { get; set; } = new();
    public int CurrentBossIndex { get; set; }
    public DateTime StartTime { get; set; }
    public int DeathCount { get; set; }
    public bool IsCompleted { get; set; }
    
    public TimeSpan GetElapsedTime()
    {
        return DateTime.Now - StartTime;
    }
    
    public DungeonBoss? GetCurrentBoss()
    {
        if (CurrentBossIndex < Dungeon.Bosses.Count)
        {
            return Dungeon.Bosses[CurrentBossIndex];
        }
        return null;
    }
    
    public void DefeatBoss()
    {
        CurrentBossIndex++;
        if (CurrentBossIndex >= Dungeon.Bosses.Count)
        {
            IsCompleted = true;
        }
    }
}
