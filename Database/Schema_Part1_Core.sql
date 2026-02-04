-- ============================================
-- RPG/MMORPG Database Schema
-- Complete Database Structure for All Systems
-- ============================================

-- ============================================
-- CHARACTERS & ACCOUNTS
-- ============================================

CREATE TABLE Accounts (
    AccountId INT PRIMARY KEY IDENTITY(1,1),
    Username NVARCHAR(50) NOT NULL UNIQUE,
    Email NVARCHAR(100) NOT NULL UNIQUE,
    PasswordHash NVARCHAR(256) NOT NULL,
    Salt NVARCHAR(128) NOT NULL,
    CreatedDate DATETIME NOT NULL DEFAULT GETDATE(),
    LastLoginDate DATETIME,
    IsBanned BIT NOT NULL DEFAULT 0,
    BanReason NVARCHAR(500),
    SubscriptionTier INT NOT NULL DEFAULT 0,
    SubscriptionExpiry DATETIME,
    INDEX IDX_Username (Username),
    INDEX IDX_Email (Email)
);

CREATE TABLE Characters (
    CharacterId INT PRIMARY KEY IDENTITY(1,1),
    AccountId INT NOT NULL,
    CharacterName NVARCHAR(50) NOT NULL UNIQUE,
    Race INT NOT NULL, -- Enum: Human=0, Elf=1, Dwarf=2, etc.
    Class INT NOT NULL, -- Enum: Warrior=0, Mage=1, etc.
    Specialization INT, -- Enum: WarriorArms=0, etc.
    Level INT NOT NULL DEFAULT 1,
    Experience INT NOT NULL DEFAULT 0,
    
    -- Primary Stats
    Strength INT NOT NULL DEFAULT 10,
    Agility INT NOT NULL DEFAULT 10,
    Intelligence INT NOT NULL DEFAULT 10,
    Stamina INT NOT NULL DEFAULT 10,
    Spirit INT NOT NULL DEFAULT 10,
    
    -- Secondary Stats
    CriticalStrike INT NOT NULL DEFAULT 0,
    Haste INT NOT NULL DEFAULT 0,
    Mastery INT NOT NULL DEFAULT 0,
    Versatility INT NOT NULL DEFAULT 0,
    
    -- Resources
    Health INT NOT NULL DEFAULT 100,
    MaxHealth INT NOT NULL DEFAULT 100,
    Mana INT NOT NULL DEFAULT 50,
    MaxMana INT NOT NULL DEFAULT 50,
    
    -- Currency
    Gold INT NOT NULL DEFAULT 0,
    PremiumCurrency INT NOT NULL DEFAULT 0,
    HonorPoints INT NOT NULL DEFAULT 0,
    ArenaRating INT NOT NULL DEFAULT 1500,
    
    -- Location
    CurrentZoneId INT,
    PositionX FLOAT NOT NULL DEFAULT 0,
    PositionY FLOAT NOT NULL DEFAULT 0,
    PositionZ FLOAT NOT NULL DEFAULT 0,
    
    -- Progression
    TalentPoints INT NOT NULL DEFAULT 0,
    AchievementPoints INT NOT NULL DEFAULT 0,
    PlayedTime INT NOT NULL DEFAULT 0, -- seconds
    
    -- Social
    GuildId INT,
    GuildRank INT,
    
    -- Morality
    Alignment INT NOT NULL DEFAULT 0, -- -100 to 100
    Karma INT NOT NULL DEFAULT 0,
    
    -- Meta
    CreatedDate DATETIME NOT NULL DEFAULT GETDATE(),
    LastPlayedDate DATETIME,
    IsDeleted BIT NOT NULL DEFAULT 0,
    
    FOREIGN KEY (AccountId) REFERENCES Accounts(AccountId),
    FOREIGN KEY (CurrentZoneId) REFERENCES Zones(ZoneId),
    FOREIGN KEY (GuildId) REFERENCES Guilds(GuildId),
    INDEX IDX_CharacterName (CharacterName),
    INDEX IDX_AccountId (AccountId),
    INDEX IDX_Level (Level)
);

-- ============================================
-- ITEMS & EQUIPMENT
-- ============================================

