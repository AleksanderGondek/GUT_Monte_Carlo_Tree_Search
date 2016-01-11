#!/usr/bin/env bash

DESTINATION_XEON_PHI="mic0"

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
    echo "Enabling icc compiler.."
    source /opt/intel/composer_xe_2013_sp1.3.174/bin/compilervars.sh intel64
    if [ $? -ne 0 ]; then
        echo "There was an error in enabling icc compiler"
        exit 1
    fi

    echo "Running command \'cmake -D CMAKE_C_COMPILER=icc -D CMAKE_CXX_COMPILER=icc ./\'.."
    cmake -D CMAKE_C_COMPILER=icc -D CMAKE_CXX_COMPILER=icc -DGUT_MCTS_ENV=${environment} ./
    if [ $? -ne 0 ]; then
        echo "There was an error in running cmake command"
        exit 1
    fi

    echo "Building application with \'make\' command.."
    make
    if [ $? -ne 0 ]; then
        echo "There was an error in building application with make command"
        exit 1
    fi

    echo "Coping needed libs to mic machine.."
    scp /opt/intel/composer_xe_2013_sp1.3.174/compiler/lib/mic/libmiomp5.so ${DESTINATION_XEON_PHI}:~
    if [ $? -ne 0 ]; then
        echo "There was an error in coping needed libs to mic machine"
        exit 1
    fi

    echo "Coping compiled application to mic machine.."
    scp .bin/GUT_Monte_Carlo_Tree_Search ${DESTINATION_XEON_PHI}:~
    if [ $? -ne 0 ]; then
        echo "There was an error in coping compiled application to mic machine"
        exit 1
    fi

    echo "SSH to mic machine"
    ssh ${DESTINATION_XEON_PHI}
    if [ $? -ne 0 ]; then
        echo "There was an error in SSHing to mic machine"
        exit 1
    fi

    echo "Exporting library path"
    export LD_LIBRARY_PATH="~"
    if [ $? -ne 0 ]; then
        echo "There was an error in exporting library path"
        exit 1
    fi

    echo "Starting up.."
    ~/GUT_Monte_Carlo_Tree_Search
    if [ $? -ne 0 ]; then
        echo "GUT_Monte_Carlo_Tree_Search exited with non-zero status"
        exit 1
    fi
else
    echo "Not yet implemented."
fi

exit 0
