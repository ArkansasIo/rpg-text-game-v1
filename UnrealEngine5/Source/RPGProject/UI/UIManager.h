#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/ScrollBox.h"
#include "Containers/List.h"
#include "UIManager.generated.h"

class UGamepadNavigationHandler;

UENUM(BlueprintType)
enum class EUIScreenType : uint8
{
	MainMenu UMETA(DisplayName = "Main Menu"),
	CharacterCreation UMETA(DisplayName = "Character Creation"),
	PauseMenu UMETA(DisplayName = "Pause Menu"),
	SettingsMenu UMETA(DisplayName = "Settings Menu"),
	InventoryUI UMETA(DisplayName = "Inventory"),
	CharacterUI UMETA(DisplayName = "Character Sheet"),
	QuestUI UMETA(DisplayName = "Quest Log"),
	MapUI UMETA(DisplayName = "Map"),
	GuildUI UMETA(DisplayName = "Guild"),
	SocialUI UMETA(DisplayName = "Social"),
	CombatUI UMETA(DisplayName = "Combat HUD"),
	DialogueUI UMETA(DisplayName = "Dialogue"),
	ShopUI UMETA(DisplayName = "Shop"),
	CraftingUI UMETA(DisplayName = "Crafting")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_One(FOnUIScreenChanged, EUIScreenType, NewScreen);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUIMenuClosed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMenuOptionSelected, int32, OptionIndex, FString, OptionName);

/**
 * Base Menu Widget Class
 */
UCLASS(BlueprintType)
class RPGPROJECT_API UBaseMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Menu")
	void OnMenuOpen();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Menu")
	void OnMenuClose();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Menu")
	void OnMenuUpdate(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Menu")
	virtual void ShowMenu();

	UFUNCTION(BlueprintCallable, Category = "Menu")
	virtual void HideMenu();

	UFUNCTION(BlueprintCallable, Category = "Menu")
	virtual void NavigateUp();

	UFUNCTION(BlueprintCallable, Category = "Menu")
	virtual void NavigateDown();

	UFUNCTION(BlueprintCallable, Category = "Menu")
	virtual void SelectOption();

	UFUNCTION(BlueprintCallable, Category = "Menu")
	virtual void CancelMenu();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu")
	EUIScreenType ScreenType;

	UPROPERTY(BlueprintAssignable, Category = "Menu")
	FOnMenuOptionSelected OnOptionSelected;

	UPROPERTY(BlueprintAssignable, Category = "Menu")
	FOnUIMenuClosed OnMenuClosed;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Menu")
	int32 CurrentSelectedIndex = 0;

	UPROPERTY(BlueprintReadOnly, Category = "Menu")
	bool bIsVisible = false;
};

/**
 * Main UI Manager - Controls all menus and UI screens
 */
UCLASS(Blueprintable, BlueprintType)
class RPGPROJECT_API UUIManager : public UGameInstance
{
	GENERATED_BODY()

public:
	UUIManager();

	// Initialize UI Manager
	UFUNCTION(BlueprintCallable, Category = "UI")
	void InitializeUIManager();

	// Show specific UI screen
	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowScreen(EUIScreenType ScreenType);

	// Hide specific UI screen
	UFUNCTION(BlueprintCallable, Category = "UI")
	void HideScreen(EUIScreenType ScreenType);

	// Toggle UI screen
	UFUNCTION(BlueprintCallable, Category = "UI")
	void ToggleScreen(EUIScreenType ScreenType);

	// Hide all UI
	UFUNCTION(BlueprintCallable, Category = "UI")
	void HideAllScreens();

	// Get current active screen
	UFUNCTION(BlueprintPure, Category = "UI")
	EUIScreenType GetActiveScreen() const { return CurrentActiveScreen; }

	// Register UI widget
	UFUNCTION(BlueprintCallable, Category = "UI")
	void RegisterScreen(EUIScreenType ScreenType, UBaseMenuWidget* Widget);

	// Unregister UI widget
	UFUNCTION(BlueprintCallable, Category = "UI")
	void UnregisterScreen(EUIScreenType ScreenType);

	// Navigate menu
	UFUNCTION(BlueprintCallable, Category = "UI")
	void NavigateMenu(bool bUp);

