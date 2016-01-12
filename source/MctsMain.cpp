#include "MctsCommon.h"
#include "games/ChessGameState.h"
#include "playouts/WithUctSort.h"
#include "playouts/WithUctSortRootParallelization.h"

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
    Mcts::GameStates::ChessGameState gameState(2, test);

    // IMPORTANT!: if number of _chips mod (k + 1) == 0, second player should win (optimal)
    // Where k is the maximum number of _chips allowed to draw at once
    // Uncomment to present a valid game
    // Mcts::GameStates::NimGameState gameState(2,400);
    // Mcts::GameStates::NimGameState gameState(MCTS_PLAYER_TWO_ID, 400);

    while (!gameState.getAvailableActions().empty())
    {
        std::cout << "Board before taking move:" << std::endl;
        std::cout << gameState.getGameRepresentation() << std::endl;

        std::string action;
        if (gameState.getLastActivePlayer() == MCTS_PLAYER_ONE_ID)
        {
            // Last player was no 1, so it's player 2 turn
            action = Mcts::Playouts::getBestMoveUsingUctSort(&gameState, 20);
        }
        else
        {
            // Last player was no 2 so it's player 1 turn
            action = Mcts::Playouts::getBestMoveUsingUctSortRootParallelization(&gameState, 20);
        }

        std::cout << "Player: " << 3 - gameState.getLastActivePlayer() << " takes his best move: " << action <<
        std::endl;

        if(action != MCTS_ACTION_NOT_AVAILABLE)
        {
            gameState.performAction(action);
            std::cout << "Board after taking move:" << std::endl;
            std::cout << gameState.getGameRepresentation() << std::endl;
        }
    }

    if (gameState.getStateValue(gameState.getLastActivePlayer()) == MCTS_PLAYER_ONE_ID)
    {
        std::cout << gameState.getLastActivePlayer() << " wins" << std::endl;
    }
    else
    {
        std::cout << 3 - gameState.getLastActivePlayer() << " wins" << std::endl;
    }

    return 0;
}