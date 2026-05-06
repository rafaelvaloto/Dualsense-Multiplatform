// Copyright (c) 2025 Rafael Valoto. All Rights Reserved.
// Project: GamepadCore
// Description: Cross-platform library for DualSense and generic gamepad input support.
// Targets: Windows, Linux, macOS.

#include "GImplementations/Libraries/DualSense/DualSenseLibrary.h"
#include "GCore/Interfaces/IAudioDevice.h"
#include "GCore/Interfaces/IPlatformHardware.h"
#include "GCore/Types/ECoreGamepad.h"
#include "GCore/Types/Structs/Context/DeviceContext.h"
#include "GCore/Utils/CR32.h"
#include "GCore/Utils/SoDefines.h"
#include "GImplementations/Utils/GamepadInput.h"
#include "GImplementations/Utils/GamepadOutput.h"
#include "GImplementations/Utils/GamepadSensors.h"
#include "GImplementations/Utils/GamepadTouch.h"
#include "GImplementations/Utils/GamepadTrigger.h"
#include <algorithm>
#include <iomanip>
#include <iostream>

using namespace FDualSenseTriggerComposer;

void FDualSenseLibrary::SetVibration(std::uint8_t LeftRumble,
                                     std::uint8_t RightRumble)
{
	FDeviceContext* Context = GetMutableDeviceContext();
	if (!Context)
	{
		return;
	}

	FOutputContext* HidOutput = &Context->Output;
	if (HidOutput->Rumbles.Left != LeftRumble ||
	    HidOutput->Rumbles.Right != RightRumble)
	{
		HidOutput->Rumbles = {LeftRumble, RightRumble};
	}
}

void FDualSenseLibrary::ResetLights()
{
	FDeviceContext* Context = GetMutableDeviceContext();
	if (!Context)
	{
		return;
	}

	FOutputContext* HidOutput = &Context->Output;
	if (HidOutput->Lightbar.G == 0 && HidOutput->Lightbar.B == 0 &&
	    HidOutput->Lightbar.R == 0)
	{
		HidOutput->Lightbar.B = 255;
	}

	HidOutput->PlayerLed.Led = static_cast<unsigned char>(EDSPlayer::One);
}

void FDualSenseLibrary::SetLightbar(DSCoreTypes::FDSColor Color)
{
	SetLightbarFlash(Color, 0.0f, 0.0f);
}

void FDualSenseLibrary::SetLightbarFlash(DSCoreTypes::FDSColor Color, float, float)
{
	FDeviceContext* Context = GetMutableDeviceContext();
	if (!Context)
	{
		return;
	}
	FOutputContext* HidOutput = &Context->Output;
	HidOutput->Lightbar.R = Color.R;
	HidOutput->Lightbar.G = Color.G;
	HidOutput->Lightbar.B = Color.B;
}

