#!/usr/bin/env bash

echo "Removing remnants of previous builds and runs.."
if [ -d "bin" ]; then
    echo "Removing ./bin/*"
    rm -rf "./bin"
fi
if [ -d "lib" ]; then
    echo "Removing ./lib/*"
    rm -rf "./lib"
fi
if [ -d "CMakeFiles" ]; then
    echo "Removing ./CMakeFiles/*"
    rm -rf "./CMakeFiles"
fi
if [ -d "CMakeScripts" ]; then
    echo "Removing ./CMakeScripts/*"
    rm -rf "./CMakeScripts"
fi
if [ -f "CMakeCache.txt" ]; then
    echo "Removing ./CMakeCache.txt"
    rm -f "./CMakeCache.txt"
fi
if [ -f "Makefile" ]; then
    echo "Removing ./Makefile"
    rm -f "./Makefile"
fi
if [ -f "cmake_install.cmake" ]; then
    echo "Removing ./cmake_install.cmake"
    rm -f "./cmake_install.cmake"
fi
if [ -f "install_manifest.txt" ]; then
    echo "Removing ./install_manifest.txt"
    rm -f "./install_manifest.txt"
fi
