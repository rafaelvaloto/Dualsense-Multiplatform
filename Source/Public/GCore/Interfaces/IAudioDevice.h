// Project: GamepadCore
// Copyright (c) 2026 rafae
// All rights reserved.
//
// Created by rafae on 4/26/2026.
//
#pragma once
#include "GCore/Types/Structs/Context/DeviceContext.h"
#include <cstdint>

class IAudioDevice
{
public:
	virtual ~IAudioDevice() = default;

	static IAudioDevice& Get();
	static void SetInstance(IAudioDevice* InInstance);

	virtual void UnregisterAudioDevice(std::string Path) = 0;
	virtual void InitializeAudioContainer(FDeviceContext* Context) = 0;
	virtual void ProcessAudioHaptic(FDeviceContext* Context, const std::vector<std::int16_t>& AudioData) = 0;
};
