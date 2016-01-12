//
// Created by agondek on 12/01/16.
//

#ifndef GUT_MONTE_CARLO_TREE_SEARCH_WITHUCTSORTLEAFPARALLELIZATION_H
#define GUT_MONTE_CARLO_TREE_SEARCH_WITHUCTSORTLEAFPARALLELIZATION_H

#include "../MctsCommon.h"
#include "../games/IGameState.h"
#include "../tree/Node.h"
#include "../utils/OmpHelpers.h"

namespace Mcts
{
    namespace Playouts
    {
        std::string getBestMoveUsingUctSortLeafParallelization(
                Mcts::GameStates::IGameState* rootState,
                int maximumIterations);
    }
}

#endif //GUT_MONTE_CARLO_TREE_SEARCH_WITHUCTSORTLEAFPARALLELIZATION_H
