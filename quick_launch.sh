#!/bin/bash

# Quick launcher for TheClipper with AudioPluginHost

set -e

# Colors
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

echo -e "${BLUE}Quick TheClipper Launcher${NC}"
echo "=========================="

# Get script directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Build plugin
echo -e "${YELLOW}Building plugin...${NC}"
cmake --build build

# Plugin and filtergraph paths
PLUGIN_PATH="$SCRIPT_DIR/build/plugin/AudioPlugin_artefacts/Debug/VST3/TheClipper.vst3"
FILTERGRAPH_PATH="$SCRIPT_DIR/clipper_test.filtergraph"

echo -e "${GREEN}Plugin built successfully!${NC}"

# Install plugin to user VST3 directory
VST3_USER_DIR="$HOME/Library/Audio/Plug-Ins/VST3"
echo -e "${YELLOW}Installing plugin to user VST3 directory...${NC}"
mkdir -p "$VST3_USER_DIR"
cp -R "$PLUGIN_PATH" "$VST3_USER_DIR/"
echo -e "${GREEN}Plugin installed!${NC}"

# AudioPluginHost path
PLUGIN_HOST="/Applications/JUCE/extras/AudioPluginHost/Builds/MacOSX/build/Debug/AudioPluginHost.app/Contents/MacOS/AudioPluginHost"

# Launch
echo -e "${YELLOW}Launching AudioPluginHost with TheClipper...${NC}"
"$PLUGIN_HOST" "$FILTERGRAPH_PATH"

echo -e "${GREEN}AudioPluginHost has closed.${NC}"
