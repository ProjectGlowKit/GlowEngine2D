import os
import sys
import json
import subprocess

if len(sys.argv) < 2:
    print("Usage: glow run <configuration>")
    sys.exit(1)

PLATFORM = "WINDOWS"
CONFIG = sys.argv[1]
PROJECT_NAME = "UntitledProject"
configFilePath = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "glowconfig.json"))
try:
    with open(configFilePath, 'r') as config_file:
        config_data = json.load(config_file)
        
        PLATFORM = config_data.get("GLOW_ENGINE", {}).get("PLATFORM", PLATFORM)
        ENGINE_ROOT = config_data.get("GLOW_ENGINE", {}).get("PATHS", {}).get("ENGINE_ROOT", "")
        PROJECT_NAME = config_data.get("GLOW_ENGINE", {}).get("PROJECT_NAME", PROJECT_NAME)

except FileNotFoundError:
    print(f"Error: {configFilePath} not found.")
except json.JSONDecodeError:
    print(f"Error: Failed to decode JSON from {configFilePath}.")
except Exception as e:
    print(f"Error reading configuration: {e}")

if PLATFORM == "WINDOWS": path = os.path.join(ENGINE_ROOT, "bin", CONFIG, PROJECT_NAME, f"{PROJECT_NAME}.exe")
else: path = os.path.join(ENGINE_ROOT, "bin", CONFIG, PROJECT_NAME)

if PLATFORM == "WINDOWS":
    print(path)
    subprocess.run(["cmd.exe", "/c", "start", path])
elif PLATFORM in ["LINUX", "MACOS"]:
    subprocess.run([path], shell=True)
else:
    print("Error generating solution: unsupported os")
    sys.exit(1)