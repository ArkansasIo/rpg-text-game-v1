# ?? HOW TO OPEN & SET UP YOUR PROJECT IN UNREAL ENGINE 5

## ?? QUICK START (15 MINUTES)

### Step 1: Prerequisites
```
Required:
? Unreal Engine 5.3+ (installed)
? Visual Studio 2022 with C++ tools
? Git (for version control)
? SQL Server or PostgreSQL (for database)
? .NET 6.0+ (for C# backend)

Recommended:
? 16+ GB RAM
? SSD with 50GB+ free space
? GPU with 4GB+ VRAM
```

### Step 2: Clone the Repository
```powershell
# Open PowerShell and navigate to your projects folder
cd "C:\Users\YourName\Documents\Projects"

# Clone the repository
git clone https://github.com/ArkansasIo/rpg-text-game-v1.git

# Navigate to the project
cd rpg-text-game-v1
```

### Step 3: Create UE5 Project
```
Option A: Via Epic Games Launcher
1. Open Epic Games Launcher
2. Click "Create"
3. Select Unreal Engine 5.3 or higher
4. Choose "Games" ? "Blank"
5. Set project name: "AethermoorRPG"
6. Set location: Your cloned repository folder
7. Click "Create Project"

Option B: Via Command Line
"C:\Program Files\Epic Games\UE_5.3\Engine\Build\BatchFiles\RunUAT.bat" 
BuildProject -Project="C:\Path\To\Project\AethermoorRPG.uproject" 
-Build -BuildConfiguration=Development -platform=Win64
```

### Step 4: Set Up the Project
```
1. Open the generated .uproject file with Unreal Editor
2. Wait for initial compilation (5-10 minutes)
3. Once opened, the editor will ask to build C++ code
4. Click "Yes" to build
5. Wait for compilation to complete
```

---

## ??? DETAILED SETUP GUIDE

### Full Setup Process (30-60 Minutes)

#### Phase 1: Prerequisites Installation

**Install Unreal Engine 5**
```
1. Download Epic Games Launcher
2. Install ? Engine ? Unreal Engine 5.3+ (latest)
3. Wait for installation (30-60 minutes)
4. Verify installation by opening Epic Launcher
```

**Install Visual Studio 2022**
```
1. Download Visual Studio Community 2022
2. Install with these components:
   ? Desktop development with C++
   ? Windows 10/11 SDK
   ? Unreal Engine compatibility
3. Complete installation
4. Open Visual Studio ? verify C++ tools installed
```

**Install .NET 6.0+**
```
1. Download .NET SDK (latest LTS)
2. Install and add to PATH
3. Verify: Open PowerShell
   dotnet --version
4. Should show: 6.0.x or higher
```

**Install SQL Server**
```
Option 1: SQL Server Express
1. Download SQL Server Express (free)
2. Install with mixed authentication
3. Remember SA password
4. Verify: Open SQL Server Management Studio

Option 2: PostgreSQL
1. Download PostgreSQL
2. Install and remember postgres password
3. Verify: Connect with pgAdmin
```

---

#### Phase 2: Repository Setup

**Clone the Repository**
```powershell
# Create projects folder
mkdir "C:\Dev\UnrealProjects"
cd "C:\Dev\UnrealProjects"

# Clone
git clone https://github.com/ArkansasIo/rpg-text-game-v1.git

# Navigate in
cd rpg-text-game-v1

# Verify git status
git status
```

**Folder Structure After Clone**
```
rpg-text-game-v1/
??? UnrealEngine5/
?   ??? Source/
?   ?   ??? RPGProject/
?   ?       ??? Input/
?   ?       ??? UI/
?   ?       ??? Components/
?   ?       ??? MMORPG/
?   ?       ??? RPGCharacter.h
?   ?       ??? RPGGameMode.h
?   ?       ??? RPGTypes.h
?   ?       ??? ...
?   ??? Binaries/
?   ??? Intermediate/
?   ??? Content/
?   ?   ??? Blueprints/
?   ??? ...
??? Database/
?   ??? Schema files
?   ??? Setup scripts
?   ??? Entities
??? Game/
?   ??? C# game systems
?   ??? World systems
??? UI/
?   ??? C# UI systems
??? Documentation/
?   ??? All markdown guides
??? README.md
```

