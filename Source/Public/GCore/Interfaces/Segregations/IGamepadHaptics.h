// Copyright (c) 2025 Rafael Valoto. All Rights Reserved.
// Project: GamepadCore
// Description: Cross-platform library for DualSense and generic gamepad input support.
// Targets: Windows, Linux, macOS.
#pragma once
#include <vector>
#include <cstdint>

/**
 *
 */
class IGamepadHaptics
{
	// Add interface functions to this class. This is the class that will be
	// inherited to implement this interface.
public:
	virtual ~IGamepadHaptics() = default;

	/**
	 * Updates the audio haptic feedback using the provided audio data.
	 * This method is expected to be implemented by subclasses to process
	 * and use the given audio data for triggering haptic feedback.
	 *
	 * @param AudioData A vector of unsigned 8-bit integers representing
	 *                  the audio data to be used for haptic feedback.
	 *                  The data is typically interpreted and processed
	 *                  to generate corresponding haptic effects.
	 */
	virtual void AudioHapticUpdate(const std::vector<std::uint8_t>& AudioData) = 0;
	/**
	 * Updates the audio haptic feedback using the provided multiChannel audio data.
	 * This method should be implemented by subclasses to process and use
	 * the given multidimensional audio data for delivering precise haptic effects.
	 *
	 * @param AudioData A two-dimensional vector where each inner vector represents
	 *                  audio samples for a specific channel. The samples are
	 *                  represented as 16-bit signed integers. The data is intended
	 *                  to be processed to create corresponding multiChannel haptic
	 *                  feedback effects.
	 */
	virtual void AudioHapticUpdate(const std::vector<std::int16_t>& AudioData) = 0;

	/**
	 * Internal method for sending legacy Bluetooth audio haptic reports.
	 * This is used to avoid infinite recursion when routing audio through IAudioDevice.
	 */
	virtual void SendLegacyBTReport(const std::vector<std::int16_t>& AudioData) = 0;
};
