namespace RPGMenuSystem.Game;

/// <summary>
/// Comprehensive NPC system for the world of Aethermoor
/// Includes major characters, quest givers, and legendary figures
/// </summary>
public static class WorldCharacters
{
    public static List<NPCCharacter> GetAllMajorCharacters()
    {
        return new List<NPCCharacter>
        {
            // ==================== LEADERS & ROYALTY ====================
            
            new NPCCharacter
            {
                CharacterId = 1,
                Name = "King Aldarin Stormborn",
                Title = "High King of Valorian",
                Race = "Human",
                Class = "Paladin",
                Level = 50,
                Faction = "The Silver Alliance",
                Location = "Thornhaven, Royal Castle Valdemere",
                Alignment = "Lawful Good",
                Description = "The great king of the realm, wise and just, leading the fight against darkness",
                HistoryText = "Aldarin united the fractured kingdoms of Mortalis under one banner"
            },
            new NPCCharacter
            {
                CharacterId = 2,
                Name = "Queen Aelindor Moonwhisper",
                Title = "High Queen of the Elves",
                Race = "High Elf",
                Class = "Wizard",
                Level = 48,
                Faction = "Elven Courts",
                Location = "Silverleaf City, Emerald Vale",
                Alignment = "Neutral Good",
                Description = "Ancient and wise queen of the magical forests",
                HistoryText = "She has ruled the elves for over 3000 years with grace and wisdom"
            },
            new NPCCharacter
            {
                CharacterId = 3,
                Name = "King Thorin Stonebeard",
                Title = "High King of the Dwarves",
                Race = "Dwarf",
                Class = "Warrior",
                Level = 49,
                Faction = "Dwarven Clans",
                Location = "Ironforge Citadel",
                Alignment = "Lawful Neutral",
                Description = "Mighty dwarf king, master of mining and craftsmanship",
                HistoryText = "Thorin reclaimed the ancient dwarven kingdoms from darkness"
            },
            new NPCCharacter
            {
                CharacterId = 4,
                Name = "Archangel Uriel",
                Title = "Divine Commander of the Celestial Order",
                Race = "Celestial",
                Class = "Divine",
                Level = 60,
                Faction = "The Celestial Order",
                Location = "Heavenspire, Celestia",
                Alignment = "Lawful Good",
                Description = "Most powerful agent of good, ancient beyond measure",
                HistoryText = "Uriel has watched over Aethermoor since its creation"
            },
            new NPCCharacter
            {
                CharacterId = 5,
                Name = "The Lich King Morthos",
                Title = "Master of Death",
                Race = "Undead (formerly Human)",
                Class = "Necromancer",
                Level = 55,
                Faction = "Shadowlands Coalition",
                Location = "Blackthorn Citadel, The Shadowlands",
                Alignment = "Chaotic Evil",
                Description = "Ancient tyrant who cursed himself with undeath",
                HistoryText = "Morthos has plagued the world for 500 years with his corruption"
            },
            new NPCCharacter
            {
                CharacterId = 6,
                Name = "Archfiend Baltazar",
                Title = "Lord of Flames",
                Race = "Demon",
                Class = "Sorcerer",
                Level = 58,
                Faction = "Demonfire Empire",
                Location = "Infernus, Demonfire Wastes",
                Alignment = "Chaotic Evil",
                Description = "Demonic prince seeking to consume the world in fire",
                HistoryText = "Summoned from the abyss by dark cults, Baltazar grows stronger each year"
            },
            
            // ==================== LEGENDARY HEROES ====================
            
            new NPCCharacter
            {
                CharacterId = 7,
                Name = "Ranger Captain Thorne",
                Title = "Warden of the Frontier",
                Race = "Human",
                Class = "Ranger",
                Level = 45,
                Faction = "Ranger's Council",
                Location = "Sentinel Keep, Northmark Frontier",
                Alignment = "Chaotic Good",
                Description = "Expert tracker and protector of the wild lands",
                HistoryText = "Thorne has defended the frontier against countless monster invasions"
            },
            new NPCCharacter
            {
                CharacterId = 8,
                Name = "Archdruid Sylvanus",
                Title = "Circle Head",
                Race = "Half-Elf",
                Class = "Druid",
                Level = 46,
                Faction = "Druidic Circle",
                Location = "Deepwood Grotto, Shadowpine Jungle",
                Alignment = "Neutral Good",
                Description = "Guardian of nature's balance and ancient forests",
                HistoryText = "Sylvanus communes with nature itself, understanding the world's pulse"
            },
            new NPCCharacter
            {
                CharacterId = 9,
                Name = "Archmagus Valdris",
                Title = "Master of Magic",
                Race = "Elf",
                Class = "Wizard",
                Level = 47,
                Faction = "Mage Council",
                Location = "Spellforge Academy, Arcane Isles",
                Alignment = "Neutral",
                Description = "Eldest mage, seeker of magical knowledge beyond comprehension",
                HistoryText = "Valdris has written grimoires that define the laws of magic itself"
            },
            new NPCCharacter
            {
                CharacterId = 10,
                Name = "High Merchant Lord Cassius",
                Title = "Lord of Trade",
                Race = "Human",
                Class = "Rogue",
                Level = 40,
                Faction = "Merchant's Confluence",
                Location = "Goldport, Merchant's Confluence",
                Alignment = "Neutral",
                Description = "Master of commerce and trade across continents",
                HistoryText = "Cassius has accumulated wealth rivaling kingdoms through shrewd dealings"
            },
            
            // ==================== LEGENDARY WARRIORS ====================
            
            new NPCCharacter
            {
                CharacterId = 11,
                Name = "Sir Greywind",
                Title = "Knight of the Silver Dragon",
                Race = "Human",
                Class = "Paladin",
                Level = 44,
                Faction = "The Silver Alliance",
                Location = "Royal Castle Valdemere",
                Alignment = "Lawful Good",
                Description = "Greatest knight of the realm, wielder of divine magic",
                HistoryText = "Greywind has never lost a single duel in his entire life"
            },
            new NPCCharacter
            {
                CharacterId = 12,
                Name = "Storm Lord Tempestus",
                Title = "Lord of Thunder",
                Race = "Storm Giant",
                Class = "Shaman",
                Level = 52,
                Faction = "Order of the Tempest",
                Location = "Stormhaven, Storm Islands",
                Alignment = "Neutral",
                Description = "Master of storms, controlling weather across the sky realms",
                HistoryText = "Tempestus has ruled the storm islands since the world's creation"
            },
            new NPCCharacter
            {
                CharacterId = 13,
                Name = "Pharaoh Amenhotep",
                Title = "Divine Ruler of Scarab Dynasty",
                Race = "Human",
                Class = "Priest",
                Level = 43,
                Faction = "Scarab Dynasty",
                Location = "Amuntep, Scarab Dynasty",
                Alignment = "Lawful Neutral",
                Description = "Ancient ruler preserving the traditions of his civilization",
                HistoryText = "Amenhotep's lineage has ruled for 2000 years unbroken"
            },
            
            // ==================== VILLAINS & DARK LORDS ====================
            
            new NPCCharacter
            {
                CharacterId = 14,
                Name = "Matriarch Lolth's Chosen",
                Title = "Spider Queen's Voice",
                Race = "Dark Elf",
                Class = "Cleric",
                Level = 50,
                Faction = "Drow Empire",
                Location = "Menzoberranzan, Underdark Abyss",
                Alignment = "Chaotic Evil",
                Description = "High priestess of the demonic spider god",
                HistoryText = "She spreads the will of Lolth through the dark realms"
            },
            new NPCCharacter
            {
                CharacterId = 15,
                Name = "Warlord Grakthak",
                Title = "Chief of Goblin Clans",
                Race = "Goblin",
                Class = "Warrior",
                Level = 38,
                Faction = "Goblin Hordes",
                Location = "Grakthak's Fortress",
                Alignment = "Chaotic Neutral",
                Description = "Brutal goblin leader controlling vast raiding parties",
                HistoryText = "Grakthak rose from slavery to become the mightiest goblin ever"
            },
            new NPCCharacter
            {
                CharacterId = 16,
                Name = "Death Knight Vorgrim",
                Title = "Harbinger of Death",
                Race = "Undead",
                Class = "Death Knight",
                Level = 48,
                Faction = "Shadowlands Coalition",
                Location = "Blackthorn Citadel",
                Alignment = "Chaotic Evil",
                Description = "Cursed warrior eternally bound to the Lich King",
                HistoryText = "Vorgrim was once a noble knight, now twisted by undeath"
            },
            
            // ==================== MENTOR CHARACTERS ====================
            
            new NPCCharacter
            {
                CharacterId = 17,
                Name = "Master Aldren",
                Title = "Combat Trainer",
                Race = "Human",
                Class = "Fighter",
                Level = 35,
                Faction = "The Silver Alliance",
                Location = "Thornhaven, Training Grounds",
                Alignment = "Lawful Good",
                Description = "Veteran warrior who trains the next generation of heroes",
                HistoryText = "Aldren has trained thousands of soldiers and adventurers"
            },
            new NPCCharacter
            {
                CharacterId = 18,
                Name = "Loremaster Eldric",
                Title = "Keeper of Ancient Knowledge",
                Race = "Elf",
                Class = "Wizard",
                Level = 42,
                Faction = "Elven Courts",
                Location = "Silverleaf Library",
                Alignment = "Neutral Good",
                Description = "Wise scholar preserving the history of ages",
                HistoryText = "Eldric's memory spans centuries of recorded history"
            },
            new NPCCharacter
            {
                CharacterId = 19,
                Name = "Grandmaster Elorah",
                Title = "Monastery Head",
                Race = "Human",
                Class = "Monk",
                Level = 44,
                Faction = "The Celestial Order",
                Location = "Skyward Monastery, Drakespine Mountains",
                Alignment = "Lawful Good",
                Description = "Master of martial arts and spiritual discipline",
                HistoryText = "Elorah has trained monks in peace and combat for 50 years"
            },
            new NPCCharacter
            {
                CharacterId = 20,
                Name = "Shaman Kaida",
                Title = "Jungle Shaman",
                Race = "Human",
                Class = "Shaman",
                Level = 40,
                Faction = "Lusatian Jungles",
                Location = "Serpent Temple",
                Alignment = "Neutral Good",
                Description = "Spiritual leader bridging the world of spirits and mortals",
                HistoryText = "Kaida communes with ancient jungle spirits dating back millennia"
            }
        };
    }
}

