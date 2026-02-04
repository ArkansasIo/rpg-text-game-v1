using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace RPGMenuSystem.Database.Entities
{
    [Table("Items")]
    public class Item
    {
        [Key]
        public int ItemID { get; set; }

        [Required]
        [MaxLength(100)]
        public string ItemName { get; set; }

        [MaxLength(500)]
        public string Description { get; set; }

        [Required]
        [MaxLength(30)]
        public string ItemType { get; set; }

        [MaxLength(30)]
        public string Rarity { get; set; } = "Common";

        public int RequiredLevel { get; set; } = 1;

        public int MaxStackSize { get; set; } = 1;

        public int VendorPrice { get; set; } = 0;

        public bool IsTradeable { get; set; } = true;

        public bool IsQuestItem { get; set; } = false;

        [Column(TypeName = "nvarchar(max)")]
        public string Stats { get; set; }

        [MaxLength(200)]
        public string IconPath { get; set; }
    }
}
