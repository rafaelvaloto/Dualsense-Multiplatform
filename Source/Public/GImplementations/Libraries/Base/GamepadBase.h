// Copyright (c) 2026 Rafael Valoto. All Rights Reserved.
// Project: GamepadCore
// Description: Cross-platform library for DualSense and generic gamepad input support.
// Targets: Windows, Linux, macOS.
#pragma once
#include "GCore/Interfaces/Segregations/IGamepadBase.h"
#include "GCore/Types/ECoreGamepad.h"

/**
 * @class GamepadBase
 * @brief An abstract base class derived from the ISonyGamepad interface.
 *
 * The GamepadBase class serves as a foundational class for implementing
 * gamepad functionality specific to Sony devices. It inherits from the
 * ISonyGamepad interface, which provides methods and features for managing
 * gamepad status, lightbar, sensors, touch input, triggers, audio-driven
 * haptics, and more.
 *
 * Classes inheriting from GamepadBase are expected to implement the
 * behaviors defined by the ISonyGamepad interface.
 */
class GamepadBase : public IGamepadBase
{

public:
	/**
	 * @brief Shuts down the library and releases associated resources.
	 *
	 * This method is invoked to perform cleanup tasks, ensuring that all
	 * resources allocated by the library are properly released. It overrides the
	 * equivalent method in the ISonyGamepad interface and ensures the integrity
	 * of the shutdown process specific to Sony gamepad implementations.
	 */
	void ShutdownLibrary() override;
	/**
	 * @brief Updates the output state of the gamepad.
	 *
	 * This method is responsible for refreshing or modifying the output-related
	 * functionality of the Sony gamepad. It overrides the UpdateOutput method
	 * defined in the ISonyGamepad interface and provides a customized
	 * implementation specific to derived classes.
	 *
	 * The UpdateOutput functionality may include updating lightbar states,
	 * haptic feedback, audio output, or other gamepad output features based on
	 * the current state or input from the system.
	 */
	void UpdateOutput() override {}
	/**
	 * @brief Updates the input state of the gamepad.
	 *
	 * The UpdateInput method is called to process and refresh the input data
	 * associated with the gamepad. This function is typically invoked on each
	 * frame with the elapsed time (Delta) since the last update, allowing input
	 * state to be updated in real-time.
	 *
	 * @param Delta The time elapsed since the previous frame, in seconds.
	 *
	 * @details This method is meant to be overridden to implement specific
	 * behaviors for handling input updates in derived classes. It ensures that
	 * the gamepad's state is continuously synchronized with the current input
	 * conditions, supporting real-time interaction within the application.
	 */
	void UpdateInput(float /*Delta*/) override {}
	/**
	 * Pure virtual function that checks the connection status of the gamepad.
	 *
	 * @return True if the gamepad is connected, false otherwise.
	 */
	bool IsConnected() override;
	/**
	 * Retrieves the type of the device.
	 *
	 * @return The type of the device as an EDeviceType enumeration.
	 */
	EDSDeviceType GetDeviceType() override;
	/**
	 * Retrieves the connection type of the device.
	 *
	 * @return The connection type of the device as an EDeviceConnection
	 * enumeration.
	 */
	EDSDeviceConnection GetConnectionType() override;
	/**
	 * Retrieves the current battery level of the Sony gamepad.
	 *
	 * @return The battery level as a floating-point value, where the exact range
	 *         and representation are dependent on the implementation. Typically,
	 *         values may range between 0.0 (empty) and 1.0 (full).
	 */
	float GetBattery() override;
	/**
	 * @brief Retrieves a mutable device context associated with the object.
	 *
	 * This method provides access to the device context in a mutable form,
	 * allowing modifications to the underlying hardware interface descriptor
	 * (HID) data specific to the device.
	 *
	 * @return A pointer to the mutable FDeviceContext object corresponding to the
	 * device's HID context.
	 */
	FDeviceContext* GetMutableDeviceContext() override
	{
		return &HIDDeviceContexts;
	}

	GamepadBase()
	    : HIDDeviceContexts()
	{}

protected:
	/**
	 * @brief Sets the device contexts for the HID device.
	 *
	 * This method assigns the provided device contexts to the internal HID device
	 * contexts, enabling the configuration or update of the underlying device
	 * settings.
	 *
	 * @param DeviceContexts A reference to the FDeviceContext object representing
	 * the new HID device contexts.
	 */
	void SetDeviceContexts(const FDeviceContext& DeviceContexts)
	{
		this->HIDDeviceContexts = DeviceContexts;
	}

private:
	/**
	 * Indicates whether a phone is connected to the system.
	 *
	 * This variable is used to store the connection status of a phone.
	 * It is updated by the SetHasPhoneConnected method.
	 * - `true`: A phone is connected.
	 * - `false`: No phone is connected.
	 */
	bool bHasPhoneConnected{};
	/**
	 * @brief Represents the context of a Human Interface Device (HID) used by
	 * Controllers.
	 *
	 * This variable holds the FDeviceContext structure, which encapsulates the
	 * necessary state and configuration details for managing the connection,
	 * communication, and interaction with a specific DualSense gamepad device. It
	 * is primarily used within the UDualSenseLibrary class for initialization,
	 * input handling, and managing device-specific settings.
	 */
	FDeviceContext HIDDeviceContexts;
};
