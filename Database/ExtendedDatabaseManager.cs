using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using RPGMenuSystem.Database.Entities;

namespace RPGMenuSystem.Database
{
    /// <summary>
    /// Extended database operations for quests, dungeons, guilds, and more
    /// </summary>
    public class ExtendedDatabaseManager
    {
        private readonly RpgDbContext _context;

        public ExtendedDatabaseManager(RpgDbContext context)
        {
            _context = context;
        }

        #region Quest Operations

        public async Task<List<Quest>> GetAvailableQuestsAsync(int characterLevel, int zoneId)
        {
            return await _context.Quests
                .Where(q => q.RequiredLevel <= characterLevel && q.StartZoneID == zoneId)
                .Include(q => q.StartZone)
                .ToListAsync();
        }

        public async Task<CharacterQuest> AcceptQuestAsync(int characterId, int questId)
        {
            var characterQuest = new CharacterQuest
            {
                CharacterID = characterId,
                QuestID = questId,
                Status = "Active",
                AcceptedAt = DateTime.UtcNow,
                CurrentProgress = 0
            };

            _context.CharacterQuests.Add(characterQuest);
            await _context.SaveChangesAsync();
            return characterQuest;
        }

        public async Task<bool> CompleteQuestAsync(int characterId, int questId)
        {
            var characterQuest = await _context.CharacterQuests
                .FirstOrDefaultAsync(cq => cq.CharacterID == characterId && 
                                           cq.QuestID == questId && 
                                           cq.Status == "Active");

            if (characterQuest == null) return false;

            characterQuest.Status = "Completed";
            characterQuest.CompletedAt = DateTime.UtcNow;

            // Award quest rewards
            var quest = await _context.Quests.FindAsync(questId);
            var character = await _context.Characters.FindAsync(characterId);

            if (quest != null && character != null)
            {
                character.ExperiencePoints += quest.ExperienceReward;
                character.Gold += quest.GoldReward;
            }

            await _context.SaveChangesAsync();
            return true;
        }

        public async Task<List<CharacterQuest>> GetActiveQuestsAsync(int characterId)
        {
            return await _context.CharacterQuests
                .Include(cq => cq.Quest)
                .Where(cq => cq.CharacterID == characterId && cq.Status == "Active")
                .ToListAsync();
        }

        #endregion

        #region Guild Operations

        public async Task<Guild> CreateGuildAsync(string guildName, string guildTag, int leaderCharacterId, string description = "")
        {
            var guild = new Guild
            {
                GuildName = guildName,
                GuildTag = guildTag,
                LeaderCharacterID = leaderCharacterId,
                Description = description,
                GuildLevel = 1,
                GuildExperience = 0,
                MaxMembers = 50,
                CreatedAt = DateTime.UtcNow
            };

            _context.Guilds.Add(guild);
            await _context.SaveChangesAsync();

            // Create default ranks
            await CreateDefaultGuildRanks(guild.GuildID);

            // Add leader as member with highest rank
            var leaderRank = await _context.GuildRanks
                .Where(r => r.GuildID == guild.GuildID)
                .OrderBy(r => r.RankOrder)
                .FirstAsync();

            await AddGuildMemberAsync(guild.GuildID, leaderCharacterId, leaderRank.RankID);

            return guild;
        }

        private async Task CreateDefaultGuildRanks(int guildId)
        {
            var ranks = new[]
            {
                new GuildRank { GuildID = guildId, RankName = "Guild Master", RankOrder = 0, CanInvite = true, CanKick = true, CanPromote = true, CanAccessBank = true, CanEditMOTD = true, BankWithdrawLimit = -1 },
                new GuildRank { GuildID = guildId, RankName = "Officer", RankOrder = 1, CanInvite = true, CanKick = true, CanPromote = false, CanAccessBank = true, CanEditMOTD = true, BankWithdrawLimit = 1000 },
                new GuildRank { GuildID = guildId, RankName = "Veteran", RankOrder = 2, CanInvite = true, CanKick = false, CanPromote = false, CanAccessBank = true, CanEditMOTD = false, BankWithdrawLimit = 500 },
                new GuildRank { GuildID = guildId, RankName = "Member", RankOrder = 3, CanInvite = false, CanKick = false, CanPromote = false, CanAccessBank = true, CanEditMOTD = false, BankWithdrawLimit = 100 },
                new GuildRank { GuildID = guildId, RankName = "Initiate", RankOrder = 4, CanInvite = false, CanKick = false, CanPromote = false, CanAccessBank = false, CanEditMOTD = false, BankWithdrawLimit = 0 }
            };

            _context.GuildRanks.AddRange(ranks);
            await _context.SaveChangesAsync();
        }

