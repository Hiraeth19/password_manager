workspace "PasswordManager"
   configurations { "Debug", "Release" }
   platforms { "x64" }

project "Encryption"
    kind "ConsoleApp"
    language "C++"
    location "src"
    cppdialect "C++17"
    files {
        "src/*.cpp",
        "src/*.h"
    }