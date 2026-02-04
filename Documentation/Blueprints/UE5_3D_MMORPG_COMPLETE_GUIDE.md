# ?? 3D MMORPG UE5 System - Complete Implementation Guide

## Overview

This guide covers the complete 3D MMORPG implementation for Unreal Engine 5, including:
- Multi-device input systems (Keyboard, Mouse, Xbox, PS5 controllers)
- Advanced menu systems with navigation
- Comprehensive settings management
- Real-time combat HUD
- Social systems (Party, Guild, Raid)
- Complete MMORPG feature set

---

## ?? File Structure

```
UnrealEngine5/Source/RPGProject/
??? Input/
?   ??? InputManager.h         # Multi-device input handling
?   ??? InputManager.cpp       # Input implementation
??? UI/
?   ??? UIManager.h            # Menu and screen management
?   ??? RuntimeCombatHUD.h     # Combat HUD display
?   ??? SettingsManager.h      # Game settings (in UIManager.h)
??? MMORPG/
    ??? MMORPGSystems.h        # Party, Raid, Guild, Social
```

---

## ?? Input System (Multi-Device Support)

### Supported Input Devices

1. **Keyboard** - WASD movement, Mouse aiming
2. **Mouse** - Click interactions, camera control
3. **Xbox Controller** - Full analog support
4. **PS5 Controller** - DualSense features (haptics, triggers)
5. **Generic Gamepad** - Compatible with most controllers

### Input Manager Features

#### Initialize Input
```cpp
UInputManager* InputManager = GetWorld()->SpawnActor<UInputManager>();
InputManager->InitializeInput(GetPlayerController(0));
```

#### Register Custom Input Actions
```cpp
FInputKeyBinding KeyBinding;
KeyBinding.PrimaryKey = EKeys::W;
KeyBinding.ControllerKey = EKeys::Gamepad_LeftStick_Up;
KeyBinding.bIsAxisInput = true;

InputManager->RegisterInputAction(FName("MoveForward"), KeyBinding);
```

#### Handle Input Events
```cpp
// Bind to input delegates
InputManager->OnMoveForward.AddDynamic(this, &AMyCharacter::MoveForward);
InputManager->OnLookRight.AddDynamic(this, &AMyCharacter::LookRight);
InputManager->OnAction.AddDynamic(this, &AMyCharacter::OnActionPressed);
```

#### Check Input State
```cpp
// Check if key is pressed
bool bWKeyPressed = InputManager->IsKeyPressed(EKeys::W);
bool bAPressed = InputManager->IsKeyPressed(EKeys::A);

// Get analog values
FVector2D LeftStick = InputManager->GetGamepadAnalogStickValue(EGamepadAnalogStick::LeftStick);
float RightTrigger = InputManager->GetGamepadTriggerValue(EGamepadTriggerAxis::RightTrigger);
```

#### Controller Feedback
```cpp
// Vibrate/Rumble
InputManager->PlayControllerVibration(0.8f, 0.5f); // Intensity, Duration

// Light vibration
InputManager->PlayControllerVibration(0.3f, 0.2f);

// Strong rumble
InputManager->PlayControllerVibration(1.0f, 1.0f);
```

#### Rebind Keys
```cpp
// Allow players to customize controls
InputManager->RebindKey(FName("MoveForward"), EKeys::Up, true);
InputManager->RebindKey(FName("MoveForward"), EKeys::W, true);
```

#### Detect Input Device
```cpp
EInputDeviceType CurrentDevice = InputManager->GetCurrentInputDevice();

switch (CurrentDevice)
{
    case EInputDeviceType::Keyboard:
        // Show keyboard prompts
        break;
    case EInputDeviceType::Mouse:
        // Show mouse prompts
        break;
    case EInputDeviceType::Gamepad_Xbox:
        // Show Xbox button prompts (A, B, X, Y)
        break;
    case EInputDeviceType::Gamepad_PS5:
        // Show PS5 button prompts (Cross, Circle, Square, Triangle)
        break;
}
```

---

## ?? UI & Menu System

### Menu Manager Features

#### Initialize UI System
```cpp
UUIManager* UIManager = GetGameInstance<UUIManager>();
UIManager->InitializeUIManager();
```