public class NPCCharacter
{
    public int CharacterId { get; set; }
    public string Name { get; set; } = string.Empty;
    public string Title { get; set; } = string.Empty;
    public string Race { get; set; } = string.Empty;
    public string Class { get; set; } = string.Empty;
    public int Level { get; set; }
    public string Faction { get; set; } = string.Empty;
    public string Location { get; set; } = string.Empty;
    public string Alignment { get; set; } = string.Empty;
    public string Description { get; set; } = string.Empty;
    public string HistoryText { get; set; } = string.Empty;
    public List<int> QuestIds { get; set; } = new();
    public List<string> AvailableDialogues { get; set; } = new();
    
    public string GetFullTitle() => $"{Name}, {Title}";
}

// ==================== LEGENDARY BEASTS & BOSSES ====================

public static class LegendaryBeasts
{
    public static List<LegendaryEnemy> GetLegendaryEnemies()
    {
        return new List<LegendaryEnemy>
        {
            new LegendaryEnemy
            {
                BeastId = 1,
                Name = "Chromatic Dragon Destronax",
                Type = "Ancient Dragon",
                HealthPoints = 100000,
                Level = 50,
                Location = "Chromatic Spire, Drakespine Mountains",
                Description = "Ancient chromatic dragon who has lived for millennia",
                LootTable = new List<string> { "Dragon Heart", "Chromatic Scale Armor", "Ancient Treasure" }
            },
            new LegendaryEnemy
            {
                BeastId = 2,
                Name = "Kraken of Blackwater",
                Type = "Ancient Sea Beast",
                HealthPoints = 80000,
                Level = 48,
                Location = "Blackwater Bay, Murky Depths",
                Description = "Tentacled horror that rules the darkest waters",
                LootTable = new List<string> { "Kraken Tentacle", "Pearl of Power", "Ocean's Blessing" }
            },
            new LegendaryEnemy
            {
                BeastId = 3,
                Name = "Lich King Morthos",
                Type = "Undead Tyrant",
                HealthPoints = 120000,
                Level = 55,
                Location = "Eternal Darkness, Blackthorn Citadel",
                Description = "Ultimate boss of the Shadowlands, source of all undeath",
                LootTable = new List<string> { "Frostmourne", "Crown of Eternal Undeath", "Philosopher's Stone" }
            },
            new LegendaryEnemy
            {
                BeastId = 4,
                Name = "Inferno Titan Pyraeos",
                Type = "Fire Giant",
                HealthPoints = 95000,
                Level = 52,
                Location = "Magma Core, Volcano Summit",
                Description = "Ancient fire deity taking mortal form",
                LootTable = new List<string> { "Flame of Creation", "Infernal Scepter", "Volcanic Heart" }
            },
            new LegendaryEnemy
            {
                BeastId = 5,
                Name = "Abyssal Hydra of the Swamp",
                Type = "Mythological Beast",
                HealthPoints = 85000,
                Level = 47,
                Location = "Yochlol's Lair, Murky Depths",
                Description = "Many-headed serpent dwelling in poisonous depths",
                LootTable = new List<string> { "Hydra Scale", "Regeneration Potion", "Poison Gland" }
            }
        };
    }
}

public class LegendaryEnemy
{
    public int BeastId { get; set; }
    public string Name { get; set; } = string.Empty;
    public string Type { get; set; } = string.Empty;
    public int HealthPoints { get; set; }
    public int Level { get; set; }
    public string Location { get; set; } = string.Empty;
    public string Description { get; set; } = string.Empty;
    public List<string> LootTable { get; set; } = new();
    public bool IsDefeated { get; set; } = false;
}
