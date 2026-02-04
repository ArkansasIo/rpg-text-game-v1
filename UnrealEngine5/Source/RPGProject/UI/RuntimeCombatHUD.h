#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/HorizontalBox.h"
#include "Components/VerticalBox.h"
#include "Components/UniformGridPanel.h"
#include "RuntimeCombatHUD.generated.h"

UENUM(BlueprintType)
enum class EHUDDisplayMode : uint8
{
	Combat UMETA(DisplayName = "Combat HUD"),
	Exploration UMETA(DisplayName = "Exploration HUD"),
	Dialog UMETA(DisplayName = "Dialog HUD"),
	Custom UMETA(DisplayName = "Custom HUD")
};

/**
 * Combat HUD Widget - Real-time combat information
 */
UCLASS(BlueprintType)
class RPGPROJECT_API URuntimeCombatHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	// Health/Mana management
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void UpdatePlayerHealth(int32 CurrentHealth, int32 MaxHealth);

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void UpdatePlayerMana(int32 CurrentMana, int32 MaxMana);

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void UpdatePlayerStamina(int32 CurrentStamina, int32 MaxStamina);

	// Experience and leveling
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void UpdateExperience(int32 CurrentXP, int32 RequiredXP);

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void UpdateLevel(int32 NewLevel);

	// Status effects
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void AddStatusEffect(const FString& EffectName, float Duration, UTexture2D* Icon);

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void RemoveStatusEffect(const FString& EffectName);

	// Abilities/Cooldowns
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void UpdateAbilityCooldown(int32 SlotIndex, float CooldownRemaining, float MaxCooldown);

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void SetAbilityReady(int32 SlotIndex, bool bReady);

	// Target information
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void SetTargetInfo(const FString& TargetName, int32 TargetHealth, int32 MaxHealth, int32 TargetLevel);

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void ClearTargetInfo();

	// Notifications
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void ShowDamageNumber(int32 Damage, FLinearColor Color = FLinearColor::Red, bool bIsCritical = false);

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void ShowHealingNumber(int32 Healing);

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void ShowCombatMessage(const FString& Message, FLinearColor Color = FLinearColor::Yellow);

	// Minimap
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void UpdateMinimapMarker(const FName& MarkerName, FVector2D Position, FLinearColor Color);

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void RemoveMinimapMarker(const FName& MarkerName);

	// HUD mode
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void SetHUDMode(EHUDDisplayMode Mode);

	UFUNCTION(BlueprintPure, Category = "HUD")
	EHUDDisplayMode GetHUDMode() const { return CurrentHUDMode; }

	// Visibility
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void ToggleHUDVisibility();

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void SetHUDVisible(bool bVisible);

protected:
	// Health bars
	UPROPERTY(BlueprintReadWrite, Category = "HUD|Health")
	UProgressBar* PlayerHealthBar;

	UPROPERTY(BlueprintReadWrite, Category = "HUD|Health")
	UProgressBar* PlayerManaBar;

	UPROPERTY(BlueprintReadWrite, Category = "HUD|Health")
	UProgressBar* PlayerStaminaBar;

	UPROPERTY(BlueprintReadWrite, Category = "HUD|Health")
	UProgressBar* TargetHealthBar;

	UPROPERTY(BlueprintReadWrite, Category = "HUD|Health")
	UProgressBar* ExperienceBar;

	// Text displays
	UPROPERTY(BlueprintReadWrite, Category = "HUD|Text")
	UTextBlock* HealthText;

	UPROPERTY(BlueprintReadWrite, Category = "HUD|Text")
	UTextBlock* ManaText;

	UPROPERTY(BlueprintReadWrite, Category = "HUD|Text")
	UTextBlock* LevelText;

	UPROPERTY(BlueprintReadWrite, Category = "HUD|Text")
	UTextBlock* TargetNameText;

	UPROPERTY(BlueprintReadWrite, Category = "HUD|Text")
	UTextBlock* CombatMessageText;

	// Status effects container
	UPROPERTY(BlueprintReadWrite, Category = "HUD|Effects")
	UHorizontalBox* StatusEffectsContainer;

	// Ability slots
	UPROPERTY(BlueprintReadWrite, Category = "HUD|Abilities")
	UUniformGridPanel* AbilitySlots;

	// Minimap
	UPROPERTY(BlueprintReadWrite, Category = "HUD|Minimap")
	UImage* MinimapImage;

	UPROPERTY(BlueprintReadWrite, Category = "HUD|Minimap")
	TMap<FName, FVector2D> MinimapMarkers;

	// State
	UPROPERTY(BlueprintReadOnly, Category = "HUD")
	EHUDDisplayMode CurrentHUDMode = EHUDDisplayMode::Combat;

	UPROPERTY(BlueprintReadOnly, Category = "HUD")
	bool bHUDVisible = true;

	// Animation
	void AnimateDamageNumber(int32 Damage, bool bIsCritical);
	void UpdateCombatMessageAnimation();

	FTimerHandle CombatMessageTimerHandle;
};

/**
 * World HUD Elements - 3D elements above characters
 */
UCLASS()
class RPGPROJECT_API AWorldHUDElement : public AActor
{
	GENERATED_BODY()

public:
	AWorldHUDElement();

	UFUNCTION(BlueprintCallable, Category = "WorldHUD")
	void ShowHealthBar();

	UFUNCTION(BlueprintCallable, Category = "WorldHUD")
	void HideHealthBar();

	UFUNCTION(BlueprintCallable, Category = "WorldHUD")
	void UpdateHealth(int32 CurrentHealth, int32 MaxHealth);

	UFUNCTION(BlueprintCallable, Category = "WorldHUD")
	void ShowFloatingNumber(int32 Damage, bool bHealing = false);

	UFUNCTION(BlueprintCallable, Category = "WorldHUD")
	void ShowIndicator(const FString& Text, FLinearColor Color);

	UFUNCTION(BlueprintCallable, Category = "WorldHUD")
	void SetNameplateVisible(bool bVisible);

protected:
	UPROPERTY(BlueprintReadWrite, Category = "WorldHUD")
	class UWidgetComponent* HealthBarWidget;

	UPROPERTY(BlueprintReadWrite, Category = "WorldHUD")
	class UWidgetComponent* FloatingNumberWidget;

	UPROPERTY(BlueprintReadWrite, Category = "WorldHUD")
	class UWidgetComponent* NameplateWidget;

	virtual void BeginPlay() override;
};
