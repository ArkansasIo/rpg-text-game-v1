#include "InputManager.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"

UInputManager::UInputManager()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 0.0f; // Tick every frame
}

void UInputManager::InitializeInput(APlayerController* InController)
{
	OwnerController = InController;

	if (!OwnerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("InputManager: Failed to initialize - no valid controller"));
		return;
	}

	// Setup player input mapping
	if (APlayerController* PC = Cast<APlayerController>(OwnerController))
	{
		// Enable input
		PC->bShowMouseCursor = true;
		PC->bEnableClickEvents = true;
		PC->bEnableTouchEvents = true;
	}

	UE_LOG(LogTemp, Warning, TEXT("InputManager: Initialized successfully"));
}

void UInputManager::RegisterInputAction(FName ActionName, const FInputKeyBinding& KeyBinding)
{
	FInputActionBinding NewBinding;
	NewBinding.ActionName = ActionName;
	NewBinding.KeyBinding = KeyBinding;
	NewBinding.bEnabled = true;

	RegisteredActions.Add(ActionName, NewBinding);

	UE_LOG(LogTemp, Warning, TEXT("InputManager: Registered action '%s'"), *ActionName.ToString());
}

void UInputManager::UnregisterInputAction(FName ActionName)
{
	if (RegisteredActions.Contains(ActionName))
	{
		RegisteredActions.Remove(ActionName);
		UE_LOG(LogTemp, Warning, TEXT("InputManager: Unregistered action '%s'"), *ActionName.ToString());
	}
}

bool UInputManager::IsKeyPressed(FKey Key) const
{
	if (!OwnerController)
		return false;

	if (Key.IsGamepadKey())
	{
		// Check gamepad button
		return OwnerController->IsInputKeyDown(Key);
	}
	else
	{
		// Check keyboard/mouse button
		return OwnerController->IsInputKeyDown(Key);
	}
}

float UInputManager::GetAxisValue(FName AxisName) const
{
	if (!OwnerController)
		return 0.0f;

	APawn* ControlledPawn = OwnerController->GetPawn();
	if (!ControlledPawn)
		return 0.0f;

	return ControlledPawn->GetInputAxisValue(AxisName);
}

FInputActionValue UInputManager::GetActionValue(FName ActionName) const
{
	if (RegisteredActions.Contains(ActionName))
	{
		return LastMoveValue; // Simplified - return last value
	}
	return FInputActionValue();
}

void UInputManager::SetInputEnabled(bool bEnabled)
{
	bInputEnabled = bEnabled;

	if (OwnerController)
	{
		if (bEnabled)
		{
			OwnerController->GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
		}
		else
		{
			OwnerController->GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
		}
	}
}

void UInputManager::SetActionEnabled(FName ActionName, bool bEnabled)
{
	if (RegisteredActions.Contains(ActionName))
	{
		RegisteredActions[ActionName].bEnabled = bEnabled;
	}
}

void UInputManager::RebindKey(FName ActionName, FKey NewKey, bool bIsPrimary)
{
	if (RegisteredActions.Contains(ActionName))
	{
		if (bIsPrimary)
		{
			RegisteredActions[ActionName].KeyBinding.PrimaryKey = NewKey;
		}
		else
		{
			RegisteredActions[ActionName].KeyBinding.SecondaryKey = NewKey;
		}

		UE_LOG(LogTemp, Warning, TEXT("InputManager: Rebound action '%s' to key"), *ActionName.ToString());
	}
}

FVector2D UInputManager::GetGamepadAnalogStickValue(EGamepadAnalogStick::Type StickType) const
{
	if (!OwnerController)
		return FVector2D::ZeroVector;

	FVector2D StickValue = FVector2D::ZeroVector;

	if (StickType == EGamepadAnalogStick::Type::LeftStick)
	{
		StickValue.X = OwnerController->GetInputAnalogStickAxisValue(EGamepadAnalogStick::LeftStickX);
		StickValue.Y = OwnerController->GetInputAnalogStickAxisValue(EGamepadAnalogStick::LeftStickY);
	}
	else if (StickType == EGamepadAnalogStick::Type::RightStick)
	{
		StickValue.X = OwnerController->GetInputAnalogStickAxisValue(EGamepadAnalogStick::RightStickX);
		StickValue.Y = OwnerController->GetInputAnalogStickAxisValue(EGamepadAnalogStick::RightStickY);
	}

	// Apply deadzone
	if (StickValue.SizeSquared() < GamepadDeadZone * GamepadDeadZone)
	{
		return FVector2D::ZeroVector;
	}

	return StickValue;
}

