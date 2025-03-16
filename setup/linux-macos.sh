#!/bin/bash

# Define the glow command
export PATH="$PWD/../tools/linux-macos:$PATH"
cd "$(dirname "$0")/.."

# Run the tools init.py
python "./setup/init/config.py"
exec bash