//
// Created by agondek on 11/01/16.
//

#include "Node.h"

namespace Mcts
{
    namespace Tree
    {
        bool compareTwoNodesWithUcb(const Node &node1, const Node &node2)
        {
            unsigned long int node1key = (unsigned long int)(
                    node1._wins / node1._visits +
                    std::sqrt(2 * std::log(node2._visits / node1._visits))
            );
            unsigned long int node2key = (unsigned long int)(
                    node2._wins / node2._visits +
                    std::sqrt(2 * std::log(node1._visits / node2._visits))
            );

            return (node1key < node2key);
        }

        bool compareNodesByVisists(const Node &node1, const Node &node2)
        {
            return (node1._visits < node2._visits);
        }

        Node::Node(std::string action, Node *parent, GameStates::IGameState *state)
        {
            this->_wins = 0;
            this->_visits = 0;

            this->_previousAction = action;
            this->_parentNode = parent;

            if(state == NULL)
            {
                this->actionsNotTaken = std::vector<std::string>();
                this->_lastActivePlayer = MCTS_PLAYER_UNKNOWN_ID;
            }
            else
            {
                this->actionsNotTaken = state->getAvailableActions();
                this->_lastActivePlayer = state->getLastActivePlayer();
            }
        }

        Node* Node::clone()
        {
            Node* toBeReturned = new Node(this->_previousAction, NULL, NULL);
            toBeReturned->_wins = this->_wins;
            toBeReturned->_visits = this->_visits;

            toBeReturned->actionsNotTaken = this->actionsNotTaken;
            toBeReturned->setLastActivePlayer(this->_lastActivePlayer);
            return toBeReturned;
        }

        Node* Node::selectNextChildNode()
        {
            std::sort(this->childNodes.begin(), this->childNodes.end(), compareTwoNodesWithUcb);
            return &this->childNodes.back();
        }

        Node* Node::addChildNode(std::string action, GameStates::IGameState *state)
        {
            // Remove action connected to newNode, from list of not taken actions
            this->actionsNotTaken.erase(std::remove(this->actionsNotTaken.begin(),
                                                    this->actionsNotTaken.end(),
                                                    action),
                                        this->actionsNotTaken.end());

            // Create new node for tree
            Node newChild(action, this, state);

            // Add new node to list of child nodes
            this->childNodes.push_back(newChild);

            // Return pointer to newly created node
            return &this->childNodes.back();
        }

        void Node::update(long int value)
        {
            this->adjustVisits(1);
            this->adjustWins(value);
        }

        // Getters and setters
        Node* Node::getParentNode()
        {
            return this->_parentNode;
        }

        std::string Node::getPreviousAction()
        {
            return this->_previousAction;
        }

        unsigned short int Node::getLastActivePlayer()
        {
            return this->_lastActivePlayer;
        }

        void Node::setLastActivePlayer(unsigned short int playerId)
        {
            this->_lastActivePlayer = playerId;
        }

        long int Node::getWins()
        {
            return this->_wins;
        }

        void Node::adjustWins(long int wins)
        {
            if(std::numeric_limits<long int>::max() < this->_wins + wins)
            {
                std::cout << "Attempt to increment Wins counter above limit" << std::endl;
                return;
            }
            if(std::numeric_limits<long int>::min() > this->_wins + wins)
            {
                std::cout << "Attempt to decrement Wins counter below limit" << std::endl;
                return;
            }

            this->_wins += wins;
        }

        unsigned long int Node::getVisits()
        {
            return this->_visits;
        }

        void Node::adjustVisits(unsigned long int visits)
        {
            if(std::numeric_limits<unsigned long int>::max() < this->_visits + visits)
            {
                std::cout << "Attempt to increment Visits counter above limit" << std::endl;
                return;
            }

            this->_visits += visits;
        }
    }
}