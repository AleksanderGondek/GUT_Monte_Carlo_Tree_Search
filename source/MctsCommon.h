//
// Created by agondek on 11/01/16.
//

#ifndef GUT_MONTE_CARLO_TREE_SEARCH_MCTSCOMMON_H
#define GUT_MONTE_CARLO_TREE_SEARCH_MCTSCOMMON_H

// Includes from standard libraries
#include <algorithm>
#include <assert.h>
#include <bits/stl_vector.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <limits>
#include <omp.h>
#include <sstream>
#include <unordered_map>
#include <vector>

// Constants definitions
// Debugging
#define MCTS__OMP_VERBOSE_MODE true

// Players ids
#define MCTS_PLAYER_ONE_ID 1
#define MCTS_PLAYER_TWO_ID 2
#define MCTS_PLAYER_UNKNOWN_ID 3

// Actions ids
#define MCTS_ACTION_NOT_AVAILABLE "N/A"

// Chess game pieces
#define MCTS_CHESS_GAME_PIECE_PAWN "P"
#define MCTS_CHESS_GAME_PIECE_KNIGHT "N"
#define MCTS_CHESS_GAME_PIECE_BISHOP "B"
#define MCTS_CHESS_GAME_PIECE_ROOK "R"
#define MCTS_CHESS_GAME_PIECE_QUEEN "Q"
#define MCTS_CHESS_GAME_PIECE_KING "K"
#define MCTS_CHESS_GAME_PIECE_UNKNOWN "X"

// Algorithm tuning
extern int MCTS_SIMULATION_MAX_ITERATIONS;

#endif //GUT_MONTE_CARLO_TREE_SEARCH_MCTSCOMMON_H
