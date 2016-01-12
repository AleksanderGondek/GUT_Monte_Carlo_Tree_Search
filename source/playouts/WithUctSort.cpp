//
// Created by agondek on 11/01/16.
//

#include "WithUctSort.h"

namespace Mcts
{
    namespace Playouts
    {
        std::string getBestMoveUsingUctSort(Mcts::GameStates::IGameState* rootState,
                                            int maximumIterations)
        {
            int i = 0;
            Mcts::Tree::Node root(MCTS_ACTION_NOT_AVAILABLE, NULL, rootState);

            while(i<maximumIterations)
            {
                Mcts::Tree::Node* node = &root;
                Mcts::GameStates::IGameState* state = rootState->clone();

                // Selection Step
                while(node->actionsNotTaken.empty() && !node->childNodes.empty())
                {
                    node = node->selectNextChildNode();
                    state->performAction(node->getPreviousAction());
                }

                // Expansion Step
                if(!node->actionsNotTaken.empty())
                {
                    srand((unsigned int) time(0));
                    std::random_shuffle(node->actionsNotTaken.begin(), node->actionsNotTaken.end());
                    std::string action = node->actionsNotTaken.back();
                    state->performAction(action);
                    node = node->addChildNode(action, state);
                }

                // Simulation Step
                int simulationStepIterations = 0;
                while(!state->getAvailableActions().empty())
                {
                    std::vector<std::string> actions = state->getAvailableActions();
                    std::random_shuffle(actions.begin(), actions.end());
                    std::string action = actions.back();
                    state->performAction(action);

                    simulationStepIterations++;
                    if(simulationStepIterations >= MCTS_SIMULATION_MAX_ITERATIONS)
                    {
                        break;
                    }
                }

                // Backpropagation Step
                while(node->getParentNode() != NULL)
                {
                    node->update(state->getStateValue(node->getLastActivePlayer()));
                    node = node->getParentNode();
                }

                i++;
            }

            std::sort(root.childNodes.begin(), root.childNodes.end(),
                      Mcts::Tree::compareNodesByVisists);
            Mcts::Tree::Node lastItemWithHighestVisits = root.childNodes.back();
            return lastItemWithHighestVisits.getPreviousAction();
        }
    }
}