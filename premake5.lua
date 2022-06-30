workspace "PasswordManager"
   configurations { "Debug", "Release" }
   platforms { "x64" }

project "Encryption"
    kind "ConsoleApp"
    language "C++"
    location "src"
    cppdialect "C++17"
    includedirs {
        "dependencies/ImGUI",
        "dependencies/glfw/include",
    }
    files {
        "src/*.cpp",
        "src/*.h"
    }
    links {
        "ImGUI",
        "glfw",
    }
project "ImGUI"
    kind "StaticLib"
    language "C++"
    location "dependencies/ImGUI"
    files{
        "dependencies/ImGUI/imconfig.h",
		"dependencies/ImGUI/imgui.h",
		"dependencies/ImGUI/imgui.cpp",
		"dependencies/ImGUI/imgui_draw.cpp",
		"dependencies/ImGUI/imgui_internal.h",
		"dependencies/ImGUI/imgui_widgets.cpp",
		"dependencies/ImGUI/imgui_tables.cpp",
		"dependencies/ImGUI/imstb_rectpack.h",
		"dependencies/ImGUI/imstb_textedit.h",
		"dependencies/ImGUI/imgui_demo.cpp",
		"dependencies/ImGUI/imstb_truetype.h",
    }
project "glfw"
    kind "StaticLib"
    language "C"
    location "dependencies/glfw"
    files{
		"dependencies/glfw/src/win32_init.c",
        "dependencies/glfw/src/win32_module.c",
        "dependencies/glfw/src/win32_joystick.c",
        "dependencies/glfw/src/win32_monitor.c",
        "dependencies/glfw/src/win32_time.h",
        "dependencies/glfw/src/win32_time.c",
        "dependencies/glfw/src/win32_thread.h",
        "dependencies/glfw/src/win32_thread.c",
        "dependencies/glfw/src/win32_window.c",
        "dependencies/glfw/src/wgl_context.c",
        "dependencies/glfw/src/egl_context.c",
        "dependencies/glfw/src/osmesa_context.c",
        "dependencies/glfw/include/GLFW/glfw3.h",
        "dependencies/glfw/include/GLFW/glfw3native.h",
        "dependencies/glfw/src/internal.h",
        "dependencies/glfw/src/platform.h",
        "dependencies/glfw/src/mappings.h",
        "dependencies/glfw/src/context.c",
        "dependencies/glfw/src/init.c",
        "dependencies/glfw/src/input.c",
        "dependencies/glfw/src/monitor.c",
        "dependencies/glfw/src/platform.c",
        "dependencies/glfw/src/vulkan.c",
        "dependencies/glfw/src/window.c",
        "dependencies/glfw/src/egl_context.c",
        "dependencies/glfw/src/osmesa_context.c",
        "dependencies/glfw/src/null_platform.h",
        "dependencies/glfw/src/null_joystick.h",
        "dependencies/glfw/src/null_init.c",
        "dependencies/glfw/src/null_monitor.c",
        "dependencies/glfw/src/null_window.c",
        "dependencies/glfw/src/null_joystick.c",

    }
    defines {
		"_GLFW_WIN32",
	    "_CRT_SECURE_NO_WARNINGS"
    }