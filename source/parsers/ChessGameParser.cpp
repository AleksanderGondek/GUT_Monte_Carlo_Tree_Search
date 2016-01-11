//
// Created by agondek on 11/01/16.
//

#include "ChessGameParser.h"

namespace Mcts
{
    namespace Parsers
    {
        namespace ChessGame
        {
            std::unordered_map<std::string, std::string> LoadChessBoard(std::string pathToFile)
            {
                // Input from file is in the following format
                // {Id of player owning piece [1|2]}:
                // {Initial letter identifying type [K]ing|[Q]ueen|[R]ook|[B]ishop|k[N]ight|[P]awn}:
                // {Postion on board [1-8][A-Z]}:
                // {Newline}
                // Example: 1:Q:1A - 1st players Queen of field 1A
                // File example:
                // 1:Q:1A
                // 1:R:2A
                // ..
                std::unordered_map<std::string, std::string> chessBoard;

                std::fstream inputFile(pathToFile);
                std::string line;
                while(std::getline(inputFile, line))
                {
                    // Board position is two last characters
                    std::string boardPosition = line.substr(4,2);
                    // Board position data
                    std::string boardData = line.substr(0, 3);
                    chessBoard[boardPosition] = boardData;
                }

                return chessBoard;
            }
        }
    }
}