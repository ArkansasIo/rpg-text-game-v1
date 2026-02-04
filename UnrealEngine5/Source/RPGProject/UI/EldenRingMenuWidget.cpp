#include "EldenRingMenuWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/VerticalBox.h"
#include "Components/HorizontalBox.h"
#include "Styling/SlateBrush.h"
#include "Styling/SlateColor.h"
#include "Engine/Font.h"

void UEldenRingMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetupThemeColors();
	ApplyEldenRingTheme();
}

void UEldenRingMenuWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UEldenRingMenuWidget::SetupThemeColors()
{
	// Elden Ring color palette setup
	PrimaryGoldColor = FLinearColor(0.835f, 0.686f, 0.216f, 1.0f);     // #D4AF37
	DarkBackgroundColor = FLinearColor(0.04f, 0.04f, 0.04f, 1.0f);    // #0a0a0a
	AccentGoldColor = FLinearColor(1.0f, 0.843f, 0.0f, 1.0f);         // #FFD700
	TextColor = FLinearColor(0.910f, 0.836f, 0.718f, 1.0f);           // #E8D5B7
	DarkGoldBorder = FLinearColor(0.318f, 0.255f, 0.114f, 1.0f);      // #514124
}

void UEldenRingMenuWidget::ApplyEldenRingTheme()
{
	if (!MainCanvas)
	{
		MainCanvas = NewObject<UCanvasPanel>(this);
		AddToViewport();
	}

	// Set background to dark
	if (BackgroundImage)
	{
		FLinearColor BgColor = DarkBackgroundColor;
		BackgroundImage->SetColorAndOpacity(BgColor);
	}

	// Setup title with gold color
	if (TitleText)
	{
		TitleText->SetColorAndOpacity(FSlateColor(AccentGoldColor));
		TitleText->SetText(FText::FromString(TEXT("ELDEN RING")));
		
		// Set gothic/elegant font properties
		if (TitleText->GetFont().FontObject)
		{
			TitleText->Font.OutlineSettings.OutlineSize = 2;
		}
	}

	CreateMainMenu();
}

void UEldenRingMenuWidget::CreateMainMenu()
{
	if (!MenuButtonContainer)
	{
		MenuButtonContainer = NewObject<UVerticalBox>(this);
		MainCanvas->AddChild(MenuButtonContainer);
	}

	MenuButtonContainer->ClearChildren();

	// Create menu buttons
	CreateStyledButton(TEXT("New Game"), FSimpleDelegate::CreateUObject(this, &UEldenRingMenuWidget::OnNewGameClicked));
	CreateStyledButton(TEXT("Continue"), FSimpleDelegate::CreateUObject(this, &UEldenRingMenuWidget::OnContinueClicked));
	CreateStyledButton(TEXT("Load Game"), FSimpleDelegate::CreateUObject(this, &UEldenRingMenuWidget::OnLoadGameClicked));
	CreateStyledButton(TEXT("Settings"), FSimpleDelegate::CreateUObject(this, &UEldenRingMenuWidget::OnSettingsClicked));
	CreateStyledButton(TEXT("Exit"), FSimpleDelegate::CreateUObject(this, &UEldenRingMenuWidget::OnExitClicked));
}

void UEldenRingMenuWidget::CreateCharacterCreationMenu()
{
	if (!MenuButtonContainer)
	{
		return;
	}

	MenuButtonContainer->ClearChildren();

	CreateStyledButton(TEXT("Select Class"), FSimpleDelegate());
	CreateStyledButton(TEXT("Customize Appearance"), FSimpleDelegate());
	CreateStyledButton(TEXT("Confirm"), FSimpleDelegate());
	CreateStyledButton(TEXT("Back"), FSimpleDelegate());
}

void UEldenRingMenuWidget::CreateSettingsMenu()
{
	if (!MenuButtonContainer)
	{
		return;
	}

	MenuButtonContainer->ClearChildren();

	CreateStyledButton(TEXT("Graphics"), FSimpleDelegate());
	CreateStyledButton(TEXT("Audio"), FSimpleDelegate());
	CreateStyledButton(TEXT("Controls"), FSimpleDelegate());
	CreateStyledButton(TEXT("Difficulty"), FSimpleDelegate());
	CreateStyledButton(TEXT("Back"), FSimpleDelegate());
}

void UEldenRingMenuWidget::CreateStyledButton(const FString& ButtonText, FSimpleDelegate OnClickedCallback)
{
	if (!MenuButtonContainer)
	{
		return;
	}

	// Create button
	UButton* NewButton = NewObject<UButton>(this);
	
	// Style button with Elden Ring colors
	FLinearColor ButtonColor = DarkGoldBorder;
	NewButton->SetColorAndOpacity(FSlateColor(ButtonColor));
	
	// Create text for button
	UTextBlock* ButtonTextBlock = NewObject<UTextBlock>(this);
	ButtonTextBlock->SetText(FText::FromString(ButtonText));
	ButtonTextBlock->SetColorAndOpacity(FSlateColor(PrimaryGoldColor));
	ButtonTextBlock->SetJustifyText(ETextJustify::Center);
	
	// Add text to button
	NewButton->AddChild(ButtonTextBlock);
	
	// Add button to container
	MenuButtonContainer->AddChild(NewButton);
	
	// Bind click event if callback provided
	if (OnClickedCallback.IsBound())
	{
		NewButton->OnClicked.Add(OnClickedCallback);
	}
	
	// Store reference
	MenuButtons.Add(NewButton);
}

void UEldenRingMenuWidget::SetupBackgroundGradient()
{
	if (!BackgroundImage)
	{
		return;
	}

	// Create a dark gradient background brush
	FSlateImageBrush BackgroundBrush(
		FString(TEXT("/Engine/EditorResources/Black")),
		FVector2D(256, 256),
		DarkBackgroundColor,
		ESlateBrushDrawType::Image
	);

	BackgroundImage->SetBrush(BackgroundBrush);
	BackgroundImage->SetColorAndOpacity(DarkBackgroundColor);
}

void UEldenRingMenuWidget::OnNewGameClicked()
{
	OnNewGameSelected.Broadcast();
}

void UEldenRingMenuWidget::OnContinueClicked()
{
	OnContinueSelected.Broadcast();
}

void UEldenRingMenuWidget::OnLoadGameClicked()
{
	OnLoadGameSelected.Broadcast();
}

void UEldenRingMenuWidget::OnSettingsClicked()
{
	OnSettingsSelected.Broadcast();
}

void UEldenRingMenuWidget::OnExitClicked()
{
	OnExitGameSelected.Broadcast();
}
