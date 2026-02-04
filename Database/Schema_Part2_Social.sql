-- ============================================
-- RPG/MMORPG Database Schema - Part 2
-- Social, Economy, Progression Systems
-- ============================================

-- ============================================
-- GUILDS
-- ============================================

CREATE TABLE Guilds (
    GuildId INT PRIMARY KEY IDENTITY(1,1),
    GuildName NVARCHAR(100) NOT NULL UNIQUE,
    GuildTag NVARCHAR(10),
    GuildLevel INT NOT NULL DEFAULT 1,
    GuildExperience INT NOT NULL DEFAULT 0,
    GuildGold INT NOT NULL DEFAULT 0,
    MemberCount INT NOT NULL DEFAULT 0,
    MaxMembers INT AS (100 + (GuildLevel * 50)) PERSISTED,
    
    -- Leader
    GuildLeaderId INT NOT NULL,
    
    -- Info
    Description NVARCHAR(1000),
    MessageOfTheDay NVARCHAR(500),
    TabardDesign NVARCHAR(200),
    
    -- Metadata
    CreatedDate DATETIME NOT NULL DEFAULT GETDATE(),
    
    FOREIGN KEY (GuildLeaderId) REFERENCES Characters(CharacterId),
    INDEX IDX_GuildName (GuildName),
    INDEX IDX_GuildLevel (GuildLevel)
);

CREATE TABLE GuildRanks (
    RankId INT PRIMARY KEY IDENTITY(1,1),
    GuildId INT NOT NULL,
    RankIndex INT NOT NULL,
    RankName NVARCHAR(50) NOT NULL,
    
    -- Permissions
    CanInvite BIT NOT NULL DEFAULT 0,
    CanKick BIT NOT NULL DEFAULT 0,
    CanPromote BIT NOT NULL DEFAULT 0,
    CanDemote BIT NOT NULL DEFAULT 0,
    CanAccessBank BIT NOT NULL DEFAULT 0,
    CanWithdrawGold BIT NOT NULL DEFAULT 0,
    DailyGoldWithdrawLimit INT NOT NULL DEFAULT 0,
    
    FOREIGN KEY (GuildId) REFERENCES Guilds(GuildId) ON DELETE CASCADE,
    UNIQUE (GuildId, RankIndex),
    INDEX IDX_GuildId (GuildId)
);

CREATE TABLE GuildBank (
    BankId INT PRIMARY KEY IDENTITY(1,1),
    GuildId INT NOT NULL,
    TabIndex INT NOT NULL,
    TabName NVARCHAR(50),
    ItemId INT NOT NULL,
    Quantity INT NOT NULL DEFAULT 1,
    SlotRow INT NOT NULL,
    SlotColumn INT NOT NULL,
    DepositedBy INT, -- CharacterId
    DepositedDate DATETIME NOT NULL DEFAULT GETDATE(),
    FOREIGN KEY (GuildId) REFERENCES Guilds(GuildId) ON DELETE CASCADE,
    FOREIGN KEY (ItemId) REFERENCES Items(ItemId),
    UNIQUE (GuildId, TabIndex, SlotRow, SlotColumn),
    INDEX IDX_GuildId (GuildId)
);

CREATE TABLE GuildPerks (
    PerkId INT PRIMARY KEY IDENTITY(1,1),
    GuildId INT NOT NULL,
    PerkType INT NOT NULL, -- ExperienceBonus=0, GoldBonus=1, etc.
    PerkLevel INT NOT NULL DEFAULT 1,
    UnlockedDate DATETIME NOT NULL DEFAULT GETDATE(),
    FOREIGN KEY (GuildId) REFERENCES Guilds(GuildId) ON DELETE CASCADE,
    INDEX IDX_GuildId (GuildId)
);

-- ============================================
-- CRAFTING & PROFESSIONS
-- ============================================

CREATE TABLE Professions (
    ProfessionId INT PRIMARY KEY IDENTITY(1,1),
    ProfessionName NVARCHAR(50) NOT NULL,
    ProfessionType INT NOT NULL, -- Gathering=0, Crafting=1, Secondary=2
    Description NVARCHAR(500),
    MaxSkill INT NOT NULL DEFAULT 300
);

