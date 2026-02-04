-- ============================================
-- RPG/MMORPG Database Schema - Part 3
-- Status Effects, World Events, Analytics
-- ============================================

-- ============================================
-- STATUS EFFECTS & BUFFS/DEBUFFS
-- ============================================

CREATE TABLE StatusEffects (
    EffectId INT PRIMARY KEY IDENTITY(1,1),
    EffectName NVARCHAR(100) NOT NULL,
    Description NVARCHAR(500),
    EffectType INT NOT NULL, -- Buff=0, Debuff=1, DOT=2, HOT=3, CC=4
    CCType INT, -- Stun=1, Root=2, Silence=3, etc.
    Duration FLOAT NOT NULL, -- seconds
    TickInterval FLOAT, -- For DOT/HOT
    MaxStacks INT NOT NULL DEFAULT 1,
    IsDispellable BIT NOT NULL DEFAULT 1,
    IconPath NVARCHAR(200),
    
    -- Effect Values (JSON)
    StatModifiersJson NVARCHAR(MAX),
    DamagePerTick INT DEFAULT 0,
    HealPerTick INT DEFAULT 0
);

CREATE TABLE CharacterStatusEffects (
    CharacterEffectId INT PRIMARY KEY IDENTITY(1,1),
    CharacterId INT NOT NULL,
    EffectId INT NOT NULL,
    SourceCharacterId INT, -- Who applied it
    StackCount INT NOT NULL DEFAULT 1,
    RemainingTime FLOAT NOT NULL,
    AppliedDate DATETIME NOT NULL DEFAULT GETDATE(),
    FOREIGN KEY (CharacterId) REFERENCES Characters(CharacterId) ON DELETE CASCADE,
    FOREIGN KEY (EffectId) REFERENCES StatusEffects(EffectId),
    FOREIGN KEY (SourceCharacterId) REFERENCES Characters(CharacterId),
    INDEX IDX_CharacterId (CharacterId)
);

-- ============================================
-- WORLD EVENTS
-- ============================================

CREATE TABLE WorldEvents (
    EventId INT PRIMARY KEY IDENTITY(1,1),
    EventName NVARCHAR(100) NOT NULL,
    Description NVARCHAR(1000),
    EventType INT NOT NULL, -- Seasonal=0, Random=1, Scheduled=2
    Duration INT NOT NULL, -- seconds
    
    -- Scheduling
    StartTime DATETIME,
    EndTime DATETIME,
    RecurrenceRule NVARCHAR(200), -- For repeating events
    
    -- Affected Zones (JSON array)
    AffectedZonesJson NVARCHAR(MAX),
    
    -- Rewards (JSON)
    RewardsJson NVARCHAR(MAX),
    
    IsActive BIT NOT NULL DEFAULT 0,
    
    INDEX IDX_IsActive (IsActive),
    INDEX IDX_StartTime (StartTime)
);

CREATE TABLE CharacterEventParticipation (
    ParticipationId INT PRIMARY KEY IDENTITY(1,1),
    CharacterId INT NOT NULL,
    EventId INT NOT NULL,
    ContributionScore INT NOT NULL DEFAULT 0,
    RewardsClaimed BIT NOT NULL DEFAULT 0,
    ParticipatedDate DATETIME NOT NULL DEFAULT GETDATE(),
    FOREIGN KEY (CharacterId) REFERENCES Characters(CharacterId) ON DELETE CASCADE,
    FOREIGN KEY (EventId) REFERENCES WorldEvents(EventId),
    INDEX IDX_CharacterId (CharacterId),
    INDEX IDX_EventId (EventId)
);

-- ============================================
-- RESOURCE NODES (Gathering)
-- ============================================

CREATE TABLE ResourceNodes (
    NodeId INT PRIMARY KEY IDENTITY(1,1),
    NodeName NVARCHAR(100) NOT NULL,
    ResourceType INT NOT NULL, -- Herb=0, Ore=1, Fish=2, Wood=3, Treasure=4
    RequiredSkill INT NOT NULL,
    ZoneId INT NOT NULL,
    PositionX FLOAT NOT NULL,
    PositionY FLOAT NOT NULL,
    PositionZ FLOAT NOT NULL,
    RespawnTime INT NOT NULL DEFAULT 300, -- seconds
    IsActive BIT NOT NULL DEFAULT 1,
    LastHarvestTime DATETIME,
    FOREIGN KEY (ZoneId) REFERENCES Zones(ZoneId),
    INDEX IDX_ZoneId (ZoneId),
    INDEX IDX_ResourceType (ResourceType)
);

