#include "EldenRingHUD.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "Styling/SlateBrush.h"
#include "Styling/SlateColor.h"

void UEldenRingHUD::NativeConstruct()
{
	Super::NativeConstruct();
	SetupHUDLayout();
	ApplyEldenRingTheme();
	UpdateAllBars();
}

void UEldenRingHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	UpdateAllBars();
}

void UEldenRingHUD::SetupHUDLayout()
{
	if (!HUDCanvas)
	{
		HUDCanvas = NewObject<UCanvasPanel>(this);
	}

	// Setup progress bars if they exist
	if (HealthBar)
	{
		HealthBar->SetPercent(CurrentHealth / MaxHealth);
		HealthBar->SetFillColorAndOpacity(FSlateColor(HealthBarColor));
	}

	if (ManaBar)
	{
		ManaBar->SetPercent(CurrentMana / MaxMana);
		ManaBar->SetFillColorAndOpacity(FSlateColor(ManaBarColor));
	}

	if (StaminaBar)
	{
		StaminaBar->SetPercent(CurrentStamina / MaxStamina);
		StaminaBar->SetFillColorAndOpacity(FSlateColor(StaminaBarColor));
	}

	// Setup text blocks
	if (HealthText)
	{
		HealthText->SetColorAndOpacity(FSlateColor(HealthBarColor));
		HealthText->SetText(FText::FromString(FString::Printf(TEXT("HP: %.0f / %.0f"), CurrentHealth, MaxHealth)));
	}

	if (ManaText)
	{
		ManaText->SetColorAndOpacity(FSlateColor(ManaBarColor));
		ManaText->SetText(FText::FromString(FString::Printf(TEXT("FP: %.0f / %.0f"), CurrentMana, MaxMana)));
	}

	if (StaminaText)
	{
		StaminaText->SetColorAndOpacity(FSlateColor(StaminaBarColor));
		StaminaText->SetText(FText::FromString(FString::Printf(TEXT("Stamina: %.0f / %.0f"), CurrentStamina, MaxStamina)));
	}

	if (LevelText)
	{
		LevelText->SetColorAndOpacity(FSlateColor(BorderColor));
		LevelText->SetText(FText::FromString(FString::Printf(TEXT("Level: %d"), PlayerLevel)));
	}

	if (ExperienceText)
	{
		ExperienceText->SetColorAndOpacity(FSlateColor(BorderColor));
		float ExpPercent = (float)CurrentExperience / (float)NextLevelExperience * 100.0f;
		ExperienceText->SetText(FText::FromString(FString::Printf(TEXT("EXP: %d / %d (%.1f%%)"), 
			CurrentExperience, NextLevelExperience, ExpPercent)));
	}
}

void UEldenRingHUD::ApplyEldenRingTheme()
{
	// Apply corner decorations with gold borders
	if (CornerDecoration)
	{
		CornerDecoration->SetColorAndOpacity(FSlateColor(BorderColor));
	}

	// Set all progress bars to have dark backgrounds with gold borders
	if (HealthBar)
	{
		HealthBar->SetBackColor(FSlateColor(BarBackgroundColor));
		HealthBar->SetBarFillStyle(EProgressBarFillStyle::LeftToRight);
	}

	if (ManaBar)
	{
		ManaBar->SetBackColor(FSlateColor(BarBackgroundColor));
		ManaBar->SetBarFillStyle(EProgressBarFillStyle::LeftToRight);
	}

	if (StaminaBar)
	{
		StaminaBar->SetBackColor(FSlateColor(BarBackgroundColor));
		StaminaBar->SetBarFillStyle(EProgressBarFillStyle::LeftToRight);
	}
}

void UEldenRingHUD::UpdateHealthBar(float NewHealth, float NewMaxHealth)
{
	CurrentHealth = FMath::Max(0.0f, NewHealth);
	MaxHealth = NewMaxHealth;

	if (HealthBar)
	{
		HealthBar->SetPercent(CurrentHealth / MaxHealth);
	}

	if (HealthText)
	{
		HealthText->SetText(FText::FromString(FString::Printf(TEXT("HP: %.0f / %.0f"), CurrentHealth, MaxHealth)));
	}
}

void UEldenRingHUD::UpdateManaBar(float NewMana, float NewMaxMana)
{
	CurrentMana = FMath::Max(0.0f, NewMana);
	MaxMana = NewMaxMana;

	if (ManaBar)
	{
		ManaBar->SetPercent(CurrentMana / MaxMana);
	}

	if (ManaText)
	{
		ManaText->SetText(FText::FromString(FString::Printf(TEXT("FP: %.0f / %.0f"), CurrentMana, MaxMana)));
	}
}

void UEldenRingHUD::UpdateStaminaBar(float NewStamina, float NewMaxStamina)
{
	CurrentStamina = FMath::Max(0.0f, NewStamina);
	MaxStamina = NewMaxStamina;

	if (StaminaBar)
	{
		StaminaBar->SetPercent(CurrentStamina / MaxStamina);
	}

	if (StaminaText)
	{
		StaminaText->SetText(FText::FromString(FString::Printf(TEXT("Stamina: %.0f / %.0f"), CurrentStamina, MaxStamina)));
	}
}

void UEldenRingHUD::UpdateLevel(int32 NewLevel)
{
	PlayerLevel = NewLevel;

	if (LevelText)
	{
		LevelText->SetText(FText::FromString(FString::Printf(TEXT("Level: %d"), PlayerLevel)));
	}
}

void UEldenRingHUD::UpdateExperience(int32 NewExp, int32 NextLevelExp)
{
	CurrentExperience = NewExp;
	NextLevelExperience = NextLevelExp;

	if (ExperienceText)
	{
		float ExpPercent = (float)CurrentExperience / (float)NextLevelExperience * 100.0f;
		ExperienceText->SetText(FText::FromString(FString::Printf(TEXT("EXP: %d / %d (%.1f%%)"), 
			CurrentExperience, NextLevelExperience, ExpPercent)));
	}
}

void UEldenRingHUD::UpdateAllBars()
{
	if (HealthBar)
	{
		HealthBar->SetPercent(CurrentHealth / MaxHealth);
	}

	if (ManaBar)
	{
		ManaBar->SetPercent(CurrentMana / MaxMana);
	}

	if (StaminaBar)
	{
		StaminaBar->SetPercent(CurrentStamina / MaxStamina);
	}
}
