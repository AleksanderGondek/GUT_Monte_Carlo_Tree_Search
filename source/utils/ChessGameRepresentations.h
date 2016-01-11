//
// Created by agondek on 11/01/16.
//

#ifndef GUT_MONTE_CARLO_TREE_SEARCH_CHESSGAMEREPRESENTATIONS_H
#define GUT_MONTE_CARLO_TREE_SEARCH_CHESSGAMEREPRESENTATIONS_H

#include "../MctsCommon.h"

namespace Mcts
{
    namespace Utils
    {
        namespace ChessBoardRepresentations
        {
            std::string ChessBoardRepresentation(std::unordered_map<std::string, std::string> chessBoard);
            void PrintOutChessBoard(std::unordered_map<std::string, std::string> chessBoard);
        };
    }
}

#endif //GUT_MONTE_CARLO_TREE_SEARCH_CHESSGAMEREPRESENTATIONS_H