bool FDualSenseLibrary::Initialize(const FDeviceContext& Context)
{
	SetDeviceContexts(Context);
	FDeviceContext* DSContext = GetMutableDeviceContext();
	if (!DSContext)
	{
		return false;
	}
	if (DSContext->ConnectionType == EDSDeviceConnection::Bluetooth)
	{
		{
			gc_lock::lock_guard<gc_lock::mutex> LockGuard(DSContext->OutputMutex);
			unsigned char* MutableBuffer = DSContext->GetRawOutputBuffer();
			size_t Padding = 2;
			MutableBuffer[0] = 0x31;
			MutableBuffer[1] = 0x02;

			unsigned char* Output = &MutableBuffer[Padding];
			Output[0] = 0xFF;
			Output[1] = 0xFF;
			Output[38] = 0x00;
			Output[44] = 0x00;
			Output[45] = 0x00;
			Output[46] = 0x00;
			if (DSContext->ConnectionType == EDSDeviceConnection::Bluetooth)
			{
				const auto CrcChecksum = GCoreUtils::CR32::Compute(MutableBuffer, 74);
				MutableBuffer[0x4A] = static_cast<unsigned char>((CrcChecksum & 0x000000FF) >> 0UL);
				MutableBuffer[0x4B] = static_cast<unsigned char>((CrcChecksum & 0x0000FF00) >> 8UL);
				MutableBuffer[0x4C] = static_cast<unsigned char>((CrcChecksum & 0x00FF0000) >> 16UL);
				MutableBuffer[0x4D] = static_cast<unsigned char>((CrcChecksum & 0xFF000000) >> 24UL);
			}

			IPlatformHardware::Get().Write(DSContext);
			gc_sync::sleep_ms(50);
		}

		DSContext->Output.Feature.VibrationMode = 0xFF;
		DSContext->Output.Feature.FeatureMode = 0x57;
		DSContext->Output.Lightbar = {100, 100, 0};
		UpdateOutput();
		gc_sync::sleep_ms(50);

		// Audio haptics bluetooth
		DSContext->BufferHapitcs[0] = 0x36;
		DSContext->BufferHapitcs[1] = 0x00;
		DSContext->BufferHapitcs[2] = 0x91;
		DSContext->BufferHapitcs[3] = 0x07;
		DSContext->BufferHapitcs[4] = 0xfe;
		DSContext->BufferHapitcs[5] = 0b11111111; // frequency filters  (?)
		DSContext->BufferHapitcs[6] = 0b11111111; // ...
		DSContext->BufferHapitcs[7] = 0b11111111; // ...
		DSContext->BufferHapitcs[8] = 0b11111111; // ...
		DSContext->BufferHapitcs[9] = 0b00111111; // sync times (?)
		// DSContext->BufferHapitcs[9] = 0b01000000; // sync times (?)
		return true;
	}

	ResetLights();
	constexpr std::uint8_t FeatureMode = 0x57;
	DSContext->Output.Feature = {FeatureMode, 0xFF, 0x00, 0x00};
	UpdateOutput();
	return true;
}

void FDualSenseLibrary::UpdateInput(float /*Delta*/)
{
	FDeviceContext* Context = GetMutableDeviceContext();
	if (!Context || !Context->IsConnected)
	{
		return;
	}

	IPlatformHardware::Get().Read(Context);
	FInputContext* InputToFill = Context->GetBackBuffer();
	const size_t Padding =
	    Context->ConnectionType == EDSDeviceConnection::Bluetooth ? 2 : 1;

	using namespace FGamepadInput;
	DualSenseRaw(&Context->Buffer[Padding], InputToFill);

	if (Context->bEnableGesture || Context->bEnableTouch)
	{
		using namespace FGamepadTouch;
		ProcessTouchDualSense(&Context->Buffer[Padding], InputToFill);
	}

	if (Context->bEnableAccelerometerAndGyroscope)
	{
		DSCoreTypes::DSVector3D GyroDeg;
		DSCoreTypes::DSVector3D AccelG;

		using namespace FGamepadSensors;
		ProcessMotionDualSense(&Context->Buffer[Padding], Context->Calibration, GyroDeg, AccelG);

		InputToFill->Gyroscope = GyroDeg;
		InputToFill->Accelerometer = AccelG;
	}

	static bool bLastMuteState = false;
	if (InputToFill->bMute && !bLastMuteState)
	{
		Context->Output.Audio.MicStatus = (Context->Output.Audio.MicStatus == 0) ? 1 : 0;
		UpdateOutput();
	}
	bLastMuteState = InputToFill->bMute;

	Context->SwapInputBuffers();
}

