import os

scriptDir = os.path.dirname(__file__)
COMMANDS = sorted([
    os.path.splitext(f)[0] for f in os.listdir(scriptDir)
    if f.endswith(".py") and f not in {os.path.basename(__file__), "glow.py"}
])
print("COMMANDS:")
for i in range(0, len(COMMANDS)):
    print("glow ", COMMANDS[i])