#### Show/Hide UI Screens
```cpp
// Show main menu
UIManager->ShowScreen(EUIScreenType::MainMenu);

// Show pause menu
UIManager->ShowScreen(EUIScreenType::PauseMenu);

// Show inventory
UIManager->ShowScreen(EUIScreenType::InventoryUI);

// Hide all screens
UIManager->HideAllScreens();

// Toggle screen
UIManager->ToggleScreen(EUIScreenType::SettingsMenu);
```

#### Available UI Screens
```cpp
EUIScreenType::MainMenu           // Game start
EUIScreenType::CharacterCreation  // Character creation
EUIScreenType::PauseMenu          // Game pause
EUIScreenType::SettingsMenu       // Settings/options
EUIScreenType::InventoryUI        // Player inventory
EUIScreenType::CharacterUI        // Character sheet
EUIScreenType::QuestUI            // Quest log
EUIScreenType::MapUI              // World map
EUIScreenType::GuildUI            // Guild management
EUIScreenType::SocialUI           // Friends, chat
EUIScreenType::CombatUI           // In-game HUD
EUIScreenType::DialogueUI         // NPC dialogue
EUIScreenType::ShopUI             // Vendor shops
EUIScreenType::CraftingUI         // Crafting interface
```

#### Menu Navigation
```cpp
// Navigate with gamepad
UIManager->NavigateMenu(true);  // Navigate up
UIManager->NavigateMenu(false); // Navigate down

// Select option
UIManager->SelectMenuOption();

// Cancel/Go back
UIManager->CancelMenu();
```

#### Notifications
```cpp
// Show simple notification
UIManager->ShowNotification(FString("Quest Completed!"), 3.0f, FLinearColor::Green);

// Show dialog with options
TArray<FString> Options = { "Yes", "No", "Cancel" };
UIManager->ShowDialog(FString("Confirm"), FString("Are you sure?"), Options);
```

---

## ?? Settings Manager

### Graphics Settings
```cpp
USettingsManager* Settings = NewObject<USettingsManager>();

// Set graphics quality
Settings->SetGraphicsQuality(3); // 0=Low, 1=Medium, 2=High, 3=Ultra
int32 Quality = Settings->GetGraphicsQuality();

// Resolution
Settings->SetResolution(FIntPoint(2560, 1440));
FIntPoint Res = Settings->GetResolution();

// Fullscreen
Settings->SetFullscreen(true);
bool bFullscreen = Settings->IsFullscreen();

// VSync
Settings->SetVSync(true);
bool bVSync = Settings->IsVSyncEnabled();
```

### Audio Settings
```cpp
// Master volume
Settings->SetMasterVolume(0.8f); // 0.0 - 1.0
float Master = Settings->GetMasterVolume();

// Music volume
Settings->SetMusicVolume(0.6f);

// SFX volume
Settings->SetSFXVolume(0.8f);

// Voice volume
Settings->SetVoiceVolume(0.9f);
```

### Game Settings
```cpp
// Difficulty
Settings->SetDifficulty(1); // 0=Easy, 1=Normal, 2=Hard, 3=Legendary

// Mouse sensitivity
Settings->SetMouseSensitivity(1.5f);

// Gamepad sensitivity
Settings->SetGamepadSensitivity(1.2f);

// Camera distance
Settings->SetCameraFollowDistance(400.0f);

// Invert mouse Y
Settings->SetInvertMouseY(true);

// Invert gamepad Y
Settings->SetInvertGamepadY(false);
```

### Accessibility Settings
```cpp
// Color blind mode
Settings->SetColorBlindMode(1); // 0=Off, 1=Deuteranopia, 2=Protanopia, 3=Tritanopia

// UI Scale
Settings->SetUIScale(1.5f); // 0.5 - 2.0

// Subtitles
Settings->SetSubtitlesEnabled(true);
```

### Save/Load Settings
```cpp
// Save settings to file
Settings->SaveSettings();

// Load settings from file
Settings->LoadSettings();

// Reset to defaults
Settings->ResetToDefaults();
```

---

## ?? Combat HUD System

### Initialize Combat HUD
```cpp
ARPGCharacter* Player = Cast<ARPGCharacter>(GetCharacter());
URuntimeCombatHUD* CombatHUD = CreateWidget<URuntimeCombatHUD>(GetWorld(), URuntimeCombatHUDClass);
CombatHUD->AddToViewport();
```

