import platform
import sys
import os
import json

ENGINE_NAME = "GlowEngine"
PROJECT_NAME = "GlowEditor"

VERSION_MAJOR = 0
VERSION_MINOR = 0

PLATFORM = "WINDOWS"

# Paths
ENGINE_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))

configFilePath = os.path.join(ENGINE_ROOT, "glowconfig.json")

osName = platform.system()
if osName == "Windows":
    PLATFORM = "WINDOWS"
elif osName == "Linux":
    PLATFORM = "LINUX"
elif osName == "Darwin":
    PLATFORM = "MACOS"
else:
    print("Error assigning PLATFORM unsupported os")
    sys.exit(1)

if os.path.exists(configFilePath):
    print(f"Configuration file already exists: {configFilePath}")
    sys.exit(0)

configData = {
    "GLOW_ENGINE":
    {
        "ENGINE_NAME": ENGINE_NAME,
        "PROJECT_NAME": PROJECT_NAME,
        "V_MAJOR": VERSION_MAJOR,
        "V_MINOR": VERSION_MINOR,
        "PLATFORM": PLATFORM,
        "PATHS":
        {
            "ENGINE_ROOT": ENGINE_ROOT
        }
    }
}

try:
    with open(configFilePath, 'w') as config_file:
        json.dump(configData, config_file, indent=4)
        print(f"Configuration written to {configFilePath}")
except Exception as e:
    print(f"Error writing configuration: {e}")
    sys.exit(1)