// Copyright (c) 2025 Rafael Valoto. All Rights Reserved.
// Project: GamepadCore
// Description: Cross-platform library for DualSense and generic gamepad input support.
// Targets: Windows, Linux, macOS.
#pragma once
#include "GCore/Interfaces/IPlatformHardware.h"
#include "GCore/Types/Structs/Context/DeviceContext.h"

namespace GamepadCore
{
	template<typename T>
	concept IsHardwarePolicy = requires(T t, FDeviceContext* ctx, std::vector<FDeviceContext>& devs) {
		{
			t.Read(ctx)
		} -> std::same_as<void>;
		{
			t.Write(ctx)
		} -> std::same_as<void>;
		{
			t.Detect(devs)
		} -> std::same_as<void>;
		{
			t.CreateHandle(ctx)
		} -> std::same_as<bool>;
		{
			t.InvalidateHandle(ctx)
		} -> std::same_as<void>;
		{
			t.ProcessAudioHaptic(ctx)
		} -> std::same_as<void>;
		{
			t.ProcessAudioHaptic(ctx, std::declval<const std::vector<std::int16_t>&>())
		} -> std::same_as<void>;
		{
			t.InitializeAudioDevice(ctx)
		} -> std::same_as<void>;
	};

	template<typename THardwarePolicy>
	class TGenericHardwareInfo : public IPlatformHardware
	{
		THardwarePolicy Policy;
		class IDeviceRegistry* Registry = nullptr;

	public:
		~TGenericHardwareInfo() override = default;

		void Read(FDeviceContext* Context) override
		{
			Policy.Read(Context);
		}

		void Write(FDeviceContext* Context) override
		{
			Policy.Write(Context);
		}

		void Detect(std::vector<FDeviceContext>& Devices) override
		{
			Policy.Detect(Devices);
		}

		bool CreateHandle(FDeviceContext* Context) override
		{
			return Policy.CreateHandle(Context);
		}

		void InvalidateHandle(FDeviceContext* Context) override
		{
			Policy.InvalidateHandle(Context);
		}

		void ProcessAudioHaptic(FDeviceContext* Context) override
		{
			Policy.ProcessAudioHaptic(Context);
		}

		void ProcessAudioHaptic(FDeviceContext* Context, const std::vector<std::int16_t>& AudioData) override
		{
			Policy.ProcessAudioHaptic(Context, AudioData);
		}

		void InitializeAudioDevice(FDeviceContext* Context) override
		{
			Policy.InitializeAudioDevice(Context);
		}

		class IGamepadBase* GetLibrary(uint32_t EngineDeviceId) override
		{
			return Registry ? Registry->GetLibrary(EngineDeviceId) : nullptr;
		}

		void SetRegistry(class IDeviceRegistry* InRegistry) override
		{
			Registry = InRegistry;
		}

		THardwarePolicy& GetPolicy() { return Policy; }
	};
} // namespace GamepadCore
