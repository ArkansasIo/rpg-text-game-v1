#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/VerticalBox.h"
#include "Components/HorizontalBox.h"
#include "Styling/SlateColor.h"
#include "EldenRingMenuWidget.generated.h"

/**
 * Elden Ring-Styled Menu Widget
 * Features iconic Elden Ring aesthetic with gold and dark colors
 */
UCLASS()
class RPGPROJECT_API UEldenRingMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	// Elden Ring color palette
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elden Ring Theme")
	FLinearColor PrimaryGoldColor = FLinearColor(0.835f, 0.686f, 0.216f, 1.0f); // #D4AF37

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elden Ring Theme")
	FLinearColor DarkBackgroundColor = FLinearColor(0.04f, 0.04f, 0.04f, 1.0f); // #0a0a0a

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elden Ring Theme")
	FLinearColor AccentGoldColor = FLinearColor(1.0f, 0.843f, 0.0f, 1.0f); // #FFD700

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elden Ring Theme")
	FLinearColor TextColor = FLinearColor(0.910f, 0.836f, 0.718f, 1.0f); // #E8D5B7

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elden Ring Theme")
	FLinearColor DarkGoldBorder = FLinearColor(0.318f, 0.255f, 0.114f, 1.0f); // #514124

	// UI Components
	UPROPERTY(meta = (BindWidgetOptional))
	UCanvasPanel* MainCanvas;

	UPROPERTY(meta = (BindWidgetOptional))
	UImage* BackgroundImage;

	UPROPERTY(meta = (BindWidgetOptional))
	UImage* LogoImage;

	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* TitleText;

	UPROPERTY(meta = (BindWidgetOptional))
	UVerticalBox* MenuButtonContainer;

	// Delegates
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNewGameSelected);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnContinueSelected);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLoadGameSelected);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSettingsSelected);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnExitGameSelected);

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnNewGameSelected OnNewGameSelected;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnContinueSelected OnContinueSelected;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnLoadGameSelected OnLoadGameSelected;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnSettingsSelected OnSettingsSelected;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnExitGameSelected OnExitGameSelected;

	// Menu Functions
	UFUNCTION(BlueprintCallable, Category = "Menu")
	void CreateMainMenu();

	UFUNCTION(BlueprintCallable, Category = "Menu")
	void CreateCharacterCreationMenu();

	UFUNCTION(BlueprintCallable, Category = "Menu")
	void CreateSettingsMenu();

	UFUNCTION(BlueprintCallable, Category = "Menu")
	void CreateStyledButton(const FString& ButtonText, FSimpleDelegate OnClickedCallback);

private:
	// Helper functions
	void SetupBackgroundGradient();
	void SetupThemeColors();
	void ApplyEldenRingTheme();

	// Button callbacks
	void OnNewGameClicked();
	void OnContinueClicked();
	void OnLoadGameClicked();
	void OnSettingsClicked();
	void OnExitClicked();

	// Store button references for styling
	UPROPERTY()
	TArray<UButton*> MenuButtons;
};
