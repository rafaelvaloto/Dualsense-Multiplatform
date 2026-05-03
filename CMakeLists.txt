cmake_minimum_required(VERSION 3.20)
set(CMAKE_POLICY_DEFAULT_CMP0000 NEW)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
include(FetchContent)

# Main project name
project(GamepadCore LANGUAGES C CXX)

# Shared test/CI options (defined early so they can affect dependency setup)
option(AUTOMATED_TESTS "Enable automated tests (timeout for CI)" OFF)

# Option to enable/disable audio support (Opus + miniaudio)
option(GAMEPAD_CORE_ENABLE_AUDIO "Enable audio support (requires Opus)" ON)

set(GAMEPAD_CORE_AUDIO_ENABLED_BUILD ${GAMEPAD_CORE_ENABLE_AUDIO})
if(AUTOMATED_TESTS)
    set(GAMEPAD_CORE_AUDIO_ENABLED_BUILD OFF)
    message(STATUS "GamepadCore: AUTOMATED_TESTS=ON -> audio dependencies disabled")
endif()

if(GAMEPAD_CORE_AUDIO_ENABLED_BUILD)
    # Opus for Bluetooth audio compression
    FetchContent_Declare(
            opus
            GIT_REPOSITORY https://github.com/xiph/opus.git
            GIT_TAG        v1.4
    )

    set(OPUS_BUILD_PROGRAMS OFF CACHE BOOL "" FORCE)
    set(OPUS_BUILD_TESTING OFF CACHE BOOL "" FORCE)

    FetchContent_MakeAvailable(opus)
    message(STATUS "GamepadCore: Opus ENABLED")
else()
    message(STATUS "GamepadCore: Opus DISABLED (set GAMEPAD_CORE_ENABLE_AUDIO=ON to enable)")
endif()

# --- Global C++ Settings ---
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable Unicode support for Windows targets
if(WIN32)
    add_compile_definitions(UNICODE _UNICODE)
endif()

add_subdirectory(Source)


# ============================================
# Audio Module (opcional)
# ============================================
if(GAMEPAD_CORE_AUDIO_ENABLED_BUILD)
    set(AUDIO_MODULE_PATH "${CMAKE_SOURCE_DIR}/3rdParty/miniaudio")

    if(EXISTS "${AUDIO_MODULE_PATH}/miniaudio.h")
        target_sources(GamepadCore PRIVATE "${AUDIO_MODULE_PATH}/miniaudio.c")
        target_include_directories(GamepadCore PUBLIC "${AUDIO_MODULE_PATH}")
        target_compile_definitions(GamepadCore PUBLIC GAMEPAD_CORE_HAS_AUDIO=1)
        message(STATUS "GamepadCore: Audio module ENABLED")
    else()
        target_compile_definitions(GamepadCore PUBLIC GAMEPAD_CORE_HAS_AUDIO=0)
        message(STATUS "GamepadCore: Audio module not found")
        message(STATUS "  To enable: git submodule update --init 3rdParty/miniaudio")
    endif()
else()
    target_compile_definitions(GamepadCore PUBLIC GAMEPAD_CORE_HAS_AUDIO=0)
    message(STATUS "GamepadCore: Audio module DISABLED")
endif()

# ============================================
# Tests Module (opcional)
# ============================================
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/Tests/Integration/CMakeLists.txt")
    # Global definition for test-specific code blocks
    add_definitions(-DBUILD_GAMEPAD_CORE_TESTS)

    option(BUILD_TESTS "Build integration tests" ON)

    if(BUILD_TESTS)
        enable_testing()
        add_subdirectory(Tests)
    endif()
else()
    message(STATUS "Tests submodule not initialized - skipping tests")
endif()