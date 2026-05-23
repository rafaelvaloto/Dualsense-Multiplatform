// Copyright (c) 2026 Rafael Valoto. All rights reserved.
// Created for: GamepadCore - Plugin to support DualSense controller on Windows.
// Planned Release Year: 2026

#include "GCore/Interfaces/IAudioDevice.h"
#include <stdexcept>

namespace GCAudio
{
	std::unique_ptr<IAudioDevice> IAudioDevice::AudioDeviceInstance = nullptr;
	IAudioDevice& IAudioDevice::Get()
	{
		return *AudioDeviceInstance;
	}

	void IAudioDevice::SetInstance(std::unique_ptr<IAudioDevice> InInstance)
	{
		AudioDeviceInstance = std::move(InInstance);
	}
} // namespace GCAudio
