import sys
import subprocess
import os

scriptDir = os.path.dirname(__file__)
COMMANDS = sorted([
    os.path.splitext(f)[0] for f in os.listdir(scriptDir)
    if f.endswith(".py") and f not in {os.path.basename(__file__), "glow.py"}
])

def RunCommand(cmd, args):
    path = os.path.join(os.path.dirname(__file__), f"{cmd}.py")
    if os.path.exists(path):
        subprocess.run(["python", path] + args)
    else:
        print("Undefined command: ", cmd)

if len(sys.argv) < 2:
    print("No command provided.")
    subprocess.run(["python", os.path.join(os.path.dirname(__file__), "help.py")])
    sys.exit(1)

commands = []
cmdcrnt = None
argscrnt = []

for i in range(1, len(sys.argv)):
    arg = sys.argv[i]

    if arg in COMMANDS:
        if cmdcrnt is not None:
            commands.append((cmdcrnt, argscrnt))
        cmdcrnt = arg
        argscrnt = []
    else:
        argscrnt.append(arg)

if cmdcrnt is not None:
    commands.append((cmdcrnt, argscrnt))
for cmd, args in commands:
    RunCommand(cmd, args)