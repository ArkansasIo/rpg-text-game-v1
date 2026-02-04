using System;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using RPGMenuSystem.Database.Entities;
using RPGMenuSystem.Game;

namespace RPGMenuSystem.Database
{
    public class DatabaseManager
    {
        private readonly RpgDbContext _context;

        public DatabaseManager(RpgDbContext context)
        {
            _context = context;
        }

        // Account Methods
        public async Task<Account> CreateAccountAsync(string username, string email, string passwordHash)
        {
            var account = new Account
            {
                Username = username,
                Email = email,
                PasswordHash = passwordHash,
                CreatedAt = DateTime.UtcNow,
                AccountStatus = "Active"
            };

            _context.Accounts.Add(account);
            await _context.SaveChangesAsync();
            return account;
        }

        public async Task<Account> GetAccountByUsernameAsync(string username)
        {
            return await _context.Accounts
                .FirstOrDefaultAsync(a => a.Username == username);
        }

        // Character Methods
        public async Task<Character> CreateCharacterAsync(int accountId, string name, string race, string className, string specialization)
        {
            var character = new Character
            {
                AccountID = accountId,
                CharacterName = name,
                Race = race,
                Class = className,
                Specialization = specialization,
                Level = 1,
                ExperiencePoints = 0,
                CurrentZoneID = 1, // Starting zone
                Gold = 100, // Starting gold
                CreatedAt = DateTime.UtcNow
            };

            // Set starting stats based on class
            SetStartingStats(character, className);

            _context.Characters.Add(character);
            await _context.SaveChangesAsync();
            return character;
        }

        public async Task<Character> GetCharacterByNameAsync(string name)
        {
            return await _context.Characters
                .Include(c => c.Account)
                .FirstOrDefaultAsync(c => c.CharacterName == name);
        }

        public async Task<Character> GetCharacterByIdAsync(int characterId)
        {
            return await _context.Characters
                .Include(c => c.Account)
                .FirstOrDefaultAsync(c => c.CharacterID == characterId);
        }

        public async Task<System.Collections.Generic.List<Character>> GetAccountCharactersAsync(int accountId)
        {
            return await _context.Characters
                .Where(c => c.AccountID == accountId)
                .OrderByDescending(c => c.LastPlayed)
                .ToListAsync();
        }

        public async Task UpdateCharacterAsync(Character character)
        {
            character.LastPlayed = DateTime.UtcNow;
            _context.Characters.Update(character);
            await _context.SaveChangesAsync();
        }

        // Convert Player to Character entity for saving
        public async Task SavePlayerAsync(Player player, int accountId)
        {
            var character = await GetCharacterByNameAsync(player.Name);

            if (character == null)
            {
                // Create new character
                character = new Character
                {
                    AccountID = accountId,
                    CharacterName = player.Name,
                    Race = player.Race ?? "Human",
                    Class = player.Class ?? "Warrior",
                    Specialization = player.Specialization ?? "Arms"
                };
                _context.Characters.Add(character);
            }

            // Update stats
            character.Level = player.Level;
            character.ExperiencePoints = player.Experience;
            character.CurrentHealth = player.CurrentHealth;
            character.MaxHealth = player.MaxHealth;
            character.CurrentMana = player.CurrentMana;
            character.MaxMana = player.MaxMana;
            character.Gold = (long)player.Gold;
            character.Strength = player.Strength;
            character.Agility = player.Agility;
            character.Intelligence = player.Intelligence;
            character.LastPlayed = DateTime.UtcNow;

            await _context.SaveChangesAsync();
        }

        // Convert Character entity to Player for loading
        public Player LoadPlayer(Character character)
        {
            return new Player
            {
                Name = character.CharacterName,
                Race = character.Race,
                Class = character.Class,
                Specialization = character.Specialization,
                Level = character.Level,
                Experience = character.ExperiencePoints,
                CurrentHealth = character.CurrentHealth,
                MaxHealth = character.MaxHealth,
                CurrentMana = character.CurrentMana,
                MaxMana = character.MaxMana,
                Gold = (int)character.Gold,
                Strength = character.Strength,
                Agility = character.Agility,
                Intelligence = character.Intelligence
            };
        }

