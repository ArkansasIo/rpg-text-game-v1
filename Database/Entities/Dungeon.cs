using System;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace RPGMenuSystem.Database.Entities
{
    [Table("Dungeons")]
    public class Dungeon
    {
        [Key]
        public int DungeonID { get; set; }

        [Required]
        [MaxLength(100)]
        public string DungeonName { get; set; }

        [MaxLength(500)]
        public string Description { get; set; }

        [Required]
        [MaxLength(30)]
        public string DungeonType { get; set; }

        public int RequiredLevel { get; set; }

        public int RecommendedPlayers { get; set; } = 5;

        public int MaxPlayers { get; set; } = 5;

        public int EstimatedTimeMinutes { get; set; } = 30;

        public int LocationZoneID { get; set; }

        [ForeignKey("LocationZoneID")]
        public virtual Zone LocationZone { get; set; }
    }

    [Table("DungeonDifficulties")]
    public class DungeonDifficulty
    {
        [Key]
        public int DifficultyID { get; set; }

        public int DungeonID { get; set; }

        [Required]
        [MaxLength(30)]
        public string DifficultyName { get; set; }

        public int RequiredItemLevel { get; set; } = 0;

        [Column(TypeName = "decimal(3,2)")]
        public decimal DamageMultiplier { get; set; } = 1.0m;

        [Column(TypeName = "decimal(3,2)")]
        public decimal HealthMultiplier { get; set; } = 1.0m;

        [Column(TypeName = "decimal(3,2)")]
        public decimal RewardMultiplier { get; set; } = 1.0m;

        [ForeignKey("DungeonID")]
        public virtual Dungeon Dungeon { get; set; }
    }

    [Table("DungeonBosses")]
    public class DungeonBoss
    {
        [Key]
        public int BossID { get; set; }

        public int DungeonID { get; set; }

        public int EnemyID { get; set; }

        public int BossOrder { get; set; }

        public bool IsFinalBoss { get; set; } = false;

        [Column(TypeName = "nvarchar(max)")]
        public string Mechanics { get; set; }

        [ForeignKey("DungeonID")]
        public virtual Dungeon Dungeon { get; set; }

        [ForeignKey("EnemyID")]
        public virtual Enemy Enemy { get; set; }
    }

    [Table("CharacterDungeonProgress")]
    public class CharacterDungeonProgress
    {
        [Key]
        public int ProgressID { get; set; }

        public int CharacterID { get; set; }

        public int DungeonID { get; set; }

        public int DifficultyID { get; set; }

        public int CompletionCount { get; set; } = 0;

        public int BestTimeSeconds { get; set; } = 0;

        public DateTime? LastCompletedAt { get; set; }

        public DateTime? FirstCompletedAt { get; set; }

        [ForeignKey("CharacterID")]
        public virtual Character Character { get; set; }

        [ForeignKey("DungeonID")]
        public virtual Dungeon Dungeon { get; set; }

        [ForeignKey("DifficultyID")]
        public virtual DungeonDifficulty Difficulty { get; set; }
    }
}