CREATE TABLE ResourceNodeDrops (
    DropId INT PRIMARY KEY IDENTITY(1,1),
    NodeId INT NOT NULL,
    ItemId INT NOT NULL,
    DropChance FLOAT NOT NULL,
    MinQuantity INT NOT NULL DEFAULT 1,
    MaxQuantity INT NOT NULL DEFAULT 1,
    FOREIGN KEY (NodeId) REFERENCES ResourceNodes(NodeId) ON DELETE CASCADE,
    FOREIGN KEY (ItemId) REFERENCES Items(ItemId),
    INDEX IDX_NodeId (NodeId)
);

-- ============================================
-- COMPANIONS
-- ============================================

CREATE TABLE Companions (
    CompanionId INT PRIMARY KEY IDENTITY(1,1),
    CompanionName NVARCHAR(100) NOT NULL,
    Class INT NOT NULL,
    Race INT NOT NULL,
    BaseLevel INT NOT NULL DEFAULT 1,
    
    -- Base Stats
    BaseHealth INT NOT NULL DEFAULT 100,
    BaseAttack INT NOT NULL DEFAULT 10,
    BaseDefense INT NOT NULL DEFAULT 5,
    BaseMagicPower INT NOT NULL DEFAULT 8,
    
    -- Story
    BackgroundStory NVARCHAR(2000),
    PersonalQuestId INT,
    
    -- Recruitment
    RecruitmentQuestId INT,
    RecruitmentLocation NVARCHAR(200),
    
    ModelPath NVARCHAR(200),
    PortraitPath NVARCHAR(200),
    
    FOREIGN KEY (PersonalQuestId) REFERENCES Quests(QuestId),
    FOREIGN KEY (RecruitmentQuestId) REFERENCES Quests(QuestId)
);

CREATE TABLE CompanionAbilities (
    AbilityId INT PRIMARY KEY IDENTITY(1,1),
    CompanionId INT NOT NULL,
    AbilityName NVARCHAR(100) NOT NULL,
    Description NVARCHAR(500),
    Cooldown INT NOT NULL, -- seconds
    ManaCost INT NOT NULL DEFAULT 0,
    Damage INT NOT NULL DEFAULT 0,
    HealAmount INT NOT NULL DEFAULT 0,
    FOREIGN KEY (CompanionId) REFERENCES Companions(CompanionId) ON DELETE CASCADE,
    INDEX IDX_CompanionId (CompanionId)
);

CREATE TABLE CharacterCompanions (
    CharacterCompanionId INT PRIMARY KEY IDENTITY(1,1),
    CharacterId INT NOT NULL,
    CompanionId INT NOT NULL,
    CustomName NVARCHAR(50),
    Level INT NOT NULL DEFAULT 1,
    Experience INT NOT NULL DEFAULT 0,
    Loyalty INT NOT NULL DEFAULT 50, -- 0-100
    
    -- Current Stats
    Health INT NOT NULL,
    MaxHealth INT NOT NULL,
    
    -- Behavior
    AIBehavior INT NOT NULL DEFAULT 2, -- Aggressive=0, Defensive=1, Balanced=2
    IsInParty BIT NOT NULL DEFAULT 0,
    
    RecruitedDate DATETIME NOT NULL DEFAULT GETDATE(),
    
    FOREIGN KEY (CharacterId) REFERENCES Characters(CharacterId) ON DELETE CASCADE,
    FOREIGN KEY (CompanionId) REFERENCES Companions(CompanionId),
    UNIQUE (CharacterId, CompanionId),
    INDEX IDX_CharacterId (CharacterId)
);

CREATE TABLE CompanionEquipment (
    EquipmentId INT PRIMARY KEY IDENTITY(1,1),
    CharacterCompanionId INT NOT NULL,
    SlotType INT NOT NULL,
    ItemId INT NOT NULL,
    FOREIGN KEY (CharacterCompanionId) REFERENCES CharacterCompanions(CharacterCompanionId) ON DELETE CASCADE,
    FOREIGN KEY (ItemId) REFERENCES Items(ItemId),
    UNIQUE (CharacterCompanionId, SlotType)
);

