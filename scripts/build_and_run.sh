#!/usr/bin/env bash

echo "~~~ GUT Monte-Carlo Tree Search Project ~~~"
echo "Build and run script starting up.."

echo "Making sure the script was run properly.."
if [ ! -f "CMakeLists.txt" ]; then
    echo "Build & Run script was not run from project root directory!"
    echo "Please do run it from root."
    exit 1
fi

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

echo "Detecting run environment.."
current_user="$(id -u -n)"
if [ ${current_user} = "agondek" ]; then
    echo "Environment set to dev"
    environment="dev"
else
    echo "Environment set to gut"
    environment="gut"
fi

if [ ${environment} = "gut" ]; then
    echo "Running command \'cmake ./\'.."
    cmake ./

    echo "Building application with \'make\' command.."
    make

    echo "Starting up.."
    ./bin/GUT_Monte_Carlo_Tree_Search
else
    echo "Not yet implemented."
fi