	// Select menu option
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SelectMenuOption();

	// Cancel menu
	UFUNCTION(BlueprintCallable, Category = "UI")
	void CancelMenu();

	// Show notification
	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowNotification(const FString& Message, float Duration = 3.0f, FLinearColor Color = FLinearColor::White);

	// Show dialog box
	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowDialog(const FString& Title, const FString& Message, const TArray<FString>& Options);

	// Delegates
	UPROPERTY(BlueprintAssignable, Category = "UI")
	FOnUIScreenChanged OnScreenChanged;

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FOnMenuOptionSelected OnMenuOptionSelected;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "UI")
	EUIScreenType CurrentActiveScreen = EUIScreenType::MainMenu;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	TMap<EUIScreenType, UBaseMenuWidget*> RegisteredScreens;

	virtual void Init() override;
	virtual void Shutdown() override;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	float UIAnimationSpeed = 0.2f;
};

/**
 * Settings Manager - Manages game settings and preferences
 */
UCLASS(Blueprintable, BlueprintType)
class RPGPROJECT_API USettingsManager : public UObject
{
	GENERATED_BODY()

public:
	// Graphics Settings
	UFUNCTION(BlueprintCallable, Category = "Settings")
	void SetGraphicsQuality(int32 Quality); // 0=Low, 1=Medium, 2=High, 3=Ultra

	UFUNCTION(BlueprintCallable, Category = "Settings")
	int32 GetGraphicsQuality() const { return GraphicsQuality; }

	UFUNCTION(BlueprintCallable, Category = "Settings")
	void SetResolution(FIntPoint NewResolution);

	UFUNCTION(BlueprintPure, Category = "Settings")
	FIntPoint GetResolution() const { return ScreenResolution; }

	UFUNCTION(BlueprintCallable, Category = "Settings")
	void SetFullscreen(bool bFullscreen);

	UFUNCTION(BlueprintPure, Category = "Settings")
	bool IsFullscreen() const { return bFullscreenMode; }

	UFUNCTION(BlueprintCallable, Category = "Settings")
	void SetVSync(bool bEnabled);

	UFUNCTION(BlueprintPure, Category = "Settings")
	bool IsVSyncEnabled() const { return bVSyncEnabled; }

	// Audio Settings
	UFUNCTION(BlueprintCallable, Category = "Settings")
	void SetMasterVolume(float Volume); // 0.0 - 1.0

	UFUNCTION(BlueprintPure, Category = "Settings")
	float GetMasterVolume() const { return MasterVolume; }

	UFUNCTION(BlueprintCallable, Category = "Settings")
	void SetMusicVolume(float Volume);

	UFUNCTION(BlueprintPure, Category = "Settings")
	float GetMusicVolume() const { return MusicVolume; }

	UFUNCTION(BlueprintCallable, Category = "Settings")
	void SetSFXVolume(float Volume);

	UFUNCTION(BlueprintPure, Category = "Settings")
	float GetSFXVolume() const { return SFXVolume; }

	UFUNCTION(BlueprintCallable, Category = "Settings")
	void SetVoiceVolume(float Volume);

	UFUNCTION(BlueprintPure, Category = "Settings")
	float GetVoiceVolume() const { return VoiceVolume; }

	// Game Settings
	UFUNCTION(BlueprintCallable, Category = "Settings")
	void SetDifficulty(int32 Difficulty); // 0=Easy, 1=Normal, 2=Hard, 3=Legendary

	UFUNCTION(BlueprintPure, Category = "Settings")
	int32 GetDifficulty() const { return GameDifficulty; }

	UFUNCTION(BlueprintCallable, Category = "Settings")
	void SetMouseSensitivity(float Sensitivity);

	UFUNCTION(BlueprintPure, Category = "Settings")
	float GetMouseSensitivity() const { return MouseSensitivity; }

	UFUNCTION(BlueprintCallable, Category = "Settings")
	void SetGamepadSensitivity(float Sensitivity);

	UFUNCTION(BlueprintPure, Category = "Settings")
	float GetGamepadSensitivity() const { return GamepadSensitivity; }

	UFUNCTION(BlueprintCallable, Category = "Settings")
	void SetCameraFollowDistance(float Distance);