        public async Task<GuildMember> AddGuildMemberAsync(int guildId, int characterId, int rankId)
        {
            var member = new GuildMember
            {
                GuildID = guildId,
                CharacterID = characterId,
                RankID = rankId,
                JoinedAt = DateTime.UtcNow
            };

            _context.GuildMembers.Add(member);
            await _context.SaveChangesAsync();
            return member;
        }

        public async Task<Guild> GetGuildByNameAsync(string guildName)
        {
            return await _context.Guilds
                .Include(g => g.Leader)
                .FirstOrDefaultAsync(g => g.GuildName == guildName);
        }

        public async Task<List<GuildMember>> GetGuildMembersAsync(int guildId)
        {
            return await _context.GuildMembers
                .Include(gm => gm.Character)
                .Include(gm => gm.Rank)
                .Where(gm => gm.GuildID == guildId)
                .OrderBy(gm => gm.Rank.RankOrder)
                .ToListAsync();
        }

        #endregion

        #region Dungeon Operations

        public async Task<List<Dungeon>> GetAvailableDungeonsAsync(int characterLevel)
        {
            return await _context.Dungeons
                .Include(d => d.LocationZone)
                .Where(d => d.RequiredLevel <= characterLevel)
                .ToListAsync();
        }

        public async Task<List<DungeonBoss>> GetDungeonBossesAsync(int dungeonId)
        {
            return await _context.DungeonBosses
                .Include(db => db.Enemy)
                .Where(db => db.DungeonID == dungeonId)
                .OrderBy(db => db.BossOrder)
                .ToListAsync();
        }

        public async Task RecordDungeonCompletionAsync(int characterId, int dungeonId, int difficultyId, int timeSeconds)
        {
            var progress = await _context.CharacterDungeonProgress
                .FirstOrDefaultAsync(p => p.CharacterID == characterId && 
                                         p.DungeonID == dungeonId && 
                                         p.DifficultyID == difficultyId);

            if (progress == null)
            {
                progress = new CharacterDungeonProgress
                {
                    CharacterID = characterId,
                    DungeonID = dungeonId,
                    DifficultyID = difficultyId,
                    CompletionCount = 1,
                    BestTimeSeconds = timeSeconds,
                    FirstCompletedAt = DateTime.UtcNow,
                    LastCompletedAt = DateTime.UtcNow
                };
                _context.CharacterDungeonProgress.Add(progress);
            }
            else
            {
                progress.CompletionCount++;
                progress.LastCompletedAt = DateTime.UtcNow;
                if (timeSeconds < progress.BestTimeSeconds || progress.BestTimeSeconds == 0)
                {
                    progress.BestTimeSeconds = timeSeconds;
                }
            }

            await _context.SaveChangesAsync();
        }

        #endregion

        #region Achievement Operations

        public async Task<bool> UnlockAchievementAsync(int characterId, int achievementId)
        {
            var existing = await _context.CharacterAchievements
                .FirstOrDefaultAsync(ca => ca.CharacterID == characterId && 
                                          ca.AchievementID == achievementId);

            if (existing != null) return false; // Already unlocked

            var achievement = await _context.Achievements.FindAsync(achievementId);
            if (achievement == null) return false;

            var characterAchievement = new CharacterAchievement
            {
                CharacterID = characterId,
                AchievementID = achievementId,
                CompletedAt = DateTime.UtcNow,
                Progress = 100
            };

            _context.CharacterAchievements.Add(characterAchievement);

            // Update character's achievement points
            var character = await _context.Characters.FindAsync(characterId);
            if (character != null)
            {
                character.AchievementPoints += achievement.PointValue;
            }

            await _context.SaveChangesAsync();
            return true;
        }

        public async Task<List<CharacterAchievement>> GetCharacterAchievementsAsync(int characterId)
        {
            return await _context.CharacterAchievements
                .Include(ca => ca.Achievement)
                .Where(ca => ca.CharacterID == characterId)
                .OrderByDescending(ca => ca.CompletedAt)
                .ToListAsync();
        }

        #endregion

        #region Crafting Operations

        public async Task<bool> LearnRecipeAsync(int characterId, int recipeId)
        {
            var existing = await _context.CharacterRecipes
                .FirstOrDefaultAsync(cr => cr.CharacterID == characterId && 
                                          cr.RecipeID == recipeId);

            if (existing != null) return false; // Already learned

            var characterRecipe = new CharacterRecipe
            {
                CharacterID = characterId,
                RecipeID = recipeId,
                LearnedAt = DateTime.UtcNow,
                CraftedCount = 0
            };

            _context.CharacterRecipes.Add(characterRecipe);
            await _context.SaveChangesAsync();
            return true;
        }

