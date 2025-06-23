#!/usr/bin/env bash
set -e

PLUGIN_NAME="PrismVSTPlugin"
UNAME=$(uname)

if [[ "$UNAME" == "Darwin" ]]; then
    EXT=".dylib"
    DEST="/Library/Audio/Plug-Ins/VST3"
elif [[ "$UNAME" == "Linux" ]]; then
    EXT=".so"
    DEST="$HOME/.vst3"
elif [[ "$UNAME" == MINGW* || "$UNAME" == CYGWIN* || "$UNAME" == MSYS* ]]; then
    EXT=".dll"
    DEST="/c/Program Files/Common Files/VST3"
else
    echo "Unsupported OS: $UNAME"
    exit 1
fi

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
BUILD_DIR="${SCRIPT_DIR}/../build"
mkdir -p "$DEST"
cp "${BUILD_DIR}/${PLUGIN_NAME}${EXT}" "$DEST/" && \
    echo "Installed ${PLUGIN_NAME}${EXT} to ${DEST}"
