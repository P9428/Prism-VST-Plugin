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

mkdir -p "$DEST"
cp "build/${PLUGIN_NAME}${EXT}" "$DEST/" && \
    echo "Installed ${PLUGIN_NAME}${EXT} to ${DEST}"
