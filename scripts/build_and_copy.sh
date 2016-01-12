#!/usr/bin/env bash

DESTINATION_XEON_PHI="mic0"

echo "~~~ GUT Monte-Carlo Tree Search Project ~~~"
echo "Build and copy script starting up.."

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
    echo "Running in dev env.."
    echo "This means this script will try to compile application using icc compiler.."
    echo "and copy all needed files to ${DESTINATION_XEON_PHI} device.."
    echo "Enabling icc compiler.."
    source /opt/intel/composer_xe_2013_sp1.3.174/bin/compilervars.sh intel64
    if [ $? -ne 0 ]; then
        echo "There was an error in enabling icc compiler"
        exit 1
    fi

    echo "Running command 'cmake -D CMAKE_C_COMPILER=icc -D CMAKE_CXX_COMPILER=icc ./'.."
    cmake -D CMAKE_C_COMPILER=icc -D CMAKE_CXX_COMPILER=icc -DGUT_MCTS_ENV=${environment} ./
    if [ $? -ne 0 ]; then
        echo "There was an error in running cmake command"
        exit 1
    fi

    echo "Building application with 'make' command.."
    make
    if [ $? -ne 0 ]; then
        echo "There was an error in building application with make command"
        exit 1
    fi

    echo "Coping needed libs to ${DESTINATION_XEON_PHI} device.."
    scp /opt/intel/composer_xe_2013_sp1.3.174/compiler/lib/mic/libiomp5.so ${DESTINATION_XEON_PHI}:~
    if [ $? -ne 0 ]; then
        echo "There was an error in coping needed libs to ${DESTINATION_XEON_PHI} device.."
        exit 1
    fi

    echo "Coping compiled application to ${DESTINATION_XEON_PHI} device.."
    scp bin/GUT_Monte_Carlo_Tree_Search ${DESTINATION_XEON_PHI}:~
    if [ $? -ne 0 ]; then
        echo "There was an error in coping compiled application to ${DESTINATION_XEON_PHI} device.."
        exit 1
    fi

    echo "Coping setup and run script to ${DESTINATION_XEON_PHI} device.."
    scp scripts/run_mcts.sh ${DESTINATION_XEON_PHI}:~
    if [ $? -ne 0 ]; then
        echo "There was an error in coping setup and run script to ${DESTINATION_XEON_PHI} device.."
        exit 1
    fi

    echo "Coping example_input.txt to ${DESTINATION_XEON_PHI} device.."
    scp example_input.txt ${DESTINATION_XEON_PHI}:~
    if [ $? -ne 0 ]; then
        echo "There was an error in coping example_input.txt to ${DESTINATION_XEON_PHI} device.."
        exit 1
    fi

    echo "SSH to ${DESTINATION_XEON_PHI} device.."
    ssh ${DESTINATION_XEON_PHI}
    if [ $? -ne 0 ]; then
        echo "There was an error in SSHing to ${DESTINATION_XEON_PHI} device.."
        exit 1
    fi
else
    echo "Running in dev env.."
    echo "This means this script will copy all project to GUT Machine with Xeon Phi devices.."
    echo "(You will have to be connected via VPN to do so)"

    echo "Checking if route to apl12(153.19.50.44) machine exists.."
    ping 153.19.50.44 -qc 1
    if [ $? -ne 0 ]; then
        echo "No route to apl12(153.19.50.44) machine exists.."
        echo "Are you connected via VPN to GUT network ?"
        exit 1
    fi

    echo "Coping files to apl12 machine.."
    sshpass -p "student" scp -r ./ student01@153.19.50.44:/home/student01/131508/GUT_Monte_Carlo_Tree_Search_SCP/
    if [ $? -ne 0 ]; then
        echo "There was an error in coping project to apl12 machine"
        exit 1
    fi
fi

exit 0
