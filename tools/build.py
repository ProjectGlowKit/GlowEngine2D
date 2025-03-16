import os
import subprocess
import json

VS_PATH = os.environ["VS_PATH"]
VS_EXE = os.environ["VS_EXE"]
MSBUILD_PATH = os.environ["MSBUILD_PATH"]

ENGINE_NAME = "UntitledEngine"
CONFIG = "Debug"

configFilePath = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "glowconfig.json"))
try:
    with open(configFilePath, 'r') as config_file:
        config_data = json.load(config_file)
        print(config_data)
        
        ENGINE_NAME = config_data.get("GLOW_ENGINE", {}).get("ENGINE_NAME", ENGINE_NAME)
        print(ENGINE_NAME)
        CONFIG = config_data.get("GLOW_ENGINE", {}).get("CONFIG", CONFIG)

except FileNotFoundError:
    print(f"Error: {configFilePath} not found.")
except json.JSONDecodeError:
    print(f"Error: Failed to decode JSON from {configFilePath}.")
except Exception as e:
    print(f"Error reading configuration: {e}")

subprocess.run([
    MSBUILD_PATH, 
    f"{ENGINE_NAME}.sln", 
    f"/property:Configuration={CONFIG}", 
    "/property:Platform=x64"
    ])
    