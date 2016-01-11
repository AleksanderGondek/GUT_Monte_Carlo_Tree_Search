//
// Created by agondek on 11/01/16.
//

#ifndef GUT_MONTE_CARLO_TREE_SEARCH_CHESSGAMESTATE_H
#define GUT_MONTE_CARLO_TREE_SEARCH_CHESSGAMESTATE_H

#include "../MctsCommon.h"
#include "../utils/ChessGameRepresentations.h"
#include "IGameState.h"

namespace Mcts
{
    namespace GameStates
    {
        class ChessGameState: public IGameState
        {
        public:
            ChessGameState(unsigned short int lastActivePlayer,
                           std::unordered_map<std::string, std::string> chessBoard);
            IGameState* clone(void);

            // Important: This needs to be set for ChessGame state to work!
            void setChessBoard(std::unordered_map<std::string, std::string> chessBoard);

            unsigned short int getLastActivePlayer(void);
            void setLastActivePlayer(unsigned short int playerId);

            long int getStateValue(unsigned short int playerId);
            std::vector<std::string> getAvailableActions(void);
            void performAction(std::string action);
            std::string getGameRepresentation(void);
        private:
            std::unordered_map<std::string, std::string> _chessBoard;
            unsigned short int _lastActivePlayer;

            bool _playerOneKingDown = false;
            bool _playerTwoKingDown = false;

            std::string GetPieceTypeFromBoardValue(std::string value);
            std::vector<std::string> getAvailableActions(std::string piecePosition,
                                                         std::string pieceData);
            std::vector<std::string> GetKingPossibleMoves(std::string kingPosition,
                                                          std::string kingData);
            std::vector<std::string> GetPawnPossibleMoves(std::string pawnPosition,
                                                          std::string pawnData);
            bool IsBoardFieldEmpty(std::string position);
        };
    }
}

#endif //GUT_MONTE_CARLO_TREE_SEARCH_CHESSGAMESTATE_H
