using System;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace RPGMenuSystem.Database.Entities
{
    [Table("Zones")]
    public class Zone
    {
        [Key]
        public int ZoneID { get; set; }

        [Required]
        [MaxLength(100)]
        public string ZoneName { get; set; }

        [MaxLength(500)]
        public string Description { get; set; }

        [Required]
        [MaxLength(30)]
        public string ZoneType { get; set; }

        public int RecommendedLevel { get; set; }

        public int MinLevel { get; set; }

        public int MaxLevel { get; set; }

        [Required]
        [MaxLength(30)]
        public string Faction { get; set; } = "Neutral";

        public bool IsSanctuary { get; set; } = false;

        public bool HasInn { get; set; } = false;

        public bool HasBank { get; set; } = false;

        public bool HasAuctionHouse { get; set; } = false;

        public bool HasFlightMaster { get; set; } = false;

        [MaxLength(200)]
        public string BackgroundMusic { get; set; }
    }

    [Table("ZoneConnections")]
    public class ZoneConnection
    {
        [Key]
        public int ConnectionID { get; set; }

        public int FromZoneID { get; set; }

        public int ToZoneID { get; set; }

        [MaxLength(50)]
        public string ConnectionType { get; set; } = "Path";

        public bool RequiresFlight { get; set; } = false;

        public bool RequiresQuest { get; set; } = false;

        public int? RequiredQuestID { get; set; }

        [ForeignKey("FromZoneID")]
        public virtual Zone FromZone { get; set; }

        [ForeignKey("ToZoneID")]
        public virtual Zone ToZone { get; set; }
    }

    [Table("CharacterZoneDiscovery")]
    public class CharacterZoneDiscovery
    {
        [Key]
        public int DiscoveryID { get; set; }

        public int CharacterID { get; set; }

        public int ZoneID { get; set; }

        public DateTime DiscoveredAt { get; set; } = DateTime.UtcNow;

        public int VisitCount { get; set; } = 1;

        [ForeignKey("CharacterID")]
        public virtual Character Character { get; set; }

        [ForeignKey("ZoneID")]
        public virtual Zone Zone { get; set; }
    }
}
