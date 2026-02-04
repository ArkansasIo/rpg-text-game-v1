using System.Text.Json;
using RPGMenuSystem.Game;

namespace RPGMenuSystem.SaveSystem;

public class SaveManager
{
    private const string SaveDirectory = "Saves";
    private const string SaveFileExtension = ".sav";

    public SaveManager()
    {
        if (!Directory.Exists(SaveDirectory))
        {
            Directory.CreateDirectory(SaveDirectory);
        }
    }

    public bool SaveGame(Player player, string slotName)
    {
        try
        {
            var saveData = new SaveData
            {
                PlayerName = player.Name,
                Level = player.Level,
                Health = player.Health,
                MaxHealth = player.MaxHealth,
                Mana = player.Mana,
                MaxMana = player.MaxMana,
                Gold = player.Gold,
                Inventory = player.Inventory.Select(item => new ItemData
                {
                    Name = item.Name,
                    Description = item.Description,
                    Value = item.Value
                }).ToList(),
                SavedAt = DateTime.Now,
                SaveSlotName = slotName
            };

            string filePath = GetSaveFilePath(slotName);
            string jsonString = JsonSerializer.Serialize(saveData, new JsonSerializerOptions
            {
                WriteIndented = true
            });

            File.WriteAllText(filePath, jsonString);
            return true;
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error saving game: {ex.Message}");
            return false;
        }
    }

    public Player? LoadGame(string slotName)
    {
        try
        {
            string filePath = GetSaveFilePath(slotName);

            if (!File.Exists(filePath))
            {
                Console.WriteLine($"Save file not found: {slotName}");
                return null;
            }

            string jsonString = File.ReadAllText(filePath);
            var saveData = JsonSerializer.Deserialize<SaveData>(jsonString);

            if (saveData == null)
                return null;

            return new Player
            {
                Name = saveData.PlayerName,
                Level = saveData.Level,
                Health = saveData.Health,
                MaxHealth = saveData.MaxHealth,
                Mana = saveData.Mana,
                MaxMana = saveData.MaxMana,
                Gold = saveData.Gold,
                Inventory = saveData.Inventory.Select(item => new Item
                {
                    Name = item.Name,
                    Description = item.Description,
                    Value = item.Value
                }).ToList()
            };
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error loading game: {ex.Message}");
            return null;
        }
    }

    public bool DeleteSave(string slotName)
    {
        try
        {
            string filePath = GetSaveFilePath(slotName);

            if (File.Exists(filePath))
            {
                File.Delete(filePath);
                return true;
            }

            return false;
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error deleting save: {ex.Message}");
            return false;
        }
    }

    public List<SaveData> GetAllSaves()
    {
        var saves = new List<SaveData>();

        try
        {
            if (!Directory.Exists(SaveDirectory))
                return saves;

            var files = Directory.GetFiles(SaveDirectory, $"*{SaveFileExtension}");

            foreach (var file in files)
            {
                string jsonString = File.ReadAllText(file);
                var saveData = JsonSerializer.Deserialize<SaveData>(jsonString);
                if (saveData != null)
                {
                    saves.Add(saveData);
                }
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error loading save list: {ex.Message}");
        }

        return saves.OrderByDescending(s => s.SavedAt).ToList();
    }

    public bool SaveExists(string slotName)
    {
        return File.Exists(GetSaveFilePath(slotName));
    }

    private string GetSaveFilePath(string slotName)
    {
        string sanitizedName = string.Join("_", slotName.Split(Path.GetInvalidFileNameChars()));
        return Path.Combine(SaveDirectory, $"{sanitizedName}{SaveFileExtension}");
    }
}
