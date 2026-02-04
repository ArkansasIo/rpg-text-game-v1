@echo off
REM =============================================
REM RPG Game Database Setup - Windows Batch File
REM =============================================

echo ================================================
echo RPG GAME DATABASE SETUP
echo ================================================
echo.

REM Check if SQL Server is accessible
sqlcmd -? >nul 2>&1
if errorlevel 1 (
    echo ERROR: sqlcmd not found!
    echo Please install SQL Server Command Line Utilities
    echo Download: https://docs.microsoft.com/en-us/sql/tools/sqlcmd-utility
    pause
    exit /b 1
)

echo sqlcmd found - proceeding with setup...
echo.

REM Set variables
set SERVER=localhost
set DATABASE=RPGGame

echo Server: %SERVER%
echo Database: %DATABASE%
echo.
echo This will create a new database and all tables.
echo WARNING: If the database exists, it will be dropped!
echo.

choice /C YN /M "Continue with database setup?"
if errorlevel 2 goto :cancel
if errorlevel 1 goto :proceed

:cancel
echo Setup cancelled.
pause
exit /b 0

:proceed
echo.
echo ================================================
echo STARTING DATABASE CREATION
echo ================================================
echo.

REM Create database
echo [1/9] Creating database...
sqlcmd -S %SERVER% -E -i "00_CreateDatabase.sql"
if errorlevel 1 (
    echo ERROR: Failed to create database!
    pause
    exit /b 1
)
echo SUCCESS!
echo.

REM Schema Part 1
echo [2/9] Creating core schema (Accounts, Characters, Items, Zones)...
sqlcmd -S %SERVER% -E -d %DATABASE% -i "Schema_Part1_Core.sql"
if errorlevel 1 (
    echo ERROR: Failed to create core schema!
    pause
    exit /b 1
)
echo SUCCESS!
echo.

REM Schema Part 2
echo [3/9] Creating social systems (Guilds, Crafting, Economy)...
sqlcmd -S %SERVER% -E -d %DATABASE% -i "Schema_Part2_Social.sql"
if errorlevel 1 (
    echo ERROR: Failed to create social schema!
    pause
    exit /b 1
)
echo SUCCESS!
echo.

REM Schema Part 3
echo [4/9] Creating advanced features (Analytics, Events)...
sqlcmd -S %SERVER% -E -d %DATABASE% -i "Schema_Part3_Advanced.sql"
if errorlevel 1 (
    echo ERROR: Failed to create advanced schema!
    pause
    exit /b 1
)
echo SUCCESS!
echo.

REM Items Part 1
echo [5/9] Inserting items - Part 1 (Swords, Daggers)...
sqlcmd -S %SERVER% -E -d %DATABASE% -i "Items_Complete_400Plus.sql"
if errorlevel 1 (
    echo ERROR: Failed to insert items part 1!
    pause
    exit /b 1
)
echo SUCCESS!
echo.

REM Items Part 2
echo [6/9] Inserting items - Part 2 (Axes, Bows, Staves)...
sqlcmd -S %SERVER% -E -d %DATABASE% -i "Items_Complete_400Plus_Part2.sql"
if errorlevel 1 (
    echo ERROR: Failed to insert items part 2!
    pause
    exit /b 1
)
echo SUCCESS!
echo.

REM Items Part 3
echo [7/9] Inserting items - Part 3 (Armor - Helmets, Chest, Legs)...
sqlcmd -S %SERVER% -E -d %DATABASE% -i "Items_Complete_400Plus_Part3.sql"
if errorlevel 1 (
    echo ERROR: Failed to insert items part 3!
    pause
    exit /b 1
)
echo SUCCESS!
echo.

REM Items Part 4
echo [8/9] Inserting items - Part 4 (Armor, Consumables, Materials)...
sqlcmd -S %SERVER% -E -d %DATABASE% -i "Items_Complete_400Plus_Part4_FINAL.sql"
if errorlevel 1 (
    echo ERROR: Failed to insert items part 4!
    pause
    exit /b 1
)
echo SUCCESS!
echo.

REM Seed Data (Optional)
echo [9/9] Inserting seed data (sample content)...
sqlcmd -S %SERVER% -E -d %DATABASE% -i "SeedData.sql"
if errorlevel 1 (
    echo WARNING: Seed data failed, but continuing...
)
echo SUCCESS!
echo.

echo ================================================
echo DATABASE SETUP COMPLETE!
echo ================================================
echo.

REM Verify
echo Verifying database...
sqlcmd -S %SERVER% -E -d %DATABASE% -Q "SELECT COUNT(*) as TableCount FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_TYPE='BASE TABLE'"
sqlcmd -S %SERVER% -E -d %DATABASE% -Q "SELECT COUNT(*) as ItemCount FROM Items"
echo.

echo ================================================
echo SETUP SUCCESSFUL!
echo ================================================
echo.
echo Next steps:
echo 1. Update appsettings.json with connection string:
echo    "Server=%SERVER%;Database=%DATABASE%;Integrated Security=true;TrustServerCertificate=true;"
echo.
echo 2. Run: dotnet restore
echo 3. Run: dotnet run
echo.
echo Your RPG game is ready to play! ??
echo.
pause