CREATE TABLE Items (
    ItemId INT PRIMARY KEY IDENTITY(1,1),
    ItemName NVARCHAR(100) NOT NULL,
    Description NVARCHAR(1000),
    ItemType INT NOT NULL, -- Enum: Weapon=0, Armor=1, Consumable=2, etc.
    Quality INT NOT NULL, -- Enum: Poor=0, Common=1, Uncommon=2, Rare=3, Epic=4, Legendary=5
    ItemLevel INT NOT NULL DEFAULT 1,
    RequiredLevel INT NOT NULL DEFAULT 1,
    RequiredClass INT, -- NULL = all classes
    MaxStack INT NOT NULL DEFAULT 1,
    Value INT NOT NULL DEFAULT 1,
    IsSoulbound BIT NOT NULL DEFAULT 0,
    IsUnique BIT NOT NULL DEFAULT 0,
    
    -- Equipment Specific
    EquipmentSlot INT, -- Enum: Head=0, Neck=1, etc.
    WeaponType INT, -- Enum: Sword=0, Axe=1, etc.
    ArmorType INT, -- Enum: Cloth=0, Leather=1, Mail=2, Plate=3
    
    -- Sockets
    SocketCount INT NOT NULL DEFAULT 0,
    
    -- Stats (JSON or separate table)
    StatsJson NVARCHAR(MAX), -- JSON: {"Strength": 10, "Agility": 5}
    
    -- Metadata
    IconPath NVARCHAR(200),
    ModelPath NVARCHAR(200),
    CreatedDate DATETIME NOT NULL DEFAULT GETDATE(),
    
    INDEX IDX_ItemType (ItemType),
    INDEX IDX_Quality (Quality),
    INDEX IDX_RequiredLevel (RequiredLevel)
);

CREATE TABLE ItemStats (
    ItemStatId INT PRIMARY KEY IDENTITY(1,1),
    ItemId INT NOT NULL,
    StatName NVARCHAR(50) NOT NULL, -- "Strength", "Agility", etc.
    StatValue INT NOT NULL,
    FOREIGN KEY (ItemId) REFERENCES Items(ItemId) ON DELETE CASCADE,
    INDEX IDX_ItemId (ItemId)
);

CREATE TABLE CharacterInventory (
    InventoryId INT PRIMARY KEY IDENTITY(1,1),
    CharacterId INT NOT NULL,
    ItemId INT NOT NULL,
    Quantity INT NOT NULL DEFAULT 1,
    SlotRow INT NOT NULL,
    SlotColumn INT NOT NULL,
    
    -- Gem/Enchant Info
    SocketedGems NVARCHAR(MAX), -- JSON array of ItemIds
    EnchantId INT,
    
    -- Metadata
    AcquiredDate DATETIME NOT NULL DEFAULT GETDATE(),
    
    FOREIGN KEY (CharacterId) REFERENCES Characters(CharacterId) ON DELETE CASCADE,
    FOREIGN KEY (ItemId) REFERENCES Items(ItemId),
    INDEX IDX_CharacterId (CharacterId),
    UNIQUE (CharacterId, SlotRow, SlotColumn)
);

CREATE TABLE CharacterEquipment (
    EquipmentId INT PRIMARY KEY IDENTITY(1,1),
    CharacterId INT NOT NULL,
    SlotType INT NOT NULL, -- Enum: Head=0, etc.
    ItemId INT NOT NULL,
    
    -- Gem/Enchant
    SocketedGems NVARCHAR(MAX), -- JSON
    EnchantId INT,
    
    FOREIGN KEY (CharacterId) REFERENCES Characters(CharacterId) ON DELETE CASCADE,
    FOREIGN KEY (ItemId) REFERENCES Items(ItemId),
    UNIQUE (CharacterId, SlotType),
    INDEX IDX_CharacterId (CharacterId)
);

CREATE TABLE CharacterBank (
    BankId INT PRIMARY KEY IDENTITY(1,1),
    CharacterId INT NOT NULL,
    TabIndex INT NOT NULL DEFAULT 0,
    ItemId INT NOT NULL,
    Quantity INT NOT NULL DEFAULT 1,
    SlotRow INT NOT NULL,
    SlotColumn INT NOT NULL,
    FOREIGN KEY (CharacterId) REFERENCES Characters(CharacterId) ON DELETE CASCADE,
    FOREIGN KEY (ItemId) REFERENCES Items(ItemId),
    INDEX IDX_CharacterId (CharacterId),
    UNIQUE (CharacterId, TabIndex, SlotRow, SlotColumn)
);

-- ============================================
-- WEAPONS & ARMOR (Detailed)
-- ============================================

CREATE TABLE Weapons (
    WeaponId INT PRIMARY KEY IDENTITY(1,1),
    ItemId INT NOT NULL UNIQUE,
    WeaponType INT NOT NULL, -- Sword, Axe, Staff, etc.
    MinDamage INT NOT NULL,
    MaxDamage INT NOT NULL,
    AttackSpeed FLOAT NOT NULL DEFAULT 2.0,
    DPS FLOAT AS (((MinDamage + MaxDamage) / 2.0) / AttackSpeed) PERSISTED,
    Range FLOAT NOT NULL DEFAULT 5.0,
    FOREIGN KEY (ItemId) REFERENCES Items(ItemId) ON DELETE CASCADE,
    INDEX IDX_WeaponType (WeaponType)
);

