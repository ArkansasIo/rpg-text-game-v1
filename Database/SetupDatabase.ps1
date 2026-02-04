# =============================================
# RPG Game Database Setup Script
# PowerShell automation for complete database setup
# =============================================

param(
    [string]$ServerName = "localhost",
    [string]$DatabaseName = "RPGGame",
    [switch]$UseIntegratedSecurity = $true,
    [string]$Username = "",
    [string]$Password = ""
)

Write-Host "================================================" -ForegroundColor Cyan
Write-Host "RPG GAME DATABASE SETUP" -ForegroundColor Cyan
Write-Host "================================================" -ForegroundColor Cyan
Write-Host ""

# Get the script directory
$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path

# Check if sqlcmd is available
$sqlcmdPath = Get-Command sqlcmd -ErrorAction SilentlyContinue
if (-not $sqlcmdPath) {
    Write-Host "ERROR: sqlcmd not found!" -ForegroundColor Red
    Write-Host "Please install SQL Server Command Line Utilities" -ForegroundColor Yellow
    Write-Host "Download: https://docs.microsoft.com/en-us/sql/tools/sqlcmd-utility" -ForegroundColor Yellow
    exit 1
}

Write-Host "? sqlcmd found: $($sqlcmdPath.Source)" -ForegroundColor Green

# Build connection string
if ($UseIntegratedSecurity) {
    $connectionParams = "-S $ServerName -E"
    Write-Host "Using Windows Authentication" -ForegroundColor Yellow
} else {
    $connectionParams = "-S $ServerName -U $Username -P $Password"
    Write-Host "Using SQL Authentication" -ForegroundColor Yellow
}

# Test connection
Write-Host ""
Write-Host "Testing connection to $ServerName..." -ForegroundColor Yellow
$testQuery = "SELECT @@VERSION"
$testResult = sqlcmd $connectionParams.Split() -Q $testQuery -h -1 2>&1

if ($LASTEXITCODE -ne 0) {
    Write-Host "ERROR: Cannot connect to SQL Server!" -ForegroundColor Red
    Write-Host $testResult -ForegroundColor Red
    exit 1
}

Write-Host "? Connection successful!" -ForegroundColor Green
Write-Host ""

# Function to execute SQL file
function Execute-SqlFile {
    param(
        [string]$FilePath,
        [string]$Description
    )
    
    if (-not (Test-Path $FilePath)) {
        Write-Host "ERROR: File not found: $FilePath" -ForegroundColor Red
        return $false
    }
    
    Write-Host "Executing: $Description" -ForegroundColor Yellow
    Write-Host "File: $FilePath" -ForegroundColor Gray
    
    $result = sqlcmd $connectionParams.Split() -d $DatabaseName -i $FilePath 2>&1
    
    if ($LASTEXITCODE -ne 0) {
        Write-Host "? FAILED!" -ForegroundColor Red
        Write-Host $result -ForegroundColor Red
        return $false
    }
    
    Write-Host "? SUCCESS!" -ForegroundColor Green
    Write-Host ""
    return $true
}

# Array of SQL files to execute in order
$sqlFiles = @(
    @{
        Path = "$ScriptDir\00_CreateDatabase.sql"
        Description = "Creating database"
        Database = "master"
    },
    @{
        Path = "$ScriptDir\Schema_Part1_Core.sql"
        Description = "Schema Part 1 - Core Tables (Accounts, Characters, Items, Zones)"
        Database = $DatabaseName
    },
    @{
        Path = "$ScriptDir\Schema_Part2_Social.sql"
        Description = "Schema Part 2 - Social Systems (Guilds, Crafting, Economy)"
        Database = $DatabaseName
    },
    @{
        Path = "$ScriptDir\Schema_Part3_Advanced.sql"
        Description = "Schema Part 3 - Advanced Features (Analytics, World Events)"
        Database = $DatabaseName
    },
    @{
        Path = "$ScriptDir\Items_Complete_400Plus.sql"
        Description = "Items Database Part 1 - Weapons (Swords, Daggers)"
        Database = $DatabaseName
    },
    @{
        Path = "$ScriptDir\Items_Complete_400Plus_Part2.sql"
        Description = "Items Database Part 2 - Weapons (Axes, Bows, Staves)"
        Database = $DatabaseName
    },
    @{
        Path = "$ScriptDir\Items_Complete_400Plus_Part3.sql"
        Description = "Items Database Part 3 - Armor (Helmets, Chest, Legs)"
        Database = $DatabaseName
    },
    @{
        Path = "$ScriptDir\Items_Complete_400Plus_Part4_FINAL.sql"
        Description = "Items Database Part 4 - Armor & Consumables (Complete)"
        Database = $DatabaseName
    },
    @{
        Path = "$ScriptDir\SeedData.sql"
        Description = "Seed Data - Sample game content (Optional)"
        Database = $DatabaseName
    }
)

