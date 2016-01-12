//
// Created by agondek on 12/01/16.
//

#ifndef GUT_MONTE_CARLO_TREE_SEARCH_WITHUCTSORTROOTPARALLELIZATION_H
#define GUT_MONTE_CARLO_TREE_SEARCH_WITHUCTSORTROOTPARALLELIZATION_H

#include "../MctsCommon.h"
#include "../games/IGameState.h"
#include "../tree/Node.h"

namespace Mcts
{
    namespace Playouts
    {
        std::string getBestMoveUsingUctSortRootParallelization(
                Mcts::GameStates::IGameState* rootState,
                int maximumIterations);
    }
}

#endif //GUT_MONTE_CARLO_TREE_SEARCH_WITHUCTSORTROOTPARALLELIZATION_H
