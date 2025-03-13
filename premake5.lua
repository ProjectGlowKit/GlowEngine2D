workspace "GlowEngine"
    startproject "GlowEngineEditor"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release"
    }

project "GlowEngineEditor"
    location "gloweditor"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    files 
    {
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.h"
    }

    flags
    {
        "FatalWarnings"
    }