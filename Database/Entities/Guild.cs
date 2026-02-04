using System;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace RPGMenuSystem.Database.Entities
{
    [Table("Guilds")]
    public class Guild
    {
        [Key]
        public int GuildID { get; set; }

        [Required]
        [MaxLength(100)]
        public string GuildName { get; set; }

        [Required]
        [MaxLength(10)]
        public string GuildTag { get; set; }

        [MaxLength(500)]
        public string Description { get; set; }

        public int LeaderCharacterID { get; set; }

        public int GuildLevel { get; set; } = 1;

        public long GuildExperience { get; set; } = 0;

        public long GuildBankGold { get; set; } = 0;

        public int MaxMembers { get; set; } = 50;

        public DateTime CreatedAt { get; set; } = DateTime.UtcNow;

        [MaxLength(200)]
        public string GuildTabard { get; set; }

        [ForeignKey("LeaderCharacterID")]
        public virtual Character Leader { get; set; }
    }

    [Table("GuildMembers")]
    public class GuildMember
    {
        [Key]
        public int MemberID { get; set; }

        public int GuildID { get; set; }

        public int CharacterID { get; set; }

        public int RankID { get; set; }

        public DateTime JoinedAt { get; set; } = DateTime.UtcNow;

        public long ContributedGold { get; set; } = 0;

        public int ContributedExperience { get; set; } = 0;

        [MaxLength(200)]
        public string PublicNote { get; set; }

        [MaxLength(200)]
        public string OfficerNote { get; set; }

        [ForeignKey("GuildID")]
        public virtual Guild Guild { get; set; }

        [ForeignKey("CharacterID")]
        public virtual Character Character { get; set; }

        [ForeignKey("RankID")]
        public virtual GuildRank Rank { get; set; }
    }

    [Table("GuildRanks")]
    public class GuildRank
    {
        [Key]
        public int RankID { get; set; }

        public int GuildID { get; set; }

        [Required]
        [MaxLength(50)]
        public string RankName { get; set; }

        public int RankOrder { get; set; }

        public bool CanInvite { get; set; } = false;

        public bool CanKick { get; set; } = false;

        public bool CanPromote { get; set; } = false;

        public bool CanAccessBank { get; set; } = true;

        public bool CanEditMOTD { get; set; } = false;

        public int BankWithdrawLimit { get; set; } = 0;

        [ForeignKey("GuildID")]
        public virtual Guild Guild { get; set; }
    }

    [Table("GuildBank")]
    public class GuildBank
    {
        [Key]
        public int BankSlotID { get; set; }

        public int GuildID { get; set; }

        public int TabNumber { get; set; }

        public int SlotNumber { get; set; }

        public int? ItemID { get; set; }

        public int Quantity { get; set; } = 0;

        public int? DepositedByCharacterID { get; set; }

        public DateTime? DepositedAt { get; set; }

        [ForeignKey("GuildID")]
        public virtual Guild Guild { get; set; }

        [ForeignKey("ItemID")]
        public virtual Item Item { get; set; }
    }
}
