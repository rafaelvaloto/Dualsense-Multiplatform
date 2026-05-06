// Copyright (c) 2025 Rafael Valoto/Publisher. All rights reserved.
// Created for: GamepadCore - Plugin to support DualSense controller on Windows.
// Planned Release Year: 2025
#pragma once
#include "GCore/Interfaces/IAudioDevice.h"
#include <ranges>
#include <vector>

namespace GamepadCore
{
	template<typename T>
	concept AudioDevicePolicy = requires(T t, typename T::DevicePathType path, typename T::AudioDeviceType audioDevice, typename T::AudioDeviceIdType audioDeviceId, typename T::AudioRingBufferType audioRingBuffer, typename T::AudioFrameCountType frameCount, typename T::ContextType ctx) {
		typename T::DevicePathType;
		typename T::AudioDeviceType;
		typename T::AudioDeviceIdType;
		typename T::AudioRingBufferType;
		typename T::AudioFrameCountType;
		typename T::ContextType;

		{ t.Close() } -> std::same_as<void>;
		{ t.IsValid() } -> std::same_as<bool>;
		{ t.InitializeAudioContainer(ctx) } -> std::same_as<bool>;
		{ t.InitializeWithDeviceId(audioDeviceId) } -> std::same_as<bool>;
		{ t.WriteHapticData(std::declval<const std::vector<std::int16_t>&>()) } -> std::same_as<bool>;
	};

	template<typename AudioDevicePolicy>
	class TAudioDeviceRegistry
	{
	public:
		~TAudioDeviceRegistry() = default;

		AudioDevicePolicy Policy;

		// EngineId Device type
		using DevicePathType = typename AudioDevicePolicy::DevicePathType;
		using ContextType = typename AudioDevicePolicy::ContextType;

		// Audio Container types
		using AudioDeviceType = typename AudioDevicePolicy::AudioDeviceType;
		using AudioDeviceIdType = typename AudioDevicePolicy::AudioDeviceIdType;
		using AudioRingBufferType = typename AudioDevicePolicy::AudioRingBufferType;
		using AudioFrameCountType = typename AudioDevicePolicy::AudioFrameCountType;

		void Close()
		{
			Policy.Close();
		}

		[[nodiscard]] bool IsValid() const
		{
			return Policy.IsValid();
		}

		bool InitializeAudioContainer(ContextType* Context)
		{
			return Policy.InitializeAudioContainer(Context);
		}

		bool InitializeWithDeviceId(const AudioDeviceIdType* pDeviceId, int InSampleRate = 48000, int InNumChannels = 4)
		{
			return Policy.InitializeWithDeviceId(pDeviceId, InSampleRate, InNumChannels);
		}

		void WriteHapticData(const std::vector<std::int16_t>& vector)
		{
			Policy.WriteHapticData(vector);
		}
	};
} // namespace GamepadCore