CREATE TABLE CharacterProfessions (
    CharacterProfessionId INT PRIMARY KEY IDENTITY(1,1),
    CharacterId INT NOT NULL,
    ProfessionId INT NOT NULL,
    SkillLevel INT NOT NULL DEFAULT 1,
    Experience INT NOT NULL DEFAULT 0,
    FOREIGN KEY (CharacterId) REFERENCES Characters(CharacterId) ON DELETE CASCADE,
    FOREIGN KEY (ProfessionId) REFERENCES Professions(ProfessionId),
    UNIQUE (CharacterId, ProfessionId),
    INDEX IDX_CharacterId (CharacterId)
);

CREATE TABLE Recipes (
    RecipeId INT PRIMARY KEY IDENTITY(1,1),
    RecipeName NVARCHAR(100) NOT NULL,
    ProfessionId INT NOT NULL,
    RequiredSkill INT NOT NULL,
    CraftedItemId INT NOT NULL,
    CraftedQuantity INT NOT NULL DEFAULT 1,
    CraftTime INT NOT NULL DEFAULT 3, -- seconds
    FOREIGN KEY (ProfessionId) REFERENCES Professions(ProfessionId),
    FOREIGN KEY (CraftedItemId) REFERENCES Items(ItemId),
    INDEX IDX_ProfessionId (ProfessionId)
);

CREATE TABLE RecipeMaterials (
    MaterialId INT PRIMARY KEY IDENTITY(1,1),
    RecipeId INT NOT NULL,
    ItemId INT NOT NULL,
    Quantity INT NOT NULL,
    FOREIGN KEY (RecipeId) REFERENCES Recipes(RecipeId) ON DELETE CASCADE,
    FOREIGN KEY (ItemId) REFERENCES Items(ItemId),
    INDEX IDX_RecipeId (RecipeId)
);

CREATE TABLE CharacterRecipes (
    CharacterRecipeId INT PRIMARY KEY IDENTITY(1,1),
    CharacterId INT NOT NULL,
    RecipeId INT NOT NULL,
    LearnedDate DATETIME NOT NULL DEFAULT GETDATE(),
    FOREIGN KEY (CharacterId) REFERENCES Characters(CharacterId) ON DELETE CASCADE,
    FOREIGN KEY (RecipeId) REFERENCES Recipes(RecipeId),
    UNIQUE (CharacterId, RecipeId),
    INDEX IDX_CharacterId (CharacterId)
);

-- ============================================
-- AUCTION HOUSE
-- ============================================

CREATE TABLE AuctionListings (
    AuctionId INT PRIMARY KEY IDENTITY(1,1),
    SellerCharacterId INT NOT NULL,
    ItemId INT NOT NULL,
    Quantity INT NOT NULL DEFAULT 1,
    StartingBid INT NOT NULL,
    BuyoutPrice INT NOT NULL,
    CurrentBid INT NOT NULL,
    CurrentBidderId INT,
    
    -- Timing
    ListedDate DATETIME NOT NULL DEFAULT GETDATE(),
    ExpiryDate DATETIME NOT NULL,
    
    -- Status
    Status INT NOT NULL DEFAULT 0, -- Active=0, Sold=1, Expired=2, Cancelled=3
    
    FOREIGN KEY (SellerCharacterId) REFERENCES Characters(CharacterId),
    FOREIGN KEY (ItemId) REFERENCES Items(ItemId),
    FOREIGN KEY (CurrentBidderId) REFERENCES Characters(CharacterId),
    INDEX IDX_SellerCharacterId (SellerCharacterId),
    INDEX IDX_ItemId (ItemId),
    INDEX IDX_Status (Status),
    INDEX IDX_ExpiryDate (ExpiryDate)
);

CREATE TABLE AuctionBidHistory (
    BidId INT PRIMARY KEY IDENTITY(1,1),
    AuctionId INT NOT NULL,
    BidderCharacterId INT NOT NULL,
    BidAmount INT NOT NULL,
    BidDate DATETIME NOT NULL DEFAULT GETDATE(),
    FOREIGN KEY (AuctionId) REFERENCES AuctionListings(AuctionId),
    FOREIGN KEY (BidderCharacterId) REFERENCES Characters(CharacterId),
    INDEX IDX_AuctionId (AuctionId),
    INDEX IDX_BidderCharacterId (BidderCharacterId)
);

