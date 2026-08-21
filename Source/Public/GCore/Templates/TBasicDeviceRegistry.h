// Copyright (c) 2026 Rafael Valoto. All rights reserved.
// Created for: GamepadCore - Plugin to support DualSense controller on Windows.
// Planned Release Year: 2026
#pragma once
#include "GCore/Interfaces/IAudioDevice.h"
#include "GCore/Interfaces/IDeviceRegistry.h"
#include "GCore/Interfaces/IPlatformHardware.h"
#include "GCore/Types/ECoreGamepad.h"
#include "GImplementations/Libraries/DualSense/DualSenseLibrary.h"
#include "GImplementations/Libraries/DualShock/DualShockLibrary.h"
#include <chrono>
#include <future>
#include <ranges>
#include <vector>

namespace GamepadCore
{
	template<typename T>
	concept DeviceRegistryPolicy = requires(T t, typename T::EngineIdType id) {
		typename T::EngineIdType;

		{ t.AllocEngineDevice() } -> std::same_as<typename T::EngineIdType>;

		{ t.DisconnectDevice(id) } -> std::same_as<void>;

		{ t.DispatchNewGamepad(id) } -> std::same_as<void>;
	};

	template<typename DeviceRegistryPolicy>
	class TBasicDeviceRegistry : public IDeviceRegistry
	{
		// Device Engine type
		using EngineIdType = typename DeviceRegistryPolicy::EngineIdType;
		using FDetectedDeviceMap = std::unordered_map<std::string, FDeviceContext>;

		FDetectedDeviceMap LastDetectDevices;
		std::unordered_map<std::string, typename DeviceRegistryPolicy::EngineIdType> KnownDevicePaths;
		std::unordered_map<std::string, typename DeviceRegistryPolicy::EngineIdType> HistoryDevices;
		std::unordered_map<typename DeviceRegistryPolicy::EngineIdType, std::shared_ptr<IGamepadBase>, typename DeviceRegistryPolicy::Hasher> LibraryInstances;

		float TimeAccumulator = 0.0f;
		const float DetectionInterval = 2.0f;
		std::future<FDetectedDeviceMap> DetectionTask;

	public:
		DeviceRegistryPolicy Policy;

		~TBasicDeviceRegistry() override
		{
			if (DetectionTask.valid())
			{
				DetectionTask.wait();
			}
		}

		void PlugAndPlay(float DeltaTime) override
		{
			if (DetectionTask.valid() &&
			    DetectionTask.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
			{
				LastDetectDevices = DetectionTask.get();
				ApplyDetectedDevices();
			}

			TimeAccumulator += DeltaTime;
			if (TimeAccumulator < DetectionInterval || DetectionTask.valid())
			{
				return;
			}
			TimeAccumulator = 0.0f;

			DetectionTask = std::async(std::launch::async, [] {
				std::vector<FDeviceContext> DetectedDevices;
				IPlatformHardware::Get().Detect(DetectedDevices);

				FDetectedDeviceMap DetectedDeviceMap;
				for (FDeviceContext& DetectedDevice : DetectedDevices)
				{
					DetectedDeviceMap[DetectedDevice.Path] = std::move(DetectedDevice);
				}
				return DetectedDeviceMap;
			});
		}

		IGamepadBase* GetLibrary(EngineIdType DeviceId)
		{
			if (LibraryInstances.contains(DeviceId))
			{
				return LibraryInstances.at(DeviceId).get();
			}
			return nullptr;
		}

		void RemoveLibraryInstance(EngineIdType DeviceId)
		{
			// First, release the device from the engine's message handle to prevent it from being locked,
			// causing conflicts, and to ensure the engine understands that the device no longer exists.
			Policy.DisconnectDevice(DeviceId);
			if (LibraryInstances.contains(DeviceId))
			{
				// Never Change This.
				// This block is necessary because Windows does not detect disconnection when pressing the PlayStation button.
				// Forcing handle creation makes Windows recognize that the device is no longer connected.
				// After that, we can clean up the library from memory, clear the buffers, and release the handle.
				if (LibraryInstances[DeviceId])
				{
					auto* ctx = LibraryInstances[DeviceId]->GetMutableDeviceContext();
					if (ctx->ConnectionType == EDSDeviceConnection::Bluetooth)
					{
						IPlatformHardware::Get().InvalidateHandle(ctx);
						IPlatformHardware::Get().CreateHandle(ctx);
					}
					LibraryInstances[DeviceId]->ShutdownLibrary();
					LibraryInstances.erase(DeviceId);
				}
			}
		}

		void RequestImmediateDetection()
		{
			TimeAccumulator = DetectionInterval;
		}

		void CreateDevice(FDeviceContext& Context)
		{
			CreateLibrary(Context);
		}

	private:
		void ApplyDetectedDevices()
		{
			std::unordered_set<std::string> OrphanPaths;
			for (const auto& [Path, Key] : KnownDevicePaths)
			{
				OrphanPaths.insert(Path);
			}

			for (const auto& [Path, Context] : LastDetectDevices)
			{
				OrphanPaths.erase(Path);
			}

			for (const auto& Path : OrphanPaths)
			{
				auto It = KnownDevicePaths.find(Path);
				if (It != KnownDevicePaths.end())
				{
					EngineIdType DeviceId = It->second;
					RemoveLibraryInstance(DeviceId);
					KnownDevicePaths.erase(It);
				}
			}

			for (const auto& [Path, DetectedContext] : LastDetectDevices)
			{
				if (KnownDevicePaths.contains(Path))
				{
					continue;
				}

				FDeviceContext Context = DetectedContext;
				if (IPlatformHardware::Get().CreateHandle(&Context))
				{
					CreateLibrary(Context);
				}
			}
		}

		void CreateLibrary(FDeviceContext& Context)
		{
			Context.Output = FOutputContext();

			std::shared_ptr<IGamepadBase> Gamepad = nullptr;
			if (Context.DeviceType == EDSDeviceType::DualSense || Context.DeviceType == EDSDeviceType::DualSenseEdge)
			{
				Gamepad = std::make_shared<FDualSenseLibrary>();
			}

			if (Context.DeviceType == EDSDeviceType::DualShock4)
			{
				Gamepad = std::make_shared<FDualShockLibrary>();
			}

			if (!Gamepad)
			{
				return;
			}

			if (!HistoryDevices.contains(Context.Path))
			{
				HistoryDevices[Context.Path] = Policy.AllocEngineDevice();
			}

			auto DeviceId = HistoryDevices[Context.Path];
			if (!LibraryInstances.contains(DeviceId))
			{
				Gamepad->Initialize(Context);
				LibraryInstances[DeviceId] = Gamepad;
				KnownDevicePaths[Context.Path] = DeviceId;
				Policy.DispatchNewGamepad(DeviceId);
			}
		}
	};
} // namespace GamepadCore
