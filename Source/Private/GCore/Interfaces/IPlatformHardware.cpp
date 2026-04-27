// Copyright (c) 2025 Rafael Valoto. All Rights Reserved.
// Project: GamepadCore
// Description: Cross-platform library for DualSense and generic gamepad input support.
// Targets: Windows, Linux, macOS.

#include "GCore/Interfaces/IPlatformHardware.h"

std::unique_ptr<IPlatformHardware>
    IPlatformHardware::PlatformInfoInstance = nullptr;

IPlatformHardware& IPlatformHardware::Get()
{
	return *PlatformInfoInstance;
}

void IPlatformHardware::SetInstance(
    std::unique_ptr<IPlatformHardware> InPlatform)
{
	PlatformInfoInstance = std::move(InPlatform);
}
