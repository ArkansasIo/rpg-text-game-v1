using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace RPGMenuSystem.Database.Entities
{
    [Table("CharacterInventory")]
    public class CharacterInventory
    {
        [Key]
        public int InventoryID { get; set; }

        public int CharacterID { get; set; }

        public int ItemID { get; set; }

        public int Quantity { get; set; } = 1;

        public int SlotPosition { get; set; }

        [MaxLength(30)]
        public string BagType { get; set; } = "Backpack";

        public bool IsEquipped { get; set; } = false;

        [Column(TypeName = "nvarchar(max)")]
        public string ItemModifiers { get; set; }

        // Navigation
        [ForeignKey("CharacterID")]
        public virtual Character Character { get; set; }

        [ForeignKey("ItemID")]
        public virtual Item Item { get; set; }
    }
}
