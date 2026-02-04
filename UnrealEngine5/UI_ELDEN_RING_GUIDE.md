# Elden Ring-Styled GUI Implementation Guide

## Overview

This guide covers the **Elden Ring-Styled UI system** for Unreal Engine 5. The system includes two main components:

1. **UEldenRingMenuWidget** - Main menu and navigation UI
2. **UEldenRingHUD** - In-game HUD with health, mana, and stamina bars

## Color Palette

All Elden Ring styling uses the authentic color scheme:

| Element | Color Code | RGB | Usage |
|---------|-----------|-----|-------|
| Primary Gold | #D4AF37 | (213, 175, 55) | Borders, accents |
| Dark Background | #0a0a0a | (10, 10, 10) | Main background |
| Accent Gold | #FFD700 | (255, 215, 0) | Highlights, titles |
| Text Color | #E8D5B7 | (232, 213, 183) | Main text |
| Dark Gold | #514124 | (81, 65, 36) | Button backgrounds |
| Health Red | #CC3333 | (204, 51, 51) | Health bars |
| Mana Blue | #3366CC | (51, 102, 204) | Mana bars |
| Stamina Gold | #CCCC33 | (204, 204, 51) | Stamina bars |

## UEldenRingMenuWidget

### Features

- Authentic Elden Ring main menu styling
- Support for multiple menu screens (main, character creation, settings)
- Easy button creation with consistent styling
- Delegate-based callbacks for menu actions

### Usage Example in C++

```cpp
// In your game mode or manager class
void AYourGameMode::SetupMainMenu()
{
    if (UEldenRingMenuWidget* MenuWidget = CreateWidget<UEldenRingMenuWidget>(
        GetWorld(), 
        APlayerController::GetLocalPlayer(),
        UEldenRingMenuWidget::StaticClass()))
    {
        MenuWidget->AddToViewport(100);
        
        // Bind menu events
        MenuWidget->OnNewGameSelected.AddDynamic(this, &AYourGameMode::HandleNewGame);
        MenuWidget->OnContinueSelected.AddDynamic(this, &AYourGameMode::HandleContinue);
        MenuWidget->OnLoadGameSelected.AddDynamic(this, &AYourGameMode::HandleLoadGame);
        MenuWidget->OnSettingsSelected.AddDynamic(this, &AYourGameMode::HandleSettings);
        MenuWidget->OnExitGameSelected.AddDynamic(this, &AYourGameMode::HandleExit);
        
        MenuWidget->CreateMainMenu();
    }
}
```

### Available Functions

```cpp
// Create different menu screens
void CreateMainMenu();
void CreateCharacterCreationMenu();
void CreateSettingsMenu();

// Customize button creation
void CreateStyledButton(const FString& ButtonText, FSimpleDelegate OnClickedCallback);
```

### Color Customization

All colors can be modified in Blueprint or C++:

```cpp
MenuWidget->PrimaryGoldColor = FLinearColor(0.835f, 0.686f, 0.216f, 1.0f);
MenuWidget->DarkBackgroundColor = FLinearColor(0.04f, 0.04f, 0.04f, 1.0f);
MenuWidget->AccentGoldColor = FLinearColor(1.0f, 0.843f, 0.0f, 1.0f);
```

## UEldenRingHUD

### Features

- Real-time health, mana, and stamina bars
- Level and experience display
- Elden Ring color-coded stat bars
- Automatic updates and tick-based refresh

### Usage Example in C++

```cpp
// In your HUD class or game mode
void AYourHUD::SetupInGameHUD()
{
    if (UEldenRingHUD* HUD = CreateWidget<UEldenRingHUD>(
        GetOwningPlayerController(),
        UEldenRingHUD::StaticClass()))
    {
        HUD->AddToViewport(0);
        HUD->SetupHUDLayout();
    }
}

// Update player stats
void AYourCharacter::OnHealthChanged(float NewHealth, float MaxHealth)
{
    if (UEldenRingHUD* HUD = GetHUDWidget())
    {
        HUD->UpdateHealthBar(NewHealth, MaxHealth);
    }
}

void AYourCharacter::OnManaChanged(float NewMana, float MaxMana)
{
    if (UEldenRingHUD* HUD = GetHUDWidget())
    {
        HUD->UpdateManaBar(NewMana, MaxMana);
    }
}

void AYourCharacter::OnLevelUp(int32 NewLevel)
{
    if (UEldenRingHUD* HUD = GetHUDWidget())
    {
        HUD->UpdateLevel(NewLevel);
    }
}
```

### Available Update Functions

```cpp
// Update individual bars
void UpdateHealthBar(float NewHealth, float NewMaxHealth);
void UpdateManaBar(float NewMana, float NewMaxMana);
void UpdateStaminaBar(float NewStamina, float NewMaxStamina);
void UpdateLevel(int32 NewLevel);
void UpdateExperience(int32 NewExp, int32 NextLevelExp);
```