        // Inventory Methods
        public async Task AddItemToInventoryAsync(int characterId, int itemId, int quantity = 1, int slotPosition = -1)
        {
            // Check if item already exists in inventory (for stackable items)
            var existingItem = await _context.CharacterInventory
                .FirstOrDefaultAsync(ci => ci.CharacterID == characterId && ci.ItemID == itemId && !ci.IsEquipped);

            var item = await _context.Items.FindAsync(itemId);

            if (existingItem != null && item.MaxStackSize > 1)
            {
                existingItem.Quantity += quantity;
                _context.CharacterInventory.Update(existingItem);
            }
            else
            {
                // Find next available slot if not specified
                if (slotPosition == -1)
                {
                    var usedSlots = await _context.CharacterInventory
                        .Where(ci => ci.CharacterID == characterId)
                        .Select(ci => ci.SlotPosition)
                        .ToListAsync();

                    slotPosition = 0;
                    while (usedSlots.Contains(slotPosition))
                    {
                        slotPosition++;
                    }
                }

                var inventoryItem = new CharacterInventory
                {
                    CharacterID = characterId,
                    ItemID = itemId,
                    Quantity = quantity,
                    SlotPosition = slotPosition,
                    BagType = "Backpack"
                };

                _context.CharacterInventory.Add(inventoryItem);
            }

            await _context.SaveChangesAsync();
        }

        public async Task<System.Collections.Generic.List<CharacterInventory>> GetCharacterInventoryAsync(int characterId)
        {
            return await _context.CharacterInventory
                .Include(ci => ci.Item)
                .Where(ci => ci.CharacterID == characterId)
                .OrderBy(ci => ci.SlotPosition)
                .ToListAsync();
        }

        private void SetStartingStats(Character character, string className)
        {
            // Base stats
            character.Strength = 10;
            character.Agility = 10;
            character.Intelligence = 10;
            character.Stamina = 10;
            character.Spirit = 10;

            // Class-specific adjustments
            switch (className.ToLower())
            {
                case "warrior":
                    character.Strength = 15;
                    character.Stamina = 14;
                    character.MaxHealth = 150;
                    character.CurrentHealth = 150;
                    character.MaxMana = 50;
                    character.CurrentMana = 50;
                    break;
                case "mage":
                    character.Intelligence = 15;
                    character.Spirit = 12;
                    character.MaxHealth = 80;
                    character.CurrentHealth = 80;
                    character.MaxMana = 200;
                    character.CurrentMana = 200;
                    break;
                case "rogue":
                    character.Agility = 15;
                    character.Strength = 12;
                    character.MaxHealth = 100;
                    character.CurrentHealth = 100;
                    character.MaxEnergy = 100;
                    character.CurrentEnergy = 100;
                    break;
                case "priest":
                    character.Intelligence = 14;
                    character.Spirit = 14;
                    character.MaxHealth = 90;
                    character.CurrentHealth = 90;
                    character.MaxMana = 180;
                    character.CurrentMana = 180;
                    break;
                case "hunter":
                    character.Agility = 14;
                    character.Stamina = 12;
                    character.MaxHealth = 110;
                    character.CurrentHealth = 110;
                    character.MaxMana = 100;
                    character.CurrentMana = 100;
                    break;
                default:
                    character.MaxHealth = 100;
                    character.CurrentHealth = 100;
                    character.MaxMana = 100;
                    character.CurrentMana = 100;
                    break;
            }
        }

        public async Task<bool> TestConnectionAsync()
        {
            try
            {
                return await _context.Database.CanConnectAsync();
            }
            catch
            {
                return false;
            }
        }
    }
}
