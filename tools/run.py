import os
import sys
import json
import subprocess

if len(sys.argv) < 3:
    print("Usage: glow run <project> <configuration>")
    sys.exit(1)

PLATFORM = "WINDOWS"
CONFIG = sys.argv[2]
PROJECT_NAME = sys.argv[1]
configFilePath = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "glowconfig.json"))
try:
    with open(configFilePath, 'r') as config_file:
        config_data = json.load(config_file)
        
        PLATFORM = config_data.get("GLOW_ENGINE", {}).get("PLATFORM", PLATFORM)
        ENGINE_ROOT = config_data.get("GLOW_ENGINE", {}).get("PATHS", {}).get("ENGINE_ROOT", "")

except FileNotFoundError:
    print(f"Error: {configFilePath} not found.")
except json.JSONDecodeError:
    print(f"Error: Failed to decode JSON from {configFilePath}.")
except Exception as e:
    print(f"Error reading configuration: {e}")

if PLATFORM == "WINDOWS": path = os.path.join(ENGINE_ROOT, "bin", CONFIG, f"{PROJECT_NAME}.exe")
else: path = os.path.join(ENGINE_ROOT, "bin", CONFIG, PROJECT_NAME)

if PLATFORM == "WINDOWS":
    print(path)
    subprocess.run(["cmd.exe", "/c", "start", path])
elif PLATFORM in ["LINUX", "MACOS"]:
    subprocess.run([path], shell=True)
else:
    print("Error generating solution: unsupported os")
    sys.exit(1)