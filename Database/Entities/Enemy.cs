using System;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace RPGMenuSystem.Database.Entities
{
    [Table("Enemies")]
    public class Enemy
    {
        [Key]
        public int EnemyID { get; set; }

        [Required]
        [MaxLength(100)]
        public string EnemyName { get; set; }

        [Required]
        [MaxLength(30)]
        public string EnemyType { get; set; }

        public int Level { get; set; }

        public int Health { get; set; }

        public int Mana { get; set; } = 0;

        public int Armor { get; set; } = 0;

        public int MinDamage { get; set; }

        public int MaxDamage { get; set; }

        public int ExperienceReward { get; set; } = 0;

        [Required]
        [MaxLength(20)]
        public string Rank { get; set; } = "Normal";

        [Column(TypeName = "nvarchar(max)")]
        public string Abilities { get; set; }

        [Column(TypeName = "nvarchar(max)")]
        public string Resistances { get; set; }

        [MaxLength(200)]
        public string ModelPath { get; set; }
    }

    [Table("EnemyLootTable")]
    public class EnemyLootTable
    {
        [Key]
        public int LootID { get; set; }

        public int EnemyID { get; set; }

        public int ItemID { get; set; }

        [Column(TypeName = "decimal(5,2)")]
        public decimal DropChance { get; set; }

        public int MinQuantity { get; set; } = 1;

        public int MaxQuantity { get; set; } = 1;

        [ForeignKey("EnemyID")]
        public virtual Enemy Enemy { get; set; }

        [ForeignKey("ItemID")]
        public virtual Item Item { get; set; }
    }

    [Table("EnemySpawns")]
    public class EnemySpawn
    {
        [Key]
        public int SpawnID { get; set; }

        public int EnemyID { get; set; }

        public int ZoneID { get; set; }

        public int SpawnRate { get; set; } = 60;

        public int MaxPopulation { get; set; } = 10;

        public bool IsElite { get; set; } = false;

        [ForeignKey("EnemyID")]
        public virtual Enemy Enemy { get; set; }

        [ForeignKey("ZoneID")]
        public virtual Zone Zone { get; set; }
    }
}
