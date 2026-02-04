# PowerShell Script to Export RPG Data for Unreal Engine 5
# Exports all database tables to JSON and CSV formats

param(
    [string]$ServerName = "localhost",
    [string]$DatabaseName = "RPGGame",
    [string]$OutputPath = ".\UE5_Export"
)

Write-Host "================================================" -ForegroundColor Cyan
Write-Host "UNREAL ENGINE 5 DATA EXPORT" -ForegroundColor Cyan
Write-Host "================================================" -ForegroundColor Cyan
Write-Host ""

# Create output directory
if (-not (Test-Path $OutputPath)) {
    New-Item -ItemType Directory -Path $OutputPath | Out-Null
    Write-Host "? Created output directory: $OutputPath" -ForegroundColor Green
}

# Function to export table to JSON
function Export-TableToJson {
    param(
        [string]$TableName,
        [string]$SelectQuery,
        [string]$OutputFile
    )
    
    Write-Host "Exporting $TableName..." -ForegroundColor Yellow
    
    $query = @"
SELECT $SelectQuery
FROM $TableName
FOR JSON PATH, INCLUDE_NULL_VALUES
"@
    
    try {
        $result = sqlcmd -S $ServerName -d $DatabaseName -Q $query -h -1 -W
        
        if ($result) {
            # Clean up the result and save
            $json = $result -join ""
            $json | Out-File -FilePath $OutputFile -Encoding UTF8
            Write-Host "? Exported to: $OutputFile" -ForegroundColor Green
            return $true
        }
    }
    catch {
        Write-Host "? Failed to export $TableName : $_" -ForegroundColor Red
        return $false
    }
}

Write-Host "Starting export..." -ForegroundColor Cyan
Write-Host ""

# Export Items (430+ items)
Export-TableToJson `
    -TableName "Items" `
    -SelectQuery @"
ItemID as 'id',
ItemName as 'name',
Description as 'description',
ItemType as 'type',
Rarity as 'rarity',
RequiredLevel as 'requiredLevel',
MaxStackSize as 'maxStackSize',
VendorPrice as 'vendorPrice',
IsTradeable as 'isTradeable',
IsQuestItem as 'isQuestItem',
Stats as 'stats',
IconPath as 'iconPath'
"@ `
    -OutputFile "$OutputPath\Items.json"

# Export Weapons specifically
$weaponQuery = @"
SELECT 
    ItemID as 'id',
    ItemName as 'name',
    Rarity as 'rarity',
    RequiredLevel as 'requiredLevel',
    JSON_VALUE(Stats, '$.Damage') as 'damage',
    JSON_VALUE(Stats, '$.AttackSpeed') as 'attackSpeed',
    JSON_VALUE(Stats, '$.WeaponType') as 'weaponType',
    JSON_VALUE(Stats, '$.Strength') as 'strength',
    JSON_VALUE(Stats, '$.Agility') as 'agility'
FROM Items 
WHERE ItemType = 'Weapon'
FOR JSON PATH
"@

sqlcmd -S $ServerName -d $DatabaseName -Q $weaponQuery -h -1 -W | Out-File "$OutputPath\Weapons.json" -Encoding UTF8
Write-Host "? Exported Weapons to: $OutputPath\Weapons.json" -ForegroundColor Green

# Export Armor
$armorQuery = @"
SELECT 
    ItemID as 'id',
    ItemName as 'name',
    Rarity as 'rarity',
    RequiredLevel as 'requiredLevel',
    JSON_VALUE(Stats, '$.Armor') as 'armor',
    JSON_VALUE(Stats, '$.ArmorType') as 'armorType',
    JSON_VALUE(Stats, '$.Slot') as 'slot',
    JSON_VALUE(Stats, '$.Strength') as 'strength',
    JSON_VALUE(Stats, '$.Stamina') as 'stamina'
FROM Items 
WHERE ItemType = 'Armor'
FOR JSON PATH
"@

sqlcmd -S $ServerName -d $DatabaseName -Q $armorQuery -h -1 -W | Out-File "$OutputPath\Armor.json" -Encoding UTF8
Write-Host "? Exported Armor to: $OutputPath\Armor.json" -ForegroundColor Green

# Export Zones
$zoneQuery = @"
SELECT 
    ZoneID as 'id',
    ZoneName as 'name',
    Description as 'description',
    ZoneType as 'type',
    RecommendedLevel as 'recommendedLevel',
    MinLevel as 'minLevel',
    MaxLevel as 'maxLevel',
    Faction as 'faction',
    IsSanctuary as 'isSanctuary',
    HasInn as 'hasInn',
    HasBank as 'hasBank',
    HasAuctionHouse as 'hasAuctionHouse'
FROM Zones
FOR JSON PATH
"@

sqlcmd -S $ServerName -d $DatabaseName -Q $zoneQuery -h -1 -W | Out-File "$OutputPath\Zones.json" -Encoding UTF8
Write-Host "? Exported Zones to: $OutputPath\Zones.json" -ForegroundColor Green

# Export Enemies
$enemyQuery = @"
SELECT 
    EnemyID as 'id',
    EnemyName as 'name',
    EnemyType as 'type',
    Level as 'level',
    Health as 'health',
    Mana as 'mana',
    Armor as 'armor',
    MinDamage as 'minDamage',
    MaxDamage as 'maxDamage',
    Rank as 'rank',
    ExperienceReward as 'experienceReward',
    Abilities as 'abilities',
    Resistances as 'resistances'
