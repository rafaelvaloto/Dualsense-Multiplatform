// Copyright (c) 2026 Rafael Valoto. All Rights Reserved.
// Project: GamepadCore
// Description: Cross-platform library for DualSense and generic gamepad input support.
// Targets: Windows, Linux, macOS.
#pragma once
#include "GCore/Types/DSCoreTypes.h"
#include "GCore/Types/Structs/Context/InputContext.h"

#define DS_TOUCHPAD_WIDTH 1920
#define DS_TOUCHPAD_HEIGHT 1080
#define DS4_TOUCHPAD_WIDTH 1920
#define DS4_TOUCHPAD_HEIGHT 942

namespace FGamepadTouch
{
	inline void ProcessTouchDualSense(const unsigned char* HIDInput, FInputContext* Input)
	{
		if (Input->TouchRadius.X == 0.0f || Input->TouchRadius.Y == 0.0f)
		{
			Input->TouchRadius = {DS_TOUCHPAD_WIDTH, DS_TOUCHPAD_HEIGHT};
		}

		const unsigned char* p0 = &HIDInput[0x20];
		const unsigned char* p1 = &HIDInput[0x24];

		auto DecodeX = [](const unsigned char* P) { return static_cast<float>(((P[2] & 0x0F) << 8) | P[1]); };
		auto DecodeY = [](const unsigned char* P) { return static_cast<float>((P[3] << 4) | ((P[2] & 0xF0) >> 4)); };

		const bool bFirstFinger = (p0[0] & 0x80) == 0;
		const bool bSecondFinger = (p1[0] & 0x80) == 0;

		Input->TouchId = 1;
		Input->bIsTouching = bFirstFinger || bSecondFinger;
		Input->TouchFingerCount = (bFirstFinger ? 1 : 0) + (bSecondFinger ? 1 : 0);

		if (bFirstFinger)
		{
			Input->TouchPosition = {DecodeX(p0), DecodeY(p0)};
		}
		else if (bSecondFinger)
		{
			Input->TouchPosition = {DecodeX(p1), DecodeY(p1)};
		}

		if (bSecondFinger)
		{
			Input->TouchRelative = {DecodeX(p1), DecodeY(p1)};
		}
	}

	inline void ProcessTouchDualShock(const unsigned char* HIDInput, FInputContext* Input, EDSDeviceConnection ConnectionType)
	{
		if (Input->TouchRadius.X == 0.0f || Input->TouchRadius.Y == 0.0f)
		{
			Input->TouchRadius = {DS4_TOUCHPAD_WIDTH, DS4_TOUCHPAD_HEIGHT};
		}

		(void)ConnectionType;
		constexpr int TouchReportOffset = 32;

		constexpr int ReportSize = 9;
		constexpr int MaxReports = 3;
		int NumReports = HIDInput[TouchReportOffset];
		if (NumReports > MaxReports)
		{
			NumReports = MaxReports;
		}

		Input->TouchId = 1;

		if (NumReports == 0)
		{
			Input->bIsTouching = false;
			Input->TouchFingerCount = 0;
			return;
		}

		// Use the most recent report.
		const unsigned char* Report = &HIDInput[TouchReportOffset + 1 + (NumReports - 1) * ReportSize];
		const unsigned char* p0 = Report + 1;
		const unsigned char* p1 = p0 + 4;

		auto DecodeX = [](const unsigned char* P) { return static_cast<float>(((P[2] & 0x0F) << 8) | P[1]); };
		auto DecodeY = [](const unsigned char* P) { return static_cast<float>((P[3] << 4) | ((P[2] & 0xF0) >> 4)); };

		const bool bFirstFinger = (p0[0] & 0x80) == 0;
		const bool bSecondFinger = (p1[0] & 0x80) == 0;

		Input->bIsTouching = bFirstFinger || bSecondFinger;
		Input->TouchFingerCount = (bFirstFinger ? 1 : 0) + (bSecondFinger ? 1 : 0);

		if (bFirstFinger)
		{
			Input->TouchPosition = {DecodeX(p0), DecodeY(p0)};
		}
		else if (bSecondFinger)
		{
			Input->TouchPosition = {DecodeX(p1), DecodeY(p1)};
		}

		if (bSecondFinger)
		{
			Input->TouchRelative = {DecodeX(p1), DecodeY(p1)};
		}
	}

} // namespace FGamepadTouch
