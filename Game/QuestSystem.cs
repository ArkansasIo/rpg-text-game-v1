namespace RPGMenuSystem.Game;

public class Quest
{
    public string Id { get; set; } = string.Empty;
    public string Name { get; set; } = string.Empty;
    public string Description { get; set; } = string.Empty;
    public QuestStatus Status { get; set; } = QuestStatus.Available;
    public int RewardGold { get; set; }
    public int RewardXP { get; set; }
    public List<QuestObjective> Objectives { get; set; } = new();
}

public enum QuestStatus
{
    Available,
    Active,
    Completed,
    Failed
}

public class QuestObjective
{
    public string Description { get; set; } = string.Empty;
    public int CurrentProgress { get; set; }
    public int RequiredProgress { get; set; }
    public bool IsCompleted => CurrentProgress >= RequiredProgress;
}

public class QuestManager
{
    private List<Quest> _quests = new();

    public QuestManager()
    {
        InitializeQuests();
    }

    private void InitializeQuests()
    {
        _quests.Add(new Quest
        {
            Id = "quest_001",
            Name = "Defeat the Dragon",
            Description = "A fierce dragon has been terrorizing the nearby village. Defeat it!",
            Status = QuestStatus.Active,
            RewardGold = 500,
            RewardXP = 1000,
            Objectives = new List<QuestObjective>
            {
                new QuestObjective { Description = "Defeat the Ancient Dragon", CurrentProgress = 0, RequiredProgress = 1 }
            }
        });

        _quests.Add(new Quest
        {
            Id = "quest_002",
            Name = "Find the Lost Sword",
            Description = "The legendary sword has been lost in the dungeon. Retrieve it.",
            Status = QuestStatus.Active,
            RewardGold = 300,
            RewardXP = 500,
            Objectives = new List<QuestObjective>
            {
                new QuestObjective { Description = "Search the dungeon", CurrentProgress = 0, RequiredProgress = 1 },
                new QuestObjective { Description = "Retrieve the sword", CurrentProgress = 0, RequiredProgress = 1 }
            }
        });

        _quests.Add(new Quest
        {
            Id = "quest_003",
            Name = "Save the Village",
            Description = "Goblins are attacking the village. Defeat 5 goblins.",
            Status = QuestStatus.Completed,
            RewardGold = 100,
            RewardXP = 200,
            Objectives = new List<QuestObjective>
            {
                new QuestObjective { Description = "Defeat goblins", CurrentProgress = 5, RequiredProgress = 5 }
            }
        });

        _quests.Add(new Quest
        {
            Id = "quest_004",
            Name = "Collect Herbs",
            Description = "The healer needs healing herbs. Collect 10 herbs.",
            Status = QuestStatus.Available,
            RewardGold = 50,
            RewardXP = 100,
            Objectives = new List<QuestObjective>
            {
                new QuestObjective { Description = "Collect herbs", CurrentProgress = 0, RequiredProgress = 10 }
            }
        });
    }

    public List<Quest> GetAllQuests() => _quests;
    public List<Quest> GetActiveQuests() => _quests.Where(q => q.Status == QuestStatus.Active).ToList();
    public List<Quest> GetCompletedQuests() => _quests.Where(q => q.Status == QuestStatus.Completed).ToList();
    public List<Quest> GetAvailableQuests() => _quests.Where(q => q.Status == QuestStatus.Available).ToList();

    public void AcceptQuest(string questId)
    {
        var quest = _quests.FirstOrDefault(q => q.Id == questId);
        if (quest != null && quest.Status == QuestStatus.Available)
        {
            quest.Status = QuestStatus.Active;
        }
    }

    public void CompleteQuest(string questId)
    {
        var quest = _quests.FirstOrDefault(q => q.Id == questId);
        if (quest != null && quest.Status == QuestStatus.Active)
        {
            quest.Status = QuestStatus.Completed;
        }
    }
}