# Execute each file
Write-Host "================================================" -ForegroundColor Cyan
Write-Host "STARTING DATABASE SETUP" -ForegroundColor Cyan
Write-Host "================================================" -ForegroundColor Cyan
Write-Host ""

$successCount = 0
$totalCount = $sqlFiles.Count

foreach ($file in $sqlFiles) {
    # Skip if file doesn't exist
    if (-not (Test-Path $file.Path)) {
        Write-Host "? Skipping: $($file.Description) (file not found)" -ForegroundColor Yellow
        Write-Host ""
        continue
    }
    
    # Use appropriate database
    $dbParam = if ($file.Database -eq "master") { "-d master" } else { "-d $DatabaseName" }
    
    $result = Execute-SqlFile -FilePath $file.Path -Description $file.Description
    
    if ($result) {
        $successCount++
    } else {
        Write-Host "Setup failed at: $($file.Description)" -ForegroundColor Red
        Write-Host "Please fix the error and try again." -ForegroundColor Yellow
        exit 1
    }
    
    Start-Sleep -Milliseconds 500
}

# Summary
Write-Host ""
Write-Host "================================================" -ForegroundColor Cyan
Write-Host "DATABASE SETUP COMPLETE!" -ForegroundColor Green
Write-Host "================================================" -ForegroundColor Cyan
Write-Host ""
Write-Host "Results:" -ForegroundColor White
Write-Host "  - Files processed: $successCount / $totalCount" -ForegroundColor White
Write-Host "  - Database: $DatabaseName" -ForegroundColor White
Write-Host "  - Server: $ServerName" -ForegroundColor White
Write-Host ""

# Verify tables
Write-Host "Verifying database..." -ForegroundColor Yellow
$tableCountQuery = @"
SELECT COUNT(*) as TableCount 
FROM INFORMATION_SCHEMA.TABLES 
WHERE TABLE_TYPE = 'BASE TABLE'
"@

$tableCount = sqlcmd $connectionParams.Split() -d $DatabaseName -Q $tableCountQuery -h -1 2>&1 | Where-Object { $_ -match '^\d+$' }

if ($tableCount) {
    Write-Host "? Total tables created: $tableCount" -ForegroundColor Green
    
    if ([int]$tableCount -gt 80) {
        Write-Host "? All tables created successfully!" -ForegroundColor Green
    }
}

# Check items count
$itemCountQuery = "SELECT COUNT(*) FROM Items"
$itemCount = sqlcmd $connectionParams.Split() -d $DatabaseName -Q $itemCountQuery -h -1 2>&1 | Where-Object { $_ -match '^\d+$' }

if ($itemCount) {
    Write-Host "? Total items in database: $itemCount" -ForegroundColor Green
}

Write-Host ""
Write-Host "Next Steps:" -ForegroundColor Cyan
Write-Host "1. Update appsettings.json with your connection string" -ForegroundColor White
Write-Host "2. Run 'dotnet restore' to install packages" -ForegroundColor White
Write-Host "3. Run 'dotnet run' to start the game!" -ForegroundColor White
Write-Host ""
Write-Host "Connection string example:" -ForegroundColor Yellow
Write-Host "Server=$ServerName;Database=$DatabaseName;Integrated Security=true;TrustServerCertificate=true;" -ForegroundColor Gray
Write-Host ""
Write-Host "Setup completed successfully! ??" -ForegroundColor Green
