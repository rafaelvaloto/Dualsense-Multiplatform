// Copyright (c) 2025 Rafael Valoto. All Rights Reserved.
// Project: GamepadCore
// Description: Cross-platform library for DualSense and generic gamepad input support.
// Targets: Windows, Linux, macOS.

#include "GImplementations/Libraries/Base/GamepadBase.h"
#include "GCore/Interfaces/IPlatformHardware.h"

void GamepadBase::ShutdownLibrary()
{
	IPlatformHardware::Get().InvalidateHandle(&HIDDeviceContexts);
}

float GamepadBase::GetBattery()
{
	return HIDDeviceContexts.GetInputState()->BatteryLevel;
}

bool GamepadBase::IsConnected()
{
	return HIDDeviceContexts.IsConnected;
}

EDSDeviceType GamepadBase::GetDeviceType()
{
	return HIDDeviceContexts.DeviceType;
}

EDSDeviceConnection GamepadBase::GetConnectionType()
{
	return HIDDeviceContexts.ConnectionType;
}
