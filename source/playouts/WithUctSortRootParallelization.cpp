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

            #pragma omp parallel num_threads(4) shared(allActionsChosen)
            {
                int i = 0;
                Mcts::Tree::Node root(MCTS_ACTION_NOT_AVAILABLE, NULL, rootState);

                while (i < maximumIterations)
                {
                    Mcts::Tree::Node *node = &root;
                    Mcts::GameStates::IGameState *state = rootState->clone();

                    // Selection Step
                    while (node->actionsNotTaken.empty() && !node->childNodes.empty())
                    {
                        node = node->selectNextChildNode();
                        state->performAction(node->getPreviousAction());
                    }

                    // Expansion Step
                    if (!node->actionsNotTaken.empty())
                    {
                        srand((unsigned int) time(0));
                        std::random_shuffle(node->actionsNotTaken.begin(), node->actionsNotTaken.end());
                        std::string action = node->actionsNotTaken.back();
                        state->performAction(action);
                        node = node->addChildNode(action, state);
                    }

                    // Simulation Step
                    while (!state->getAvailableActions().empty())
                    {
                        std::vector<std::string> actions = state->getAvailableActions();
                        std::random_shuffle(actions.begin(), actions.end());
                        std::string action = actions.back();
                        state->performAction(action);
                    }

                    // Backpropagation Step
                    while (node->getParentNode() != NULL)
                    {
                        node->update(state->getStateValue(node->getLastActivePlayer()));
                        node = node->getParentNode();
                    }

                    i++;
                }

                std::sort(root.childNodes.begin(), root.childNodes.end(),
                          Mcts::Tree::compareNodesByVisists);
                Mcts::Tree::Node lastItemWithHighestVisits = root.childNodes.back();
                std::string action = lastItemWithHighestVisits.getPreviousAction();
                allActionsChosen.push_back(action);
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