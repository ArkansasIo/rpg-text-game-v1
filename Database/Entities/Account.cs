using System;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace RPGMenuSystem.Database.Entities
{
    [Table("Accounts")]
    public class Account
    {
        [Key]
        public int AccountID { get; set; }

        [Required]
        [MaxLength(50)]
        public string Username { get; set; }

        [Required]
        [MaxLength(256)]
        public string PasswordHash { get; set; }

        [Required]
        [MaxLength(100)]
        public string Email { get; set; }

        public DateTime CreatedAt { get; set; } = DateTime.UtcNow;

        public DateTime? LastLogin { get; set; }

        [Required]
        [MaxLength(20)]
        public string AccountStatus { get; set; } = "Active";

        public bool IsPremium { get; set; } = false;

        public DateTime? PremiumExpiry { get; set; }
    }
}
