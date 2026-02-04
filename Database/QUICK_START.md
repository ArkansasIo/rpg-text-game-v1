# =============================================
# QUICK START GUIDE - Database Setup
# =============================================

## ?? Quick Setup (Choose One Method)

### ? Method 1: Automated PowerShell (RECOMMENDED)
**Windows PowerShell (Run as Administrator):**
```powershell
cd Database
.\SetupDatabase.ps1
```

**With custom server:**
```powershell
.\SetupDatabase.ps1 -ServerName ".\SQLEXPRESS"
```

**With SQL Authentication:**
```powershell
.\SetupDatabase.ps1 -ServerName "localhost" -UseIntegratedSecurity:$false -Username "sa" -Password "YourPassword"
```

---

### ? Method 2: Batch File (Windows)
**Double-click:**
```
Database\SetupDatabase.bat
```

Or from Command Prompt:
```cmd
cd Database
SetupDatabase.bat
```

---

### ? Method 3: Manual SQL Server Management Studio (SSMS)

1. **Open SSMS** and connect to your server

2. **Create Database:**
   - File ? Open ? File ? `Database/00_CreateDatabase.sql`
   - Click Execute (F5)

3. **Execute Schema Files in Order:**
   - `Schema_Part1_Core.sql` (Core tables)
   - `Schema_Part2_Social.sql` (Social features)
   - `Schema_Part3_Advanced.sql` (Advanced features)

4. **Insert Items (430+ items):**
   - `Items_Complete_400Plus.sql` (Part 1)
   - `Items_Complete_400Plus_Part2.sql` (Part 2)
   - `Items_Complete_400Plus_Part3.sql` (Part 3)
   - `Items_Complete_400Plus_Part4_FINAL.sql` (Part 4)

5. **(Optional) Sample Data:**
   - `SeedData.sql` (Test data)

---

### ? Method 4: Command Line (sqlcmd)

```cmd
cd Database

REM Create database
sqlcmd -S localhost -E -i "00_CreateDatabase.sql"

REM Create schema
sqlcmd -S localhost -E -d RPGGame -i "Schema_Part1_Core.sql"
sqlcmd -S localhost -E -d RPGGame -i "Schema_Part2_Social.sql"
sqlcmd -S localhost -E -d RPGGame -i "Schema_Part3_Advanced.sql"

REM Insert items
sqlcmd -S localhost -E -d RPGGame -i "Items_Complete_400Plus.sql"
sqlcmd -S localhost -E -d RPGGame -i "Items_Complete_400Plus_Part2.sql"
sqlcmd -S localhost -E -d RPGGame -i "Items_Complete_400Plus_Part3.sql"
sqlcmd -S localhost -E -d RPGGame -i "Items_Complete_400Plus_Part4_FINAL.sql"

REM (Optional) Seed data
sqlcmd -S localhost -E -d RPGGame -i "SeedData.sql"
```

---

## ?? Configure Connection String

After database setup, update **`appsettings.json`**:

### For localhost with Windows Authentication:
```json
{
  "ConnectionStrings": {
    "DefaultConnection": "Server=localhost;Database=RPGGame;Integrated Security=true;TrustServerCertificate=true;"
  }
}
```

### For SQL Server Express:
```json
{
  "ConnectionStrings": {
    "DefaultConnection": "Server=localhost\\SQLEXPRESS;Database=RPGGame;Integrated Security=true;TrustServerCertificate=true;"
  }
}
```

### For LocalDB:
```json
{
  "ConnectionStrings": {
    "DefaultConnection": "Server=(localdb)\\mssqllocaldb;Database=RPGGame;Trusted_Connection=True;MultipleActiveResultSets=true"
  }
}
```

### For SQL Authentication:
```json
{
  "ConnectionStrings": {
    "DefaultConnection": "Server=localhost;Database=RPGGame;User Id=sa;Password=YourPassword;TrustServerCertificate=true;"
  }
}
```

---

## ?? Run the Game

```bash
# Restore packages
dotnet restore

# Build
dotnet build

# Run
dotnet run
```

---

## ? Verify Setup

### Check Tables:
```sql
USE RPGGame;
SELECT COUNT(*) as TableCount 
FROM INFORMATION_SCHEMA.TABLES 
WHERE TABLE_TYPE = 'BASE TABLE';
-- Should return 80+
```

### Check Items:
```sql
SELECT COUNT(*) as ItemCount FROM Items;
-- Should return 430+
```

### Sample Query:
```sql
-- Get all legendary weapons
SELECT ItemName, ItemType, RequiredLevel, Stats
FROM Items
WHERE Rarity = 'Legendary' 
  AND ItemType = 'Weapon'
ORDER BY RequiredLevel;
```

---

## ?? What You Get

After setup, your database contains:

### ?? **Tables (80+)**
- Core: Accounts, Characters, Items, Zones, NPCs
- Combat: Enemies, Dungeons, Bosses, Loot Tables
- Social: Guilds, Parties, Friends, Chat
- Economy: Auction House, Mail, Trading
- Crafting: Professions, Recipes, Materials
- Progression: Quests, Achievements, Talents
- World: Zones, Events, Resource Nodes
- Analytics: Sessions, Actions, Leaderboards

### ??? **Items (430+)**
- **185 Weapons**
  - 50 One-Handed Swords (Common ? Legendary)
  - 30 Two-Handed Swords (including Frostmourne!)
  - 25 Daggers (Assassin weapons)
  - 20 Axes (Gorehowl, Hellreaver)
  - 20 Maces (Hand of Ragnaros, Sulfuron)
  - 20 Bows (Thori'dal, Rhok'delar)
  - 20 Staves (Atiesh, Benediction)

- **145 Armor Pieces**
  - Helmets, Chest, Legs, Shoulders, Boots
  - All armor types: Cloth, Leather, Mail, Plate
  - Complete sets (Bloodfang, Judgment, Stormrage)

- **50 Consumables**
  - Healing/Mana potions (6 tiers)
  - Buff elixirs and flasks
  - Food and drinks
  - Resistance potions

- **50 Crafting Materials**
  - Ores (Copper ? Titansteel)
  - Cloth (Linen ? Netherweave)
  - Leather (Light ? Dragonscale)
  - Herbs (Peacebloom ? Black Lotus)
  - Enchanting materials

- **20 Quest Items**

---

## ?? Troubleshooting

### "sqlcmd not found"
Install SQL Server Command Line Utilities:
https://docs.microsoft.com/en-us/sql/tools/sqlcmd-utility

### "Cannot connect to server"
1. Check SQL Server is running: `services.msc` ? SQL Server
2. Verify server name: `localhost`, `.\SQLEXPRESS`, or `(localdb)\mssqllocaldb`
3. Enable TCP/IP in SQL Server Configuration Manager

### "Login failed"
- **Windows Auth:** Run as Administrator
- **SQL Auth:** Enable in SQL Server properties ? Security ? SQL Server and Windows Authentication mode

### "Database already exists"
The script will drop and recreate. To keep data, comment out the DROP DATABASE line in `00_CreateDatabase.sql`

### Script execution errors
Run scripts **one at a time** in SSMS to see detailed error messages.

---

## ?? Additional Resources

- Full documentation: `Database/README.md`
- Setup instructions: `Database/SETUP_INSTRUCTIONS.md`
- Schema reference: See individual `Schema_*.sql` files

---

## ?? You're Ready!

Once setup is complete:
1. ? Database created with 80+ tables
2. ? 430+ items ready to loot
3. ? Complete game world populated
4. ? Entity Framework configured

**Just run `dotnet run` and start playing!** ??
