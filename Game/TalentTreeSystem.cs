namespace RPGMenuSystem.Game;

public enum TalentTreeType
{
    Class,
    Specialization,
    General,
    Racial
}

public class TalentNode
{
    public int Id { get; set; }
    public string Name { get; set; } = string.Empty;
    public string Description { get; set; } = string.Empty;
    public int MaxRank { get; set; } = 1;
    public int CurrentRank { get; set; } = 0;
    public int RequiredLevel { get; set; }
    public int RequiredPoints { get; set; }
    public List<int> PrerequisiteNodes { get; set; } = new();
    public TalentEffect Effect { get; set; } = new();
    public int Row { get; set; }
    public int Column { get; set; }
    
    public bool IsAvailable(int playerLevel, int spentPoints, Dictionary<int, int> acquiredTalents)
    {
        if (playerLevel < RequiredLevel) return false;
        if (spentPoints < RequiredPoints) return false;
        
        foreach (var prereq in PrerequisiteNodes)
        {
            if (!acquiredTalents.ContainsKey(prereq) || acquiredTalents[prereq] == 0)
                return false;
        }
        
        return true;
    }
}

public class TalentEffect
{
    public Dictionary<string, float> StatModifiers { get; set; } = new();
    public List<string> UnlockedAbilities { get; set; } = new();
    public Dictionary<string, float> AbilityModifiers { get; set; } = new();
    public List<string> PassiveEffects { get; set; } = new();
}

public class TalentTree
{
    public string Name { get; set; } = string.Empty;
    public TalentTreeType Type { get; set; }
    public CharacterClass? AssociatedClass { get; set; }
    public ClassSpecialization? AssociatedSpec { get; set; }
    public List<TalentNode> Nodes { get; set; } = new();
    public int PointsSpent { get; set; }
    public int MaxPoints { get; set; } = 51;
    
    public bool CanAllocatePoint(TalentNode node, int playerLevel, Dictionary<int, int> acquiredTalents)
    {
        if (PointsSpent >= MaxPoints) return false;
        if (node.CurrentRank >= node.MaxRank) return false;
        if (!node.IsAvailable(playerLevel, PointsSpent, acquiredTalents)) return false;
        
        return true;
    }
    
    public void AllocatePoint(TalentNode node)
    {
        node.CurrentRank++;
        PointsSpent++;
    }
    
    public void RemovePoint(TalentNode node)
    {
        if (node.CurrentRank > 0)
        {
            node.CurrentRank--;
            PointsSpent--;
        }
    }
    
    public void ResetTree()
    {
        foreach (var node in Nodes)
        {
            node.CurrentRank = 0;
        }
        PointsSpent = 0;
    }
}

public class SkillTreeManager
{
    public List<TalentTree> Trees { get; set; } = new();
    public int AvailablePoints { get; set; }
    
    public void AddPointsOnLevelUp(int level)
    {
        AvailablePoints++;
    }
    
    public bool SpendPoint(TalentTree tree, TalentNode node, int playerLevel)
    {
        if (AvailablePoints <= 0) return false;
        
        var acquiredTalents = GetAcquiredTalents(tree);
        if (tree.CanAllocatePoint(node, playerLevel, acquiredTalents))
        {
            tree.AllocatePoint(node);
            AvailablePoints--;
            return true;
        }
        
        return false;
    }
    
    public Dictionary<int, int> GetAcquiredTalents(TalentTree tree)
    {
        var acquired = new Dictionary<int, int>();
        foreach (var node in tree.Nodes)
        {
            if (node.CurrentRank > 0)
            {
                acquired[node.Id] = node.CurrentRank;
            }
        }
        return acquired;
    }
    
    public Dictionary<string, float> GetAllStatModifiers()
    {
        var stats = new Dictionary<string, float>();
        
        foreach (var tree in Trees)
        {
            foreach (var node in tree.Nodes)
            {
                if (node.CurrentRank > 0)
                {
                    foreach (var stat in node.Effect.StatModifiers)
                    {
                        if (!stats.ContainsKey(stat.Key))
                            stats[stat.Key] = 0;
                        stats[stat.Key] += stat.Value * node.CurrentRank;
                    }
                }
            }
        }
        
        return stats;
    }
    
    public static TalentTree CreateWarriorArmsTree()
    {
        var tree = new TalentTree
        {
            Name = "Arms",
            Type = TalentTreeType.Specialization,
            AssociatedSpec = ClassSpecialization.WarriorArms,
            Nodes = new List<TalentNode>
            {
                new TalentNode { Id = 1, Name = "Improved Heroic Strike", Description = "Increases damage of Heroic Strike by 5% per rank", MaxRank = 3, RequiredLevel = 10, Row = 0, Column = 0, Effect = new TalentEffect { AbilityModifiers = new Dictionary<string, float> { { "HeroicStrike", 0.05f } } } },
                new TalentNode { Id = 2, Name = "Deflection", Description = "Increases Parry chance by 1% per rank", MaxRank = 5, RequiredLevel = 10, Row = 0, Column = 1, Effect = new TalentEffect { StatModifiers = new Dictionary<string, float> { { "Parry", 1f } } } },
                new TalentNode { Id = 3, Name = "Improved Rend", Description = "Increases damage of Rend by 10% per rank", MaxRank = 3, RequiredLevel = 10, Row = 0, Column = 2, Effect = new TalentEffect { AbilityModifiers = new Dictionary<string, float> { { "Rend", 0.1f } } } },
                new TalentNode { Id = 4, Name = "Tactical Mastery", Description = "Retain up to 5 rage per rank after switching stances", MaxRank = 5, RequiredLevel = 15, RequiredPoints = 5, Row = 1, Column = 0, Effect = new TalentEffect { PassiveEffects = new List<string> { "RetainRage" } } },
                new TalentNode { Id = 5, Name = "Deep Wounds", Description = "Critical strikes cause target to bleed", MaxRank = 3, RequiredLevel = 20, RequiredPoints = 10, Row = 2, Column = 1, PrerequisiteNodes = new List<int> { 2 }, Effect = new TalentEffect { PassiveEffects = new List<string> { "BleedOnCrit" } } },
                new TalentNode { Id = 6, Name = "Sweeping Strikes", Description = "Your next 5 melee attacks strike an additional target", MaxRank = 1, RequiredLevel = 30, RequiredPoints = 20, Row = 4, Column = 1, Effect = new TalentEffect { UnlockedAbilities = new List<string> { "SweepingStrikes" } } },
                new TalentNode { Id = 7, Name = "Mortal Strike", Description = "A vicious strike that deals weapon damage and reduces healing", MaxRank = 1, RequiredLevel = 40, RequiredPoints = 30, Row = 6, Column = 1, PrerequisiteNodes = new List<int> { 6 }, Effect = new TalentEffect { UnlockedAbilities = new List<string> { "MortalStrike" } } }
            }
        };
        
        return tree;
    }
}
