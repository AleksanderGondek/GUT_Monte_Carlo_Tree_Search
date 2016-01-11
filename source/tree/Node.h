//
// Created by agondek on 11/01/16.
//

#ifndef GUT_MONTE_CARLO_TREE_SEARCH_NODE_H
#define GUT_MONTE_CARLO_TREE_SEARCH_NODE_H

#include "../MctsCommon.h"
#include "../games/IGameState.h"

namespace Mcts
{
    namespace Tree
    {
        class Node
        {
        public:
            Node(std::string action, Node* parent, GameStates::IGameState* state);

            std::vector<std::string> actionsNotTaken;
            std::vector<Node> childNodes;

            Node* getParentNode(void);
            std::string getPreviousAction(void);
            unsigned short int getLastActivePlayer(void);
            void setLastActivePlayer(unsigned short int playerId);
            long int getWins(void);
            void adjustWins(long int wins);
            unsigned long int getVisits(void);
            void adjustVisits(unsigned long int visits);

            Node* selectNextChildNode(void);
            Node* addChildNode(std::string action, GameStates::IGameState* state);

            void update(long int value);
            unsigned long int _visits;
        private:
            Node*_parentNode;
            std::string _previousAction;
            unsigned short int _lastActivePlayer;
            long int _wins;
        };

        bool compareTwoNodesWithUcb(Mcts::Tree::Node &node1, Mcts::Tree::Node &node2);
        bool compareNodesByVisists(Mcts::Tree::Node &node1, Mcts::Tree::Node &node2);
    }
}

#endif //GUT_MONTE_CARLO_TREE_SEARCH_NODE_H
