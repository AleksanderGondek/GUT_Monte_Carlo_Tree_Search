//
// Created by agondek on 11/01/16.
//

#include "ChessGameRepresentations.h"

namespace Mcts
{
    namespace Utils
    {
        namespace ChessBoardRepresentations
        {
            std::string ChessBoardRepresentation(std::unordered_map<std::string, std::string> chessBoard)
            {
                std::stringstream buffer;
                std::string spaceBreak = "   ";
                std::string boardDimensionLetters = "ABCDEFGH";

                for(int i = 1 ; i<9; i++)
                {
                    // Add dimension descriptor and space break
                    buffer << std::to_string(i) << spaceBreak;

                    for(std::string::iterator it = boardDimensionLetters.begin();
                        it != boardDimensionLetters.end(); ++it)
                    {
                        // Board position is in [1-8][A-Z] format
                        std::string boardPosition = std::to_string(i);
                        boardPosition+=*it;

                        // If key exists
                        if (chessBoard.find(boardPosition) != chessBoard.end())
                        {
                            buffer << "[" << chessBoard[boardPosition] << "]";
                        }
                            // If key doesn't exist
                        else
                        {
                            buffer << "[" << spaceBreak << "]";
                        }
                    }

                    buffer << std::endl;
                }

                // At the very bottom print out dimension descriptors
                // Empty space to match up number, than space break
                buffer << " " << spaceBreak;
                for(std::string::iterator it = boardDimensionLetters.begin();
                    it != boardDimensionLetters.end(); ++it)
                {
                    // Then letter, surrounded by breaks, to match up three chars per column
                    buffer << "  " << *it << "  ";
                }
                buffer << std::endl;

                return buffer.str();
            }

            void PrintOutChessBoard(std::unordered_map<std::string, std::string> chessBoard)
            {
                std::cout << ChessBoardRepresentation(chessBoard) << std::endl;
            }
        };
    }
}
