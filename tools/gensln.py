import sys
import os
import subprocess
import platform

osName = platform.system()
if osName == "Windows":
    file = "premake5windows.exe"
elif osName == "Linux":
    file = "premake5linux"
elif osName == "Darwin":
    file = "premake5macos"
else:
    print("Error generating solution: unsupported os")
    sys.exit(1)

premakePath = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "premake/", file))

if not os.path.exists(premakePath):
    print(f"Error: Premake binary not found at {premakePath}")
    sys.exit(1)

def GenerateSolution(solutiontype):
    validsolutions = ["vs2022", "vs2019", "gmake", "xcode"]

    if solutiontype not in validsolutions:
        print(f"Unknown solution type: {solutiontype}")
        sys.exit(1)

    cmd = [premakePath, solutiontype]
    print(f"Generating solution using: {' '.join(cmd)}")
    subprocess.run(cmd)

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: gensln <solution type>")
        sys.exit(1)

    GenerateSolution(sys.argv[1])