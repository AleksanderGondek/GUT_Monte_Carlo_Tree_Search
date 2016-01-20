//
// Created by agondek on 12/01/16.
//

#include "WithUctSortLeafParallelization.h"

namespace Mcts
{
    namespace Playouts
    {
        std::string getBestMoveUsingUctSortLeafParallelization(
                Mcts::GameStates::IGameState* rootState, int maximumIterations)
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

                // Copy all possible actions to vector (not array cause it's not-stadard and
                // causes compilation errors
                // = sign is overloaded to copy contents of one vector into another
                std::vector<std::string> actionsForThreads = node->actionsNotTaken;

                #pragma omp parallel \
                default(none) \
                shared(node,state) \
                firstprivate(actionsForThreads,MCTS_SIMULATION_MAX_ITERATIONS)
                {
                    int index;
                    Mcts::Tree::Node* localNode;
                    Mcts::GameStates::IGameState* localState;

                    Mcts::Utils::OmpHelpers::Message("Pragma Omp Parallel section started..");
                    #pragma omp for
                    for(index=0; index<actionsForThreads.size(); index++)
                    {
                        #pragma omp critical
                        {
                            // Expansion step
                            Mcts::Utils::OmpHelpers::Message("Pragma Omp For Expansion Step started..");
                            std::string expansionAction = actionsForThreads[index];
                            localState = state->clone();
                            localState->performAction(expansionAction);
                            localNode = node->addChildNode(expansionAction, localState);

                            // Copy to local variables to not break shared mem
                            Mcts::Utils::OmpHelpers::Message("Pragma Omp For Coping values started..");
                            localNode = localNode->clone();
                        }

                        // Simulation Step
                        int simulationStepIterations = 0;
                        Mcts::Utils::OmpHelpers::Message("Pragma Omp For Simulation Step started..");
                        while (!localState->getAvailableActions().empty())
                        {
                            std::vector<std::string> actions = localState->getAvailableActions();
                            std::random_shuffle(actions.begin(), actions.end());
                            std::string action = actions.back();
                            localState->performAction(action);

                            simulationStepIterations++;
                            if (simulationStepIterations >= MCTS_SIMULATION_MAX_ITERATIONS)
                            {
                                break;
                            }
                        }

                        #pragma omp critical
                        {
                            //Backpropagation step
                            // Step 1. Find node child that has the same previousAction;
                            Mcts::Utils::OmpHelpers::Message("Pragma Omp For Backpropagation Step started..");
                            for (int j = 0; j < node->childNodes.size(); j++)
                            {
                                Mcts::Tree::Node *browsingNode = &node->childNodes[j];
                                Mcts::Utils::OmpHelpers::Message("Pragma Omp For Backpropagation check started..");
                                if (browsingNode->getPreviousAction() ==
                                    localNode->getPreviousAction())
                                {
                                    Mcts::Utils::OmpHelpers::Message("Pragma Omp For Backpropagation if hit!");
                                    while (browsingNode->getParentNode() != NULL)
                                    {
                                        Mcts::Utils::OmpHelpers::Message("Pragma Omp For Backpropagation while..");
                                        // Step 2. Update it with appropriate value
                                        browsingNode->update(
                                                localState->getStateValue(
                                                        browsingNode->getLastActivePlayer()
                                                )
                                        );
                                        browsingNode = browsingNode->getParentNode();
                                    }
                                    break;
                                }
                            }
                        }

                        Mcts::Utils::OmpHelpers::Message("Pragma Omp Parallel section finishing..");
                    }
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