---

#### Phase 3: UE5 Project Creation

**Method 1: Using Epic Games Launcher (Recommended)**
```
1. Open Epic Games Launcher
2. Click "Create" button
3. Select Engine Version: 5.3 (or latest)
4. Choose Template: "Blank" (C++)
5. Configure:
   - Project Name: AethermoorRPG
   - Project Type: Games
   - Quality: Maximum
   - Target Hardware: Desktop
   - With Starter Content: ? (optional)
6. Project Location: 
   C:\Dev\UnrealProjects\rpg-text-game-v1
7. Click "Create Project"
8. Wait 5-10 minutes for initial setup
```

**Method 2: Command Line Setup**
```powershell
# Navigate to UE5 installation
cd "C:\Program Files\Epic Games\UE_5.3\Engine\Build\BatchFiles"

# Generate project
RunUAT.bat GenerateProjectFiles -project=
"C:\Dev\UnrealProjects\rpg-text-game-v1\AethermoorRPG.uproject" 
-game -engine

# Build project
RunUAT.bat BuildProject -Project=
"C:\Dev\UnrealProjects\rpg-text-game-v1\AethermoorRPG.uproject" 
-Build -BuildConfiguration=Development -platform=Win64
```

---

#### Phase 4: C++ Code Integration

**Copy C++ Source Files**
```
1. In your UE5 project folder, create:
   Source/AethermoorRPG/
   
2. Copy from repository to new location:
   rpg-text-game-v1/UnrealEngine5/Source/RPGProject/*
   ? AethermoorRPG/Source/AethermoorRPG/
   
3. Files to copy:
   ??? Input/
   ?   ??? InputManager.h
   ?   ??? InputManager.cpp
   ??? UI/
   ?   ??? UIManager.h
   ?   ??? RuntimeCombatHUD.h
   ??? Components/
   ?   ??? CombatComponent.h
   ?   ??? InventoryComponent.h
   ?   ??? QuestComponent.h
   ?   ??? GuildComponent.h
   ??? MMORPG/
   ?   ??? MMORPGSystems.h
   ??? RPGCharacter.h
   ??? RPGGameMode.h
   ??? RPGTypes.h
   ??? Other files
```

**Regenerate Visual Studio Project**
```
1. Open File Explorer
2. Navigate to project folder
3. Right-click on .uproject file
4. Select "Generate Visual Studio project files"
5. Close any open Visual Studio instances
6. Right-click again ? "Open with Visual Studio"
7. Visual Studio will open the solution
```

**Build the Project**
```
In Visual Studio:
1. Solution Explorer ? Select your project
2. Build ? Build Solution
3. Wait for compilation (5-15 minutes, first time)
4. Verify: "Build Succeeded" message

Or via Command Line:
cd "C:\Dev\UnrealProjects\rpg-text-game-v1"
.\AethermoorRPG.sln
# Build from Visual Studio
```

---

#### Phase 5: Blueprint Framework Setup

**Create Blueprint Folders**
```
In Unreal Editor:
1. Content Browser ? Create Folder Structure:
   
   Content/
   ??? Blueprints/
       ??? Core/
       ?   ??? BP_GameFramework
       ?   ??? BP_GameState
       ?   ??? BP_PlayerController
       ??? Characters/
       ?   ??? BP_CharacterBase
       ?   ??? BP_PlayerCharacter
       ??? UI/
       ?   ??? MainMenu/
       ?   ??? InGame/
       ?   ??? Settings/
       ??? Systems/
       ?   ??? BP_InventoryComponent
       ?   ??? BP_CombatComponent
       ?   ??? BP_ProgressionComponent
       ??? Items/
       ??? NPCs/
       ??? Enemies/
       ??? Abilities/
       ??? Effects/
       ??? Maps/
       ??? Managers/
```

