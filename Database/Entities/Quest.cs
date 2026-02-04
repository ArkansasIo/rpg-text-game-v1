using System;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace RPGMenuSystem.Database.Entities
{
    [Table("Quests")]
    public class Quest
    {
        [Key]
        public int QuestID { get; set; }

        [Required]
        [MaxLength(200)]
        public string QuestName { get; set; }

        [Column(TypeName = "nvarchar(max)")]
        public string Description { get; set; }

        [Required]
        [MaxLength(30)]
        public string QuestType { get; set; }

        public int RequiredLevel { get; set; } = 1;

        public int RecommendedLevel { get; set; } = 1;

        public bool IsRepeatable { get; set; } = false;

        public bool IsDailyQuest { get; set; } = false;

        public int? RequiredQuestID { get; set; }

        public int ExperienceReward { get; set; } = 0;

        public int GoldReward { get; set; } = 0;

        public int ReputationReward { get; set; } = 0;

        public int? ReputationFactionID { get; set; }

        [MaxLength(30)]
        public string QuestGiver { get; set; }

        public int? QuestGiverNPCID { get; set; }

        public int StartZoneID { get; set; }

        [ForeignKey("StartZoneID")]
        public virtual Zone StartZone { get; set; }
    }

    [Table("QuestObjectives")]
    public class QuestObjective
    {
        [Key]
        public int ObjectiveID { get; set; }

        public int QuestID { get; set; }

        [Required]
        [MaxLength(200)]
        public string ObjectiveDescription { get; set; }

        [Required]
        [MaxLength(30)]
        public string ObjectiveType { get; set; }

        public int? TargetItemID { get; set; }

        public int? TargetEnemyID { get; set; }

        public int? TargetNPCID { get; set; }

        public int? TargetZoneID { get; set; }

        public int RequiredCount { get; set; } = 1;

        [ForeignKey("QuestID")]
        public virtual Quest Quest { get; set; }
    }

    [Table("CharacterQuests")]
    public class CharacterQuest
    {
        [Key]
        public int CharacterQuestID { get; set; }

        public int CharacterID { get; set; }

        public int QuestID { get; set; }

        [Required]
        [MaxLength(20)]
        public string Status { get; set; } = "Active";

        public DateTime AcceptedAt { get; set; } = DateTime.UtcNow;

        public DateTime? CompletedAt { get; set; }

        public int CurrentProgress { get; set; } = 0;

        [Column(TypeName = "nvarchar(max)")]
        public string ObjectiveProgress { get; set; }

        [ForeignKey("CharacterID")]
        public virtual Character Character { get; set; }

        [ForeignKey("QuestID")]
        public virtual Quest Quest { get; set; }
    }

    [Table("QuestRewardItems")]
    public class QuestRewardItem
    {
        [Key]
        public int RewardID { get; set; }

        public int QuestID { get; set; }

        public int ItemID { get; set; }

        public int Quantity { get; set; } = 1;

        public bool IsChoiceReward { get; set; } = false;

        [ForeignKey("QuestID")]
        public virtual Quest Quest { get; set; }

        [ForeignKey("ItemID")]
        public virtual Item Item { get; set; }
    }
}