	UFUNCTION(BlueprintPure, Category = "Settings")
	float GetCameraFollowDistance() const { return CameraFollowDistance; }

	UFUNCTION(BlueprintCallable, Category = "Settings")
	void SetInvertMouseY(bool bInvert);

	UFUNCTION(BlueprintPure, Category = "Settings")
	bool IsMouseYInverted() const { return bInvertMouseY; }

	UFUNCTION(BlueprintCallable, Category = "Settings")
	void SetInvertGamepadY(bool bInvert);

	UFUNCTION(BlueprintPure, Category = "Settings")
	bool IsGamepadYInverted() const { return bInvertGamepadY; }

	// Accessibility Settings
	UFUNCTION(BlueprintCallable, Category = "Settings|Accessibility")
	void SetColorBlindMode(int32 Mode); // 0=Off, 1=Deuteranopia, 2=Protanopia, 3=Tritanopia

	UFUNCTION(BlueprintPure, Category = "Settings|Accessibility")
	int32 GetColorBlindMode() const { return ColorBlindMode; }

	UFUNCTION(BlueprintCallable, Category = "Settings|Accessibility")
	void SetUIScale(float Scale); // 0.5 - 2.0

	UFUNCTION(BlueprintPure, Category = "Settings|Accessibility")
	float GetUIScale() const { return UIScale; }

	UFUNCTION(BlueprintCallable, Category = "Settings|Accessibility")
	void SetSubtitlesEnabled(bool bEnabled);

	UFUNCTION(BlueprintPure, Category = "Settings|Accessibility")
	bool AreSubtitlesEnabled() const { return bSubtitlesEnabled; }

	// Save/Load Settings
	UFUNCTION(BlueprintCallable, Category = "Settings")
	void SaveSettings();

	UFUNCTION(BlueprintCallable, Category = "Settings")
	void LoadSettings();

	UFUNCTION(BlueprintCallable, Category = "Settings")
	void ResetToDefaults();

protected:
	// Graphics
	UPROPERTY(BlueprintReadWrite, Category = "Settings")
	int32 GraphicsQuality = 2; // High

	UPROPERTY(BlueprintReadWrite, Category = "Settings")
	FIntPoint ScreenResolution = FIntPoint(1920, 1080);

	UPROPERTY(BlueprintReadWrite, Category = "Settings")
	bool bFullscreenMode = true;

	UPROPERTY(BlueprintReadWrite, Category = "Settings")
	bool bVSyncEnabled = true;

	// Audio
	UPROPERTY(BlueprintReadWrite, Category = "Settings")
	float MasterVolume = 0.8f;

	UPROPERTY(BlueprintReadWrite, Category = "Settings")
	float MusicVolume = 0.6f;

	UPROPERTY(BlueprintReadWrite, Category = "Settings")
	float SFXVolume = 0.8f;

	UPROPERTY(BlueprintReadWrite, Category = "Settings")
	float VoiceVolume = 0.9f;

	// Game
	UPROPERTY(BlueprintReadWrite, Category = "Settings")
	int32 GameDifficulty = 1; // Normal

	UPROPERTY(BlueprintReadWrite, Category = "Settings")
	float MouseSensitivity = 1.0f;

	UPROPERTY(BlueprintReadWrite, Category = "Settings")
	float GamepadSensitivity = 1.0f;

	UPROPERTY(BlueprintReadWrite, Category = "Settings")
	float CameraFollowDistance = 300.0f;

	UPROPERTY(BlueprintReadWrite, Category = "Settings")
	bool bInvertMouseY = false;

	UPROPERTY(BlueprintReadWrite, Category = "Settings")
	bool bInvertGamepadY = false;

	// Accessibility
	UPROPERTY(BlueprintReadWrite, Category = "Settings|Accessibility")
	int32 ColorBlindMode = 0; // Off

	UPROPERTY(BlueprintReadWrite, Category = "Settings|Accessibility")
	float UIScale = 1.0f;

	UPROPERTY(BlueprintReadWrite, Category = "Settings|Accessibility")
	bool bSubtitlesEnabled = true;

private:
	void ApplyGraphicsSettings();
	void ApplyAudioSettings();
	void ApplyGameSettings();
	void ApplyAccessibilitySettings();
};