FROM Enemies
FOR JSON PATH
"@

sqlcmd -S $ServerName -d $DatabaseName -Q $enemyQuery -h -1 -W | Out-File "$OutputPath\Enemies.json" -Encoding UTF8
Write-Host "? Exported Enemies to: $OutputPath\Enemies.json" -ForegroundColor Green

# Export Quests
$questQuery = @"
SELECT 
    QuestID as 'id',
    QuestName as 'name',
    Description as 'description',
    QuestType as 'type',
    RequiredLevel as 'requiredLevel',
    IsRepeatable as 'isRepeatable',
    ExperienceReward as 'experienceReward',
    GoldReward as 'goldReward',
    QuestGiver as 'questGiver'
FROM Quests
FOR JSON PATH
"@

sqlcmd -S $ServerName -d $DatabaseName -Q $questQuery -h -1 -W | Out-File "$OutputPath\Quests.json" -Encoding UTF8
Write-Host "? Exported Quests to: $OutputPath\Quests.json" -ForegroundColor Green

# Export Achievements
$achievementQuery = @"
SELECT 
    AchievementID as 'id',
    AchievementName as 'name',
    Description as 'description',
    Category as 'category',
    PointValue as 'pointValue',
    IsHidden as 'isHidden'
FROM Achievements
FOR JSON PATH
"@

sqlcmd -S $ServerName -d $DatabaseName -Q $achievementQuery -h -1 -W | Out-File "$OutputPath\Achievements.json" -Encoding UTF8
Write-Host "? Exported Achievements to: $OutputPath\Achievements.json" -ForegroundColor Green

# Export Mounts
$mountQuery = @"
SELECT 
    MountID as 'id',
    MountName as 'name',
    Description as 'description',
    MountType as 'type',
    SpeedBonus as 'speedBonus',
    CanFly as 'canFly',
    Rarity as 'rarity',
    RequiredLevel as 'requiredLevel'
FROM Mounts
FOR JSON PATH
"@

sqlcmd -S $ServerName -d $DatabaseName -Q $mountQuery -h -1 -W | Out-File "$OutputPath\Mounts.json" -Encoding UTF8
Write-Host "? Exported Mounts to: $OutputPath\Mounts.json" -ForegroundColor Green

# Export Pets
$petQuery = @"
SELECT 
    PetID as 'id',
    PetName as 'name',
    Description as 'description',
    PetType as 'type',
    Rarity as 'rarity',
    IsCombatPet as 'isCombatPet',
    BaseHealth as 'baseHealth',
    BaseDamage as 'baseDamage'
FROM Pets
FOR JSON PATH
"@

sqlcmd -S $ServerName -d $DatabaseName -Q $petQuery -h -1 -W | Out-File "$OutputPath\Pets.json" -Encoding UTF8
Write-Host "? Exported Pets to: $OutputPath\Pets.json" -ForegroundColor Green

# Create CSV exports for UE5 Data Table import
Write-Host ""
Write-Host "Creating CSV exports for UE5 Data Tables..." -ForegroundColor Cyan

# Items CSV
$itemsCsvQuery = @"
SELECT 
    ItemID,
    ItemName as Name,
    REPLACE(Description, ',', ';') as Description,
    ItemType as Type,
    Rarity,
    RequiredLevel,
    MaxStackSize,
    VendorPrice,
    CAST(IsTradeable as varchar) as IsTradeable,
    IconPath
FROM Items
"@

sqlcmd -S $ServerName -d $DatabaseName -Q $itemsCsvQuery -s "," -W -h -1 | Out-File "$OutputPath\Items.csv" -Encoding UTF8
Write-Host "? Exported Items CSV" -ForegroundColor Green

# Summary
Write-Host ""
Write-Host "================================================" -ForegroundColor Cyan
Write-Host "EXPORT COMPLETE!" -ForegroundColor Green
Write-Host "================================================" -ForegroundColor Cyan
Write-Host ""
Write-Host "Files exported to: $OutputPath" -ForegroundColor White
Write-Host ""
Write-Host "Exported data:" -ForegroundColor Yellow
Write-Host "  - Items.json (430+ items)" -ForegroundColor White
Write-Host "  - Weapons.json (185 weapons)" -ForegroundColor White
Write-Host "  - Armor.json (145 armor pieces)" -ForegroundColor White
Write-Host "  - Zones.json (72 zones)" -ForegroundColor White
Write-Host "  - Enemies.json (26+ enemies)" -ForegroundColor White
Write-Host "  - Quests.json" -ForegroundColor White
Write-Host "  - Achievements.json" -ForegroundColor White
Write-Host "  - Mounts.json" -ForegroundColor White
Write-Host "  - Pets.json" -ForegroundColor White
Write-Host "  - Items.csv (for Data Table import)" -ForegroundColor White
Write-Host ""
Write-Host "Next Steps:" -ForegroundColor Cyan
Write-Host "1. Open Unreal Engine 5 project" -ForegroundColor White
Write-Host "2. Create Data Table structures (see UE5_Integration_Guide.md)" -ForegroundColor White
Write-Host "3. Import JSON/CSV files into Data Tables" -ForegroundColor White
Write-Host "4. Create Blueprints to read data" -ForegroundColor White
Write-Host ""
Write-Host "See UE5_Integration_Guide.md for detailed instructions!" -ForegroundColor Green
