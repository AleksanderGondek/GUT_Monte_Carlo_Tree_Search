#!/usr/bin/env bash

echo "~~~ GUT Monte-Carlo Tree Search Project ~~~"
echo "Setup and run script starting up.."

echo "Making sure the script was run properly.."
if [ $# -ne 3 ]; then
    echo "You have run this script with invalid parameters (or lack of them)"
    echo "Valid usage: run_mcts.sh {QUANTITY_OF_OMP_THREADS_TO_USE} {MAXIMUM_NUMBER_OF_ITERATIONS_FOR_SIMULATION_STEP} {FULL_PATH_TO_STARTING_BOARD_FILE}"
    echo "i.e. ./run_mcts.sh 8 200 /home/student01/example_input.txt"
    echo "Setting QUANTITY_OF_OMP_THREADS_TO_USE to default (8)"
    echo "Setting MAXIMUM_NUMBER_OF_ITERATIONS_FOR_SIMULATION_STEP to default (200)"
    echo "Setting FULL_PATH_TO_STARTING_BOARD_FILE to default (/home/student01/example_input.txt)"
    omp_number_of_threads=8
    max_iterations_for_simulation=200
    full_path_to_starting_board=/home/student01/example_input.txt
else
    echo "Setting QUANTITY_OF_OMP_THREADS_TO_USE to ($1)"
    echo "Setting MAXIMUM_NUMBER_OF_ITERATIONS_FOR_SIMULATION_STEP to ($2)"
    echo "Setting FULL_PATH_TO_STARTING_BOARD_FILE to ($3)"
    omp_number_of_threads=$1
    max_iterations_for_simulation=$2
    full_path_to_starting_board=$3
fi

echo "Exporting library path (LD_LIBRARY_PATH = \'~\')"
export LD_LIBRARY_PATH="~"
if [ $? -ne 0 ]; then
    echo "There was an error in exporting library path"
    exit 1
fi

echo "Starting up.."
~/GUT_Monte_Carlo_Tree_Search 8 200 /home/student01/example_input.txt
if [ $? -ne 0 ]; then
    echo "GUT_Monte_Carlo_Tree_Search exited with non-zero status"
    exit 1
fi
