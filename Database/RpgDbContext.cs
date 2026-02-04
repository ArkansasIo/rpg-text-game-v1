using Microsoft.EntityFrameworkCore;
using RPGMenuSystem.Database.Entities;

namespace RPGMenuSystem.Database
{
    public class RpgDbContext : DbContext
    {
        public RpgDbContext(DbContextOptions<RpgDbContext> options) : base(options)
        {
        }

        // Core Tables
        public DbSet<Account> Accounts { get; set; }
        public DbSet<Character> Characters { get; set; }
        public DbSet<Item> Items { get; set; }
        public DbSet<CharacterInventory> CharacterInventory { get; set; }

        // World Tables
        public DbSet<Zone> Zones { get; set; }
        public DbSet<ZoneConnection> ZoneConnections { get; set; }
        public DbSet<CharacterZoneDiscovery> CharacterZoneDiscoveries { get; set; }

        // Quest Tables
        public DbSet<Quest> Quests { get; set; }
        public DbSet<QuestObjective> QuestObjectives { get; set; }
        public DbSet<CharacterQuest> CharacterQuests { get; set; }
        public DbSet<QuestRewardItem> QuestRewardItems { get; set; }

        // Enemy Tables
        public DbSet<Enemy> Enemies { get; set; }
        public DbSet<EnemyLootTable> EnemyLootTables { get; set; }
        public DbSet<EnemySpawn> EnemySpawns { get; set; }

        // Dungeon Tables
        public DbSet<Dungeon> Dungeons { get; set; }
        public DbSet<DungeonDifficulty> DungeonDifficulties { get; set; }
        public DbSet<DungeonBoss> DungeonBosses { get; set; }
        public DbSet<CharacterDungeonProgress> CharacterDungeonProgress { get; set; }

        // Guild Tables
        public DbSet<Guild> Guilds { get; set; }
        public DbSet<GuildMember> GuildMembers { get; set; }
        public DbSet<GuildRank> GuildRanks { get; set; }
        public DbSet<GuildBank> GuildBank { get; set; }

        // Progression Tables
        public DbSet<Achievement> Achievements { get; set; }
        public DbSet<CharacterAchievement> CharacterAchievements { get; set; }
        public DbSet<Mount> Mounts { get; set; }
        public DbSet<CharacterMount> CharacterMounts { get; set; }
        public DbSet<Pet> Pets { get; set; }
        public DbSet<CharacterPet> CharacterPets { get; set; }

        // Crafting Tables
        public DbSet<Profession> Professions { get; set; }
        public DbSet<CharacterProfession> CharacterProfessions { get; set; }
        public DbSet<Recipe> Recipes { get; set; }
        public DbSet<RecipeMaterial> RecipeMaterials { get; set; }
        public DbSet<CharacterRecipe> CharacterRecipes { get; set; }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            base.OnModelCreating(modelBuilder);

            // Configure relationships and constraints
            modelBuilder.Entity<Character>()
                .HasOne(c => c.Account)
                .WithMany()
                .HasForeignKey(c => c.AccountID)
                .OnDelete(DeleteBehavior.Cascade);

            modelBuilder.Entity<CharacterInventory>()
                .HasOne(ci => ci.Character)
                .WithMany()
                .HasForeignKey(ci => ci.CharacterID)
                .OnDelete(DeleteBehavior.Cascade);

            modelBuilder.Entity<CharacterInventory>()
                .HasOne(ci => ci.Item)
                .WithMany()
                .HasForeignKey(ci => ci.ItemID)
                .OnDelete(DeleteBehavior.Restrict);

            // Quest relationships
            modelBuilder.Entity<CharacterQuest>()
                .HasOne(cq => cq.Character)
                .WithMany()
                .HasForeignKey(cq => cq.CharacterID)
                .OnDelete(DeleteBehavior.Cascade);

            // Guild relationships
            modelBuilder.Entity<GuildMember>()
                .HasOne(gm => gm.Guild)
                .WithMany()
                .HasForeignKey(gm => gm.GuildID)
                .OnDelete(DeleteBehavior.Cascade);

            // Indexes for performance
            modelBuilder.Entity<Account>()
                .HasIndex(a => a.Username)
                .IsUnique();

            modelBuilder.Entity<Character>()
                .HasIndex(c => c.CharacterName)
                .IsUnique();

            modelBuilder.Entity<Character>()
                .HasIndex(c => new { c.AccountID, c.Level });

            modelBuilder.Entity<CharacterInventory>()
                .HasIndex(ci => new { ci.CharacterID, ci.SlotPosition });

            modelBuilder.Entity<Quest>()
                .HasIndex(q => new { q.RequiredLevel, q.QuestType });

            modelBuilder.Entity<Enemy>()
                .HasIndex(e => new { e.Level, e.EnemyType });

            modelBuilder.Entity<Guild>()
                .HasIndex(g => g.GuildName)
                .IsUnique();

            modelBuilder.Entity<CharacterQuest>()
                .HasIndex(cq => new { cq.CharacterID, cq.Status });

            modelBuilder.Entity<GuildMember>()
                .HasIndex(gm => new { gm.GuildID, gm.CharacterID });
        }
    }
}
