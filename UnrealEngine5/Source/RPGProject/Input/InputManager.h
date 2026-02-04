#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Containers/Map.h"
#include "InputManager.generated.h"

// Input action binding delegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FInputActionDelegate, const FInputActionValue&, Value, float, DeltaTime);

/**
 * Comprehensive Input Management System
 * Supports: Keyboard, Mouse, Xbox Controller, PS5 Controller
 */
UENUM(BlueprintType)
enum class EInputDeviceType : uint8
{
	Keyboard UMETA(DisplayName = "Keyboard"),
	Mouse UMETA(DisplayName = "Mouse"),
	Gamepad_Xbox UMETA(DisplayName = "Xbox Controller"),
	Gamepad_PS5 UMETA(DisplayName = "PS5 Controller"),
	Gamepad_Generic UMETA(DisplayName = "Generic Gamepad")
};

USTRUCT(BlueprintType)
struct FInputKeyBinding
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	FKey PrimaryKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	FKey SecondaryKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	FKey ControllerKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	float AxisScale = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	bool bIsAxisInput = false;
};

USTRUCT(BlueprintType)
struct FInputActionBinding
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	FName ActionName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	FInputKeyBinding KeyBinding;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	bool bEnabled = true;
};

/**
 * Input Manager - Handles all input from multiple devices
 */
UCLASS(Blueprintable, BlueprintType)
class RPGPROJECT_API UInputManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UInputManager();

	// Initialize input system
	UFUNCTION(BlueprintCallable, Category = "Input")
	void InitializeInput(class APlayerController* InController);

	// Register input action
	UFUNCTION(BlueprintCallable, Category = "Input")
	void RegisterInputAction(FName ActionName, const FInputKeyBinding& KeyBinding);

	// Unregister input action
	UFUNCTION(BlueprintCallable, Category = "Input")
	void UnregisterInputAction(FName ActionName);

	// Get current input device type
	UFUNCTION(BlueprintPure, Category = "Input")
	EInputDeviceType GetCurrentInputDevice() const { return CurrentInputDevice; }

	// Check if specific key is pressed
	UFUNCTION(BlueprintPure, Category = "Input")
	bool IsKeyPressed(FKey Key) const;

	// Get axis value
	UFUNCTION(BlueprintPure, Category = "Input")
	float GetAxisValue(FName AxisName) const;

	// Get action input value
	UFUNCTION(BlueprintPure, Category = "Input")
	FInputActionValue GetActionValue(FName ActionName) const;

	// Enable/disable all input
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetInputEnabled(bool bEnabled);

	// Enable/disable specific action
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetActionEnabled(FName ActionName, bool bEnabled);

	// Rebind key
	UFUNCTION(BlueprintCallable, Category = "Input")
	void RebindKey(FName ActionName, FKey NewKey, bool bIsPrimary = true);

	// Get controller analog stick value
	UFUNCTION(BlueprintPure, Category = "Input")
	FVector2D GetGamepadAnalogStickValue(EGamepadAnalogStick::Type StickType) const;

	// Get controller trigger value
	UFUNCTION(BlueprintPure, Category = "Input")
	float GetGamepadTriggerValue(EGamepadTriggerAxis::Type TriggerAxis) const;

	// Vibrate controller (rumble)
	UFUNCTION(BlueprintCallable, Category = "Input")
	void PlayControllerVibration(float Intensity, float Duration, int32 ControllerIndex = 0);

	// Action delegates
	UPROPERTY(BlueprintAssignable, Category = "Input")
	FInputActionDelegate OnMoveForward;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FInputActionDelegate OnMoveSide;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FInputActionDelegate OnLookUp;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FInputActionDelegate OnLookRight;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FInputActionDelegate OnAction;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FInputActionDelegate OnInteract;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FInputActionDelegate OnOpenMenu;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FInputActionDelegate OnPause;

	// Input callbacks
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Input")
	APlayerController* OwnerController;

	UPROPERTY(BlueprintReadOnly, Category = "Input")
	EInputDeviceType CurrentInputDevice;

	UPROPERTY(BlueprintReadWrite, Category = "Input")
	TMap<FName, FInputActionBinding> RegisteredActions;

	UPROPERTY(BlueprintReadWrite, Category = "Input")
	bool bInputEnabled = true;

	// Track current input values
	FInputActionValue LastMoveValue;
	FInputActionValue LastLookValue;
	float LastTriggerValue = 0.0f;

	void UpdateInputDevice();
	void ProcessGamepadInput(float DeltaTime);
	void ProcessKeyboardMouseInput(float DeltaTime);

private:
	float GamepadDeadZone = 0.15f;
};