-- ============================================
-- DIALOGUE SYSTEM
-- ============================================

CREATE TABLE DialogueTrees (
    DialogueTreeId INT PRIMARY KEY IDENTITY(1,1),
    TreeName NVARCHAR(100) NOT NULL,
    NpcId INT,
    CompanionId INT,
    FOREIGN KEY (NpcId) REFERENCES NPCs(NpcId),
    FOREIGN KEY (CompanionId) REFERENCES Companions(CompanionId)
);

CREATE TABLE DialogueNodes (
    NodeId INT PRIMARY KEY IDENTITY(1,1),
    DialogueTreeId INT NOT NULL,
    NodeIndex INT NOT NULL,
    SpeakerName NVARCHAR(100),
    DialogueText NVARCHAR(2000),
    EmotionTag NVARCHAR(50),
    AudioPath NVARCHAR(200),
    FOREIGN KEY (DialogueTreeId) REFERENCES DialogueTrees(DialogueTreeId) ON DELETE CASCADE,
    INDEX IDX_DialogueTreeId (DialogueTreeId)
);

CREATE TABLE DialogueChoices (
    ChoiceId INT PRIMARY KEY IDENTITY(1,1),
    NodeId INT NOT NULL,
    ChoiceText NVARCHAR(500),
    NextNodeIndex INT NOT NULL,
    
    -- Requirements
    RequiresSkillCheck BIT NOT NULL DEFAULT 0,
    RequiredSkill NVARCHAR(50),
    RequiredSkillLevel INT,
    
    -- Effects
    MoralityImpact INT NOT NULL DEFAULT 0,
    ReputationChange INT NOT NULL DEFAULT 0,
    FactionId INT,
    
    -- Rewards/Consequences (JSON)
    ConsequencesJson NVARCHAR(MAX),
    
    FOREIGN KEY (NodeId) REFERENCES DialogueNodes(NodeId) ON DELETE CASCADE,
    FOREIGN KEY (FactionId) REFERENCES Factions(FactionId),
    INDEX IDX_NodeId (NodeId)
);

-- ============================================
-- TRANSMOG / APPEARANCE
-- ============================================

CREATE TABLE TransmogAppearances (
    AppearanceId INT PRIMARY KEY IDENTITY(1,1),
    ItemId INT NOT NULL UNIQUE,
    AppearanceName NVARCHAR(100),
    Category INT NOT NULL, -- Weapon=0, Armor=1, Back=2, etc.
    FOREIGN KEY (ItemId) REFERENCES Items(ItemId)
);

CREATE TABLE CharacterTransmog (
    TransmogId INT PRIMARY KEY IDENTITY(1,1),
    CharacterId INT NOT NULL,
    SlotType INT NOT NULL,
    AppearanceId INT NOT NULL,
    FOREIGN KEY (CharacterId) REFERENCES Characters(CharacterId) ON DELETE CASCADE,
    FOREIGN KEY (AppearanceId) REFERENCES TransmogAppearances(AppearanceId),
    UNIQUE (CharacterId, SlotType),
    INDEX IDX_CharacterId (CharacterId)
);

CREATE TABLE CharacterUnlockedAppearances (
    UnlockId INT PRIMARY KEY IDENTITY(1,1),
    CharacterId INT NOT NULL,
    AppearanceId INT NOT NULL,
    UnlockedDate DATETIME NOT NULL DEFAULT GETDATE(),
    FOREIGN KEY (CharacterId) REFERENCES Characters(CharacterId) ON DELETE CASCADE,
    FOREIGN KEY (AppearanceId) REFERENCES TransmogAppearances(AppearanceId),
    UNIQUE (CharacterId, AppearanceId),
    INDEX IDX_CharacterId (CharacterId)
);

-- ============================================
-- FRIENDS & SOCIAL
-- ============================================

