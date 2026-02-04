using System;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace RPGMenuSystem.Database.Entities
{
    [Table("Professions")]
    public class Profession
    {
        [Key]
        public int ProfessionID { get; set; }

        [Required]
        [MaxLength(50)]
        public string ProfessionName { get; set; }

        [MaxLength(500)]
        public string Description { get; set; }

        [Required]
        [MaxLength(30)]
        public string Type { get; set; }

        public int MaxSkillLevel { get; set; } = 300;

        [MaxLength(200)]
        public string IconPath { get; set; }
    }

    [Table("CharacterProfessions")]
    public class CharacterProfession
    {
        [Key]
        public int CharacterProfessionID { get; set; }

        public int CharacterID { get; set; }

        public int ProfessionID { get; set; }

        public int SkillLevel { get; set; } = 1;

        public int SkillMax { get; set; } = 75;

        public DateTime LearnedAt { get; set; } = DateTime.UtcNow;

        [ForeignKey("CharacterID")]
        public virtual Character Character { get; set; }

        [ForeignKey("ProfessionID")]
        public virtual Profession Profession { get; set; }
    }

    [Table("Recipes")]
    public class Recipe
    {
        [Key]
        public int RecipeID { get; set; }

        [Required]
        [MaxLength(100)]
        public string RecipeName { get; set; }

        public int ProfessionID { get; set; }

        public int RequiredSkillLevel { get; set; }

        public int ResultItemID { get; set; }

        public int ResultQuantity { get; set; } = 1;

        public int CraftingTimeSeconds { get; set; } = 3;

        [Required]
        [MaxLength(30)]
        public string Difficulty { get; set; } = "Easy";

        [ForeignKey("ProfessionID")]
        public virtual Profession Profession { get; set; }

        [ForeignKey("ResultItemID")]
        public virtual Item ResultItem { get; set; }
    }

    [Table("RecipeMaterials")]
    public class RecipeMaterial
    {
        [Key]
        public int MaterialID { get; set; }

        public int RecipeID { get; set; }

        public int ItemID { get; set; }

        public int Quantity { get; set; } = 1;

        [ForeignKey("RecipeID")]
        public virtual Recipe Recipe { get; set; }

        [ForeignKey("ItemID")]
        public virtual Item Item { get; set; }
    }

    [Table("CharacterRecipes")]
    public class CharacterRecipe
    {
        [Key]
        public int CharacterRecipeID { get; set; }

        public int CharacterID { get; set; }

        public int RecipeID { get; set; }

        public DateTime LearnedAt { get; set; } = DateTime.UtcNow;

        public int CraftedCount { get; set; } = 0;

        [ForeignKey("CharacterID")]
        public virtual Character Character { get; set; }

        [ForeignKey("RecipeID")]
        public virtual Recipe Recipe { get; set; }
    }
}
