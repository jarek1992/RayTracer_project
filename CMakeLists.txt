cmake_minimum_required(VERSION 3.11.0)
project(ray_tracer)

# Flags for the compiler
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Vulkan setup
set(VULKAN_SDK "$ENV{VULKAN_SDK}")
include_directories(${VULKAN_SDK}/include)
link_directories(${VULKAN_SDK}/lib)

# vcpkg integration
set(CMAKE_TOOLCHAIN_FILE "C:/Users/micha/Desktop/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "vcpkg toolchain file")

# Path to ImGui files
set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/libs/imgui") # Change for ImGui destination
include_directories(${IMGUI_DIR})
include_directories(${IMGUI_DIR}/backends)
include_directories(${IMGUI_DIR}/misc/stb)

# Find and link Vulkan and GLFW libraries
find_package(Vulkan REQUIRED)
set(glfw3_DIR "C:/Users/micha/Desktop/vcpkg/vcpkg/installed/x64-windows/share/glfw3")
find_package(glfw3 CONFIG REQUIRED)

# Dependencies for GLFW using vcpkg
include_directories("C:/Users/micha/Desktop/vcpkg/vcpkg/installed/x64-windows/include")
link_directories("C:/Users/micha/Desktop/vcpkg/vcpkg/installed/x64-windows/lib")

# Add sources
add_executable(ray_tracer main.cpp
    libs/imgui/imgui.cpp
    libs/imgui/imgui_draw.cpp
    libs/imgui/imgui_tables.cpp
    libs/imgui/imgui_demo.cpp
    libs/imgui/imgui_widgets.cpp
    libs/imgui/backends/imgui_impl_vulkan.cpp
    libs/imgui/backends/imgui_impl_glfw.cpp
)

# Link Vulkan and GLFW to the ray_tracer executable
target_link_libraries(ray_tracer Vulkan::Vulkan glfw)