CREATE TABLE FriendsList (
    FriendshipId INT PRIMARY KEY IDENTITY(1,1),
    CharacterId INT NOT NULL,
    FriendCharacterId INT NOT NULL,
    FriendshipStatus INT NOT NULL DEFAULT 0, -- Pending=0, Accepted=1, Blocked=2
    RequestedDate DATETIME NOT NULL DEFAULT GETDATE(),
    AcceptedDate DATETIME,
    FOREIGN KEY (CharacterId) REFERENCES Characters(CharacterId),
    FOREIGN KEY (FriendCharacterId) REFERENCES Characters(CharacterId),
    CHECK (CharacterId != FriendCharacterId),
    UNIQUE (CharacterId, FriendCharacterId),
    INDEX IDX_CharacterId (CharacterId)
);

CREATE TABLE IgnoreList (
    IgnoreId INT PRIMARY KEY IDENTITY(1,1),
    CharacterId INT NOT NULL,
    IgnoredCharacterId INT NOT NULL,
    IgnoredDate DATETIME NOT NULL DEFAULT GETDATE(),
    Reason NVARCHAR(200),
    FOREIGN KEY (CharacterId) REFERENCES Characters(CharacterId) ON DELETE CASCADE,
    FOREIGN KEY (IgnoredCharacterId) REFERENCES Characters(CharacterId),
    UNIQUE (CharacterId, IgnoredCharacterId),
    INDEX IDX_CharacterId (CharacterId)
);

-- ============================================
-- CHAT & COMMUNICATION
-- ============================================

CREATE TABLE ChatMessages (
    MessageId INT PRIMARY KEY IDENTITY(1,1),
    SenderCharacterId INT NOT NULL,
    Channel INT NOT NULL, -- Say=0, Yell=1, Guild=2, Party=3, Whisper=4, etc.
    RecipientCharacterId INT, -- For whispers
    MessageText NVARCHAR(1000) NOT NULL,
    SentDate DATETIME NOT NULL DEFAULT GETDATE(),
    FOREIGN KEY (SenderCharacterId) REFERENCES Characters(CharacterId),
    FOREIGN KEY (RecipientCharacterId) REFERENCES Characters(CharacterId),
    INDEX IDX_SenderCharacterId (SenderCharacterId),
    INDEX IDX_Channel (Channel),
    INDEX IDX_SentDate (SentDate)
);

-- ============================================
-- ANALYTICS & TELEMETRY
-- ============================================

CREATE TABLE PlayerSessions (
    SessionId INT PRIMARY KEY IDENTITY(1,1),
    CharacterId INT NOT NULL,
    LoginTime DATETIME NOT NULL DEFAULT GETDATE(),
    LogoutTime DATETIME,
    SessionDuration AS DATEDIFF(SECOND, LoginTime, LogoutTime) PERSISTED,
    IPAddress NVARCHAR(50),
    FOREIGN KEY (CharacterId) REFERENCES Characters(CharacterId),
    INDEX IDX_CharacterId (CharacterId),
    INDEX IDX_LoginTime (LoginTime)
);

CREATE TABLE PlayerActions (
    ActionId BIGINT PRIMARY KEY IDENTITY(1,1),
    CharacterId INT NOT NULL,
    ActionType INT NOT NULL, -- Login=0, Logout=1, QuestComplete=2, ItemCraft=3, etc.
    ActionData NVARCHAR(MAX), -- JSON
    Timestamp DATETIME NOT NULL DEFAULT GETDATE(),
    FOREIGN KEY (CharacterId) REFERENCES Characters(CharacterId),
    INDEX IDX_CharacterId (CharacterId),
    INDEX IDX_ActionType (ActionType),
    INDEX IDX_Timestamp (Timestamp)
);

CREATE TABLE EconomyTransactions (
    TransactionId BIGINT PRIMARY KEY IDENTITY(1,1),
    CharacterId INT NOT NULL,
    TransactionType INT NOT NULL, -- Buy=0, Sell=1, Trade=2, AuctionBuy=3, etc.
    ItemId INT,
    Quantity INT NOT NULL DEFAULT 1,
    Price INT NOT NULL,
    OtherCharacterId INT, -- For trades
    Timestamp DATETIME NOT NULL DEFAULT GETDATE(),
    FOREIGN KEY (CharacterId) REFERENCES Characters(CharacterId),
    FOREIGN KEY (ItemId) REFERENCES Items(ItemId),
    FOREIGN KEY (OtherCharacterId) REFERENCES Characters(CharacterId),
    INDEX IDX_CharacterId (CharacterId),
    INDEX IDX_TransactionType (TransactionType),
    INDEX IDX_Timestamp (Timestamp)
);