### Stat Bars Explanation

| Bar | Default Color | Represents |
|-----|---------------|------------|
| Health | Red (#CC3333) | Current HP |
| Mana | Blue (#3366CC) | Focus Points (FP) |
| Stamina | Gold (#CCCC33) | Stamina pool |

## Blueprint Integration

Both widgets are **Blueprint-compatible** and can be used in UMG Designer:

### In UMG Designer:

1. Create a new Widget Blueprint
2. Set "Parent Class" to **UEldenRingMenuWidget** or **UEldenRingHUD**
3. Design your layout in the Designer tab
4. Bind widgets to the provided UI components (HealthBar, ManaBar, etc.)
5. Use "Construct" event to customize colors

### Example Blueprint Setup:

```
Canvas Panel
??? Background Image (BackgroundImage)
??? Logo Image (LogoImage)
??? Title Text (TitleText - "ELDEN RING")
??? Vertical Box (MenuButtonContainer)
    ??? New Game Button
    ??? Continue Button
    ??? Load Game Button
    ??? Settings Button
    ??? Exit Button
```

## Customization Guide

### Changing Colors

To create your own color variant:

```cpp
// In your custom widget class
void UYourCustomMenu::SetupCustomTheme()
{
    PrimaryGoldColor = FLinearColor(0.8f, 0.6f, 0.2f, 1.0f);    // Custom gold
    DarkBackgroundColor = FLinearColor(0.02f, 0.02f, 0.02f, 1.0f); // Darker
    AccentGoldColor = FLinearColor(0.95f, 0.8f, 0.0f, 1.0f);    // Brighter
}
```

### Adding Animation

To add fade-in/fade-out animations:

```cpp
void UEldenRingMenuWidget::FadeInMenu()
{
    if (UCanvasPanelSlot* CanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(MenuButtonContainer))
    {
        // Create animation
        TweenValue(0.0f, 1.0f, 1.0f, /* OnUpdate */);
    }
}
```

### Custom Button Styling

Extend the class to add custom button effects:

```cpp
void UEldenRingMenuWidget::CreateHoverEffect(UButton* Button)
{
    Button->OnHovered.AddDynamic(this, &UEldenRingMenuWidget::OnButtonHovered);
    Button->OnUnhovered.AddDynamic(this, &UEldenRingMenuWidget::OnButtonUnhovered);
}

void UEldenRingMenuWidget::OnButtonHovered()
{
    // Scale up, change color, play sound
}
```

## File Structure

```
UnrealEngine5/Source/RPGProject/UI/
??? EldenRingMenuWidget.h       // Main menu widget header
??? EldenRingMenuWidget.cpp      // Main menu widget implementation
??? EldenRingHUD.h              // In-game HUD header
??? EldenRingHUD.cpp            // In-game HUD implementation
??? UIManager.h                 // Existing UI manager
??? RuntimeCombatHUD.h          // Existing combat HUD
```

## Performance Considerations

- **HUD Updates**: The HUD updates every frame via `NativeTick()` for smooth bar animations
- **Menu Performance**: Menu widgets use deferred updates and only refresh when data changes
- **Memory**: Color values are stored as `FLinearColor` (16 bytes each) for optimal memory usage

## Troubleshooting

### Colors not appearing correctly?

Check that your project has proper texture/material support for UI:
- Enable "UMG Editor" plugin in plugins
- Ensure `FLinearColor` values are in 0-1 range (not 0-255)

### Widgets not showing?

Ensure:
- Widget is added to viewport with `AddToViewport()`
- Parent canvas is set up in the widget hierarchy
- Canvas panel slot anchors are properly configured

### Animation stuttering?

Disable unnecessary ticking or use `SetTickableWhenPaused(false)` to prevent unnecessary updates during menus.

## Integration with Existing Systems

To integrate with your existing RPG systems:

```cpp
// In your Character class
void AYourCharacter::BeginPlay()
{
    Super::BeginPlay();
    
    if (APlayerController* PC = Cast<APlayerController>(Controller))
    {
        if (UEldenRingHUD* HUD = CreateWidget<UEldenRingHUD>(PC))
        {
            HUD->AddToViewport();
            
            // Connect to your stats system
            Stats->OnHealthChanged.AddDynamic(HUD, &UEldenRingHUD::UpdateHealthBar);
            Stats->OnManaChanged.AddDynamic(HUD, &UEldenRingHUD::UpdateManaBar);
        }
    }
}
```

## Next Steps

1. Create Widget Blueprints based on these C++ classes
2. Customize the layout and positioning in UMG Designer
3. Add animations and transitions
4. Integrate with your game's stat systems
5. Add sound effects for menu interactions

---

For questions or customization needs, refer to the Unreal Engine 5 UMG documentation or the project's UI system files.
