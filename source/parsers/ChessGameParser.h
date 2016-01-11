//
// Created by agondek on 11/01/16.
//

#ifndef GUT_MONTE_CARLO_TREE_SEARCH_CHESSGAMEPARSER_H
#define GUT_MONTE_CARLO_TREE_SEARCH_CHESSGAMEPARSER_H


#include "../MctsCommon.h"

namespace Mcts
{
    namespace Parsers
    {
        namespace ChessGame
        {
            std::unordered_map<std::string, std::string> LoadChessBoard(std::string pathToFile);
        }
    }
}


#endif //GUT_MONTE_CARLO_TREE_SEARCH_CHESSGAMEPARSER_H
