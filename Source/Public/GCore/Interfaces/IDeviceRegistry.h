// Copyright (c) 2026 Rafael Valoto. All rights reserved.
// Created for: GamepadCore - Plugin to support DualSense controller on Windows.
// Planned Release Year: 2026
#pragma once
class IDeviceRegistry
{
public:
	virtual ~IDeviceRegistry() = default;
	virtual void PlugAndPlay(float DeltaTime) = 0;
};
