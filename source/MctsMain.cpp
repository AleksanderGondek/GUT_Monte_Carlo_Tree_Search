#include "MctsCommon.h"
#include "games/ChessGameState.h"
#include "playouts/WithUctSort.h"
#include "playouts/WithUctSortRootParallelization.h"
#include "parsers/ChessGameParser.h"

// Algorithm tuning
int MCTS_SIMULATION_MAX_ITERATIONS = 200;

int main(int argc, char* argv[])
{
    // Parse arguments
    if(argc < 4)
    {
        // We expect 4 arguments: program name,
        // quantity of omp_threads that should be usd,
        // number of maximum simulations allowed for one step,
        // and full path to file with chess starting board.
        std::cerr <<
                "Usage: " <<
                argv[0] <<
                "{OMP_THREADS_TO_USE}" <<
                "{MAX_SIMULATION_ITERATIONS}" <<
                "{FULL_PATH_TO_FILE_WITH_STARTING_BOARD}" <<
                std::endl;
        return 1;
    }

    // Set variables from arguments
    // Omp related
    omp_set_dynamic(0);                         // Explicitly disable dynamic teams
    omp_set_num_threads(std::stoi(argv[1]));    // Use given quantity of threads for
                                                // all consecutive parallel regions

    // Mcts related
    MCTS_SIMULATION_MAX_ITERATIONS = std::stoi(argv[2]); // Set maximum number of iterations
                                                         // for simulation step.
    std::unordered_map<std::string, std::string> test =
            Mcts::Parsers::ChessGame::LoadChessBoard(argv[3]); // Load default board

    Mcts::Utils::ChessBoardRepresentations::PrintOutChessBoard(test);
    Mcts::GameStates::ChessGameState gameState(2, test);

    while (!gameState.getAvailableActions().empty())
    {
        std::cout << "Board before taking move:" << std::endl;
        std::cout << gameState.getGameRepresentation() << std::endl;

        std::string action;
        if (gameState.getLastActivePlayer() == MCTS_PLAYER_ONE_ID)
        {
            // Last player was no 1, so it's player 2 turn
            action = Mcts::Playouts::getBestMoveUsingUctSort(&gameState, 40);
        }
        else
        {
            // Last player was no 2 so it's player 1 turn
            action = Mcts::Playouts::getBestMoveUsingUctSortRootParallelization(&gameState, 40);
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