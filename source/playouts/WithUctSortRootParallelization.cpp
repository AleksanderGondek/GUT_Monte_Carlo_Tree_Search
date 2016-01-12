//
// Created by agondek on 12/01/16.
//

#include "WithUctSortRootParallelization.h"

namespace Mcts
{
    namespace Playouts
    {
        std::string getBestMoveUsingUctSortRootParallelization(
                Mcts::GameStates::IGameState* rootState, int maximumIterations)
        {
            std::vector<std::string> allActionsChosen;

            #pragma omp parallel num_threads(8)
            {
                Mcts::Utils::OmpHelpers::Message("Pragma Omp Parallel section started..");
                int i = 0;
                Mcts::Tree::Node root(MCTS_ACTION_NOT_AVAILABLE, NULL, rootState);

                Mcts::Utils::OmpHelpers::Message("Entering while loop..");
                while (i < maximumIterations)
                {
                    Mcts::Utils::OmpHelpers::Message("Cloning rootState..");
                    Mcts::Tree::Node *node = &root;
                    Mcts::GameStates::IGameState *state = rootState->clone();

                    // Selection Step
                    Mcts::Utils::OmpHelpers::Message("Starting selection step..");
                    while (node->actionsNotTaken.empty() && !node->childNodes.empty())
                    {
                        node = node->selectNextChildNode();
                        state->performAction(node->getPreviousAction());
                    }

                    // Expansion Step
                    Mcts::Utils::OmpHelpers::Message("Starting expansion step..");
                    if (!node->actionsNotTaken.empty())
                    {
                        srand((unsigned int) time(0));
                        std::random_shuffle(node->actionsNotTaken.begin(), node->actionsNotTaken.end());
                        std::string action = node->actionsNotTaken.back();
                        state->performAction(action);
                        node = node->addChildNode(action, state);
                    }

                    // Simulation Step
                    Mcts::Utils::OmpHelpers::Message("Starting simulation step..");
                    int simulationStepIterations = 0;
                    while (!state->getAvailableActions().empty())
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
                    Mcts::Utils::OmpHelpers::Message("Starting backpropagation step..");
                    while (node->getParentNode() != NULL)
                    {
                        node->update(state->getStateValue(node->getLastActivePlayer()));
                        node = node->getParentNode();
                    }

                    i++;
                    Mcts::Utils::OmpHelpers::Message("Exiting while loop..");
                }

                Mcts::Utils::OmpHelpers::Message("Sorting possible moves..");
                std::sort(root.childNodes.begin(), root.childNodes.end(),
                          Mcts::Tree::compareNodesByVisists);
                Mcts::Tree::Node lastItemWithHighestVisits = root.childNodes.back();
                std::string action = lastItemWithHighestVisits.getPreviousAction();
                Mcts::Utils::OmpHelpers::Message("Saving most valuable action in shared vector..");
                allActionsChosen.push_back(action);
                Mcts::Utils::OmpHelpers::Message("Pragma Omp Parallel section ended..");
            }

            // Sort before getting most frequent element
            std::sort(allActionsChosen.begin(), allActionsChosen.end());
            int mostFrequentElementOccurencesCounter = 0;
            int currentElementOccurencesCounter =0;
            std::string mostFrequentElement = "";
            std::string currentElement = "";
            for(std::vector<std::string>::iterator it = allActionsChosen.begin();
                it != allActionsChosen.end(); ++it)
            {
                // If this is first iteration
                if(currentElement == "")
                {
                    currentElement = *it;
                    mostFrequentElement = *it;
                }

                // If we have found another, same element
                if(currentElement == *it)
                {
                    currentElementOccurencesCounter++;
                }
                // If we have found new element
                else
                {
                    currentElement = *it;
                    currentElementOccurencesCounter = 1;
                }

                if(currentElementOccurencesCounter >= mostFrequentElementOccurencesCounter)
                {
                    mostFrequentElement = currentElement;
                    mostFrequentElementOccurencesCounter = currentElementOccurencesCounter;
                }
            }

            // Return the most frequently returned action
            return mostFrequentElement;
        }
    }
}