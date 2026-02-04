using System;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace RPGMenuSystem.Database.Entities
{
    [Table("Characters")]
    public class Character
    {
        [Key]
        public int CharacterID { get; set; }

        public int AccountID { get; set; }

        [Required]
        [MaxLength(50)]
        public string CharacterName { get; set; }

        [Required]
        [MaxLength(30)]
        public string Race { get; set; }

        [Required]
        [MaxLength(30)]
        public string Class { get; set; }

        [MaxLength(50)]
        public string Specialization { get; set; }

        public int Level { get; set; } = 1;

        public long ExperiencePoints { get; set; } = 0;

        public int CurrentZoneID { get; set; }

        // Primary Stats
        public int Strength { get; set; }
        public int Agility { get; set; }
        public int Intelligence { get; set; }
        public int Stamina { get; set; }
        public int Spirit { get; set; }

        // Secondary Stats
        public int CritChance { get; set; }
        public int Haste { get; set; }
        public int Mastery { get; set; }
        public int Versatility { get; set; }

        // Resources
        public int CurrentHealth { get; set; }
        public int MaxHealth { get; set; }
        public int CurrentMana { get; set; }
        public int MaxMana { get; set; }
        public int CurrentEnergy { get; set; } = 100;
        public int MaxEnergy { get; set; } = 100;

        // Currency
        public long Gold { get; set; } = 0;
        public int HonorPoints { get; set; } = 0;
        public int JusticePoints { get; set; } = 0;

        // Progression
        public int TalentPoints { get; set; } = 0;
        public int AchievementPoints { get; set; } = 0;

        public DateTime CreatedAt { get; set; } = DateTime.UtcNow;
        public DateTime? LastPlayed { get; set; }

        public int PlaytimeMinutes { get; set; } = 0;

        // Navigation
        [ForeignKey("AccountID")]
        public virtual Account Account { get; set; }
    }
}
