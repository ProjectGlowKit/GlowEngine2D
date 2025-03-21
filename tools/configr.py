import sys
import os
import json

ENGINE_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
configFilePath = os.path.join(ENGINE_ROOT, "glowconfig.json")

try:
    with open(configFilePath, "r") as file:
        config = json.load(file)
except:
    print(f"Couldnt open config file at: {configFilePath}")

if len(sys.argv) < 3:
    print("Usage: glow configr <ProjectKey> <VariableKey>")
    print(config)
    sys.exit(1)

prjKey = sys.argv[1]
varKey = sys.argv[2]

if prjKey in config and varKey in config[prjKey]:
    print(config[prjKey][varKey])
else:
    print(f"Error: '{varKey}' not found in '{prjKey}'")