CREATE TABLE Armor (
    ArmorId INT PRIMARY KEY IDENTITY(1,1),
    ItemId INT NOT NULL UNIQUE,
    ArmorType INT NOT NULL, -- Cloth, Leather, Mail, Plate
    ArmorValue INT NOT NULL,
    FOREIGN KEY (ItemId) REFERENCES Items(ItemId) ON DELETE CASCADE,
    INDEX IDX_ArmorType (ArmorType)
);

-- ============================================
-- ZONES & WORLD
-- ============================================

CREATE TABLE Zones (
    ZoneId INT PRIMARY KEY IDENTITY(1,1),
    ZoneName NVARCHAR(100) NOT NULL,
    Description NVARCHAR(1000),
    ZoneType INT NOT NULL, -- Town=0, Village=1, Forest=2, etc.
    BiomeType INT NOT NULL, -- Grassland=0, Desert=1, etc.
    RecommendedLevel INT NOT NULL,
    IsUnderground BIT NOT NULL DEFAULT 0,
    Depth INT, -- For underground zones
    
    -- Features
    HasShop BIT NOT NULL DEFAULT 0,
    HasInn BIT NOT NULL DEFAULT 0,
    HasBank BIT NOT NULL DEFAULT 0,
    HasAuctionHouse BIT NOT NULL DEFAULT 0,
    HasFlightMaster BIT NOT NULL DEFAULT 0,
    
    -- Location
    ContinentId INT,
    ParentZoneId INT,
    
    -- Weather
    DefaultWeather INT NOT NULL DEFAULT 0,
    
    INDEX IDX_ZoneType (ZoneType),
    INDEX IDX_RecommendedLevel (RecommendedLevel)
);

CREATE TABLE ZoneConnections (
    ConnectionId INT PRIMARY KEY IDENTITY(1,1),
    FromZoneId INT NOT NULL,
    ToZoneId INT NOT NULL,
    IsDiscoverable BIT NOT NULL DEFAULT 1,
    FOREIGN KEY (FromZoneId) REFERENCES Zones(ZoneId),
    FOREIGN KEY (ToZoneId) REFERENCES Zones(ZoneId),
    INDEX IDX_FromZone (FromZoneId)
);

CREATE TABLE CharacterZoneDiscovery (
    DiscoveryId INT PRIMARY KEY IDENTITY(1,1),
    CharacterId INT NOT NULL,
    ZoneId INT NOT NULL,
    DiscoveredDate DATETIME NOT NULL DEFAULT GETDATE(),
    FOREIGN KEY (CharacterId) REFERENCES Characters(CharacterId) ON DELETE CASCADE,
    FOREIGN KEY (ZoneId) REFERENCES Zones(ZoneId),
    UNIQUE (CharacterId, ZoneId),
    INDEX IDX_CharacterId (CharacterId)
);

-- ============================================
-- NPCS
-- ============================================

CREATE TABLE NPCs (
    NpcId INT PRIMARY KEY IDENTITY(1,1),
    NpcName NVARCHAR(100) NOT NULL,
    Title NVARCHAR(100),
    NpcType INT NOT NULL, -- Vendor=0, QuestGiver=1, Trainer=2, etc.
    Level INT NOT NULL DEFAULT 1,
    Health INT NOT NULL DEFAULT 100,
    
    -- Location
    ZoneId INT NOT NULL,
    PositionX FLOAT NOT NULL,
    PositionY FLOAT NOT NULL,
    PositionZ FLOAT NOT NULL,
    
    -- Behavior
    IsHostile BIT NOT NULL DEFAULT 0,
    FactionId INT,
    
    -- Services
    IsVendor BIT NOT NULL DEFAULT 0,
    IsQuestGiver BIT NOT NULL DEFAULT 0,
    IsTrainer BIT NOT NULL DEFAULT 0,
    IsBanker BIT NOT NULL DEFAULT 0,
    IsFlightMaster BIT NOT NULL DEFAULT 0,
    
    -- Dialog
    GreetingText NVARCHAR(500),
    
    FOREIGN KEY (ZoneId) REFERENCES Zones(ZoneId),
    INDEX IDX_ZoneId (ZoneId),
    INDEX IDX_NpcType (NpcType)
);

