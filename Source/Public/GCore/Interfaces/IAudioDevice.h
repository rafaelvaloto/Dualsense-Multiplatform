// Copyright (c) 2026 Rafael Valoto. All rights reserved.
// Created for: GamepadCore - Plugin to support DualSense controller on Windows.
// Planned Release Year: 2026

#pragma once
#include "GCore/Types/Structs/Context/DeviceContext.h"
#include <cstdint>

namespace GCAudio
{
	class IAudioDevice
	{
	public:
		virtual ~IAudioDevice() = default;

		static IAudioDevice& Get();
		static void SetInstance(std::unique_ptr<IAudioDevice> InInstance);

		virtual void UnregisterAudioDevice(std::string Path) = 0;
		virtual void InitializeAudioContainer(FDeviceContext* Context) = 0;
		virtual void ProcessAudioHaptic(FDeviceContext* Context, const std::vector<float>& AudioData) = 0;

	protected:
		IAudioDevice() = default;

	private:
		static std::unique_ptr<IAudioDevice> AudioDeviceInstance;
	};
} // namespace GCAudio