-- ============================================
-- MAIL SYSTEM
-- ============================================

CREATE TABLE Mail (
    MailId INT PRIMARY KEY IDENTITY(1,1),
    SenderCharacterId INT,
    RecipientCharacterId INT NOT NULL,
    Subject NVARCHAR(100),
    Body NVARCHAR(2000),
    GoldAttachment INT NOT NULL DEFAULT 0,
    ItemAttachmentId INT,
    ItemQuantity INT DEFAULT 1,
    
    IsRead BIT NOT NULL DEFAULT 0,
    SentDate DATETIME NOT NULL DEFAULT GETDATE(),
    ReadDate DATETIME,
    ExpiryDate DATETIME,
    
    FOREIGN KEY (SenderCharacterId) REFERENCES Characters(CharacterId),
    FOREIGN KEY (RecipientCharacterId) REFERENCES Characters(CharacterId),
    FOREIGN KEY (ItemAttachmentId) REFERENCES Items(ItemId),
    INDEX IDX_RecipientCharacterId (RecipientCharacterId),
    INDEX IDX_IsRead (IsRead)
);

-- ============================================
-- TALENTS & SKILLS
-- ============================================

CREATE TABLE TalentTrees (
    TreeId INT PRIMARY KEY IDENTITY(1,1),
    TreeName NVARCHAR(50) NOT NULL,
    TreeType INT NOT NULL, -- Class=0, Specialization=1, General=2
    AssociatedClass INT,
    AssociatedSpec INT,
    MaxPoints INT NOT NULL DEFAULT 51
);

CREATE TABLE TalentNodes (
    NodeId INT PRIMARY KEY IDENTITY(1,1),
    TreeId INT NOT NULL,
    NodeName NVARCHAR(100) NOT NULL,
    Description NVARCHAR(500),
    MaxRank INT NOT NULL DEFAULT 1,
    RequiredLevel INT NOT NULL,
    RequiredPoints INT NOT NULL,
    Row INT NOT NULL,
    Col INT NOT NULL,
    
    -- Prerequisites (JSON array of NodeIds)
    PrerequisitesJson NVARCHAR(200),
    
    -- Effects (JSON)
    EffectsJson NVARCHAR(MAX),
    
    FOREIGN KEY (TreeId) REFERENCES TalentTrees(TreeId) ON DELETE CASCADE,
    INDEX IDX_TreeId (TreeId)
);

CREATE TABLE CharacterTalents (
    CharacterTalentId INT PRIMARY KEY IDENTITY(1,1),
    CharacterId INT NOT NULL,
    NodeId INT NOT NULL,
    CurrentRank INT NOT NULL DEFAULT 0,
    FOREIGN KEY (CharacterId) REFERENCES Characters(CharacterId) ON DELETE CASCADE,
    FOREIGN KEY (NodeId) REFERENCES TalentNodes(NodeId),
    UNIQUE (CharacterId, NodeId),
    INDEX IDX_CharacterId (CharacterId)
);

-- ============================================
-- ACHIEVEMENTS
-- ============================================

CREATE TABLE Achievements (
    AchievementId INT PRIMARY KEY IDENTITY(1,1),
    AchievementName NVARCHAR(100) NOT NULL,
    Description NVARCHAR(500),
    Category INT NOT NULL, -- Combat=0, Exploration=1, Questing=2, etc.
    Points INT NOT NULL DEFAULT 10,
    
    -- Requirements (JSON)
    RequirementsJson NVARCHAR(MAX),
    
    -- Rewards
    RewardTitle NVARCHAR(50),
    RewardItemId INT,
    
    IsHidden BIT NOT NULL DEFAULT 0,
    
    FOREIGN KEY (RewardItemId) REFERENCES Items(ItemId),
    INDEX IDX_Category (Category)
);

CREATE TABLE CharacterAchievements (
    CharacterAchievementId INT PRIMARY KEY IDENTITY(1,1),
    CharacterId INT NOT NULL,
    AchievementId INT NOT NULL,
    Progress INT NOT NULL DEFAULT 0,
    IsCompleted BIT NOT NULL DEFAULT 0,
    CompletedDate DATETIME,
    FOREIGN KEY (CharacterId) REFERENCES Characters(CharacterId) ON DELETE CASCADE,
    FOREIGN KEY (AchievementId) REFERENCES Achievements(AchievementId),
    UNIQUE (CharacterId, AchievementId),
    INDEX IDX_CharacterId (CharacterId)
);

