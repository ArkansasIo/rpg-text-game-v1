#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "EldenRingHUD.generated.h"

/**
 * Elden Ring-Styled In-Game HUD
 * Displays health, mana, stamina with iconic Elden Ring UI elements
 */
UCLASS()
class RPGPROJECT_API UEldenRingHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	// Elden Ring Theme Colors
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elden Ring Theme")
	FLinearColor HealthBarColor = FLinearColor(0.8f, 0.2f, 0.2f, 1.0f); // Red

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elden Ring Theme")
	FLinearColor ManaBarColor = FLinearColor(0.2f, 0.4f, 0.8f, 1.0f); // Blue

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elden Ring Theme")
	FLinearColor StaminaBarColor = FLinearColor(0.8f, 0.7f, 0.2f, 1.0f); // Gold

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elden Ring Theme")
	FLinearColor BarBackgroundColor = FLinearColor(0.1f, 0.1f, 0.1f, 0.8f); // Dark

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elden Ring Theme")
	FLinearColor BorderColor = FLinearColor(0.835f, 0.686f, 0.216f, 1.0f); // Gold

	// UI Components
	UPROPERTY(meta = (BindWidgetOptional))
	UCanvasPanel* HUDCanvas;

	UPROPERTY(meta = (BindWidgetOptional))
	UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidgetOptional))
	UProgressBar* ManaBar;

	UPROPERTY(meta = (BindWidgetOptional))
	UProgressBar* StaminaBar;

	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* HealthText;

	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* ManaText;

	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* StaminaText;

	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* LevelText;

	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* ExperienceText;

	UPROPERTY(meta = (BindWidgetOptional))
	UImage* CornerDecoration;

	// Data properties
	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	float CurrentHealth = 100.0f;

	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	float MaxHealth = 100.0f;

	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	float CurrentMana = 50.0f;

	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	float MaxMana = 50.0f;

	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	float CurrentStamina = 100.0f;

	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	float MaxStamina = 100.0f;

	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	int32 PlayerLevel = 1;

	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	int32 CurrentExperience = 0;

	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	int32 NextLevelExperience = 1000;

	// Update functions
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void UpdateHealthBar(float NewHealth, float NewMaxHealth);

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void UpdateManaBar(float NewMana, float NewMaxMana);

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void UpdateStaminaBar(float NewStamina, float NewMaxStamina);

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void UpdateLevel(int32 NewLevel);

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void UpdateExperience(int32 NewExp, int32 NextLevelExp);

private:
	void SetupHUDLayout();
	void ApplyEldenRingTheme();
	void UpdateAllBars();
};
