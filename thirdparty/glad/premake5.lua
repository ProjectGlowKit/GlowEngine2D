local root_dir = path.join(os.getcwd(), "../..")

project "Glad"
    kind "StaticLib"
    language "C"
    staticruntime "on"

    targetdir (path.join(root_dir, "bin/%{cfg.buildcfg}/%{prj.name}"))
    objdir (path.join(root_dir, "bin-obj/%{cfg.buildcfg}/%{prj.name}"))

    files 
    {
        "include/**.h",
        "src/**.c"
    }

    sysincludedirs 
    {
        "include"
    }

    filter "system:windows"
        systemversion "latest"

    filter "system:macosx"
        xcodebuildsettings
        {
            ["MACOSX_DEPLOYMENT_TARGET"] = "15.0",
            ["UseModernBuildSystem"] = "NO"
        }
    
    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"
    
    filter "configurations:Release"
        runtime "Release"
        symbols "off"
        optimize "on"