-- ============================================
-- REPUTATION & FACTIONS
-- ============================================

CREATE TABLE Factions (
    FactionId INT PRIMARY KEY IDENTITY(1,1),
    FactionName NVARCHAR(100) NOT NULL,
    Description NVARCHAR(500),
    IsHostile BIT NOT NULL DEFAULT 0,
    ParentFactionId INT,
    FOREIGN KEY (ParentFactionId) REFERENCES Factions(FactionId),
    INDEX IDX_FactionName (FactionName)
);

CREATE TABLE CharacterReputation (
    ReputationId INT PRIMARY KEY IDENTITY(1,1),
    CharacterId INT NOT NULL,
    FactionId INT NOT NULL,
    ReputationValue INT NOT NULL DEFAULT 0, -- 0 to 30000
    ReputationLevel INT AS (
        CASE 
            WHEN ReputationValue >= 30000 THEN 7 -- Exalted
            WHEN ReputationValue >= 24000 THEN 6 -- Revered
            WHEN ReputationValue >= 18000 THEN 5 -- Honored
            WHEN ReputationValue >= 12000 THEN 4 -- Friendly
            WHEN ReputationValue >= 9000 THEN 3 -- Neutral
            WHEN ReputationValue >= 6000 THEN 2 -- Unfriendly
            WHEN ReputationValue >= 3000 THEN 1 -- Hostile
            ELSE 0 -- Hated
        END
    ) PERSISTED,
    FOREIGN KEY (CharacterId) REFERENCES Characters(CharacterId) ON DELETE CASCADE,
    FOREIGN KEY (FactionId) REFERENCES Factions(FactionId),
    UNIQUE (CharacterId, FactionId),
    INDEX IDX_CharacterId (CharacterId)
);

-- ============================================
-- MOUNTS & PETS
-- ============================================

CREATE TABLE Mounts (
    MountId INT PRIMARY KEY IDENTITY(1,1),
    MountName NVARCHAR(100) NOT NULL,
    MountType INT NOT NULL, -- Ground=0, Flying=1, Aquatic=2
    SpeedBonus INT NOT NULL DEFAULT 60, -- Percentage
    RequiredLevel INT NOT NULL DEFAULT 20,
    CanFly BIT NOT NULL DEFAULT 0,
    Description NVARCHAR(500),
    ModelPath NVARCHAR(200)
);

CREATE TABLE CharacterMounts (
    CharacterMountId INT PRIMARY KEY IDENTITY(1,1),
    CharacterId INT NOT NULL,
    MountId INT NOT NULL,
    AcquiredDate DATETIME NOT NULL DEFAULT GETDATE(),
    FOREIGN KEY (CharacterId) REFERENCES Characters(CharacterId) ON DELETE CASCADE,
    FOREIGN KEY (MountId) REFERENCES Mounts(MountId),
    UNIQUE (CharacterId, MountId),
    INDEX IDX_CharacterId (CharacterId)
);

CREATE TABLE Pets (
    PetId INT PRIMARY KEY IDENTITY(1,1),
    PetName NVARCHAR(100) NOT NULL,
    PetType INT NOT NULL, -- Combat=0, Companion=1, Vanity=2
    Species INT NOT NULL,
    BaseHealth INT NOT NULL DEFAULT 100,
    BaseAttack INT NOT NULL DEFAULT 10,
    BaseDefense INT NOT NULL DEFAULT 5,
    ModelPath NVARCHAR(200)
);

CREATE TABLE CharacterPets (
    CharacterPetId INT PRIMARY KEY IDENTITY(1,1),
    CharacterId INT NOT NULL,
    PetId INT NOT NULL,
    CustomName NVARCHAR(50),
    Level INT NOT NULL DEFAULT 1,
    Experience INT NOT NULL DEFAULT 0,
    Happiness INT NOT NULL DEFAULT 100,
    IsActive BIT NOT NULL DEFAULT 0,
    AcquiredDate DATETIME NOT NULL DEFAULT GETDATE(),
    FOREIGN KEY (CharacterId) REFERENCES Characters(CharacterId) ON DELETE CASCADE,
    FOREIGN KEY (PetId) REFERENCES Pets(PetId),
    INDEX IDX_CharacterId (CharacterId)
);

