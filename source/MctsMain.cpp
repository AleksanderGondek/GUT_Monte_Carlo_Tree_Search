#include "MctsCommon.h"

// Tmp includes for sake of testing
#include "parsers/ChessGameParser.h"
#include "utils/ChessGameRepresentations.h"

int main(int argc, char* argv[])
{
// Exemplary code of OMP
//    char const* str = "Hello world";
//    unsigned const len = std::strlen(str);
//#pragma omp parallel for num_threads(4)
//    for (unsigned thread = 0; thread < 4; ++thread)
//    {
//        for (unsigned i = 0; i < len; ++i)
//        {
//            std::cout << str[i] << std::endl;
//        }
//    }
    std::unordered_map<std::string, std::string> test =
            Mcts::Parsers::ChessGame::LoadChessBoard("/home/student01/example_input.txt");
    Mcts::Utils::ChessBoardRepresentations::PrintOutChessBoard(test);

    return 0;
}