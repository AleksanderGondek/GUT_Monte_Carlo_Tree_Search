cmake_minimum_required(VERSION 2.8)
project(GUT_Monte_Carlo_Tree_Search)

# OpenMP Releated
FIND_PACKAGE(OpenMP REQUIRED)
SET(GUT_MCTS_ENV "dev" CACHE STRING "Defines which env we are building in")
message(STATUS "Variable GUT_MCTS_ENV equals to: ${GUT_MCTS_ENV}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
if("${GUT_MCTS_ENV}" STREQUAL "dev")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x ${OpenMP_CXX_FLAGS}")
elseif("${GUT_MCTS_ENV}" STREQUAL "gut")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mmic -std=c++0x ${OpenMP_CXX_FLAGS}")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x ${OpenMP_CXX_FLAGS}")
endif()
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")

# Save all output files in lib and bin directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(SOURCE_FILES
        source/MctsMain.cpp
        source/MctsCommon.h
        source/parsers/ChessGameParser.cpp
        source/parsers/ChessGameParser.h
        source/utils/ChessGameRepresentations.cpp
        source/utils/ChessGameRepresentations.h
        source/games/IGameState.h
        source/games/ChessGameState.cpp
        source/games/ChessGameState.h
        source/tree/Node.cpp
        source/tree/Node.h
        source/playouts/WithUctSort.cpp
        source/playouts/WithUctSort.h
        source/playouts/WithUctSortRootParallelization.cpp
        source/playouts/WithUctSortRootParallelization.h
        source/utils/OmpHelpers.cpp
        source/utils/OmpHelpers.h source/playouts/WithUctSortLeafParallelization.cpp source/playouts/WithUctSortLeafParallelization.h)
add_executable(GUT_Monte_Carlo_Tree_Search ${SOURCE_FILES})
