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
![macOS](https://img.shields.io/badge/macOS-000000?style=for-the-badge&logo=apple&logoColor=white)
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
![Unity](https://img.shields.io/badge/Unity-000000?style=for-the-badge&logo=unity&logoColor=white)
![O3DE](https://img.shields.io/badge/O3DE-FF6D00?style=for-the-badge&logo=op3n&logoColor=white)

---

**Works with any C++ project — Game Engines, Emulators, Desktop Apps, and more**

[Features](#-features) • [Examples](#-implementations--integrations) • [Installation](#-installation--submodules) • [Tests](#-tests) • [Integration](#minimal-example-standalone-c) • [Architecture](#-architecture) • [Contributing](#-contributing)

The core library provides high-performance HID communication with Sony's DualSense and DualShock 4 controllers.
<h3 align="center"><a href="https://youtu.be/JJFxJJESFUo?si=TlucVlhuunGG99Id" target="_blank">🎥 Watch the video here </a></h3>
</div>

> [!IMPORTANT]
> **API Migration Notice (v1.0.0+):** To improve clarity and architectural separation, gamepad features (Lightbar, Triggers, Haptics, etc.) are now accessed via specialized interfaces. 
> Use the new helper methods (e.g., `GetIGamepadLightbar()`) to retrieve the specific interface before calling its functions.
> [See more](#break-changes-v100)

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
* [Ryochan7/DS4Windows](https://github.com/Ryochan7/DS4Windows) - Industry standard for DualShock/DualSense on Windows.
* [linux/drivers/hid/hid-playstation.c](https://github.com/torvalds/linux/blob/master/drivers/hid/hid-playstation.c#L1709) - Reference for calibration, gyroscope, and Linux driver standards.

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