-- ============================================
-- ENEMIES & BOSSES
-- ============================================

CREATE TABLE Enemies (
    EnemyId INT PRIMARY KEY IDENTITY(1,1),
    EnemyName NVARCHAR(100) NOT NULL,
    EnemyType INT NOT NULL, -- Beast=0, Humanoid=1, Undead=2, etc.
    EnemyRank INT NOT NULL, -- Normal=0, Elite=1, RareElite=2, Boss=3, WorldBoss=4
    Level INT NOT NULL,
    Health INT NOT NULL,
    Mana INT NOT NULL DEFAULT 0,
    
    -- Stats
    Attack INT NOT NULL,
    Defense INT NOT NULL,
    MagicPower INT NOT NULL DEFAULT 0,
    
    -- Rewards
    ExperienceReward INT NOT NULL,
    GoldReward INT NOT NULL,
    
    -- Abilities (JSON)
    AbilitiesJson NVARCHAR(MAX),
    
    -- Resistances (JSON)
    ResistancesJson NVARCHAR(MAX),
    WeaknessesJson NVARCHAR(MAX),
    
    -- Metadata
    Description NVARCHAR(500),
    ModelPath NVARCHAR(200),
    
    INDEX IDX_EnemyType (EnemyType),
    INDEX IDX_EnemyRank (EnemyRank),
    INDEX IDX_Level (Level)
);

CREATE TABLE EnemyLootTable (
    LootId INT PRIMARY KEY IDENTITY(1,1),
    EnemyId INT NOT NULL,
    ItemId INT NOT NULL,
    DropChance FLOAT NOT NULL, -- 0.0 to 1.0
    MinQuantity INT NOT NULL DEFAULT 1,
    MaxQuantity INT NOT NULL DEFAULT 1,
    FOREIGN KEY (EnemyId) REFERENCES Enemies(EnemyId) ON DELETE CASCADE,
    FOREIGN KEY (ItemId) REFERENCES Items(ItemId),
    INDEX IDX_EnemyId (EnemyId)
);

CREATE TABLE EnemySpawns (
    SpawnId INT PRIMARY KEY IDENTITY(1,1),
    EnemyId INT NOT NULL,
    ZoneId INT NOT NULL,
    PositionX FLOAT NOT NULL,
    PositionY FLOAT NOT NULL,
    PositionZ FLOAT NOT NULL,
    RespawnTime INT NOT NULL DEFAULT 300, -- seconds
    SpawnRadius FLOAT NOT NULL DEFAULT 10.0,
    FOREIGN KEY (EnemyId) REFERENCES Enemies(EnemyId),
    FOREIGN KEY (ZoneId) REFERENCES Zones(ZoneId),
    INDEX IDX_ZoneId (ZoneId)
);

-- ============================================
-- DUNGEONS & RAIDS
-- ============================================

CREATE TABLE Dungeons (
    DungeonId INT PRIMARY KEY IDENTITY(1,1),
    DungeonName NVARCHAR(100) NOT NULL,
    DungeonType INT NOT NULL, -- StandardDungeon=0, Raid=1, Trial=2, etc.
    Description NVARCHAR(1000),
    MinLevel INT NOT NULL,
    MaxLevel INT NOT NULL,
    MinPlayers INT NOT NULL,
    MaxPlayers INT NOT NULL,
    EstimatedTime INT NOT NULL, -- minutes
    LocationZoneId INT NOT NULL,
    
    FOREIGN KEY (LocationZoneId) REFERENCES Zones(ZoneId),
    INDEX IDX_DungeonType (DungeonType)
);

CREATE TABLE DungeonDifficulties (
    DifficultyId INT PRIMARY KEY IDENTITY(1,1),
    DungeonId INT NOT NULL,
    Difficulty INT NOT NULL, -- Normal=0, Heroic=1, Mythic=2, MythicPlus=3
    HealthMultiplier FLOAT NOT NULL DEFAULT 1.0,
    DamageMultiplier FLOAT NOT NULL DEFAULT 1.0,
    RewardMultiplier FLOAT NOT NULL DEFAULT 1.0,
    FOREIGN KEY (DungeonId) REFERENCES Dungeons(DungeonId) ON DELETE CASCADE,
    INDEX IDX_DungeonId (DungeonId)
);

CREATE TABLE DungeonBosses (
    BossId INT PRIMARY KEY IDENTITY(1,1),
    DungeonId INT NOT NULL,
    EnemyId INT NOT NULL,
    BossOrder INT NOT NULL, -- 1st boss, 2nd boss, etc.
    IsRaidBoss BIT NOT NULL DEFAULT 0,
    FOREIGN KEY (DungeonId) REFERENCES Dungeons(DungeonId) ON DELETE CASCADE,
    FOREIGN KEY (EnemyId) REFERENCES Enemies(EnemyId),
    INDEX IDX_DungeonId (DungeonId)
);

