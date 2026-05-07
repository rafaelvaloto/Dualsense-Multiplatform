// Copyright (c) 2025 Rafael Valoto. All Rights Reserved.
// Project: GamepadCore
// Description: Cross-platform library for DualSense and generic gamepad input support.
// Targets: Windows, Linux, macOS.
#pragma once
#include "GCore/Types/DSCoreTypes.h"

class IGamepadSettings
{
public:
	virtual ~IGamepadSettings() = default;
	/**
	 * Configures various settings for the Sony gamepad, including audio, lightbar,
	 * and rumble features. Allows customization of multiple gamepad functionalities
	 * to enhance user experience.
	 *
	 * @param bIsMic Indicates whether the microphone is enabled (1) or disabled (0).
	 * @param bIsHeadset Indicates whether the headset is enabled (1) or disabled (0).
	 * @param bIsSpeaker Indicates whether the speaker is enabled (1) or disabled (0).
	 * @param MicVolume Specifies the microphone volume level.
	 * @param AudioVolume Specifies the audio volume level.
	 * @param RumbleMode Sets the rumble mode configuration value.
	 * @param RumbleReduce Adjusts the intensity reduction for the rumble effect.
	 * @param TriggerReduce Adjusts the intensity reduction for the trigger effect.
	 */
	virtual void DualSenseSettings(std::uint8_t bIsMic, std::uint8_t bIsHeadset, std::uint8_t bIsSpeaker, std::uint8_t MicVolume, std::uint8_t AudioVolume, std::uint8_t RumbleMode, std::uint8_t RumbleReduce, std::uint8_t TriggerReduce) = 0;
};
