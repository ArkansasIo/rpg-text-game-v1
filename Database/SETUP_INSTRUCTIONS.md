# Database Setup Instructions

## Prerequisites
- SQL Server 2016+ or SQL Server Express
- .NET 6.0 SDK
- Visual Studio 2022 or VS Code with C# extension

## Step 1: Install SQL Server

### Option A: SQL Server Express (Recommended for Development)
1. Download SQL Server Express from: https://www.microsoft.com/sql-server/sql-server-downloads
2. Run the installer and choose "Basic" installation
3. Note the server name (usually `localhost\SQLEXPRESS` or just `localhost`)

### Option B: SQL Server LocalDB (Lightweight)
1. Install with Visual Studio (included by default)
2. Server name: `(localdb)\mssqllocaldb`

## Step 2: Create Database

### Using SQL Server Management Studio (SSMS)
1. Open SSMS and connect to your server
2. Right-click "Databases" ? New Database
3. Name it `RPGGame`
4. Click OK

### Using Command Line
```bash
sqlcmd -S localhost -Q "CREATE DATABASE RPGGame"
```

## Step 3: Execute Schema Scripts

Execute the SQL files in this order:

1. **Schema_Part1_Core.sql** (Core tables: Accounts, Characters, Items, Zones, Enemies, Dungeons, Quests)
   ```sql
   USE RPGGame;
   GO
   -- Copy and paste contents of Schema_Part1_Core.sql
   ```

2. **Schema_Part2_Social.sql** (Social features: Guilds, Crafting, Economy, PvP)
   ```sql
   USE RPGGame;
   GO
   -- Copy and paste contents of Schema_Part2_Social.sql
   ```

3. **Schema_Part3_Advanced.sql** (Advanced features: Analytics, Companions, World Events)
   ```sql
   USE RPGGame;
   GO
   -- Copy and paste contents of Schema_Part3_Advanced.sql
   ```

4. **SeedData.sql** (Optional - Sample data for testing)
   ```sql
   USE RPGGame;
   GO
   -- Copy and paste contents of SeedData.sql
   ```

### Execute All at Once (PowerShell)
```powershell
sqlcmd -S localhost -d RPGGame -i Database/Schema_Part1_Core.sql
sqlcmd -S localhost -d RPGGame -i Database/Schema_Part2_Social.sql
sqlcmd -S localhost -d RPGGame -i Database/Schema_Part3_Advanced.sql
sqlcmd -S localhost -d RPGGame -i Database/SeedData.sql
```

## Step 4: Configure Connection String

Edit `appsettings.json` with your SQL Server details:

```json
{
  "ConnectionStrings": {
    "DefaultConnection": "Server=YOUR_SERVER_NAME;Database=RPGGame;Integrated Security=true;TrustServerCertificate=true;"
  }
}
```

### Common Connection Strings

**SQL Server Express:**
```
Server=localhost\\SQLEXPRESS;Database=RPGGame;Integrated Security=true;TrustServerCertificate=true;
```

**SQL Server LocalDB:**
```
Server=(localdb)\\mssqllocaldb;Database=RPGGame;Trusted_Connection=True;MultipleActiveResultSets=true
```

**SQL Server with SQL Authentication:**
```
Server=localhost;Database=RPGGame;User Id=sa;Password=YourPassword;TrustServerCertificate=true;
```

## Step 5: Install NuGet Packages

Run in your project directory:
```bash
dotnet restore
```

This installs:
- Microsoft.EntityFrameworkCore (6.0.25)
- Microsoft.EntityFrameworkCore.SqlServer (6.0.25)
- Microsoft.EntityFrameworkCore.Tools (6.0.25)
- Microsoft.Extensions.Configuration (6.0.1)
- Microsoft.Extensions.Configuration.Json (6.0.0)

## Step 6: Test Connection

Run the application:
```bash
dotnet run
```

You should see:
```
? Database connection successful!
==============================================
Save Mode: DATABASE
==============================================
```

## Step 7: Create Test Account and Character

### Using SSMS or SQL Query:
```sql
-- Create test account
INSERT INTO Accounts (Username, PasswordHash, Email, AccountStatus)
VALUES ('TestPlayer', 'hash_placeholder', 'test@example.com', 'Active');

-- Get the AccountID (should be 1 for first account)
SELECT AccountID FROM Accounts WHERE Username = 'TestPlayer';
```

### Using the Game:
The game will automatically create characters when you complete character creation.

## Troubleshooting

### "Cannot connect to database"
- Verify SQL Server is running: `services.msc` ? SQL Server service
- Check connection string matches your server name
- Test with: `sqlcmd -S YOUR_SERVER_NAME -Q "SELECT @@VERSION"`

### "Login failed for user"
- Using Windows Authentication? Connection string needs `Integrated Security=true`
- Using SQL Auth? Ensure SQL Server Authentication is enabled

### "Database does not exist"
- Verify database was created: `SELECT name FROM sys.databases`
- Create manually: `CREATE DATABASE RPGGame;`

### "Invalid object name 'Accounts'"
- Schema scripts not executed
- Run Schema_Part1_Core.sql first

### Entity Framework Migrations (Optional)

If you want to use EF migrations instead of SQL scripts:

```bash
# Create initial migration
dotnet ef migrations add InitialCreate

# Apply migration to database
dotnet ef database update
```

## Verify Installation

Run these queries to verify all tables exist:

```sql
USE RPGGame;
GO

-- Should return 80+ tables
SELECT COUNT(*) as TableCount 
FROM INFORMATION_SCHEMA.TABLES 
WHERE TABLE_TYPE = 'BASE TABLE';

-- List all tables
SELECT TABLE_NAME 
FROM INFORMATION_SCHEMA.TABLES 
WHERE TABLE_TYPE = 'BASE TABLE'
ORDER BY TABLE_NAME;
```

## Next Steps

1. ? Database created
2. ? Schema applied
3. ? Connection string configured
4. ? Application connects successfully
5. ?? Create character and play!

## Features Now Available

With database mode enabled:
- ? Persistent character saves
- ? Multi-character support
- ? Account system
- ? Inventory persistence
- ?? Guild system (coming soon)
- ?? Auction house (coming soon)
- ?? Achievement tracking (coming soon)

## Need Help?

Check README.md for database schema documentation and sample queries.