float UInputManager::GetGamepadTriggerValue(EGamepadTriggerAxis::Type TriggerAxis) const
{
	if (!OwnerController)
		return 0.0f;

	float TriggerValue = 0.0f;

	if (TriggerAxis == EGamepadTriggerAxis::LeftTrigger)
	{
		TriggerValue = OwnerController->GetInputAnalogStickAxisValue(EGamepadAnalogStick::LeftTrigger);
	}
	else if (TriggerAxis == EGamepadTriggerAxis::RightTrigger)
	{
		TriggerValue = OwnerController->GetInputAnalogStickAxisValue(EGamepadAnalogStick::RightTrigger);
	}

	return FMath::Max(0.0f, TriggerValue);
}

void UInputManager::PlayControllerVibration(float Intensity, float Duration, int32 ControllerIndex)
{
	if (!OwnerController)
		return;

	// Create vibration parameters
	FHapticFeedbackValues LeftVibration;
	LeftVibration.Amplitude = Intensity;

	FHapticFeedbackValues RightVibration;
	RightVibration.Amplitude = Intensity;

	// Play vibration
	OwnerController->PlayHapticEffect(nullptr, EControllerHand::Left, LeftVibration);
	OwnerController->PlayHapticEffect(nullptr, EControllerHand::Right, RightVibration);

	// Optional: Stop after duration
	if (Duration > 0.0f)
	{
		GetWorld()->GetTimerManager().SetTimer(
			FTimerHandle(),
			[this]()
			{
				FHapticFeedbackValues ZeroVibration;
				ZeroVibration.Amplitude = 0.0f;
				if (OwnerController)
				{
					OwnerController->PlayHapticEffect(nullptr, EControllerHand::Left, ZeroVibration);
					OwnerController->PlayHapticEffect(nullptr, EControllerHand::Right, ZeroVibration);
				}
			},
			Duration,
			false
		);
	}
}

void UInputManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bInputEnabled || !OwnerController)
		return;

	UpdateInputDevice();
	ProcessGamepadInput(DeltaTime);
	ProcessKeyboardMouseInput(DeltaTime);
}

void UInputManager::UpdateInputDevice()
{
	if (!OwnerController)
		return;

	// Check what device is being used
	if (OwnerController->IsInputKeyDown(EKeys::Gamepad_LeftStick_Up) ||
		OwnerController->IsInputKeyDown(EKeys::Gamepad_LeftStick_Down) ||
		OwnerController->IsInputKeyDown(EKeys::Gamepad_LeftStick_Left) ||
		OwnerController->IsInputKeyDown(EKeys::Gamepad_LeftStick_Right) ||
		OwnerController->IsInputKeyDown(EKeys::Gamepad_FaceButton_Bottom) ||
		OwnerController->IsInputKeyDown(EKeys::Gamepad_FaceButton_Right) ||
		OwnerController->IsInputKeyDown(EKeys::Gamepad_FaceButton_Top) ||
		OwnerController->IsInputKeyDown(EKeys::Gamepad_FaceButton_Left))
	{
		CurrentInputDevice = EInputDeviceType::Gamepad_Generic;
	}
	else if (OwnerController->IsInputKeyDown(EKeys::LeftMouseButton) ||
			 OwnerController->IsInputKeyDown(EKeys::RightMouseButton) ||
			 OwnerController->IsInputKeyDown(EKeys::MiddleMouseButton))
	{
		CurrentInputDevice = EInputDeviceType::Mouse;
	}
	else
	{
		CurrentInputDevice = EInputDeviceType::Keyboard;
	}
}