void FDualSenseLibrary::DualSenseSettings(std::uint8_t bIsMic, std::uint8_t bIsHeadset, std::uint8_t bIsSpeaker, std::uint8_t MicVolume, std::uint8_t AudioVolume, std::uint8_t RumbleMode, std::uint8_t RumbleReduce, std::uint8_t TriggerReduce)
{
	FDeviceContext* Context = GetMutableDeviceContext();
	if (!Context || !Context->IsConnected)
	{
		return;
	}

	Context->Output.Audio.MicStatus = bIsMic;
	Context->Output.Audio.MicVolume = MicVolume;
	Context->Output.Audio.HeadsetVolume = AudioVolume;
	Context->Output.Audio.SpeakerVolume = AudioVolume;

	Context->Output.Audio.Mode = 0x05;
	if (bIsHeadset == 1 && bIsSpeaker == 1)
	{
		Context->Output.Audio.Mode = 0x21;
	}
	else if (bIsHeadset == 0 && bIsSpeaker == 1)
	{
		Context->Output.Audio.Mode = 0x31;
	}

	Context->Output.Feature = {Context->Output.Feature.FeatureMode, RumbleMode, RumbleReduce, TriggerReduce};
}

void FDualSenseLibrary::UpdateOutput()
{
	FDeviceContext* Context = GetMutableDeviceContext();
	if (!Context || !Context->IsConnected)
	{
		return;
	}
	FGamepadOutput::OutputDualSense(Context);
}

void FDualSenseLibrary::SetResistance(std::uint8_t StartZones,
                                      std::uint8_t Strength,
                                      const EDSGamepadHand& Hand)
{
	FDeviceContext* Context = GetMutableDeviceContext();
	if (!Context || !Context->IsConnected)
	{
		return;
	}
	Resistance(Context, StartZones, Strength, Hand);
}

void FDualSenseLibrary::SetGalloping23(std::uint8_t StartPosition,
                                       std::uint8_t EndPosition,
                                       std::uint8_t FirstFoot,
                                       std::uint8_t SecondFoot,
                                       std::uint8_t Frequency,
                                       const EDSGamepadHand& Hand)
{
	FDeviceContext* Context = GetMutableDeviceContext();
	if (!Context || !Context->IsConnected)
	{
		return;
	}
	Galloping23(Context, StartPosition, EndPosition, FirstFoot, SecondFoot,
	            Frequency, Hand);
}

void FDualSenseLibrary::StopTrigger(const EDSGamepadHand& Hand)
{
	FDeviceContext* Context = GetMutableDeviceContext();
	if (!Context || !Context->IsConnected)
	{
		return;
	}
	Off(Context, Hand);
}

void FDualSenseLibrary::SetGameCube(const EDSGamepadHand& Hand)
{
	FDeviceContext* Context = GetMutableDeviceContext();
	if (!Context || !Context->IsConnected)
	{
		return;
	}
	GameCube(Context, Hand);
}

void FDualSenseLibrary::SetBow22(std::uint8_t StartZone, std::uint8_t SnapBack,
                                 const EDSGamepadHand& Hand)
{
	FDeviceContext* Context = GetMutableDeviceContext();
	if (!Context || !Context->IsConnected)
	{
		return;
	}
	Context->bOverrideTriggerBytes = false;
	Bow22(Context, StartZone, SnapBack, Hand);
}

void FDualSenseLibrary::SetWeapon25(std::uint8_t StartZone,
                                    std::uint8_t Amplitude,
                                    std::uint8_t Behavior, std::uint8_t Trigger,
                                    const EDSGamepadHand& Hand)
{
	FDeviceContext* Context = GetMutableDeviceContext();
	if (!Context || !Context->IsConnected)
	{
		return;
	}
	Weapon25(Context, StartZone, Amplitude, Behavior, Trigger, Hand);
}

void FDualSenseLibrary::SetMachineGun26(std::uint8_t StartZone,
                                        std::uint8_t Behavior,
                                        std::uint8_t Amplitude,
                                        std::uint8_t Frequency,
                                        const EDSGamepadHand& Hand)
{
	FDeviceContext* Context = GetMutableDeviceContext();
	if (!Context || !Context->IsConnected)
	{
		return;
	}
	MachineGun26(Context, StartZone, Behavior, Amplitude, Frequency, Hand);
}

