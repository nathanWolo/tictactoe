#ifndef UTT_ENGINE_H
#define UTT_ENGINE_H
#include <iostream>
#include <chrono>
#include <vector>
#include <stdlib.h>
#include "utt_board.h"
#include "base_tictactoe_board.h"

int evaluate(UltimateTicTacToeBoard board, char rootPlayer);

int negamax(UltimateTicTacToeBoard board, int depth, int ply, char rootPlayer, int color, int alpha, int beta,
            std::chrono::time_point<std::chrono::high_resolution_clock> endTime);

std::vector<int> getBestMove(UltimateTicTacToeBoard board, char rootPlayer, int maxTime);

int oldEvaluate(UltimateTicTacToeBoard board, char rootPlayer);

int oldNegamax(UltimateTicTacToeBoard board, int depth, int ply, char rootPlayer, int color, 
            std::chrono::time_point<std::chrono::high_resolution_clock> endTime);

std::vector<int> oldGetBestMove(UltimateTicTacToeBoard board, char rootPlayer, int maxTime);

#endif