namespace RPGMenuSystem.Game;

public class GuildSystem
{
    public string Name { get; set; } = string.Empty;
    public int Level { get; set; } = 1;
    public int MemberCount { get; set; }
    public int MaxMembers => 100 + (Level * 50);
    public int GuildGold { get; set; }
    public List<string> GuildPerks { get; set; } = new();
    public Dictionary<string, int> GuildAchievements { get; set; } = new();
    public string GuildTabard { get; set; } = string.Empty;
}

public class AchievementSystem
{
    public List<Achievement> CompletedAchievements { get; set; } = new();
    public int TotalPoints => CompletedAchievements.Sum(a => a.Points);
    
    public static List<Achievement> GetAllAchievements()
    {
        return new List<Achievement>
        {
            new Achievement { Id = 1, Name = "First Kill", Description = "Defeat your first enemy", Points = 10 },
            new Achievement { Id = 2, Name = "Level 10", Description = "Reach level 10", Points = 10 },
            new Achievement { Id = 3, Name = "Explorer", Description = "Discover 20 zones", Points = 25 },
            new Achievement { Id = 4, Name = "Dungeon Master", Description = "Complete 10 dungeons", Points = 50 },
            new Achievement { Id = 5, Name = "Raid Leader", Description = "Complete your first raid", Points = 100 },
            new Achievement { Id = 6, Name = "Wealthy", Description = "Accumulate 10,000 gold", Points = 30 },
            new Achievement { Id = 7, Name = "Fully Equipped", Description = "Have epic item in every slot", Points = 75 },
            new Achievement { Id = 8, Name = "Dragon Slayer", Description = "Defeat an ancient dragon", Points = 100 },
            new Achievement { Id = 9, Name = "Max Level", Description = "Reach maximum level", Points = 200 },
            new Achievement { Id = 10, Name = "Legendary", Description = "Obtain a legendary item", Points = 150 }
        };
    }
}

public class Achievement
{
    public int Id { get; set; }
    public string Name { get; set; } = string.Empty;
    public string Description { get; set; } = string.Empty;
    public int Points { get; set; }
    public DateTime? CompletedDate { get; set; }
    public bool IsCompleted => CompletedDate.HasValue;
}

public class CraftingSystem
{
    public enum Profession
    {
        Blacksmithing,
        Alchemy,
        Enchanting,
        Engineering,
        Herbalism,
        Mining,
        Skinning,
        Tailoring,
        Leatherworking,
        Jewelcrafting,
        Inscription,
        Cooking,
        FirstAid,
        Fishing
    }

    public class ProfessionSkill
    {
        public Profession Profession { get; set; }
        public int SkillLevel { get; set; }
        public int MaxSkill { get; set; } = 300;
        public List<Recipe> KnownRecipes { get; set; } = new();
    }

    public class Recipe
    {
        public int Id { get; set; }
        public string Name { get; set; } = string.Empty;
        public Profession RequiredProfession { get; set; }
        public int RequiredSkill { get; set; }
        public Dictionary<string, int> Materials { get; set; } = new();
        public AdvancedItem CraftedItem { get; set; } = null!;
    }
}

public class PartySystem
{
    public List<Player> Members { get; set; } = new();
    public int MaxMembers { get; set; } = 5;
    public Player? Leader { get; set; }
    public LootDistribution LootMode { get; set; } = LootDistribution.GroupLoot;

    public enum LootDistribution
    {
        FreeForAll,
        RoundRobin,
        GroupLoot,
        MasterLooter,
        NeedBeforeGreed
    }

    public bool AddMember(Player player)
    {
        if (Members.Count < MaxMembers)
        {
            Members.Add(player);
            if (Members.Count == 1)
                Leader = player;
            return true;
        }
        return false;
    }

    public void RemoveMember(Player player)
    {
        Members.Remove(player);
        if (Leader == player && Members.Count > 0)
        {
            Leader = Members[0];
        }
    }

    public int GetAverageLevel()
    {
        return Members.Count > 0 ? (int)Members.Average(m => m.Level) : 0;
    }
}

public class RaidSystem : PartySystem
{
    public RaidSystem()
    {
        MaxMembers = 40;
    }

    public List<PartySystem> RaidGroups { get; set; } = new();
    
    public void OrganizeIntoGroups()
    {
        RaidGroups.Clear();
        for (int i = 0; i < Members.Count; i += 5)
        {
            var group = new PartySystem();
            for (int j = 0; j < 5 && (i + j) < Members.Count; j++)
            {
                group.AddMember(Members[i + j]);
            }
            RaidGroups.Add(group);
        }
    }
}

public class PvPSystem
{
    public int HonorPoints { get; set; }
    public int ArenaRating { get; set; } = 1500;
    public int Kills { get; set; }
    public int Deaths { get; set; }
    public PvPRank Rank { get; set; } = PvPRank.Scout;
    
    public enum PvPRank
    {
        Scout,
        Grunt,
        Sergeant,
        Champion,
        Warlord,
        HighWarlord,
        Gladiator,
        Duelist,
        Rival,
        Challenger
    }

    public float KDRatio => Deaths > 0 ? (float)Kills / Deaths : Kills;
}

public class ReputationSystem
{
    public Dictionary<string, int> Factions { get; set; } = new();
    
    public enum ReputationLevel
    {
        Hated = 0,
        Hostile = 3000,
        Unfriendly = 6000,
        Neutral = 9000,
        Friendly = 12000,
        Honored = 18000,
        Revered = 24000,
        Exalted = 30000
    }

    public ReputationLevel GetReputationLevel(string faction)
    {
        if (!Factions.ContainsKey(faction))
            return ReputationLevel.Neutral;

        int rep = Factions[faction];
        
        if (rep >= 30000) return ReputationLevel.Exalted;
        if (rep >= 24000) return ReputationLevel.Revered;
        if (rep >= 18000) return ReputationLevel.Honored;
        if (rep >= 12000) return ReputationLevel.Friendly;
        if (rep >= 9000) return ReputationLevel.Neutral;
        if (rep >= 6000) return ReputationLevel.Unfriendly;
        if (rep >= 3000) return ReputationLevel.Hostile;
        return ReputationLevel.Hated;
    }

    public void AddReputation(string faction, int amount)
    {
        if (!Factions.ContainsKey(faction))
            Factions[faction] = 9000; // Start at Neutral

        Factions[faction] = Math.Min(30000, Math.Max(0, Factions[faction] + amount));
    }
}

public class MountSystem
{
    public List<Mount> OwnedMounts { get; set; } = new();
    public Mount? ActiveMount { get; set; }

    public class Mount
    {
        public int Id { get; set; }
        public string Name { get; set; } = string.Empty;
        public MountType Type { get; set; }
        public int SpeedBonus { get; set; } = 60; // Percentage
        public int RequiredLevel { get; set; }
        public bool CanFly { get; set; }
        public string Description { get; set; } = string.Empty;
    }

    public enum MountType
    {
        Ground,
        Flying,
        Aquatic,
        Special
    }
}
