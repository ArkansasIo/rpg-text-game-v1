using System;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace RPGMenuSystem.Database.Entities
{
    [Table("Achievements")]
    public class Achievement
    {
        [Key]
        public int AchievementID { get; set; }

        [Required]
        [MaxLength(200)]
        public string AchievementName { get; set; }

        [MaxLength(500)]
        public string Description { get; set; }

        [Required]
        [MaxLength(50)]
        public string Category { get; set; }

        public int PointValue { get; set; } = 10;

        public bool IsHidden { get; set; } = false;

        [MaxLength(200)]
        public string IconPath { get; set; }

        [Column(TypeName = "nvarchar(max)")]
        public string Requirements { get; set; }
    }

    [Table("CharacterAchievements")]
    public class CharacterAchievement
    {
        [Key]
        public int CharacterAchievementID { get; set; }

        public int CharacterID { get; set; }

        public int AchievementID { get; set; }

        public DateTime CompletedAt { get; set; } = DateTime.UtcNow;

        public int Progress { get; set; } = 100;

        [ForeignKey("CharacterID")]
        public virtual Character Character { get; set; }

        [ForeignKey("AchievementID")]
        public virtual Achievement Achievement { get; set; }
    }

    [Table("Mounts")]
    public class Mount
    {
        [Key]
        public int MountID { get; set; }

        [Required]
        [MaxLength(100)]
        public string MountName { get; set; }

        [MaxLength(500)]
        public string Description { get; set; }

        [Required]
        [MaxLength(30)]
        public string MountType { get; set; }

        public int SpeedBonus { get; set; } = 100;

        public bool CanFly { get; set; } = false;

        [Required]
        [MaxLength(30)]
        public string Rarity { get; set; } = "Common";

        public int RequiredLevel { get; set; } = 20;

        [MaxLength(200)]
        public string ModelPath { get; set; }
    }

    [Table("CharacterMounts")]
    public class CharacterMount
    {
        [Key]
        public int CharacterMountID { get; set; }

        public int CharacterID { get; set; }

        public int MountID { get; set; }

        public DateTime AcquiredAt { get; set; } = DateTime.UtcNow;

        public bool IsFavorite { get; set; } = false;

        [ForeignKey("CharacterID")]
        public virtual Character Character { get; set; }

        [ForeignKey("MountID")]
        public virtual Mount Mount { get; set; }
    }

    [Table("Pets")]
    public class Pet
    {
        [Key]
        public int PetID { get; set; }

        [Required]
        [MaxLength(100)]
        public string PetName { get; set; }

        [MaxLength(500)]
        public string Description { get; set; }

        [Required]
        [MaxLength(30)]
        public string PetType { get; set; }

        [Required]
        [MaxLength(30)]
        public string Rarity { get; set; } = "Common";

        public bool IsCombatPet { get; set; } = false;

        public int? BaseHealth { get; set; }

        public int? BaseDamage { get; set; }

        [MaxLength(200)]
        public string ModelPath { get; set; }
    }

    [Table("CharacterPets")]
    public class CharacterPet
    {
        [Key]
        public int CharacterPetID { get; set; }

        public int CharacterID { get; set; }

        public int PetID { get; set; }

        [MaxLength(100)]
        public string CustomName { get; set; }

        public int Level { get; set; } = 1;

        public int Experience { get; set; } = 0;

        public DateTime AcquiredAt { get; set; } = DateTime.UtcNow;

        public bool IsFavorite { get; set; } = false;

        [ForeignKey("CharacterID")]
        public virtual Character Character { get; set; }

        [ForeignKey("PetID")]
        public virtual Pet Pet { get; set; }
    }
}
