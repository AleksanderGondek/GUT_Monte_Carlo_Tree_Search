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
    echo "Removing .bin/*"
    rm -rf "./bin"
fi
if [ -d "lib" ]; then
    echo "Removing .lib/*"
    rm -rf "./lib"
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
