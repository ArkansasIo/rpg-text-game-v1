# ? UNREAL ENGINE 5 QUICK START - 15 MINUTES

## ?? FASTEST PATH TO A RUNNING UE5 PROJECT

### **STEP 1: Prerequisites Check (2 minutes)**

```
Have you installed?
? Unreal Engine 5.3+ ? REQUIRED
? Visual Studio 2022 ? REQUIRED  
? .NET 6.0+ ? REQUIRED
? SQL Server or PostgreSQL ? OPTIONAL (for database)

If NO to any above:
? Download from links at bottom
? Install and come back here
```

### **STEP 2: Clone Repository (2 minutes)**

**Option A: Git Command**
```powershell
# Open PowerShell
# Copy & paste this:

cd Documents
git clone https://github.com/ArkansasIo/rpg-text-game-v1.git
cd rpg-text-game-v1

# DONE! Your files are ready
```

**Option B: Download ZIP**
```
1. Go: https://github.com/ArkansasIo/rpg-text-game-v1
2. Click: Green "Code" button
3. Click: "Download ZIP"
4. Extract to Documents folder
5. You have all files
```

### **STEP 3: Create UE5 Project (5 minutes)**

**Using Epic Games Launcher:**
```
1. Open Epic Games Launcher
2. Click "Create" (top right)
3. Select Engine: 5.3 or higher
4. Click "Blank" template
5. Configure:
   Project Name: AethermoorRPG
   Location: Your cloned folder
   Click: "Create Project"
6. WAIT 5 minutes (it's compiling)
```

**Result: Unreal Editor opens automatically**

### **STEP 4: Set Up Database (3 minutes - OPTIONAL)**

**Quick Database Setup:**
```
If you have SQL Server:
1. Navigate to: rpg-text-game-v1\Database
2. Double-click: SetupDatabase.bat
3. Follow prompts
4. Database created! ?

If you don't have SQL Server:
? Skip this for now
? Add later after testing
```

### **STEP 5: Start Building (3 minutes)**

**In Unreal Editor:**
```
1. Click: Content Browser (bottom left)
2. Create ? New Folder: "Blueprints"
3. Create ? New Folder: "Maps"
4. Right-click in Content:
   ? Blueprint Class
   ? Select "Character"
   ? Name: BP_Player
5. Click: "Compile" button
6. You just created your first Blueprint! ??
```

### **STEP 6: Test the Setup**

```
1. Click: "Play" button (top)
2. You should see:
   - Game viewport opens
   - You can move character (WASD keys)
   - Press ESC to exit
3. SUCCESS! ? Your project is working
```

---

## ? DONE! You now have:

```
? Unreal Engine 5 running
? Complete framework ready
? Blueprint system working
? Database set up (optional)
? Game ready to build
```

---

## ?? NEXT: Read Framework Documentation

**Choose your next step:**

### Option 1: Quick Learn (30 minutes)
1. Read: `UE5_BLUEPRINT_FRAMEWORK_QUICK_START.md`
2. Result: Understand the system

### Option 2: Deep Dive (2 hours)
1. Read: `UE5_UNIVERSAL_BLUEPRINT_FRAMEWORK.md`
2. Read: `UE5_UNIVERSAL_BLUEPRINT_FRAMEWORK_IMPLEMENTATION.md`
3. Result: Master the system

### Option 3: Start Building (1 hour)
1. Read: `UE5_BLUEPRINT_TEMPLATES.md`
2. Create: First blueprints
3. Result: Have working game systems

---

## ?? COMMON FIRST BLUEPRINTS TO CREATE

### Create Your First Menu
```
1. Content ? Blueprints folder
2. Right-click ? Blueprint Class
3. Search: "Widget"
4. Select: "User Widget"
5. Name: WBP_MainMenu
6. Double-click to open
7. In Designer tab:
   - Add: Canvas Panel
   - Add: Button widget
   - Add: Text label
   - Style your menu
8. Compile & Save
9. You have a menu! ??
```

### Create Your First Character
```
1. Content ? Blueprints ? Characters
2. Right-click ? Blueprint Class
3. Search: "Character"
4. Name: BP_Player
5. Double-click to open
6. In Components tab:
   - Add: Mesh component
   - Add: Camera
   - Add: Spring Arm
7. In Details:
   - Set mesh to "SK_Mannequin"
   - Adjust camera position
8. Compile & Save
9. You have a character! ??
```

### Create Your First Inventory
```
1. Content ? Blueprints ? Systems
2. Right-click ? Blueprint Class
3. Search: "Actor Component"
4. Name: BP_InventoryComponent
5. Double-click to open
6. In Details:
   - Create variable: Inventory Items (Array)
   - Create variable: Gold (Int)
   - Create variable: Capacity (Int)
7. Add functions:
   - Add Item
   - Remove Item
   - Get Inventory
8. Compile & Save
9. You have inventory! ??
```

---

## ?? WHAT'S NEXT AFTER QUICK START

**Week 1:** Create core blueprints (menus, character, inventory)  
**Week 2:** Add game systems (combat, progression, quests)  
**Week 3:** Create game content (maps, NPCs, items)  
**Week 4:** Polish & test  

---

## ?? IF SOMETHING GOES WRONG

### Project won't open?
```
1. Delete: Intermediate folder
2. Delete: Binaries folder  
3. Right-click .uproject ? "Generate VS files"
4. Try again
```

### Blueprints won't compile?
```
1. Make sure C++ code compiled first
2. Right-click Blueprint ? Recompile
3. Check Output Log for errors
```

### Database won't connect?
```
1. Make sure SQL Server is running
2. Check connection string in appsettings.json
3. Run: SetupDatabase.bat again
```

### Can't find templates?
```
1. Make sure you selected correct template
2. Create new Blueprint Class ? Search parent
3. All UE5 templates should be available
```

---

## ?? DOWNLOAD LINKS

**Unreal Engine 5:**
? https://www.unrealengine.com/download

**Visual Studio 2022:**
? https://visualstudio.microsoft.com/downloads/

**.NET 6.0:**
? https://dotnet.microsoft.com/download

**SQL Server Express:**
? https://www.microsoft.com/en-us/sql-server/sql-server-downloads

**Git:**
? https://git-scm.com/download/win

---

## ?? REFERENCE DOCUMENTS

**Setup Guide (Detailed):**
? `HOW_TO_OPEN_IN_UNREAL_ENGINE_5.md`

**Framework Guide:**
? `UE5_UNIVERSAL_BLUEPRINT_FRAMEWORK.md`

**Implementation Guide:**
? `UE5_UNIVERSAL_BLUEPRINT_FRAMEWORK_IMPLEMENTATION.md`

**Troubleshooting:**
? `UE5_Complete_Setup_Guide.md`

---

## ?? TIMELINE

```
Now:          Start here (you are here)
+15 min:      UE5 running with first blueprint
+1 hour:      Create core systems
+1 week:      Have playable game
+4 weeks:     Complete framework
```

---

## ?? CONGRATULATIONS!

You now have:
- ? A running Unreal Engine 5 project
- ? Complete blueprint framework
- ? All documentation & source code
- ? Database ready to connect
- ? Everything to build an AAA RPG/MMORPG

**Start creating!** ????

---

**Status:** Ready to Launch ?  
**Time Invested:** 15 minutes  
**Next:** Read Framework Documentation  

**Your game is about to be created!**
