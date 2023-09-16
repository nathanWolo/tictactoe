#include <iostream>
#include <vector>
#include <stdlib.h>
#include "base_tictactoe_board.cpp"

int simpleMiniMax(TicTacToeBoard board) {
    if (board.checkWinner() == 'X') {
        return 1;
    } else if (board.checkWinner() == 'O') {
        return -1;
    } else if (board.isDrawn()) {
        return 0;
    }
    if (board.getSideToMove() == 'X') {
        int bestScore = -1000;
        std::vector<int> legalMoves = board.getLegalMoves();
        for (int i = 0; i < legalMoves.size(); ++i) {
            board.makeMove(legalMoves[i]);
            int score = simpleMiniMax(board);
            board.unmakeMove(legalMoves[i]);
            if (score > bestScore) {
                bestScore = score;
            }
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        std::vector<int> legalMoves = board.getLegalMoves();
        for (int i = 0; i < legalMoves.size(); ++i) {
            board.makeMove(legalMoves[i]);
            int score = simpleMiniMax(board);
            board.unmakeMove(legalMoves[i]);
            if (score < bestScore) {
                bestScore = score;
            }
        }
        return bestScore;
    }
}


int main() {
    TicTacToeBoard board;
    while (board.checkWinner() == ' ' && !board.isDrawn()) {
        board.display_board();
        std::vector<int> legalMoves = board.getLegalMoves();
        std::cout << "Legal moves: ";
        if (board.getSideToMove() == 'X') {
            //choose move based off minimax
            int bestScore = -1000;
            int bestMove = -1;
            for (int i = 0; i < legalMoves.size(); ++i) {
                board.makeMove(legalMoves[i]);
                int score = simpleMiniMax(board);
                board.unmakeMove(legalMoves[i]);
                if (score > bestScore) {
                    bestScore = score;
                    bestMove = legalMoves[i];
                }
            }
            board.makeMove(bestMove);
        } else {
            //human move

            
            for (int i = 0; i < legalMoves.size(); ++i) {
                std::cout << legalMoves[i] << " ";
            }
            std::cout << std::endl;
            int move;
            std::cout << "Enter move: ";
            std::cin >> move;
            board.makeMove(move);
        }
    }
    board.display_board();
    if (board.isDrawn()) {
        std::cout << "Draw!" << std::endl;
    } else if (board.checkWinner() != ' '){
        std::cout << board.checkWinner() << " wins!" << std::endl;
    }
    return 0;
}