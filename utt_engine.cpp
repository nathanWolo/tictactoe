#include <iostream>
#include <vector>
#include <stdlib.h>
#include <chrono>
#include "utt_board.h"
#include "base_tictactoe_board.h"
#include "utt_engine.h"


EngineV1AlphaBeta::EngineV1AlphaBeta() {
    bestMoveRoot = {0, 0};
}


int EngineV1AlphaBeta::evaluate(UltimateTicTacToeBoard board, char rootPlayer) {
    int xScore = 0;
    int oScore = 0;
    char enemyPlayer;
    for (int metaRow = 0; metaRow < 3; ++metaRow) {
        for (int metaCol = 0; metaCol < 3; ++metaCol) {
            char winner = board.checkWinnerSubGame(metaRow, metaCol);
            if (winner == 'X') {
                xScore += 100;
            }
            else if (winner == 'O') {
                oScore += 100;
            }
        }
    }
    if (rootPlayer == 'X') {
        return xScore - oScore;
    } else {
        return oScore - xScore;
    }
}

int EngineV1AlphaBeta::negamax(UltimateTicTacToeBoard board, int depth, int ply, char rootPlayer, int color, int alpha, int beta,
                    std::chrono::time_point<std::chrono::high_resolution_clock> endTime) {
    if (std::chrono::high_resolution_clock::now() > endTime) {
        return color * -9999;
    }
    
    char enemyPlayer;
    if (rootPlayer == 'X') {
        enemyPlayer = 'O';
    } else {
        enemyPlayer = 'X';
    }
    if (board.checkWinner() == rootPlayer) {
        return color * 999 - ply;
    } else if (board.checkWinner() == enemyPlayer) {
        return color * -999 - ply;
    }
    else if (board.isDrawn()) {
        return 0;
    }
    if (depth == 0) {
        return color * evaluate(board, rootPlayer);
    }
    int maxEval = -999;
    std::vector<std::vector<int>> legalMoves = board.getLegalMoves();
    std::vector<int> bestMove = legalMoves[0];

    for (int moveIndex = 0; moveIndex < legalMoves.size(); ++moveIndex) {

        board.makeMove(legalMoves[moveIndex][0], legalMoves[moveIndex][1]);
        int eval = -negamax(board, depth - 1, ply + 1, rootPlayer, -color, -beta, -alpha, endTime);
        board.unmakeMove(legalMoves[moveIndex][0], legalMoves[moveIndex][1]);

        if (eval > maxEval) {
            alpha = std::max(alpha, eval);
            maxEval = eval;
            bestMove = legalMoves[moveIndex];
            if (ply == 0) {
                bestMoveRoot = bestMove;
            }
        }
        if (alpha >= beta) {
            break;
        }
    }
    return maxEval;
}

std::vector<int> EngineV1AlphaBeta::getBestMove(UltimateTicTacToeBoard board, char rootPlayer, int maxTime) {
    using namespace std::chrono;
    auto start = high_resolution_clock::now();
    auto endTime = start + milliseconds(maxTime);
    // std::vector<std::vector<int>> legalMoves = board.getLegalMoves();
    // std::vector<int> bestMove = legalMoves[0];
    int maxDepth = 99;
    for (int depth = 1; depth <= maxDepth; ++depth) {
        int alpha = -999999;
        int beta = 999999;
        int eval = negamax(board, depth, 0, rootPlayer, 1, alpha, beta, endTime);
        std::cout << "Depth: " << depth << " Best Move: (" << bestMoveRoot[0] << ", " << bestMoveRoot[1] << ")" << " Score: " << eval << std::endl;
        if (high_resolution_clock::now() > endTime) {
            break;
        }
    }
    // return bestMove;
    return bestMoveRoot;
}

//previous versions for testing improvements
EngineV0NaiveNegamax::EngineV0NaiveNegamax() {

}
int EngineV0NaiveNegamax::evaluate(UltimateTicTacToeBoard board, char rootPlayer) {
    int xScore = 0;
    int oScore = 0;
    char enemyPlayer;
    for (int metaRow = 0; metaRow < 3; ++metaRow) {
        for (int metaCol = 0; metaCol < 3; ++metaCol) {
            char winner = board.checkWinnerSubGame(metaRow, metaCol);
            if (winner == 'X') {
                xScore += 100;
            }
            else if (winner == 'O') {
                oScore += 100;
            }
        }
    }
    if (rootPlayer == 'X') {
        return xScore - oScore;
    } else {
        return oScore - xScore;
    }
}

int EngineV0NaiveNegamax::negamax(UltimateTicTacToeBoard board, int depth, int ply, char rootPlayer, int color, std::chrono::time_point<std::chrono::high_resolution_clock> endTime) {
    if (std::chrono::high_resolution_clock::now() > endTime) {
        return color * -9999;
    }
    
    char enemyPlayer;
    if (rootPlayer == 'X') {
        enemyPlayer = 'O';
    } else {
        enemyPlayer = 'X';
    }
    if (board.checkWinner() == rootPlayer) {
        return color * 999 - ply;
    } else if (board.checkWinner() == enemyPlayer) {
        return color * -999 - ply;
    }
    else if (board.isDrawn()) {
        return 0;
    }
    if (depth == 0) {
        return color * evaluate(board, rootPlayer);
    }
    int maxEval = -999;
    std::vector<std::vector<int>> legalMoves = board.getLegalMoves();
    std::vector<int> bestMove = legalMoves[0];

    for (int moveIndex = 0; moveIndex < legalMoves.size(); ++moveIndex) {

        board.makeMove(legalMoves[moveIndex][0], legalMoves[moveIndex][1]);
        int eval = -negamax(board, depth - 1, ply + 1, rootPlayer, -color, endTime);
        board.unmakeMove(legalMoves[moveIndex][0], legalMoves[moveIndex][1]);

        if (eval > maxEval) {
            maxEval = eval;
            bestMove = legalMoves[moveIndex];
        }
    }
    return maxEval;
}

std::vector<int> EngineV0NaiveNegamax::getBestMove(UltimateTicTacToeBoard board, char rootPlayer, int maxTime) {
    using namespace std::chrono;
    auto start = high_resolution_clock::now();
    auto endTime = start + milliseconds(maxTime);
    std::vector<std::vector<int>> legalMoves = board.getLegalMoves();
    std::vector<int> bestMove = legalMoves[0];
    int maxDepth = 99;
    for (int depth = 1; depth <= maxDepth; ++depth) {
        int maxEval = -999999;
        for(int moveIndex = 0; moveIndex < legalMoves.size(); ++moveIndex) {
            board.makeMove(legalMoves[moveIndex][0], legalMoves[moveIndex][1]);
            int eval = -negamax(board, depth - 1, 1, rootPlayer, -1, endTime);
            board.unmakeMove(legalMoves[moveIndex][0], legalMoves[moveIndex][1]);
            if (eval > maxEval) {
                maxEval = eval;
                bestMove = legalMoves[moveIndex];
            }
        }
        // std::cout << "Depth: " << depth << " Best Move: (" << bestMove[0] << ", " << bestMove[1] << ")" << " Score: " << maxEval << std::endl;
        if (high_resolution_clock::now() > endTime) {
            return bestMove;
        }
    }
    return bestMove;
}