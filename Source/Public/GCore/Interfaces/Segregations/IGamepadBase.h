// Copyright (c) 2025 Rafael Valoto. All Rights Reserved.
// Project: GamepadCore
// Description: Cross-platform library for DualSense and generic gamepad input support.
// Targets: Windows, Linux, macOS.
#pragma once
#include "GCore/Types/Structs/Context/DeviceContext.h"
#include "IGamepadHaptics.h"
#include "IGamepadLightbar.h"
#include "IGamepadRumbles.h"
#include "IGamepadSensors.h"
#include "IGamepadSettings.h"
#include "IGamepadStatus.h"
#include "IGamepadTouch.h"
#include "IGamepadTrigger.h"

/**
 * Provides the base interface for interacting with a gamepad device.
 *
 * This interface serves as a foundational abstraction for functionality
 * related to gamepad hardware. Derived classes or implementations of
 * this interface should define specific behaviors and features supported
 * by a gamepad device.
 */
class IGamepadBase : public IGamepadStatus
{

public:
	~IGamepadBase() override = default;
	/**
	 * Initializes the system or a specific component to a ready state.
	 *
	 * This method is used to set up necessary configurations or prepare resources.
	 *
	 * @param Context A reference to a device context containing information about the gamepad and its current state.
	 * This context may include details such as connection type, device type, and other
	 * @return A boolean indicating whether the initialization was successful.
	 */
	virtual bool Initialize(const FDeviceContext& Context) = 0;
	/**
	 * Shuts down and cleans up resources used by the library.
	 *
	 * This method is responsible for ensuring that all resources
	 * allocated by the library are released and any necessary
	 * finalization steps are performed before terminating its use.
	 */
	virtual void ShutdownLibrary() = 0;
	/**
	 * Updates the output stream with the latest data or changes.
	 *
	 * This method is used to modify or refresh the current output
	 * to ensure it reflects the most recent state or information.
	 *
	 * It is intended for scenarios where the output must be recalculated
	 * or synchronized based on specific input or internal logic updates.
	 */
	virtual void UpdateOutput() = 0;
	/**
	 * Updates the current input state for the application.
	 *
	 * This method processes input events and updates the internal state
	 * based on user interactions or automated inputs.
	 *
	 * @param Delta The time elapsed since the last frame, in seconds. This parameter is
	 */
	virtual void UpdateInput(float Delta) = 0;
	/**
	 * Retrieves the gamepad trigger interface associated with the gamepad.
	 *
	 * This method provides access to an object representing the gamepad's trigger functionality.
	 * If the gamepad does not support a trigger or the implementation is unavailable, it returns nullptr.
	 *
	 * @return A pointer to an object implementing the IGamepadTrigger interface, or nullptr if unavailable.
	 */
	virtual IGamepadTrigger* GetIGamepadTrigger() { return nullptr; }
	/**
	 * Retrieves the lightbar interface associated with the gamepad.
	 *
	 * This method is intended to provide access to the lightbar functionality
	 * of the gamepad by returning an instance of the `IGamepadLightbar` interface.
	 * If the lightbar is not available or not implemented, this method returns nullptr.
	 *
	 * @return A pointer to the `IGamepadLightbar` interface, or nullptr if the
	 *         lightbar functionality is not supported.
	 */
	virtual IGamepadLightbar* GetIGamepadLightbar() { return nullptr; }
	/**
	 * Retrieves the IGamepadRumbles interface associated with the gamepad.
	 *
	 * This method provides access to the gamepad's vibration or rumble capabilities,
	 * allowing control over the intensity and behavior of the device's vibration motors.
	 *
	 * @return A pointer to the IGamepadRumbles interface if available; otherwise, returns nullptr.
	 */
	virtual IGamepadRumbles* GetIGamepadRumbles() { return nullptr; }
	/**
	 * Retrieves an interface to access the sensors of the gamepad, such as the
	 * gyroscope and accelerometer.
	 *
	 * This method allows access to gyroscope and accelerometer functionalities
	 * through the IGamepadSensors interface. The base implementation returns
	 * nullptr, and specific implementations may override this to provide
	 * actual functionality.
	 *
	 * @return A pointer to an IGamepadSensors interface if supported, or nullptr
	 * if the sensors are not available or not implemented.
	 */
	virtual IGamepadSensors* GetIGamepadSensors() { return nullptr; }
	/**
	 * Retrieves the haptics interface associated with the gamepad.
	 *
	 * This method provides access to the haptics functionality, enabling vibration
	 * or other tactile feedback features supported by the gamepad.
	 *
	 * @return The haptics interface for the gamepad.
	 */
	virtual IGamepadHaptics* GetIGamepadHaptics() { return nullptr; }
	/**
	 * Retrieves the touch interface associated with the gamepad.
	 *
	 * This method provides access to the touchpad functionality of the gamepad
	 * through the `IGamepadTouch` interface. If the touchpad is not available
	 * or not implemented, this method returns nullptr.
	 *
	 * @return A pointer to an `IGamepadTouch` interface if supported, or nullptr
	 *         if the touchpad functionality is not available or not implemented.
	 */
	virtual IGamepadTouch* GetIGamepadTouch() { return nullptr; }
	/**
	 * Retrieves the settings interface associated with the gamepad.
	 *
	 * This method provides access to an `IGamepadSettings` instance, allowing
	 * configurations or settings specific to the gamepad to be accessed or modified.
	 * If the settings functionality is not supported or available, this method returns nullptr.
	 *
	 * @return A pointer to an `IGamepadSettings` interface if available, or nullptr
	 *         if the settings functionality is not supported or not implemented.
	 */
	virtual IGamepadSettings* GetIGamepadSettings() { return nullptr; }
};
