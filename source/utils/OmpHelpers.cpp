//
// Created by agondek on 12/01/16.
//

#include "OmpHelpers.h"

namespace Mcts
{
    namespace Utils
    {
        namespace OmpHelpers
        {
            void Message(std::string messageToPrint)
            {
                if(!MCTS__OMP_VERBOSE_MODE)
                {
                    return;
                }

                std::cout << "[Thread (" <<
                        omp_get_thread_num() + 1 <<
                        "/" << omp_get_num_threads() <<
                        ")] " << messageToPrint << std::endl;
            }
        }
    }
}