void UInputManager::ProcessGamepadInput(float DeltaTime)
{
	if (CurrentInputDevice != EInputDeviceType::Gamepad_Generic &&
		CurrentInputDevice != EInputDeviceType::Gamepad_Xbox &&
		CurrentInputDevice != EInputDeviceType::Gamepad_PS5)
		return;

	// Process movement
	FVector2D LeftStick = GetGamepadAnalogStickValue(EGamepadAnalogStick::LeftStick);
	if (LeftStick.SizeSquared() > 0.0f)
	{
		FInputActionValue MoveValue(EInputActionValueType::Axis2D, LeftStick);
		OnMoveForward.Broadcast(FInputActionValue(EInputActionValueType::Axis1D, FVector(LeftStick.Y, 0, 0)), DeltaTime);
		OnMoveSide.Broadcast(FInputActionValue(EInputActionValueType::Axis1D, FVector(LeftStick.X, 0, 0)), DeltaTime);
	}

	// Process look
	FVector2D RightStick = GetGamepadAnalogStickValue(EGamepadAnalogStick::RightStick);
	if (RightStick.SizeSquared() > 0.0f)
	{
		OnLookUp.Broadcast(FInputActionValue(EInputActionValueType::Axis1D, FVector(RightStick.Y, 0, 0)), DeltaTime);
		OnLookRight.Broadcast(FInputActionValue(EInputActionValueType::Axis1D, FVector(RightStick.X, 0, 0)), DeltaTime);
	}

	// Process action buttons
	if (OwnerController->IsInputKeyDown(EKeys::Gamepad_FaceButton_Bottom))
	{
		OnAction.Broadcast(FInputActionValue(EInputActionValueType::Digital, FVector(1, 0, 0)), DeltaTime);
	}

	if (OwnerController->IsInputKeyDown(EKeys::Gamepad_FaceButton_Right))
	{
		OnInteract.Broadcast(FInputActionValue(EInputActionValueType::Digital, FVector(1, 0, 0)), DeltaTime);
	}

	if (OwnerController->IsInputKeyDown(EKeys::Gamepad_Special_Left))
	{
		OnOpenMenu.Broadcast(FInputActionValue(EInputActionValueType::Digital, FVector(1, 0, 0)), DeltaTime);
	}

	if (OwnerController->IsInputKeyDown(EKeys::Gamepad_Special_Right))
	{
		OnPause.Broadcast(FInputActionValue(EInputActionValueType::Digital, FVector(1, 0, 0)), DeltaTime);
	}
}

void UInputManager::ProcessKeyboardMouseInput(float DeltaTime)
{
	if (CurrentInputDevice == EInputDeviceType::Gamepad_Generic ||
		CurrentInputDevice == EInputDeviceType::Gamepad_Xbox ||
		CurrentInputDevice == EInputDeviceType::Gamepad_PS5)
		return;

	// Process keyboard input
	if (OwnerController->IsInputKeyDown(EKeys::W) || OwnerController->IsInputKeyDown(EKeys::Up))
	{
		OnMoveForward.Broadcast(FInputActionValue(EInputActionValueType::Axis1D, FVector(1, 0, 0)), DeltaTime);
	}
	else if (OwnerController->IsInputKeyDown(EKeys::S) || OwnerController->IsInputKeyDown(EKeys::Down))
	{
		OnMoveForward.Broadcast(FInputActionValue(EInputActionValueType::Axis1D, FVector(-1, 0, 0)), DeltaTime);
	}

	if (OwnerController->IsInputKeyDown(EKeys::D) || OwnerController->IsInputKeyDown(EKeys::Right))
	{
		OnMoveSide.Broadcast(FInputActionValue(EInputActionValueType::Axis1D, FVector(1, 0, 0)), DeltaTime);
	}
	else if (OwnerController->IsInputKeyDown(EKeys::A) || OwnerController->IsInputKeyDown(EKeys::Left))
	{
		OnMoveSide.Broadcast(FInputActionValue(EInputActionValueType::Axis1D, FVector(-1, 0, 0)), DeltaTime);
	}

	// Action keys
	if (OwnerController->IsInputKeyDown(EKeys::SpaceBar))
	{
		OnAction.Broadcast(FInputActionValue(EInputActionValueType::Digital, FVector(1, 0, 0)), DeltaTime);
	}

	if (OwnerController->IsInputKeyDown(EKeys::E))
	{
		OnInteract.Broadcast(FInputActionValue(EInputActionValueType::Digital, FVector(1, 0, 0)), DeltaTime);
	}

	if (OwnerController->IsInputKeyDown(EKeys::I) || OwnerController->IsInputKeyDown(EKeys::M))
	{
		OnOpenMenu.Broadcast(FInputActionValue(EInputActionValueType::Digital, FVector(1, 0, 0)), DeltaTime);
	}

	if (OwnerController->IsInputKeyDown(EKeys::Escape))
	{
		OnPause.Broadcast(FInputActionValue(EInputActionValueType::Digital, FVector(1, 0, 0)), DeltaTime);
	}
}