-- ============================================
-- PLAYER HOUSING
-- ============================================

CREATE TABLE Houses (
    HouseId INT PRIMARY KEY IDENTITY(1,1),
    CharacterId INT NOT NULL UNIQUE,
    HouseType INT NOT NULL, -- Small=0, Medium=1, Large=2, Mansion=3, Castle=4
    HouseName NVARCHAR(100),
    MaxDecorations INT NOT NULL DEFAULT 50,
    StorageSlots INT NOT NULL DEFAULT 100,
    
    -- Features
    HasCraftingStation BIT NOT NULL DEFAULT 0,
    HasBank BIT NOT NULL DEFAULT 0,
    HasVendor BIT NOT NULL DEFAULT 0,
    
    -- Access
    IsPublic BIT NOT NULL DEFAULT 0,
    
    PurchasedDate DATETIME NOT NULL DEFAULT GETDATE(),
    
    FOREIGN KEY (CharacterId) REFERENCES Characters(CharacterId) ON DELETE CASCADE
);

CREATE TABLE HouseDecorations (
    DecorationId INT PRIMARY KEY IDENTITY(1,1),
    HouseId INT NOT NULL,
    ItemId INT NOT NULL,
    PositionX FLOAT NOT NULL,
    PositionY FLOAT NOT NULL,
    PositionZ FLOAT NOT NULL,
    RotationX FLOAT NOT NULL DEFAULT 0,
    RotationY FLOAT NOT NULL DEFAULT 0,
    RotationZ FLOAT NOT NULL DEFAULT 0,
    PlacedDate DATETIME NOT NULL DEFAULT GETDATE(),
    FOREIGN KEY (HouseId) REFERENCES Houses(HouseId) ON DELETE CASCADE,
    FOREIGN KEY (ItemId) REFERENCES Items(ItemId),
    INDEX IDX_HouseId (HouseId)
);

-- ============================================
-- PVP SYSTEMS
-- ============================================

CREATE TABLE PvPStats (
    PvPStatsId INT PRIMARY KEY IDENTITY(1,1),
    CharacterId INT NOT NULL UNIQUE,
    HonorPoints INT NOT NULL DEFAULT 0,
    HonorLevel INT NOT NULL DEFAULT 1,
    ArenaRating INT NOT NULL DEFAULT 1500,
    Kills INT NOT NULL DEFAULT 0,
    Deaths INT NOT NULL DEFAULT 0,
    KDRatio AS (CASE WHEN Deaths > 0 THEN CAST(Kills AS FLOAT) / Deaths ELSE CAST(Kills AS FLOAT) END) PERSISTED,
    CurrentRank INT NOT NULL DEFAULT 0, -- Scout=0, Grunt=1, etc.
    FOREIGN KEY (CharacterId) REFERENCES Characters(CharacterId) ON DELETE CASCADE
);

CREATE TABLE PvPMatches (
    MatchId INT PRIMARY KEY IDENTITY(1,1),
    MatchType INT NOT NULL, -- Arena2v2=0, Arena3v3=1, Arena5v5=2, Battleground=3
    StartTime DATETIME NOT NULL,
    EndTime DATETIME,
    WinningTeam INT,
    MapId INT
);

CREATE TABLE PvPMatchParticipants (
    ParticipantId INT PRIMARY KEY IDENTITY(1,1),
    MatchId INT NOT NULL,
    CharacterId INT NOT NULL,
    Team INT NOT NULL,
    Kills INT NOT NULL DEFAULT 0,
    Deaths INT NOT NULL DEFAULT 0,
    DamageDealt INT NOT NULL DEFAULT 0,
    HealingDone INT NOT NULL DEFAULT 0,
    RatingChange INT NOT NULL DEFAULT 0,
    FOREIGN KEY (MatchId) REFERENCES PvPMatches(MatchId),
    FOREIGN KEY (CharacterId) REFERENCES Characters(CharacterId),
    INDEX IDX_MatchId (MatchId),
    INDEX IDX_CharacterId (CharacterId)
);

-- Continued in next file...
