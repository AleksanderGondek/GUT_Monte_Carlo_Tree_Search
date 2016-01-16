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
                shared(node,state) \
                firstprivate(actionsForThreads,MCTS_SIMULATION_MAX_ITERATIONS)
                {
                    int index;
                    Mcts::Tree::Node* localNode;
                    Mcts::GameStates::IGameState* localState;

                    #pragma omp for
                    for(index=0; index<actionsForThreads.size(); index++)
                    {
                        #pragma omp critical
                        {
                            // Expansion step
                            std::string expansionAction = actionsForThreads[index];
                            state->performAction(expansionAction);
                            localNode = node->addChildNode(expansionAction, state);
                            localState = state->clone();

                            // Simulation Step
                            int simulationStepIterations = 0;
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

                            // Backpropagation Step
                            while(localNode->getParentNode() != NULL)
                            {
                                std::string messageToDisplay = "localNode previousAction: ";
                                messageToDisplay += localNode->getPreviousAction();
                                messageToDisplay += " | localNode lastActivePlayer: ";
                                messageToDisplay += std::to_string(localNode->getLastActivePlayer());
                                messageToDisplay += " | localState value: ";
                                messageToDisplay += std::to_string(localState->getStateValue(localNode->getLastActivePlayer()));

                                Mcts::Utils::OmpHelpers::Message(messageToDisplay);

                                localNode->update(localState->getStateValue(localNode->getLastActivePlayer()));
                                localNode = localNode->getParentNode();
                            }
                        }
                    }
                }

                i++;
                std::cout << "End of iteration" << std::endl;
            }

            std::sort(root.childNodes.begin(), root.childNodes.end(),
                      Mcts::Tree::compareNodesByVisists);
            Mcts::Tree::Node lastItemWithHighestVisits = root.childNodes.back();
            return lastItemWithHighestVisits.getPreviousAction();
        }
    }
}