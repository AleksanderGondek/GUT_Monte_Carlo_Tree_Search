#!/usr/bin/env bash

echo "~~~ GUT Monte-Carlo Tree Search Project ~~~"
echo "Setup and run script starting up.."

echo "Exporting library path (LD_LIBRARY_PATH = \'~\')"
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
