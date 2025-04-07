workspace "GlowEngine"
    startproject "GlowEditor"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release"
    }

-- Thirdparty Dependecies
thirdparty = {}
thirdparty["SDL3"] = "thirdparty/SDL3"
thirdparty["spdlog"] = "thirdparty/spdlog"
thirdparty["glad"] = "thirdparty/glad"

-- Compile glad
include "thirdparty/glad"

project "GlowLib"
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
        "glowlib/include/**.hpp",
        "glowlib/src/**.cpp",
        "glowlib/src/**.h",
        "glowlib/**.natvis",
        -- specialy compile ImGui files
        "glowlib/include/thirdparty/ImGui/**.cpp"
    }

    sysincludedirs 
    {
        "glowlib/include",
        "%{thirdparty.SDL3}/include",
        "%{thirdparty.spdlog}/include",
        "%{thirdparty.glad}/include"
    }

    flags
    {
    }

    defines
    {
        "GLFW_INCLUDE_NONE"
    }

    filter "system:windows"
        systemversion "latest"
        defines
        {
            "GWE_PLATFORM_WINDOWS"
        }

    filter "system:linux"
        defines
        {
            "GWE_PLATFORM_LINUX"
        }

    filter "system:macosx"
        xcodebuildsettings
        {
            ["MACOSX_DEPLOYMENT_TARGET"] = "15.0",
            ["UseModernBuildSystem"] = "NO"
        }
        defines
        {
            "GWE_PLATFORM_MACOS"
        }
    
    filter "configurations:Debug"
        defines
        {
            "DEBUG",
            "GWE_CONFIG_DEBUG"
        }
        runtime "Debug"
        symbols "on"
    
    filter "configurations:Release"
        defines
        {
            "NDEBUG",
            "GWE_CONFIG_RELEASE"
        }
        runtime "Release"
        symbols "off"
        optimize "on"
    
    filter "action:vs*"
        buildoptions { "/utf-8" }

project "GlowEditor"
    location "gloweditor"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/%{cfg.buildcfg}/%{prj.name}")
    objdir ("bin-obj/%{cfg.buildcfg}/%{prj.name}")

    links "GlowLib"

    files 
    {
        "gloweditor/src/**.cpp",
        "gloweditor/src/**.h"
    }

    sysincludedirs 
    {
        "glowlib/include",
        "%{thirdparty.spdlog}/include"
    }

    flags
    {
    }

    filter "system:windows"
        systemversion "latest"
        defines
        {
            "GWE_PLATFORM_WINDOWS"
        }
        libdirs
        {
            "%{thirdparty.SDL3}/lib"
        }
        links
        {
            "SDL3",
            "glad"
        }

    filter "system:linux"
        defines
        {
            "GWE_PLATFORM_LINUX"
        }

    filter "system:macosx"
        xcodebuildsettings
        {
            ["MACOSX_DEPLOYMENT_TARGET"] = "15.0",
            ["UseModernBuildSystem"] = "NO"
        }
        defines
        {
            "GWE_PLATFORM_MACOS"
        }
    
    filter "configurations:Debug"
        defines
        {
            "DEBUG",
            "GWE_CONFIG_DEBUG"
        }
        runtime "Debug"
        symbols "on"
    
    filter "configurations:Release"
        defines
        {
            "NDEBUG",
            "GWE_CONFIG_RELEASE"
        }
        runtime "Release"
        symbols "off"
        optimize "on"
    
    filter "action:vs*"
        buildoptions { "/utf-8" }

-- Examples
project "Pong"
    location "examples/pong"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/%{cfg.buildcfg}/examples/%{prj.name}")
    objdir ("bin-obj/%{cfg.buildcfg}/examples/%{prj.name}")

    links "GlowLib"

    files 
    {
        "examples/pong/src/**.cpp",
        "examples/pong/src/**.h"
    }

    sysincludedirs 
    {
        "%{wks.location}/glowlib/include",
        "examples/pong/include",
        "%{wks.location}/%{thirdparty.spdlog}/include"
    }

    flags
    {
    }

    filter "system:windows"
        systemversion "latest"
        defines
        {
            "GWE_PLATFORM_WINDOWS"
        }
        libdirs
        {
            "%{wks.location}/thirdparty/SDL3/lib"
        }
        links
        {
            "SDL3",
            "glad"
        }

    filter "system:linux"
        defines
        {
            "GWE_PLATFORM_LINUX"
        }

    filter "system:macosx"
        xcodebuildsettings
        {
            ["MACOSX_DEPLOYMENT_TARGET"] = "15.0",
            ["UseModernBuildSystem"] = "NO"
        }
        defines
        {
            "GWE_PLATFORM_MACOS"
        }

    filter "configurations:Debug"
        defines
        {
            "DEBUG",
            "GWE_CONFIG_DEBUG"
        }
        runtime "Debug"
        symbols "on"
    
    filter "configurations:Release"
        defines
        {
            "NDEBUG",
            "GWE_CONFIG_RELEASE"
        }
        runtime "Release"
        symbols "off"
        optimize "on"