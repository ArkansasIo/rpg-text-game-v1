namespace RPGMenuSystem.Game;

public enum HousingType
{
    Small,
    Medium,
    Large,
    Mansion,
    Castle,
    GuildHall
}

public class PlayerHouse
{
    public int Id { get; set; }
    public string Name { get; set; } = "My House";
    public HousingType Type { get; set; }
    public int MaxDecorations { get; set; } = 50;
    public List<Decoration> PlacedDecorations { get; set; } = new();
    public int StorageSlots { get; set; } = 100;
    public GridInventory Storage { get; set; } = new(10, 10);
    public bool HasCraftingStation { get; set; }
    public bool HasBank { get; set; }
    public bool HasVendor { get; set; }
    public List<string> AllowedVisitors { get; set; } = new();
    public bool IsPublic { get; set; }
    
    public bool CanPlaceDecoration()
    {
        return PlacedDecorations.Count < MaxDecorations;
    }
}

public class Decoration
{
    public int Id { get; set; }
    public string Name { get; set; } = string.Empty;
    public DecorationCategory Category { get; set; }
    public Vector3 Position { get; set; }
    public Vector3 Rotation { get; set; }
    public bool IsWallMounted { get; set; }
    public bool IsFloorItem { get; set; }
}

public enum DecorationCategory
{
    Furniture,
    Lighting,
    Decoration,
    Trophy,
    Plant,
    Storage,
    Crafting
}

public struct Vector3
{
    public float X { get; set; }
    public float Y { get; set; }
    public float Z { get; set; }
}

public class CompanionSystem
{
    public List<Companion> RecruitedCompanions { get; set; } = new();
    public List<Companion> ActiveParty { get; set; } = new();
    public int MaxActiveCompanions { get; set; } = 3;
    
    public bool RecruitCompanion(Companion companion)
    {
        if (!RecruitedCompanions.Contains(companion))
        {
            RecruitedCompanions.Add(companion);
            return true;
        }
        return false;
    }
    
    public bool AddToParty(Companion companion)
    {
        if (ActiveParty.Count < MaxActiveCompanions && !ActiveParty.Contains(companion))
        {
            ActiveParty.Add(companion);
            return true;
        }
        return false;
    }
}

public class Companion
{
    public int Id { get; set; }
    public string Name { get; set; } = string.Empty;
    public CharacterClass Class { get; set; }
    public int Level { get; set; } = 1;
    public int Health { get; set; }
    public int MaxHealth { get; set; }
    public int Loyalty { get; set; } = 50; // 0-100
    
    // Stats
    public int Attack { get; set; }
    public int Defense { get; set; }
    public int MagicPower { get; set; }
    
    // Equipment
    public AdvancedEquipment Equipment { get; set; } = new();
    
    // Personal quest
    public Quest? PersonalQuest { get; set; }
    
    // AI Behavior
    public CompanionBehavior Behavior { get; set; } = CompanionBehavior.Balanced;
    
    // Abilities
    public List<string> Abilities { get; set; } = new();
    
    public void GainLoyalty(int amount)
    {
        Loyalty = Math.Min(100, Loyalty + amount);
    }
    
    public void LoseLoyalty(int amount)
    {
        Loyalty = Math.Max(0, Loyalty - amount);
    }
}

public enum CompanionBehavior
{
    Aggressive,
    Defensive,
    Balanced,
    Passive,
    Healing,
    Support
}

public class DialogueSystem
{
    public List<DialogueNode> CurrentDialogue { get; set; } = new();
    public int CurrentNodeIndex { get; set; } = 0;
    
    public DialogueNode? GetCurrentNode()
    {
        if (CurrentNodeIndex >= 0 && CurrentNodeIndex < CurrentDialogue.Count)
        {
            return CurrentDialogue[CurrentNodeIndex];
        }
        return null;
    }
    
    public void SelectChoice(int choiceIndex)
    {
        var node = GetCurrentNode();
        if (node != null && choiceIndex >= 0 && choiceIndex < node.Choices.Count)
        {
            var choice = node.Choices[choiceIndex];
            CurrentNodeIndex = choice.NextNodeIndex;
            
            // Execute any actions
            choice.OnSelected?.Invoke();
        }
    }
}

public class DialogueNode
{
    public int Id { get; set; }
    public string SpeakerName { get; set; } = string.Empty;
    public string Text { get; set; } = string.Empty;
    public List<DialogueChoice> Choices { get; set; } = new();
    public string EmotionTag { get; set; } = "Neutral";
}

public class DialogueChoice
{
    public string Text { get; set; } = string.Empty;
    public int NextNodeIndex { get; set; }
    public bool RequiresSkillCheck { get; set; }
    public string RequiredSkill { get; set; } = string.Empty;
    public int RequiredSkillLevel { get; set; }
    public Action? OnSelected { get; set; }
    public int MoralityImpact { get; set; } // Negative = Evil, Positive = Good
}

public class MoralitySystem
{
    public int Alignment { get; set; } = 0; // -100 (Evil) to 100 (Good)
    public int Karma { get; set; } = 0;
    public List<string> MoralChoices { get; set; } = new();
    
    public AlignmentType GetAlignment()
    {
        if (Alignment >= 50) return AlignmentType.Good;
        if (Alignment >= 10) return AlignmentType.Lawful;
        if (Alignment >= -10) return AlignmentType.Neutral;
        if (Alignment >= -50) return AlignmentType.Chaotic;
        return AlignmentType.Evil;
    }
    
    public void AddMoralChoice(string description, int alignmentChange)
    {
        MoralChoices.Add(description);
        Alignment = Math.Max(-100, Math.Min(100, Alignment + alignmentChange));
    }
}

public enum AlignmentType
{
    Good,
    Lawful,
    Neutral,
    Chaotic,
    Evil
}

public class PetSystem
{
    public List<Pet> Pets { get; set; } = new();
    public Pet? ActivePet { get; set; }
    public int MaxPets { get; set; } = 50;
    
    public bool AddPet(Pet pet)
    {
        if (Pets.Count < MaxPets)
        {
            Pets.Add(pet);
            return true;
        }
        return false;
    }
    
    public void SummonPet(Pet pet)
    {
        if (ActivePet != null)
        {
            DismissPet();
        }
        ActivePet = pet;
    }
    
    public void DismissPet()
    {
        ActivePet = null;
    }
}

public class Pet
{
    public int Id { get; set; }
    public string Name { get; set; } = string.Empty;
    public PetType Type { get; set; }
    public int Level { get; set; } = 1;
    public int Happiness { get; set; } = 100;
    public List<string> Abilities { get; set; } = new();
    public PetBehavior Behavior { get; set; } = PetBehavior.Defensive;
}

public enum PetType
{
    Combat,
    Companion,
    Mount,
    Gathering,
    Vanity
}

public enum PetBehavior
{
    Aggressive,
    Defensive,
    Passive,
    Assist
}
