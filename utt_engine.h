#ifndef UTT_ENGINE_H
#define UTT_ENGINE_H
#include <iostream>
#include <chrono>
#include <vector>
#include <stdlib.h>
#include "utt_board.h"
#include "base_tictactoe_board.h"


class EngineV1AlphaBeta  {
    private:
        std::vector<int> bestMoveRoot;

    public:
        EngineV1AlphaBeta();
        int evaluate(UltimateTicTacToeBoard board, char rootPlayer);
        int negamax(UltimateTicTacToeBoard board, int depth, int ply, char rootPlayer, int color, int alpha, int beta,
                    std::chrono::time_point<std::chrono::high_resolution_clock> endTime);
        std::vector<int> getBestMove(UltimateTicTacToeBoard board, char rootPlayer, int maxTime);
};

class EngineV0NaiveNegamax {
public:
    EngineV0NaiveNegamax();
    int evaluate(UltimateTicTacToeBoard board, char rootPlayer);
    int negamax(UltimateTicTacToeBoard board, int depth, int ply, char rootPlayer, int color, 
                std::chrono::time_point<std::chrono::high_resolution_clock> endTime);
    std::vector<int> getBestMove(UltimateTicTacToeBoard board, char rootPlayer, int maxTime);
};

#endif