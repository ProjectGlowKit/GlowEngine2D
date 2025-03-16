import os
import json

VERSION_MAJOR = 0
VERSION_MINOR = 0

configFilePath = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "glowconfig.json"))
try:
    with open(configFilePath, 'r') as config_file:
        config_data = json.load(config_file)
        
        VERSION_MAJOR = config_data.get("GLOW_ENGINE", {}).get("V_MAJOR", VERSION_MAJOR)
        VERSION_MINOR = config_data.get("GLOW_ENGINE", {}).get("V_MINOR", VERSION_MINOR)

except FileNotFoundError:
    print(f"Error: {configFilePath} not found.")
except json.JSONDecodeError:
    print(f"Error: Failed to decode JSON from {configFilePath}.")
except Exception as e:
    print(f"Error reading configuration: {e}")

print("GlowEngine -v{}.{}".format(VERSION_MAJOR, VERSION_MINOR))