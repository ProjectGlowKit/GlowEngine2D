import os
import subprocess
import json
import sys
import shutil

if len(sys.argv) < 2:
    print("Usage: glow build <configuration>")
    sys.exit(1)

#Editor related paths
VS_PATH = os.environ["VS_PATH"]
VS_EXE = os.environ["VS_EXE"]
MSBUILD_PATH = os.environ["MSBUILD_PATH"]

#Engine paths
ENGINE_NAME = "UntitledEngine"
PROJECT_NAME = "UntitledProject"
ENGINE_ROOT = ""
CONFIG = sys.argv[1]

configFilePath = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "glowconfig.json"))
try:
    with open(configFilePath, 'r') as config_file:
        config_data = json.load(config_file)
        print(config_data)
        
        ENGINE_NAME = config_data.get("GLOW_ENGINE", {}).get("ENGINE_NAME", ENGINE_NAME)
        ENGINE_ROOT = config_data.get("GLOW_ENGINE", {}).get("ENGINE_ROOT", ENGINE_ROOT)
        PROJECT_NAME = config_data.get("GLOW_ENGINE", {}).get("PROJECT_NAME", PROJECT_NAME)

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
    
#Copy all .dll files
dllDir = os.path.join(ENGINE_ROOT, "thirdparty", "dlls")
outputDir = os.path.join(ENGINE_ROOT, "bin", CONFIG, PROJECT_NAME)

if not os.path.exists(dllDir):
    print(f"Error: DLL directory '{dllDir}' does not exist.")
else:
    os.makedirs(outputDir, exist_ok=True)
    for file in os.listdir(dllDir):
        if file.endswith(".dll"):
            shutil.copy2(os.path.join(dllDir, file), os.path.join(outputDir, file))
            print(f"Copied: {file} -> {outputDir}")