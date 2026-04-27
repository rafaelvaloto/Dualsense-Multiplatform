// Copyright (c) 2025 Rafael Valoto/Publisher. All rights reserved.
// Created for: GamepadCore - Plugin to support DualSense controller on Windows.
// Planned Release Year: 2025
#pragma once
#include "GCore/Interfaces/IAudioDevice.h"
#include "GCore/Interfaces/IDeviceRegistry.h"
#include "GCore/Interfaces/IPlatformHardware.h"
#include "GCore/Types/ECoreGamepad.h"
#include "GImplementations/Libraries/DualSense/DualSenseLibrary.h"
#include "GImplementations/Libraries/DualShock/DualShockLibrary.h"
#include <ranges>
#include <vector>

namespace GamepadCore
{

	template<typename T>
	concept AudioDevicePolicy = requires(T t, typename T::EngineIdType id, typename T::AudioDeviceType audioDevice, typename T::AudioDeviceIdType audioDeviceId, typename T::AudioRingBufferType audioRingBuffer, typename T::AudioFrameCountType frameCount) {
		typename T::EngineIdType;
		typename T::AudioDeviceType;
		typename T::AudioDeviceIdType;
		typename T::AudioRingBufferType;
		typename T::AudioFrameCountType;

		{ t.Initialize() } -> std::same_as<bool>;
		{ t.Close() } -> std::same_as<void>;
		{ t.IsValid() } -> std::same_as<bool>;
		{ t.InitializeWithDeviceId(T::AudioDeviceIdType) } -> std::same_as<bool>;
		{ t.GetAvailableWriteFrames() } -> std::same_as<typename T::AudioFrameCountType>;
		{ t.WriteHapticData(std::declval<const std::vector<std::int16_t>&>()) } -> std::same_as<bool>;
		{ t.UnregisterAudioDevice(T::EngineIdType) } -> std::same_as<void>;
		{ t.RegisterAudioDevice(T::EngineIdType, T::AudioDeviceIdType) } -> std::same_as<void>;
	};

	template<typename AudioDevicePolicy>
	class TAudioDeviceRegistry : public IAudioDevice
	{
	public:

		~TAudioDeviceRegistry() override = default;

		// EngineId Device type
		using EngineIdType = typename AudioDevicePolicy::EngineIdType;

		// Audio Container types
		using AudioDeviceType = typename AudioDevicePolicy::AudioDeviceType;
		using AudioDeviceIdType = typename AudioDevicePolicy::AudioDeviceIdType;
		using AudioRingBufferType = typename AudioDevicePolicy::AudioRingBufferType;
		using AudioFrameCountType = typename AudioDevicePolicy::AudioFrameCountType;

		AudioDevicePolicy Policy;

		void Close()
		{
			Policy.clear();
		}

		bool IsValid()
		{
			return Policy.IsValid();
		}

		bool Initialize(int InSampleRate = 48000, int InNumChannels = 4)
		{
			return Policy.Initialize(InSampleRate, InNumChannels);
		}

		bool InitializeWithDeviceId(const AudioDeviceIdType* pDeviceId, int InSampleRate = 48000, int InNumChannels = 4)
		{
			return Policy.InitializeWithDeviceId(pDeviceId, InSampleRate, InNumChannels);
		}

		void ProcessAudioHaptic(const std::vector<std::int16_t>& AudioData)
		{
			Policy.WriteHapticData(AudioData);
		}

		void ProcessAudioHaptic(FDeviceContext* Context, const std::vector<std::int16_t>& AudioData) override
		{
			Policy.ProcessAudioHaptic(Context, AudioData);
		}

		void RegisterAudioDevice(EngineIdType EngineId, const AudioDeviceIdType* id = nullptr)
		{
			Policy.RegisterAudioDevice(EngineId, id);
		}

		void UnregisterAudioDevice(EngineIdType EngineId)
		{
			Policy.UnregisterAudioDevice(EngineId);
		}
	};

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

		std::unordered_map<std::string, typename DeviceRegistryPolicy::EngineIdType> KnownDevicePaths;
		std::unordered_map<std::string, typename DeviceRegistryPolicy::EngineIdType> HistoryDevices;
		std::unordered_map<typename DeviceRegistryPolicy::EngineIdType, std::shared_ptr<IGamepadBase>, typename DeviceRegistryPolicy::Hasher> LibraryInstances;

		float TimeAccumulator = 0.0f;
		const float DetectionInterval = 1.0f;

	public:
		DeviceRegistryPolicy Policy;

		~TBasicDeviceRegistry() override = default;

		void PlugAndPlay(float DeltaTime) override
		{
			TimeAccumulator += DeltaTime;
			if (TimeAccumulator < DetectionInterval)
			{
				return;
			}
			TimeAccumulator = 0.0f;

			std::unordered_set<std::string> OrphanPaths;
			OrphanPaths.clear();
			for (const auto& [Path, Key] : KnownDevicePaths)
			{
				OrphanPaths.insert(Path);
			}

			std::vector<FDeviceContext> DetectedDevices;
			DetectedDevices.clear();
			IPlatformHardware::Get().Detect(DetectedDevices);

			for (const auto& Context : DetectedDevices)
			{
				OrphanPaths.erase(Context.Path);
			}

			for (const std::string& Path : OrphanPaths)
			{
				auto It = KnownDevicePaths.find(Path);
				if (It != KnownDevicePaths.end())
				{
					EngineIdType DeviceId = It->second;
					RemoveLibraryInstance(DeviceId);
					KnownDevicePaths.erase(It);
				}
			}

			for (auto Context : DetectedDevices)
			{
				Context.Output = FOutputContext();
				if (bool IsCreateHandle = IPlatformHardware::Get().CreateHandle(&Context))
				{
					CreateLibrary(Context);
				}
			}
		}

		IGamepadBase* GetLibrary(EngineIdType DeviceId) override
		{
			if (LibraryInstances.contains(DeviceId))
			{
				return LibraryInstances.at(DeviceId).get();
			}
			return nullptr;
		}

		void RemoveLibraryInstance(EngineIdType DeviceId)
		{
			Policy.DisconnectDevice(DeviceId);
			if (LibraryInstances.contains(DeviceId))
			{
				LibraryInstances[DeviceId]->ShutdownLibrary();
				LibraryInstances.erase(DeviceId);
			}
		}

		void RequestImmediateDetection()
		{
			TimeAccumulator = DetectionInterval;
		}

	private:
		void CreateLibrary(FDeviceContext& Context)
		{
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
				Context.EngineDeviceId = static_cast<uint32_t>(DeviceId);
				Gamepad->Initialize(Context);
				LibraryInstances[DeviceId] = Gamepad;
				KnownDevicePaths[Context.Path] = DeviceId;
				Policy.DispatchNewGamepad(DeviceId);
			}
		}
	};
} // namespace GamepadCore