### Update Player Stats
```cpp
// Update health bar
CombatHUD->UpdatePlayerHealth(75, 100); // Current, Max

// Update mana bar
CombatHUD->UpdatePlayerMana(45, 100);

// Update stamina
CombatHUD->UpdatePlayerStamina(80, 100);

// Update level
CombatHUD->UpdateLevel(25);

// Update experience
CombatHUD->UpdateExperience(5000, 10000);
```

### Status Effects Display
```cpp
// Add status effect
UTexture2D* PoisonIcon = LoadObject<UTexture2D>(nullptr, TEXT("/Game/Icons/Poison"));
CombatHUD->AddStatusEffect(FString("Poisoned"), 10.0f, PoisonIcon);

// Remove status effect
CombatHUD->RemoveStatusEffect(FString("Poisoned"));
```

### Ability Cooldowns
```cpp
// Update cooldown for ability slot 0
CombatHUD->UpdateAbilityCooldown(0, 2.5f, 5.0f); // Current cooldown, Max cooldown

// Mark ability as ready
CombatHUD->SetAbilityReady(0, true);
```

### Target Information
```cpp
// Set target info
CombatHUD->SetTargetInfo(
    FString("Goblin Warrior"),
    75,     // Current health
    100,    // Max health
    15      // Level
);

// Clear target
CombatHUD->ClearTargetInfo();
```

### Combat Numbers
```cpp
// Show damage number (floating text)
CombatHUD->ShowDamageNumber(47);               // Normal damage
CombatHUD->ShowDamageNumber(127, FLinearColor::Red, true); // Critical damage

// Show healing
CombatHUD->ShowHealingNumber(50);

// Show combat message
CombatHUD->ShowCombatMessage(FString("Spell Fizzled!"), FLinearColor::Yellow);
```

### HUD Display Modes
```cpp
// Set HUD mode
CombatHUD->SetHUDMode(EHUDDisplayMode::Combat);        // Full combat HUD
CombatHUD->SetHUDMode(EHUDDisplayMode::Exploration);   // Minimal HUD
CombatHUD->SetHUDMode(EHUDDisplayMode::Dialog);        // Dialog mode

// Get current mode
EHUDDisplayMode CurrentMode = CombatHUD->GetHUDMode();

// Toggle visibility
CombatHUD->ToggleHUDVisibility(); // Press 'H' to toggle
CombatHUD->SetHUDVisible(true);
```

### Minimap
```cpp
// Add marker to minimap
CombatHUD->UpdateMinimapMarker(FName("Quest_Marker_1"), FVector2D(150, 200), FLinearColor::Red);

// Remove marker
CombatHUD->RemoveMinimapMarker(FName("Quest_Marker_1"));
```

---

## ?? MMORPG Social Systems

### Party System

#### Create and Manage Parties
```cpp
APartySystem* PartySystem = GetWorld()->SpawnActor<APartySystem>();

// Create party
PartySystem->CreateParty(Player, FString("Dragon Slayers"));

// Invite player
PartySystem->InviteToParty(OtherPlayer);

// Accept invite
PartySystem->AcceptPartyInvite(Player);

// Leave party
PartySystem->LeaveParty();

// Disband party (leader only)
PartySystem->DisbandParty();
```

#### Party Information
```cpp
// Get party members
TArray<FPartyMember> Members = PartySystem->GetPartyMembers();

// Get specific member
FPartyMember Member = PartySystem->GetPartyMember(FName("PlayerName"));

// Check party size
int32 Size = PartySystem->GetPartySize(); // Max 5

// Check if member in party
bool bInParty = PartySystem->IsMemberInParty(FName("PlayerName"));

// Check if leader
bool bLeader = PartySystem->IsPartyLeader(FName("PlayerName"));
```

#### Party Events
```cpp
// Listen for party events
PartySystem->OnMemberJoined.AddDynamic(this, &AMyCharacter::OnPartyMemberJoined);
PartySystem->OnMemberLeft.AddDynamic(this, &AMyCharacter::OnPartyMemberLeft);
PartySystem->OnPartyDisbanded.AddDynamic(this, &AMyCharacter::OnPartyDisbanded);
PartySystem->OnMemberHealthChanged.AddDynamic(this, &AMyCharacter::OnMemberHealthChanged);
```

#### Loot Distribution
```cpp
// Set loot distribution mode
// 0 = Need Before Greed
// 1 = Round Robin
// 2 = Master Loot
// 3 = Free For All
PartySystem->SetLootDistribution(0);

// Distribute loot
PartySystem->DistributeLoot(ItemDropped, ItemRarity);
```