**Create Blueprint Classes from C++**
```
In Unreal Editor:
1. Content Browser ? New ? Blueprint Class
2. Search for parent class (e.g., "Character")
3. Create Blueprint (e.g., BP_PlayerCharacter)
4. Open the blueprint
5. Reference your C++ classes in components
6. Add variables and events
7. Compile and save
```

**Use the Documentation**
```
Reference these files for blueprint creation:
??? UE5_UNIVERSAL_BLUEPRINT_FRAMEWORK.md
??? UE5_UNIVERSAL_BLUEPRINT_FRAMEWORK_IMPLEMENTATION.md
??? UE5_BLUEPRINT_FRAMEWORK_QUICK_START.md
??? UE5_BLUEPRINT_TEMPLATES.md

Copy blueprint specifications from documentation
and implement in Unreal Editor.
```

---

#### Phase 6: Database Setup

**Set Up Database**
```
Option 1: SQL Server
1. Open SQL Server Management Studio
2. Connect to local server
3. Create new database: "AethermoorRPG"
4. Execute scripts in order:
   1. Database/00_CreateDatabase.sql
   2. Database/Schema_Part1_Core.sql
   3. Database/Schema_Part2_Social.sql
   4. Database/Schema_Part3_Advanced.sql
   5. Database/SeedData.sql
5. Verify tables created in Object Explorer

Option 2: PowerShell Setup
1. Open PowerShell as Administrator
2. Navigate to Database folder
3. Run: .\SetupDatabase.ps1
4. Follow prompts
5. Database will be created automatically
```

**Update Connection String**
```
File: appsettings.json

Modify:
"ConnectionStrings": {
  "DefaultConnection": "Server=YOUR_SERVER;
  Database=AethermoorRPG;User Id=sa;
  Password=YOUR_PASSWORD;Encrypt=false;"
}

Or for PostgreSQL:
"DefaultConnection": "Host=localhost;
Database=aethermoorpg;Username=postgres;
Password=YOUR_PASSWORD;Port=5432;"
```

**Test Database Connection**
```
In Visual Studio:
1. Open Package Manager Console
2. Set default project to: YourGame.csproj
3. Run: Update-Database
4. Verify: Tables appear in SQL Server
```

---

#### Phase 7: Running the Project

**First Launch**
```
1. Open Unreal Editor:
   Double-click AethermoorRPG.uproject
   OR
   Right-click ? Open with Unreal Engine 5

2. Wait for initial load (5-10 minutes)
   - Compiling shaders
   - Building lighting
   - Initializing systems

3. When editor opens:
   - Bottom-right: "Building lighting..." may appear
   - Wait for completion
   - Editor is ready when no messages show

4. Test by:
   - Pressing "Play" button
   - Should see game viewport
   - Check console for any errors
```

**Verify Installation**
```
Checklist:
? Unreal Editor opens without errors
? Content Browser shows Blueprint folders
? Output Log shows no critical errors
? Play button works
? Database connection verified
? C++ classes visible in Blueprint creation
```

---

## ?? NEXT STEPS AFTER SETUP

### 1. Import Blueprint Framework (1-2 hours)
```
1. Read: UE5_BLUEPRINT_FRAMEWORK_QUICK_START.md
2. Follow: UE5_UNIVERSAL_BLUEPRINT_FRAMEWORK_IMPLEMENTATION.md
3. Create core blueprints:
   - BP_GameFramework
   - BP_GameState
   - BP_PlayerController
   - BP_CharacterBase
   - WBP_MainMenuSystem
4. Test menu navigation
```