-- ============================================
-- MODERATION & REPORTS
-- ============================================

CREATE TABLE PlayerReports (
    ReportId INT PRIMARY KEY IDENTITY(1,1),
    ReporterCharacterId INT NOT NULL,
    ReportedCharacterId INT NOT NULL,
    ReportType INT NOT NULL, -- Cheating=0, Harassment=1, Spam=2, etc.
    Description NVARCHAR(2000),
    Evidence NVARCHAR(MAX), -- Screenshots, logs, etc.
    Status INT NOT NULL DEFAULT 0, -- Pending=0, Reviewed=1, Resolved=2, Dismissed=3
    ReportDate DATETIME NOT NULL DEFAULT GETDATE(),
    ResolvedDate DATETIME,
    ResolvedBy NVARCHAR(100),
    ResolutionNotes NVARCHAR(1000),
    FOREIGN KEY (ReporterCharacterId) REFERENCES Characters(CharacterId),
    FOREIGN KEY (ReportedCharacterId) REFERENCES Characters(CharacterId),
    INDEX IDX_Status (Status),
    INDEX IDX_ReportDate (ReportDate)
);

CREATE TABLE Bans (
    BanId INT PRIMARY KEY IDENTITY(1,1),
    AccountId INT,
    CharacterId INT,
    BanType INT NOT NULL, -- Temporary=0, Permanent=1, Suspension=2
    Reason NVARCHAR(1000) NOT NULL,
    BannedBy NVARCHAR(100) NOT NULL,
    BanDate DATETIME NOT NULL DEFAULT GETDATE(),
    ExpiryDate DATETIME,
    IsActive BIT NOT NULL DEFAULT 1,
    FOREIGN KEY (AccountId) REFERENCES Accounts(AccountId),
    FOREIGN KEY (CharacterId) REFERENCES Characters(CharacterId),
    INDEX IDX_AccountId (AccountId),
    INDEX IDX_IsActive (IsActive)
);

-- ============================================
-- LEADERBOARDS
-- ============================================

CREATE TABLE Leaderboards (
    LeaderboardId INT PRIMARY KEY IDENTITY(1,1),
    LeaderboardType INT NOT NULL, -- Level=0, PvP=1, Wealth=2, Achievements=3, etc.
    Season INT,
    StartDate DATETIME NOT NULL,
    EndDate DATETIME
);

CREATE TABLE LeaderboardEntries (
    EntryId INT PRIMARY KEY IDENTITY(1,1),
    LeaderboardId INT NOT NULL,
    CharacterId INT NOT NULL,
    Rank INT NOT NULL,
    Score BIGINT NOT NULL,
    UpdatedDate DATETIME NOT NULL DEFAULT GETDATE(),
    FOREIGN KEY (LeaderboardId) REFERENCES Leaderboards(LeaderboardId) ON DELETE CASCADE,
    FOREIGN KEY (CharacterId) REFERENCES Characters(CharacterId),
    UNIQUE (LeaderboardId, CharacterId),
    INDEX IDX_LeaderboardId_Rank (LeaderboardId, Rank)
);

-- ============================================
-- INDEXES FOR PERFORMANCE
-- ============================================

-- Additional composite indexes for common queries
CREATE INDEX IDX_Characters_AccountId_Level ON Characters(AccountId, Level);
CREATE INDEX IDX_Characters_GuildId_GuildRank ON Characters(GuildId, GuildRank);
CREATE INDEX IDX_Items_Type_Quality ON Items(ItemType, Quality);
CREATE INDEX IDX_Enemies_Level_Type ON Enemies(Level, EnemyType);
CREATE INDEX IDX_Quests_Level_Type ON Quests(RequiredLevel, QuestType);
CREATE INDEX IDX_AuctionListings_Status_ItemId ON AuctionListings(Status, ItemId);
CREATE INDEX IDX_CharacterQuests_CharacterId_Status ON CharacterQuests(CharacterId, Status);