### Guild System

#### Create and Manage Guilds
```cpp
AGuildSystem* GuildSystem = GetWorld()->SpawnActor<AGuildSystem>();

// Create guild
GuildSystem->CreateGuild(FounderPlayer, FString("The Fellowship"), FString("We Fight as One"));

// Invite player
GuildSystem->InviteToGuild(NewPlayer);

// Join guild
GuildSystem->JoinGuild(NewPlayer);

// Leave guild
GuildSystem->LeaveGuild(LeavingPlayer);

// Kick member
GuildSystem->KickFromGuild(FName("BadPlayer"));

// Disband guild (founder only)
GuildSystem->DisbandGuild();
```

#### Guild Ranks
```cpp
// Set member rank
// Founder, LeadOfficer, Officer, Member, Initiate
GuildSystem->SetMemberRank(FName("PlayerName"), EGuildRank::Officer);

// Get member rank
EGuildRank Rank = GuildSystem->GetMemberRank(FName("PlayerName"));
```

#### Guild Progression
```cpp
// Add experience to guild
GuildSystem->AddGuildXP(500);

// Get guild info
FGuildInfo Info = GuildSystem->GetGuildInfo();
UE_LOG(LogTemp, Warning, TEXT("Guild: %s (Level %d)"), *Info.GuildName, Info.Level);

// Get guild members
TArray<FGuildMember> Members = GuildSystem->GetGuildMembers();

// Get member count
int32 Count = GuildSystem->GetMemberCount();
```

#### Guild Events
```cpp
GuildSystem->OnMemberJoined.AddDynamic(this, &AMyCharacter::OnGuildMemberJoined);
GuildSystem->OnMemberLeft.AddDynamic(this, &AMyCharacter::OnGuildMemberLeft);
GuildSystem->OnGuildLevelUp.AddDynamic(this, &AMyCharacter::OnGuildLevelUp);
```

### Raid System

#### Raid Management
```cpp
ARaidSystem* RaidSystem = GetWorld()->SpawnActor<ARaidSystem>();

// Create raid (20 players)
RaidSystem->CreateRaid(RaidLeader, FString("Dragon's Lair"), 20);

// Invite and join
RaidSystem->InviteToRaid(Player);
RaidSystem->JoinRaid();

// Disband raid
RaidSystem->DisbandRaid();
```

#### Ready Check
```cpp
// Start ready check
RaidSystem->InitiateReadyCheck();

// Mark player as ready
RaidSystem->MarkReady(true);
```

#### Group Management
```cpp
// Set group (1-8 groups for 20-player raids)
RaidSystem->SetGroup(FName("PlayerName"), 2);

// Get member's group
int32 Group = RaidSystem->GetMemberGroup(FName("PlayerName"));

// Get raid members
TArray<FRaidMember> Members = RaidSystem->GetRaidMembers();
```

### Social System

#### Friends
```cpp
ASocialSystem* SocialSystem = GetWorld()->SpawnActor<ASocialSystem>();

// Add friend
SocialSystem->AddFriend(FName("FriendName"));

// Remove friend
SocialSystem->RemoveFriend(FName("FriendName"));

// Block player
SocialSystem->BlockPlayer(FName("PlayerName"));

// Unblock
SocialSystem->UnblockPlayer(FName("PlayerName"));

// Get friends list
TArray<FFriend> Friends = SocialSystem->GetFriends();

// Check if friend
bool bFriend = SocialSystem->IsFriend(FName("PlayerName"));

// Check if blocked
bool bBlocked = SocialSystem->IsBlocked(FName("PlayerName"));
```

#### Chat
```cpp
// Send message to chat channel
// 0 = Say (nearby), 1 = Party, 2 = Guild, 3 = Trade, 4 = Whisper
SocialSystem->SendMessage(FString("Hello everyone!"), 0);

// Send whisper (private message)
SocialSystem->SendWhisper(FName("FriendName"), FString("Hey there!"));
```

---

## ?? Complete Example: Game Flow