### 2. Set Up Game Systems (2-3 hours)
```
1. Create game systems:
   - BP_InventoryComponent
   - BP_CombatComponent
   - BP_ProgressionComponent
   - BP_QuestComponent
2. Add to character blueprint
3. Test functionality
```

### 3. Create Content (4-5 hours)
```
1. Create maps
2. Place NPCs
3. Add quests
4. Set up enemies
5. Configure spawning
```

### 4. Test & Debug (1-2 hours)
```
1. Play test
2. Check logs for errors
3. Debug issues
4. Verify database integration
5. Test menu flow
```

---

## ?? DOCUMENTATION REFERENCES

**For Setup Issues:**
```
??? UE5_Complete_Setup_Guide.md
??? UE5_Integration_Guide.md
??? Database/SETUP_INSTRUCTIONS.md
??? Database/QUICK_START.md
```

**For Blueprint Framework:**
```
??? UE5_UNIVERSAL_BLUEPRINT_FRAMEWORK.md
??? UE5_UNIVERSAL_BLUEPRINT_FRAMEWORK_IMPLEMENTATION.md
??? UE5_BLUEPRINT_FRAMEWORK_QUICK_START.md
??? UE5_BLUEPRINT_TEMPLATES.md
```

**For Database:**
```
??? Database/README.md
??? Database/SETUP_INSTRUCTIONS.md
??? UnrealEngine5/ExportDataToUE5.sql
```

---

## ?? TROUBLESHOOTING

### Issue: Project won't open
```
Solution:
1. Delete Intermediate folder
2. Delete Binaries folder
3. Right-click .uproject ? Generate Visual Studio files
4. Open in Visual Studio ? Build
5. Double-click .uproject again
```

### Issue: C++ code won't compile
```
Solution:
1. Close Unreal Editor
2. Delete Intermediate folder
3. Open in Visual Studio ? Clean Solution
4. Rebuild Solution
5. Reopen Unreal Editor
```

### Issue: Database connection failed
```
Solution:
1. Verify SQL Server is running
2. Check connection string in appsettings.json
3. Test connection with SSMS
4. Run migration: Update-Database
5. Verify tables exist
```

### Issue: Blueprints won't compile
```
Solution:
1. Check parent class exists
2. Verify C++ code is compiled
3. Restart Unreal Editor
4. Right-click Blueprint ? Recompile
5. Check Output Log for errors
```

---

## ? VERIFICATION CHECKLIST

- [ ] Unreal Engine 5 installed
- [ ] Visual Studio 2022 with C++ tools
- [ ] .NET 6.0+ installed
- [ ] SQL Server or PostgreSQL installed
- [ ] Repository cloned
- [ ] UE5 project created
- [ ] C++ files copied to project
- [ ] Visual Studio project regenerated
- [ ] Project compiled successfully
- [ ] Unreal Editor opens without errors
- [ ] Content Browser shows Blueprint folders
- [ ] Database created and populated
- [ ] Connection string configured
- [ ] Play button works
- [ ] No critical errors in Output Log

---

## ?? YOU'RE READY TO:

? Open Unreal Engine 5  
? Import the Blueprint Framework  
? Create game content  
? Build your MMORPG/RPG  
? Deploy to production  

---

## ?? QUICK REFERENCE

**Unreal Engine Installation:**
? https://www.unrealengine.com/download

**Visual Studio Installation:**
? https://visualstudio.microsoft.com/downloads/

**.NET Installation:**
? https://dotnet.microsoft.com/download

**SQL Server Installation:**
? https://www.microsoft.com/en-us/sql-server/sql-server-downloads

**PostgreSQL Installation:**
? https://www.postgresql.org/download/

---

**Status:** Ready to Launch in UE5 ?  
**Time to First Play:** 30-60 minutes  
**Time to Complete Setup:** 2-3 hours  

**Let's build your game in Unreal Engine 5!** ????
