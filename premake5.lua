workspace "GlowEngine"
    startproject "GlowEditor"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release"
    }

project "GlowEngine"
    location "glowlib"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/%{cfg.buildcfg}/%{prj.name}")
    objdir ("bin-obj/%{cfg.buildcfg}/%{prj.name}")

    files 
    {
        "glowlib/include/**.h",
        "glowlib/src/**.cpp",
        "glowlib/src/**.h"
    }

    sysincludedirs 
    {
        "glowlib/include"
    }

    flags
    {
        "FatalWarnings"
    }

    filter "system:windows"
        systemversion "latest"
        defines
        {
            GWE_PLATFORM_WINDOWS
        }

    filter "system:linux"
        defines
        {
            GWE_PLATFORM_LINUX
        }

    filter "system:macosx"
        xcodebuildsettings
        {
            ["MACOSX_DEPLOYMENT_TARGET"] = "15.0",
            ["UseModernBuildSystem"] = "NO"
        }
        defines
        {
            GWE_PLATFORM_MACOS
        }
    
    filter "configurations:Debug"
        defines
        {
            GWE_CONFIG_DEBUG
        }
        runtime "Debug"
        symbols "on"
    
    filter "configurations:Release"
        defines
        {
            GWE_CONFIG_RELEASE
        }
        runtime "Release"
        symbols "off"
        optimize "on"

project "GlowEditor"
    location "gloweditor"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir ("bin/%{cfg.buildcfg}/%{prj.name}")
    objdir ("bin-obj/%{cfg.buildcfg}/%{prj.name}")

    links "GlowEngine"

    files 
    {
        "gloweditor/src/**.cpp",
        "gloweditor/src/**.h"
    }

    sysincludedirs 
    {
        "glowlib/include"
    }

    flags
    {
        "FatalWarnings"
    }

    filter "system:windows"
        systemversion "latest"
        defines
        {
            GWE_PLATFORM_WINDOWS
        }

    filter "system:linux"
        defines
        {
            GWE_PLATFORM_LINUX
        }

    filter "system:macosx"
        xcodebuildsettings
        {
            ["MACOSX_DEPLOYMENT_TARGET"] = "15.0",
            ["UseModernBuildSystem"] = "NO"
        }
        defines
        {
            GWE_PLATFORM_MACOS
        }
    
    filter "configurations:Debug"
        defines
        {
            GWE_CONFIG_DEBUG
        }
        runtime "Debug"
        symbols "on"
    
    filter "configurations:Release"
        defines
        {
            GWE_CONFIG_RELEASE
        }
        runtime "Release"
        symbols "off"
        optimize "on"