```cpp
void AMyGameMode::BeginPlay()
{
    Super::BeginPlay();

    // Initialize all systems
    UInputManager* InputManager = NewObject<UInputManager>();
    InputManager->RegisterComponent();
    InputManager->InitializeInput(GetWorld()->GetFirstPlayerController());

    UUIManager* UIManager = GetGameInstance<UUIManager>();
    UIManager->InitializeUIManager();

    USettingsManager* SettingsManager = NewObject<USettingsManager>();
    SettingsManager->LoadSettings();

    // Setup input bindings
    InputManager->OnMoveForward.AddDynamic(this, &AMyGameMode::HandleMoveForward);
    InputManager->OnLookRight.AddDynamic(this, &AMyGameMode::HandleLookRight);
    InputManager->OnOpenMenu.AddDynamic(this, &AMyGameMode::HandleOpenMenu);

    // Create social systems
    APartySystem* PartySystem = GetWorld()->SpawnActor<APartySystem>();
    AGuildSystem* GuildSystem = GetWorld()->SpawnActor<AGuildSystem>();
    ASocialSystem* SocialSystem = GetWorld()->SpawnActor<ASocialSystem>();

    // Create and show combat HUD
    URuntimeCombatHUD* CombatHUD = CreateWidget<URuntimeCombatHUD>(
        GetWorld()->GetFirstPlayerController(),
        URuntimeCombatHUDClass
    );
    if (CombatHUD)
    {
        CombatHUD->AddToViewport();
        CombatHUD->SetHUDMode(EHUDDisplayMode::Combat);
    }
}

void AMyGameMode::HandleMoveForward(const FInputActionValue& Value, float DeltaTime)
{
    // Handle movement
    ACharacter* PlayerCharacter = GetWorld()->GetFirstPlayerController()->GetCharacter();
    if (PlayerCharacter)
    {
        PlayerCharacter->AddMovementInput(
            PlayerCharacter->GetActorForwardVector(),
            Value.GetMagnitude() * DeltaTime
        );
    }
}

void AMyGameMode::HandleOpenMenu()
{
    // Toggle pause menu
    UUIManager* UIManager = GetGameInstance<UUIManager>();
    UIManager->ToggleScreen(EUIScreenType::PauseMenu);
}
```

---

## ?? Keyboard Controls Summary

### Movement & Camera
- `W` / `Up Arrow` - Move Forward
- `A` / `Left Arrow` - Strafe Left
- `S` / `Down Arrow` - Move Backward
- `D` / `Right Arrow` - Strafe Right
- `Mouse Move` - Look Around
- `Right Mouse Button` - Free Look

### Actions & Abilities
- `Space` - Primary Action / Jump
- `E` - Interact with NPC/Objects
- `1-0` - Ability Bar Slots
- `F` - Toggle Targeting
- `T` - Toggle PvP
- `N` - Toggle Nameplates

### UI & Menus
- `I` or `M` - Toggle Inventory/Menu
- `C` - Open Character Sheet
- `Q` - Open Quest Log
- `Escape` - Pause Menu / Cancel
- `H` - Toggle HUD
- `Tab` - Toggle Map

### Social
- `Enter` - Chat
- `/` - Command Input
- `B` - Open Social/Friends

---

## ?? Controller Buttons

### Xbox Controller
- `A` - Jump / Select / Confirm
- `B` - Interact / Cancel
- `X` - Ability 1
- `Y` - Ability 2
- `LB/RB` - Ability 3/4
- `LT/RT` - Aim / Secondary Action
- `Left Stick` - Movement
- `Right Stick` - Camera Control
- `Start` - Pause Menu
- `Back` - Inventory

### PS5 Controller (DualSense)
- `Cross (X)` - Jump / Select / Confirm
- `Circle (O)` - Interact / Cancel
- `Square` - Ability 1
- `Triangle` - Ability 2
- `L1/R1` - Ability 3/4
- `L2/R2` - Aim / Secondary Action (with trigger resistance!)
- `Left Stick` - Movement
- `Right Stick` - Camera Control
- `Options` - Pause Menu
- `Share` - Inventory

---

## ?? Configuration & Customization

All systems are fully configurable in Blueprint:

1. Create your own Menu widgets inheriting from `UBaseMenuWidget`
2. Register custom input actions in `UInputManager`
3. Create custom HUD layouts extending `URuntimeCombatHUD`
4. Customize all social system limits in the respective systems

---

## ?? Additional Resources

- **Input System:** InputManager.h/cpp
- **UI System:** UIManager.h
- **HUD System:** RuntimeCombatHUD.h
- **Social Systems:** MMORPGSystems.h
- **Settings:** UIManager.h (USettingsManager class)

---

**This comprehensive system provides everything needed for a modern 3D MMORPG with full multi-platform controller support!**
