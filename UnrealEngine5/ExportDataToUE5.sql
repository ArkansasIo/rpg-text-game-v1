-- =============================================
-- UNREAL ENGINE 5 DATA EXPORT
-- Export Items as JSON for UE5 Data Tables
-- =============================================

USE RPGGame;
GO

-- Export Items to JSON format compatible with UE5
DECLARE @json NVARCHAR(MAX);

SET @json = (
    SELECT 
        ItemID as 'ItemID',
        ItemName as 'Name',
        Description as 'Description',
        ItemType as 'Type',
        Rarity as 'Rarity',
        RequiredLevel as 'RequiredLevel',
        MaxStackSize as 'MaxStackSize',
        VendorPrice as 'VendorPrice',
        IsTradeable as 'IsTradeable',
        Stats as 'Stats',
        IconPath as 'IconPath'
    FROM Items
    FOR JSON PATH
);

-- Save to file (you'll need to copy this output)
SELECT @json AS 'ItemsJSON';
GO

-- Export Zones
DECLARE @zonesJson NVARCHAR(MAX);

SET @zonesJson = (
    SELECT 
        ZoneID as 'ZoneID',
        ZoneName as 'Name',
        Description as 'Description',
        ZoneType as 'Type',
        RecommendedLevel as 'RecommendedLevel',
        MinLevel as 'MinLevel',
        MaxLevel as 'MaxLevel',
        Faction as 'Faction',
        IsSanctuary as 'IsSanctuary',
        HasInn as 'HasInn',
        HasBank as 'HasBank',
        HasAuctionHouse as 'HasAuctionHouse',
        HasFlightMaster as 'HasFlightMaster'
    FROM Zones
    FOR JSON PATH
);

SELECT @zonesJson AS 'ZonesJSON';
GO

-- Export Enemies
DECLARE @enemiesJson NVARCHAR(MAX);

SET @enemiesJson = (
    SELECT 
        EnemyID as 'EnemyID',
        EnemyName as 'Name',
        EnemyType as 'Type',
        Level as 'Level',
        Health as 'Health',
        Mana as 'Mana',
        Armor as 'Armor',
        MinDamage as 'MinDamage',
        MaxDamage as 'MaxDamage',
        ExperienceReward as 'ExperienceReward',
        Rank as 'Rank',
        Abilities as 'Abilities',
        Resistances as 'Resistances',
        ModelPath as 'ModelPath'
    FROM Enemies
    FOR JSON PATH
);

SELECT @enemiesJson AS 'EnemiesJSON';
GO

-- Export Quests
DECLARE @questsJson NVARCHAR(MAX);

SET @questsJson = (
    SELECT 
        QuestID as 'QuestID',
        QuestName as 'Name',
        Description as 'Description',
        QuestType as 'Type',
        RequiredLevel as 'RequiredLevel',
        RecommendedLevel as 'RecommendedLevel',
        IsRepeatable as 'IsRepeatable',
        IsDailyQuest as 'IsDailyQuest',
        ExperienceReward as 'ExperienceReward',
        GoldReward as 'GoldReward',
        ReputationReward as 'ReputationReward',
        QuestGiver as 'QuestGiver',
        StartZoneID as 'StartZoneID'
    FROM Quests
    FOR JSON PATH
);

SELECT @questsJson AS 'QuestsJSON';
GO

-- Export to CSV format for UE5 DataTables
PRINT '================================================';
PRINT 'UNREAL ENGINE 5 DATA EXPORT COMPLETE';
PRINT '================================================';
PRINT '';
PRINT 'Next Steps:';
PRINT '1. Copy JSON output from query results';
PRINT '2. Save as .json files in your UE5 project';
PRINT '3. Import into UE5 as Data Tables';
PRINT '4. See UE5_Integration_Guide.md for details';
PRINT '================================================';
GO