void FDualSenseLibrary::SetMachine27(std::uint8_t StartZone,
                                     std::uint8_t BehaviorFlag,
                                     std::uint8_t Force, std::uint8_t Amplitude,
                                     std::uint8_t Period,
                                     std::uint8_t Frequency,
                                     const EDSGamepadHand& Hand)
{
	FDeviceContext* Context = GetMutableDeviceContext();
	if (!Context || !Context->IsConnected)
	{
		return;
	}
	Machine27(Context, StartZone, BehaviorFlag, Force, Amplitude, Period,
	          Frequency, Hand);
}

void FDualSenseLibrary::SetCustomTrigger(
    const EDSGamepadHand& Hand, const std::vector<std::uint8_t>& HexBytes)
{
	FDeviceContext* Context = GetMutableDeviceContext();
	if (!Context || !Context->IsConnected)
	{
		return;
	}
	CustomTrigger(Context, Hand, HexBytes);
}

void FDualSenseLibrary::SetPlayerLed(EDSPlayer Led, std::uint8_t Brightness)
{
	FDeviceContext* Context = GetMutableDeviceContext();
	if (!Context || !Context->IsConnected)
	{
		return;
	}
	FOutputContext* HidOutput = &Context->Output;
	if ((HidOutput->PlayerLed.Led != static_cast<unsigned char>(Led)) || (HidOutput->PlayerLed.Brightness !=
	                                                                      static_cast<unsigned char>(Brightness)))
	{
		HidOutput->PlayerLed.Led = static_cast<unsigned char>(Led);
		HidOutput->PlayerLed.Brightness = static_cast<unsigned char>(Brightness);
	}
}

void FDualSenseLibrary::SetMicrophoneLed(EDSMic Led)
{
	FDeviceContext* Context = GetMutableDeviceContext();
	if (!Context || !Context->IsConnected)
	{
		return;
	}
	if (FOutputContext* HidOutput = &Context->Output; HidOutput->Audio.MicStatus != static_cast<unsigned char>(Led))
	{
		HidOutput->Audio.MicStatus = static_cast<unsigned char>(Led);
	}
}

void FDualSenseLibrary::AudioHapticUpdate(const std::vector<std::uint8_t>& HapticsData)
{
	FDeviceContext* Context = GetMutableDeviceContext();
	if (!Context || !Context->IsConnected)
	{
		return;
	}

	{
		gc_lock::lock_guard<gc_lock::mutex> LockGuard(Context->AudioMutex);
		unsigned char* Audio = &Context->BufferHapitcs[0];
		Audio[10] = (AudioVibrationSequence++) & 0xFF;
		Audio[11] = 0x92;
		Audio[12] = 0x40;
		if (!HapticsData.empty())
		{
			std::memcpy(&Audio[13], HapticsData.data(), HapticsData.size());
		}
		FGamepadOutput::SendAudioHapticAdvanced(Context, 394);
	}
}

void FDualSenseLibrary::AudioHapticUpdate(const std::vector<std::uint8_t>& HapticsData, const std::vector<std::uint8_t>& AudioData)
{
	FDeviceContext* Context = GetMutableDeviceContext();
	if (!Context || !Context->IsConnected)
	{
		return;
	}

	{
		gc_lock::lock_guard<gc_lock::mutex> LockGuard(Context->AudioMutex);
		unsigned char* Audio = &Context->BufferHapitcs[0];
		Audio[10] = (AudioVibrationSequence++) & 0xFF;
		Audio[11] = 0x92;
		Audio[12] = 0x40;
		Audio[77] = 0x95;
		Audio[78] = AudioData.size();
		if (!HapticsData.empty())
		{
			std::memcpy(&Audio[13], HapticsData.data(), HapticsData.size());
		}
		if (!AudioData.empty())
		{
			std::memcpy(&Audio[79], AudioData.data(), AudioData.size());
		}
		FGamepadOutput::SendAudioHapticAdvanced(Context, 394);
	}
}

void FDualSenseLibrary::AudioHapticUpdate(const std::vector<std::int16_t>& AudioData)
{
	FDeviceContext* Context = GetMutableDeviceContext();
	if (!Context || !Context->IsConnected)
	{
		return;
	}
	IAudioDevice::Get().ProcessAudioHaptic(Context, AudioData);
}
