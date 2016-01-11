#!/usr/bin/env bash

echo "~~~ GUT Monte-Carlo Tree Search Project ~~~"
echo "Build and run script starting up.."

echo "Making sure the script was run properly.."
if [ ! -f "CMakeLists.txt" ]; then
    echo "Build & Run script was not run from project root directory!"
    echo "Please do run it from root."
    exit 1
fi

./scripts/clean_up.sh

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
    echo "Enabling icc and mpicc compilers.."
    source /opt/intel/composer_xe_2013_sp1.3.174/bin/compilervars.sh intel64

    echo "Running command \'cmake -D CMAKE_C_COMPILER=icc -D CMAKE_CXX_COMPILER=icc ./\'.."
    cmake -D CMAKE_C_COMPILER=icc -D CMAKE_CXX_COMPILER=icc -DGUT_MCTS_ENV=${environment} ./

    echo "Building application with \'make\' command.."
    make

    echo "Starting up.."
    ./bin/GUT_Monte_Carlo_Tree_Search
else
    echo "Not yet implemented."
fi
