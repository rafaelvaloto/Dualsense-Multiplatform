<div align="center">

# 🎮 Dualsense-Multiplatform

### The Ultimate Cross-Platform DualSense & DualShock API
**Pure C++ • Zero Dependencies • Engine Agnostic**

[![Build Status](https://img.shields.io/github/actions/workflow/status/rafaelvaloto/Gamepad-Core/build.yml?style=for-the-badge&logo=github&label=Build&color=2ea44f)](https://github.com/rafaelvaloto/Gamepad-Core/actions)
[![CodeQL](https://img.shields.io/github/actions/workflow/status/rafaelvaloto/Gamepad-Core/build.yml?style=for-the-badge&logo=github&label=CodeQL&color=2ea44f)](https://github.com/rafaelvaloto/Gamepad-Core/security/code-scanning)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)](https://github.com/rafaelvaloto/Gamepad-Core/blob/main/LICENSE)

---

[Report Bug](https://github.com/rafaelvaloto/Gamepad-Core/issues) · [Suggest a Feature](https://github.com/rafaelvaloto/Gamepad-Core/pulls) · [Documentation](https://github.com/rafaelvaloto/Gamepad-Core/wiki) · [Security Policy](https://github.com/rafaelvaloto/Gamepad-Core/security/policy)

**Core Tech Stack**
<br>
[![C++20](https://img.shields.io/badge/C++-20-00599C.svg?style=for-the-badge&logo=c%2B%2B)](https://isocpp.org/)
[![CMake](https://img.shields.io/badge/CMake-3.20+-064F8C.svg?style=for-the-badge&logo=cmake)](https://cmake.org/)

**Supported Platforms**
<br>
![Windows](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![macOS](https://img.shields.io/badge/macOS-536878?style=for-the-badge&logo=apple&logoColor=white)
![PlayStation](https://img.shields.io/badge/PlayStation-003791?style=for-the-badge&logo=playstation&logoColor=white)

**Microcontrollers & SBCs**
<br>
![Raspberry Pi](https://img.shields.io/badge/Raspberry_Pi-C51A4A?style=for-the-badge&logo=raspberrypi&logoColor=white)
![ESP32](https://img.shields.io/badge/ESP32-E7352C?style=for-the-badge&logo=espressif&logoColor=white)
![Pico W](https://img.shields.io/badge/Pico_W-0087BE?style=for-the-badge&logo=raspberrypi&logoColor=white)

**Game Engine Ready**
<br>
![Unreal Engine](https://img.shields.io/badge/Unreal_Engine-313131?style=for-the-badge&logo=unrealengine&logoColor=white)
![Godot](https://img.shields.io/badge/Godot-478CBF?style=for-the-badge&logo=godotengine&logoColor=white)
![Unity](https://img.shields.io/badge/Unity-536878?style=for-the-badge&logo=unity&logoColor=white)
![O3DE](https://img.shields.io/badge/O3DE-FF6D00?style=for-the-badge&logo=op3n&logoColor=white)

---

**Works with any C++ project — Game Engines, Emulators, Desktop Apps, and more**

[Features](#-features) • [Examples](#-implementations--integrations) • [Installation](#-installation--submodules) • [Tests](#-tests) • [Integration](#minimal-example-standalone-c) • [Architecture](#-architecture) • [Contributing](#-contributing)

---

<p align="center">
	Download the sample app on Steam, or watch the demonstration video on YouTube:
</p>
<p align="center">
	<a href="https://rafaelvaloto.itch.io/audio-vibration-sample" title="On itchio"><img src="https://img.shields.io/badge/itchio-fa5c5c?style=for-the-badge&logo=data:image/svg%2bxml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIGhlaWdodD0iNTYiIHdpZHRoPSI1NiIgZmlsbD0iI2ZmZiIgdmlld0JveD0iMCAwIDI0NS4zNzEgMjIwLjczNiI+PHBhdGggZD0iTTMxLjk5IDEuMzY1QzIxLjI4NyA3LjcyLjIgMzEuOTQ1IDAgMzguMjk4djEwLjUxNkMwIDYyLjE0NCAxMi40NiA3My44NiAyMy43NzMgNzMuODZjMTMuNTg0IDAgMjQuOTAyLTExLjI1OCAyNC45MDMtMjQuNjIgMCAxMy4zNjIgMTAuOTMgMjQuNjIgMjQuNTE1IDI0LjYyIDEzLjU4NiAwIDI0LjE2NS0xMS4yNTggMjQuMTY1LTI0LjYyIDAgMTMuMzYyIDExLjYyMiAyNC42MiAyNS4yMDcgMjQuNjJoLjI0NmMxMy41ODYgMCAyNS4yMDgtMTEuMjU4IDI1LjIwOC0yNC42MiAwIDEzLjM2MiAxMC41OCAyNC42MiAyNC4xNjQgMjQuNjIgMTMuNTg1IDAgMjQuNTE1LTExLjI1OCAyNC41MTUtMjQuNjIgMCAxMy4zNjIgMTEuMzIgMjQuNjIgMjQuOTAzIDI0LjYyIDExLjMxMyAwIDIzLjc3My0xMS43MTQgMjMuNzczLTI1LjA0NlYzOC4yOThjLS4yLTYuMzU0LTIxLjI4Ny0zMC41OC0zMS45ODgtMzYuOTMzQzE4MC4xMTguMTk3IDE1Ny4wNTYtLjAwNSAxMjIuNjg1IDBjLTM0LjM3LjAwMy04MS4yMjguNTQtOTAuNjk3IDEuMzY1em02NS4xOTQgNjYuMjE3YTI4LjAyNSAyOC4wMjUgMCAwIDEtNC43OCA2LjE1NWMtNS4xMjggNS4wMTQtMTIuMTU3IDguMTIyLTE5LjkwNiA4LjEyMmEyOC40ODIgMjguNDgyIDAgMCAxLTE5Ljk0OC04LjEyNmMtMS44NTgtMS44Mi0zLjI3LTMuNzY2LTQuNTYzLTYuMDMybC0uMDA2LjAwNGMtMS4yOTIgMi4yNy0zLjA5MiA0LjIxNS00Ljk1NCA2LjAzN2EyOC41IDI4LjUgMCAwIDEtMTkuOTQ4IDguMTJjLS45MzQgMC0xLjkwNi0uMjU4LTIuNjkyLS41MjgtMS4wOTIgMTEuMzcyLTEuNTUzIDIyLjI0LTEuNzE2IDMwLjE2NGwtLjAwMi4wNDVjLS4wMiA0LjAyNC0uMDQgNy4zMzMtLjA2IDExLjkzLjIxIDIzLjg2LTIuMzYzIDc3LjMzNCAxMC41MiA5MC40NzMgMTkuOTY0IDQuNjU1IDU2LjcgNi43NzUgOTMuNTU1IDYuNzg4aC4wMDZjMzYuODU0LS4wMTMgNzMuNTktMi4xMzMgOTMuNTU0LTYuNzg4IDEyLjg4My0xMy4xNCAxMC4zMS02Ni42MTQgMTAuNTItOTAuNDc0LS4wMjItNC41OTYtLjA0LTcuOTA1LS4wNi0xMS45M2wtLjAwMy0uMDQ1Yy0uMTYyLTcuOTI2LS42MjMtMTguNzkzLTEuNzE1LTMwLjE2NS0uNzg2LjI3LTEuNzU3LjUyOC0yLjY5Mi41MjhhMjguNSAyOC41IDAgMCAxLTE5Ljk0OC04LjEyYy0xLjg2Mi0xLjgyMi0zLjY2Mi0zLjc2Ni00Ljk1NS02LjAzN2wtLjAwNi0uMDA0Yy0xLjI5NCAyLjI2Ni0yLjcwNSA0LjIxMy00LjU2MyA2LjAzMmEyOC40OCAyOC40OCAwIDAgMS0xOS45NDcgOC4xMjVjLTcuNzQ4IDAtMTQuNzc4LTMuMTEtMTkuOTA2LTguMTIzYTI4LjAyNSAyOC4wMjUgMCAwIDEtNC43OC02LjE1NSAyNy45OSAyNy45OSAwIDAgMS00LjczNiA2LjE1NSAyOC40OSAyOC40OSAwIDAgMS0xOS45NSA4LjEyNGMtLjI3IDAtLjU0LS4wMTItLjgxLS4wMmgtLjAwN2MtLjI3LjAwOC0uNTQuMDItLjgxMy4wMmEyOC40OSAyOC40OSAwIDAgMS0xOS45NS04LjEyMyAyNy45OTIgMjcuOTkyIDAgMCAxLTQuNzM2LTYuMTU1em0tMjAuNDg2IDI2LjQ5bC0uMDAyLjAxaC4wMTVjOC4xMTMuMDE3IDE1LjMyIDAgMjQuMjUgOS43NDYgNy4wMjgtLjczNyAxNC4zNzItMS4xMDUgMjEuNzIyLTEuMDk0aC4wMDZjNy4zNS0uMDEgMTQuNjk0LjM1NyAyMS43MjMgMS4wOTQgOC45My05Ljc0NyAxNi4xMzctOS43MyAyNC4yNS05Ljc0NmguMDE0bC0uMDAyLS4wMWMzLjgzMyAwIDE5LjE2NiAwIDI5Ljg1IDMwLjAwN0wyMTAgMTY1LjI0NGM4LjUwNCAzMC42MjQtMi43MjMgMzEuMzczLTE2LjcyNyAzMS40LTIwLjc2OC0uNzczLTMyLjI2Ny0xNS44NTUtMzIuMjY3LTMwLjkzNS0xMS40OTYgMS44ODQtMjQuOTA3IDIuODI2LTM4LjMxOCAyLjgyN2gtLjAwNmMtMTMuNDEyIDAtMjYuODIzLS45NDMtMzguMzE4LTIuODI3IDAgMTUuMDgtMTEuNSAzMC4xNjItMzIuMjY3IDMwLjkzNS0xNC4wMDQtLjAyNy0yNS4yMy0uNzc1LTE2LjcyNi0zMS40TDQ2Ljg1IDEyNC4wOEM1Ny41MzQgOTQuMDczIDcyLjg2NyA5NC4wNzMgNzYuNyA5NC4wNzN6bTQ1Ljk4NSAyMy41ODJ2LjAwNmMtLjAyLjAyLTIxLjg2MyAyMC4wOC0yNS43OSAyNy4yMTVsMTQuMzA0LS41NzN2MTIuNDc0YzAgLjU4NCA1Ljc0LjM0NiAxMS40ODYuMDhoLjAwNmM1Ljc0NC4yNjYgMTEuNDg1LjUwNCAxMS40ODUtLjA4di0xMi40NzRsMTQuMzA0LjU3M2MtMy45MjgtNy4xMzUtMjUuNzktMjcuMjE1LTI1Ljc5LTI3LjIxNXYtLjAwNmwtLjAwMy4wMDJ6IiBjb2xvcj0iIzAwMCIvPjwvc3ZnPg==&logoColor=white" alt="On itchio"></a>   
	<a href="https://store.steampowered.com/app/4746690/Audio_vibration_sample_bluetooth_ps5_controller/" title="On Steam"><img src="https://img.shields.io/badge/Steam-536878?style=for-the-badge&logo=steam&logoColor=white" alt="On Steam"></a>    
	<a href="https://youtu.be/JJFxJJESFUo?si=lhIcLWosU6UYANz9" title="Watch YouTube"><img src="https://img.shields.io/badge/YouTube-FF0000?style=for-the-badge&logo=YouTube&logoColor=white" alt="Watch YouTube"></a>
</p>

</div>

---
### 🚀 What is Dualsense-Multiplatform?

**Dualsense-Multiplatform** is a high-performance, policy-based C++ library that unlocks the **full potential** of Sony's DualSense and DualShock 4 controllers through direct HID communication. 

Unlike generic gamepad APIs (XInput, SDL, etc.), Gamepad-Core gives you **raw, low-level access** to advanced hardware features that standard drivers can't touch.

### 🌍 True Cross-Platform Architecture

Dualsense-Multiplatform is **engine-agnostic by design**. It is a pure C++ library that works anywhere C++20 is supported. 

The library leverages **policy-based design** to abstract platform-specific details. This zero-cost abstraction makes it trivial to extend support to new platforms or custom hardware without touching the core logic.

---

## ✨ Features

* **🏗️ Extensible Multi-Platform Architecture**
    Engine-agnostic C++20 design. Supporting new hardware is as simple as implementing the core connection interface, making it suitable for any environment—from PC to embedded systems.
* **🔌 Dynamic Connection (Hot-Swap)**
    Robust plug-and-play logic that automatically detects controller connection and disconnection in real-time.
* **⚡ High-Performance & Low-Latency**
    Optimized for minimal CPU overhead and memory footprint, ensuring zero impact on the main application loop.
* **🎮 Transparent Integration**
    Designed to coexist with existing system input managers without device conflicts or driver interference.
* **🎯 Adaptive Triggers**
    Precise low-level control over resistance, haptic effects, and vibration for R2/L2 triggers.
* **💡 Lightbar & LED Control**
    Programmatic control over the controller's LED colors and player indicators.
* **🎤 Smart Mute Logic**
    Automatic handling of the microphone mute LED state based on device status.
* **🎮 Multi-Controller Support**
    Native support for DualSense (Standard/Edge) and DualShock 4. The model-agnostic architecture is prepared for legacy hardware expansion, such as PS1 and PS2 models.

---


## 🏆 Implementations & Integrations

### 1. Unreal Engine — Primary Integration
**[Unreal-Dualsense](https://github.com/rafaelvaloto/Unreal-Dualsense)**

The flagship plugin bringing native DualSense support to UE5 via Blueprint and C++.
* ✅ Live Adaptive Trigger prototyping via Data Tables.
* ✅ Real-time Audio-to-Haptics submix processing.
* ✅ Native Input System integration for Force Feedback & Motion.

### 2. Raspberry Pico W — Microcontroller Integration
Demonstrating the extreme portability and architectural efficiency of the library, the same core logic used in AAA game engines runs perfectly on a **Pico W (264KB RAM / 2MB Flash)**.

**[🎥 Watch the example video on YouTube](https://www.youtube.com/watch?v=GgKDtwfS6v4)**

The Pico W implementation includes **complete support** for all advanced DualSense capabilities:

| **Input** | **Output (Haptics & More)** |
| :--- | :--- |
| **Motion:** Full 6-Axis Gyro & Accel | **Adaptive Triggers:** Weapon, Feedback & Buzz modes |
| **Touchpad:** Multi-touch & Coordinates | **Haptic Feedback:** Dual independent motor control |
| **System:** Battery & Charging status | **RGB Lightbar:** Full color & Player LED control |
| **Standard:** All 17 buttons + Analog sticks | **Architecture:** Production-ready C++20 |

*The Pico W implementation uses the exact same C++ core files as the Unreal and O3DE integrations, with zero logic changes.*

[👉 Check out the Pico W implementation](https://github.com/rafaelvaloto/Pico_W-Dualsense)


### 3. Other Prototypes & Mods

* **[O3DE-Dualsense](https://github.com/rafaelvaloto/o3de-dualsense)** — O3DE Gem integration.
* **[Godot-Dualsense](https://github.com/rafaelvaloto/Godot-Dualsense)** — GDExtension for Godot 4.x.
* **[Mod Audio Haptics](https://github.com/rafaelvaloto/Gaming-Mods-Dualsense)** — Session Skate Sim mod.

---

### Prerequisites

- **CMake** 3.20 or higher
- **C++20** compatible compiler (MSVC, GCC, Clang)
- **Ninja** (recommended) or Make
 
## 📦 Installation & Submodules

Depending on your project needs, you can clone **Gamepad-Core** in different ways. The library is designed to be modular, allowing you to include only what is necessary for your target environment.

### 1. 🍃 Minimal Version (Core Only)
**Ideal for:** Embedded systems (ESP32, Raspberry Pi Pico W, etc.), OS-level applications, engine integrations, or resource-constrained environments where external audio libraries are not required.

* **Features:** Basic HID communication, buttons, sticks, triggers (feedback/resistance), and lightbar control.

*   **Engine & App Ready:** Designed as a lightweight backend for custom engines (Unreal, Unity via Native C++) or standalone desktop applications.

*   **Size:** Very small footprint with zero external dependencies.

*   **Flexibility:** This core version serves as the foundation for all implementations; you can manually link your own OS-native audio API if needed.

```bash
git clone https://github.com/rafaelvaloto/Gamepad-Core.git
```

### 2. 🛠️ Developer Version (Full + Tests)
**Ideal for:** Contributors, library development, or if you want to run the integration tests on your hardware.
*   **Features:** Everything in Standard + the complete Integration Test suite.

```bash
git clone --recursive https://github.com/rafaelvaloto/Gamepad-Core.git
```

If you have already cloned the repository without submodules, run:

```bash
git submodule update --init --recursive
```

---

## 🧪 Tests

The fastest way to verify Gamepad-Core on your hardware is by running the **Integration Tests**. This requires cloning the repository with all submodules.

```bash

# Configure and build
cmake -S . -B cmake-build-release -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=ON
cmake --build cmake-build-release --target test-gamepad-outputs -j

# Run (make sure your DualSense/DualShock is connected)
./cmake-build-release/Tests/Integration/test-gamepad-inputs
```

### 🎮 Test Controls
Once the console application is running, use your DualSense to test the features:

### Input Testing (test-gamepad-inputs)
The `test-gamepad-inputs` executable allows you to monitor controller data in real-time. To avoid log misalignment due to terminal width limits, **it is highly recommended to test one parameter at a time**.

**Usage:**
```bash
./cmake-build-release/Tests/Integration/test-gamepad-inputs [flags]
```

**Available Flags:**

| Flag | Description |
| :--- | :--- |
| `--buttons` | Displays digital button states (Cross, Circle, etc.) |
| `--analogs` | Displays stick and trigger positions (Default if no flags) |
| `--touch` | Displays detailed touchpad data (ID, Fingers, Position, Velocity) |
| `--sensors` | Displays Motion Sensor data (Gyroscope and Accelerometer) |

*Note: When `--touch` or `--sensors` are passed, the respective hardware features are automatically enabled on the controller.*

---

### Output Testing (test-gamepad-outputs)
The `test-gamepad-outputs` executable allows you to test various controller feedback mechanisms, including vibrations, lightbar colors, and adaptive triggers.

**Usage:**
```bash
./cmake-build-release/Tests/Integration/test-gamepad-outputs
```

#### [ FACE BUTTONS ]
| Button | Action | Effect |
| :--- | :--- | :--- |
| **❌ Cross** | Vibration/LED | Heavy Rumble + 🔴 Red Light |
| **⭕ Circle** | Vibration/LED | Soft Rumble + 🔵 Blue Light |
| **🟥 Square** | Trigger Effect | Activates **GameCube-style** trigger snap on **R2** |
| **🔺 Triangle** | Reset | **Stops all effects** (Panic Button) |

#### [ D-PAD & SHOULDERS (Trigger Mods) ]
| Button | Hand | Effect |
| :--- | :--- | :--- |
| **L1** | **L2** | **Gallop** Effect (Vibration on trigger) |
| **R1** | **R2** | **Machine Gun** Effect (Fast vibration) |
| **⬆️ Up** | **L2** | **Feedback** (Rigid Resistance) |
| **⬇️ Down** | **R2** | **Bow** (String Tension) |
| **⬅️ Left** | **R2** | **Weapon** (Semi-Automatic) |
| **➡️ Right** | **R2** | **Automatic Gun** (Buzzing) |

## Break Changes v1.0.0
```cpp
// Scan for connected devices
Registry->PlugAndPlay(DeltaTime);
auto* Gamepad = Registry->GetLibrary(0)

if (Gamepad->IsConnected())
{
    if (auto* Lightbar = Gamepad->GetIGamepadLightbar())
    {
       Lightbar->SetLightbar({0, 255, 0});
    }
    
    if (auto* Trigger = Gamepad->GetIGamepadTrigger())
    {
    }
    
    // ⚠️ REQUIRED: Update output to apply all changes
    gamepad->UpdateOutput();
}

// Available methods for retrieving interfaces.
IGamepadTouch* GetIGamepadTouch() override { return this; }
IGamepadTrigger* GetIGamepadTrigger() override { return this; }
IGamepadHaptics* GetIGamepadHaptics() override { return this; }
IGamepadLightbar* GetIGamepadLightbar() override { return this; }
IGamepadRumbles* GetIGamepadRumbles() override { return this; }
IGamepadSensors* GetIGamepadSensors() override { return this; }
IGamepadSettings* GetIGamepadSettings() override { return this; }
```

## Minimal Example (Standalone C++)

```cpp
#include "GCore/Templates/TBasicDeviceRegistry.h"

// 1. Choose your platform policy
#ifdef _WIN32
    #include "Platform/windows/windows_hardware_policy.h"
    using platform_hardware = windows_platform::windows_hardware;
#else
    #include "Platform/linux/linux_hardware_policy.h"
    using platform_hardware = linux_platform::linux_hardware;
#endif

// 2. Define your registry policy
#include "Examples/Adapters/Tests/test_device_registry_policy.h"
using DeviceRegistry = GamepadCore::TBasicDeviceRegistry<Test_DeviceRegistryPolicy>;

int main() {
    // Initialize hardware layer
    auto Hardware = std::make_unique<HardwareInfo>();
    IPlatformHardwareInfo::SetInstance(std::move(Hardware));

    // Create device registry
    auto Registry = std::make_unique<DeviceRegistry>();

    // Game loop
    while (true) {
        float DeltaTime = 0.016f; // 60 FPS
        
        // Scan for connected devices
        Registry->PlugAndPlay(DeltaTime);

        // Get first connected gamepad
        if (auto* Gamepad = Registry->GetLibrary(0)) {
    if (Gamepad->IsConnected()) {
                // Update input state
                Gamepad->UpdateInput(DeltaTime);
                
                // Read button state
                auto Context = Gamepad->GetMutableDeviceContext();
                auto Input = Context->GetInputState();
                
                if (Input.bCross) {
                    // Trigger haptic feedback
                    Gamepad->GetIGamepadLightbar()->SetLightbar({255, 0, 0});
                    // Apply vibration
                    Gamepad->GetIGamepadRumbles()->SetRumble(255, 128);
                    
                    // ⚠️ REQUIRED: Update output to apply all changes
                    Gamepad->UpdateOutput();
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds((int)(DeltaTime * 1000)));
    }
}
```

This design makes it trivial to support **custom platforms** (e.g., PlayStation SDK, proprietary embedded systems) without touching core logic.


## 🧩 Architecture

Gamepad-Core follows **strict separation of concerns** to ensure portability and extensibility:

```
┌─────────────────────────────────────────────────────────────┐
│                    Your Application                         │
│              (Game Engine, Desktop App, Tool)               │
└────────────────────────┬────────────────────────────────────┘
                         │
         ┌───────────────┴───────────────┐
         │   Adapter Layer (Policy)      │  ◄── You implement this
         │  (Engine-specific bindings)   │      (or use examples)
         └───────────────┬───────────────┘
                         │
         ┌───────────────┴───────────────┐
         │      GCore (Abstract)         │
         │  • Device Registry            │  ◄── Pure C++, stable API
         │  • ISonyGamepad Interface     │
         │  • IGamepadTrigger Interface  │
         └───────────────┬───────────────┘
                         │
         ┌───────────────┴───────────────┐
         │   GImplementations (Drivers)  │
         │  • DualSense HID Protocol     │  ◄── Hardware-specific
         │  • DualShock 4 HID Protocol   │
         └───────────────┬───────────────┘
                         │
         ┌───────────────┴───────────────┐
         │   Platform Policy (OS/HAL)    │  ◄── OS-specific I/O
         │  • Windows (SetupAPI + HID)   │
         │  • Linux (HIDAPI)             │
         │  • macOS (IOKit)              │
         │  • Custom (PS5 SDK, etc.)     │
         └───────────────────────────────┘
```
## 🎵 Audio Pipeline — How It Works

Gamepad-Core provides a **complete audio-to-haptics and audio-to-speaker pipeline**.  Here's how the data flows from your application to the DualSense hardware:

```aiignore
┌─────────────────────────────────────────────────────────────┐
│                    YOUR APPLICATION                         │
│  • Captures audio (game sounds, music, etc.)                │
│  • Mixes audio channels                                     │
│  • Applies effects/filters                                  │
└──────────────────────┬──────────────────────────────────────┘
                       │ (sends audio buffer)
                       ▼
┌─────────────────────────────────────────────────────────────┐
│                   GAMEPAD-CORE LIB                          │
│  • Receives audio buffer                                    │
│  • Converts to haptic commands (for haptics)                │
│  • Encodes for speaker output (for speaker)                 │
│  • Sends via HID (USB/Bluetooth)                            │
└──────────────────────┬──────────────────────────────────────┘
                       │ (HID commands)
                       ▼
┌─────────────────────────────────────────────────────────────┐
│                   DUALSENSE HARDWARE                        │
│  • Vibration motors (haptics)                               │
│  • Built-in speaker                                         │
└─────────────────────────────────────────────────────────────┘
```

---

## 🤝 Contributing

- Add support for a new platform (e.g., FreeBSD, Android)
- Improve documentation or examples
- Optimize HID communication
- Report bugs or suggest features

Feel free to open an **Issue** or submit a **Pull Request**. 

### Guidelines

1. Follow the existing code style (use `clang-format`)
2. Test your changes with a physical controller
3. Update documentation if you add new features
4. Keep commits focused and well-described

---

## ⭐ Credits and Acknowledgments

The foundation of this plugin was built upon the research and code from several amazing projects in the community:

* [DualSense on Windows API](https://github.com/Ohjurot/DualSense-Windows) - Initial DS5 implementation logic.
* [Nielk1 on GIST](https://gist.github.com/Nielk1/6d54cc2c00d2201ccb8c2720ad7538db) - HID report structures.
* [DualSenseAPI](https://github.com/BadMagic100/DualSenseAPI/tree/master) - Hardware communication references.
* [flok pydualsense](https://github.com/flok/pydualsense) - Feature report research.
* [SAxense](https://github.com/egormanga/SAxense) - Base for Bluetooth Audio Haptics.
* [Awalol/DS5Dongle](https://github.com/awalol/DS5Dongle) - Reference **Bluetooth Audio (Headset/Speaker)** opus codec and buffer sizes.
* [miniaudio](https://github.com/mackron/miniaudio) - Audio playback and conversion library.
* [Ryochan7/DS4Windows](https://github.com/Ryochan7/DS4Windows) - Industry standard for DualShock/DualSense on Windows.
* [linux/drivers/hid/hid-playstation.c](https://github.com/torvalds/linux/blob/master/drivers/hid/hid-playstation.c#L1709) - Reference for calibration, gyroscope, and Linux driver standards.

Special thanks to the community members who helped improve this plugin:

* **[yncat](https://github.com/yncat)**: For the extensive research and implementation logic regarding **USB Audio Haptics**, which was crucial for supporting high-fidelity haptics via USB ([Issue #105](https://github.com/rafaelvaloto/Unreal-Dualsense/issues/105)).

---

## ⚖️ Legal & Trademarks

This software is an **independent project** and is **not affiliated** with Sony Interactive Entertainment Inc., Epic Games, Unity Technologies, Godot Engine, or any of their subsidiaries.

**Trademarks belong to their respective owners:**

- **Sony:** PlayStation, DualSense, DualShock are trademarks of Sony Interactive Entertainment Inc.
- **Microsoft:** Windows, Xbox are trademarks of Microsoft Corporation
- **Apple:** macOS is a trademark of Apple Inc.
- **Epic Games:** Unreal Engine is a trademark of Epic Games, Inc. 
- **Unity:** Unity is a trademark of Unity Technologies
- **Godot:** Godot and the Godot logo are trademarks of the Godot Engine project

---

<div align="center">

[⬆ Back to Top](#-dualsense-multiplatform)

<br>


This project is licensed under the **MIT License**. See the `LICENSE` file for details.

Copyright (c) 2026 **Rafael Valoto**

</div>
