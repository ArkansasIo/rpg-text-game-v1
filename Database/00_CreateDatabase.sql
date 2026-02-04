-- =============================================
-- COMPLETE DATABASE SETUP SCRIPT
-- Run this file to create everything in one go
-- =============================================

USE master;
GO

-- Drop database if it exists (CAUTION: This deletes all data!)
IF EXISTS (SELECT name FROM sys.databases WHERE name = 'RPGGame')
BEGIN
    ALTER DATABASE RPGGame SET SINGLE_USER WITH ROLLBACK IMMEDIATE;
    DROP DATABASE RPGGame;
    PRINT 'Existing database dropped';
END
GO

-- Create the database
CREATE DATABASE RPGGame;
GO

PRINT '? Database ''RPGGame'' created successfully';
GO

USE RPGGame;
GO

PRINT '================================================';
PRINT 'STARTING SCHEMA CREATION';
PRINT '================================================';
GO

-- Now run the schema files in order
-- You'll need to execute Schema_Part1_Core.sql next
-- Then Schema_Part2_Social.sql
-- Then Schema_Part3_Advanced.sql
-- Then the Items files

PRINT '';
PRINT 'Next steps:';
PRINT '1. Execute Database\Schema_Part1_Core.sql';
PRINT '2. Execute Database\Schema_Part2_Social.sql';
PRINT '3. Execute Database\Schema_Part3_Advanced.sql';
PRINT '4. Execute Database\Items_Complete_400Plus.sql';
PRINT '5. Execute Database\Items_Complete_400Plus_Part2.sql';
PRINT '6. Execute Database\Items_Complete_400Plus_Part3.sql';
PRINT '7. Execute Database\Items_Complete_400Plus_Part4_FINAL.sql';
PRINT '8. (Optional) Execute Database\SeedData.sql';
PRINT '';
PRINT 'Or use the PowerShell script: Database\SetupDatabase.ps1';
GO
