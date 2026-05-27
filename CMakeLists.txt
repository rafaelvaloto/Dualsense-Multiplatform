cmake_minimum_required(VERSION 3.20)
set(CMAKE_POLICY_DEFAULT_CMP0000 NEW)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
include(FetchContent)

# Main project name
project(GamepadCore LANGUAGES C CXX)

# --- Global C++ Settings ---
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Shared test/CI options (defined early so they can affect dependency setup)
option(AUTOMATED_TESTS "Enable automated tests (timeout for CI)" OFF)

# Enable Unicode support for Windows targets
if(WIN32)
    add_compile_definitions(UNICODE _UNICODE)
endif()
add_subdirectory(Source)

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