        public async Task<List<Recipe>> GetAvailableRecipesAsync(int characterId, int professionId)
        {
            var characterProfession = await _context.CharacterProfessions
                .FirstOrDefaultAsync(cp => cp.CharacterID == characterId && 
                                          cp.ProfessionID == professionId);

            if (characterProfession == null) return new List<Recipe>();

            return await _context.Recipes
                .Include(r => r.ResultItem)
                .Where(r => r.ProfessionID == professionId && 
                           r.RequiredSkillLevel <= characterProfession.SkillLevel)
                .ToListAsync();
        }

        public async Task<bool> CraftItemAsync(int characterId, int recipeId)
        {
            var recipe = await _context.Recipes
                .Include(r => r.ResultItem)
                .FirstOrDefaultAsync(r => r.RecipeID == recipeId);

            if (recipe == null) return false;

            // Check materials (simplified - would need full inventory check)
            var materials = await _context.RecipeMaterials
                .Where(rm => rm.RecipeID == recipeId)
                .ToListAsync();

            // Add crafted item to inventory
            var inventoryManager = new DatabaseManager(_context);
            await inventoryManager.AddItemToInventoryAsync(characterId, recipe.ResultItemID, recipe.ResultQuantity);

            // Update crafted count
            var characterRecipe = await _context.CharacterRecipes
                .FirstOrDefaultAsync(cr => cr.CharacterID == characterId && 
                                          cr.RecipeID == recipeId);

            if (characterRecipe != null)
            {
                characterRecipe.CraftedCount++;
            }

            await _context.SaveChangesAsync();
            return true;
        }

        #endregion

        #region Mount & Pet Operations

        public async Task<bool> UnlockMountAsync(int characterId, int mountId)
        {
            var existing = await _context.CharacterMounts
                .FirstOrDefaultAsync(cm => cm.CharacterID == characterId && 
                                          cm.MountID == mountId);

            if (existing != null) return false; // Already unlocked

            var characterMount = new CharacterMount
            {
                CharacterID = characterId,
                MountID = mountId,
                AcquiredAt = DateTime.UtcNow,
                IsFavorite = false
            };

            _context.CharacterMounts.Add(characterMount);
            await _context.SaveChangesAsync();
            return true;
        }

        public async Task<List<CharacterMount>> GetCharacterMountsAsync(int characterId)
        {
            return await _context.CharacterMounts
                .Include(cm => cm.Mount)
                .Where(cm => cm.CharacterID == characterId)
                .OrderByDescending(cm => cm.IsFavorite)
                .ThenBy(cm => cm.Mount.MountName)
                .ToListAsync();
        }

        public async Task<bool> UnlockPetAsync(int characterId, int petId, string customName = null)
        {
            var characterPet = new CharacterPet
            {
                CharacterID = characterId,
                PetID = petId,
                CustomName = customName,
                Level = 1,
                Experience = 0,
                AcquiredAt = DateTime.UtcNow,
                IsFavorite = false
            };

            _context.CharacterPets.Add(characterPet);
            await _context.SaveChangesAsync();
            return true;
        }

        public async Task<List<CharacterPet>> GetCharacterPetsAsync(int characterId)
        {
            return await _context.CharacterPets
                .Include(cp => cp.Pet)
                .Where(cp => cp.CharacterID == characterId)
                .OrderByDescending(cp => cp.Level)
                .ToListAsync();
        }

        #endregion

        #region Zone & Exploration

        public async Task<bool> DiscoverZoneAsync(int characterId, int zoneId)
        {
            var existing = await _context.CharacterZoneDiscoveries
                .FirstOrDefaultAsync(czd => czd.CharacterID == characterId && 
                                           czd.ZoneID == zoneId);

            if (existing != null)
            {
                existing.VisitCount++;
                await _context.SaveChangesAsync();
                return false; // Already discovered
            }

            var discovery = new CharacterZoneDiscovery
            {
                CharacterID = characterId,
                ZoneID = zoneId,
                DiscoveredAt = DateTime.UtcNow,
                VisitCount = 1
            };

            _context.CharacterZoneDiscoveries.Add(discovery);
            await _context.SaveChangesAsync();
            return true; // Newly discovered
        }

        public async Task<List<Zone>> GetDiscoveredZonesAsync(int characterId)
        {
            return await _context.CharacterZoneDiscoveries
                .Include(czd => czd.Zone)
                .Where(czd => czd.CharacterID == characterId)
                .Select(czd => czd.Zone)
                .ToListAsync();
        }

        #endregion
    }
}