CREATE TABLE CharacterDungeonProgress (
    ProgressId INT PRIMARY KEY IDENTITY(1,1),
    CharacterId INT NOT NULL,
    DungeonId INT NOT NULL,
    Difficulty INT NOT NULL,
    BossesDefeated INT NOT NULL DEFAULT 0,
    IsCompleted BIT NOT NULL DEFAULT 0,
    CompletionTime INT, -- seconds
    DeathCount INT NOT NULL DEFAULT 0,
    CompletedDate DATETIME,
    FOREIGN KEY (CharacterId) REFERENCES Characters(CharacterId) ON DELETE CASCADE,
    FOREIGN KEY (DungeonId) REFERENCES Dungeons(DungeonId),
    INDEX IDX_CharacterId (CharacterId)
);

-- ============================================
-- QUESTS
-- ============================================

CREATE TABLE Quests (
    QuestId INT PRIMARY KEY IDENTITY(1,1),
    QuestName NVARCHAR(100) NOT NULL,
    Description NVARCHAR(2000),
    QuestType INT NOT NULL, -- Main=0, Side=1, Daily=2, Weekly=3, etc.
    RequiredLevel INT NOT NULL DEFAULT 1,
    
    -- Rewards
    ExperienceReward INT NOT NULL DEFAULT 0,
    GoldReward INT NOT NULL DEFAULT 0,
    ReputationReward INT NOT NULL DEFAULT 0,
    FactionId INT,
    
    -- Requirements
    RequiredQuestId INT, -- Prerequisite quest
    RequiredClass INT, -- NULL = all classes
    RequiredRace INT, -- NULL = all races
    
    -- NPC
    QuestGiverNpcId INT,
    QuestCompleterNpcId INT,
    
    -- Objectives (JSON or separate table)
    ObjectivesJson NVARCHAR(MAX),
    
    -- Metadata
    IsRepeatable BIT NOT NULL DEFAULT 0,
    IsSharable BIT NOT NULL DEFAULT 1,
    
    FOREIGN KEY (QuestGiverNpcId) REFERENCES NPCs(NpcId),
    FOREIGN KEY (QuestCompleterNpcId) REFERENCES NPCs(NpcId),
    INDEX IDX_QuestType (QuestType),
    INDEX IDX_RequiredLevel (RequiredLevel)
);

CREATE TABLE QuestObjectives (
    ObjectiveId INT PRIMARY KEY IDENTITY(1,1),
    QuestId INT NOT NULL,
    ObjectiveType INT NOT NULL, -- Kill=0, Collect=1, Interact=2, Escort=3, etc.
    Description NVARCHAR(500),
    TargetId INT, -- EnemyId or ItemId or NpcId depending on type
    RequiredCount INT NOT NULL DEFAULT 1,
    FOREIGN KEY (QuestId) REFERENCES Quests(QuestId) ON DELETE CASCADE,
    INDEX IDX_QuestId (QuestId)
);

CREATE TABLE CharacterQuests (
    CharacterQuestId INT PRIMARY KEY IDENTITY(1,1),
    CharacterId INT NOT NULL,
    QuestId INT NOT NULL,
    Status INT NOT NULL, -- Available=0, Active=1, Completed=2, Failed=3
    CurrentProgress NVARCHAR(MAX), -- JSON: {"ObjectiveId": progress}
    AcceptedDate DATETIME,
    CompletedDate DATETIME,
    FOREIGN KEY (CharacterId) REFERENCES Characters(CharacterId) ON DELETE CASCADE,
    FOREIGN KEY (QuestId) REFERENCES Quests(QuestId),
    INDEX IDX_CharacterId (CharacterId),
    INDEX IDX_Status (Status)
);

CREATE TABLE QuestRewardItems (
    RewardId INT PRIMARY KEY IDENTITY(1,1),
    QuestId INT NOT NULL,
    ItemId INT NOT NULL,
    Quantity INT NOT NULL DEFAULT 1,
    IsChoiceReward BIT NOT NULL DEFAULT 0, -- Player can choose one
    FOREIGN KEY (QuestId) REFERENCES Quests(QuestId) ON DELETE CASCADE,
    FOREIGN KEY (ItemId) REFERENCES Items(ItemId),
    INDEX IDX_QuestId (QuestId)
);

-- Continued in next file...
