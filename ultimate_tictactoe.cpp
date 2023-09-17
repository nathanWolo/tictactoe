#include <iostream>
#include <vector>
#include <stdlib.h>
#include <unistd.h>
#include "utt_board.h"
#include "base_tictactoe_board.h"
#include "utt_engine.h"

int main() {
    srand(time(NULL));
    int computerWins = 0;
    int computerLosses = 0;
    int computerDraws = 0;
    for (int i = 0; i < 100; ++i) {
        UltimateTicTacToeBoard board = UltimateTicTacToeBoard();
        while(board.checkWinner() == ' ' && !board.isDrawn()) {
            board.displayBoard();
            std::cout << "new version wins: " << computerWins << " new version  draws: " << computerDraws << " new version  losses: " << computerLosses << std::endl;
            
            if (board.getSideToMove() == 'X') {
                //old version of engine plays X
                std::vector<int> bestMove = oldGetBestMove(board, 'X', 100);
                board.makeMove(bestMove[0], bestMove[1]);
            }
            else {
                // std::cout << "Computer wins: " << computerWins << " Computer draws: " << computerDraws << " Computer losses: " << computerLosses << std::endl;
                // std::cout << "Computer's turn..." << std::endl;
                // std::cout << "Computer is thinking..." << std::endl;

                std::vector<int> bestMove = getBestMove(board, 'O', 100);
                // std::cout << "Computers best move: (" << bestMove[0] << ", " << bestMove[1] << ")" << std::endl;
                // usleep(100000);
                board.makeMove(bestMove[0], bestMove[1]);
            }

            //sleep for 500ms
            // usleep(500000);
            
            board.displayBoard();

            if (board.isDrawn()) {
                std::cout << "Draw!" << std::endl;
                computerDraws++;
            } else if (board.checkWinner() != ' '){
                std::cout << board.checkWinner() << " wins!" << std::endl;
                if (board.checkWinner() == 'O') {
                    computerWins++;
                }
                else {
                    computerLosses++;
                }
            }
        }
        std::cout << "Game over!" << std::endl;
    }
    std::cout << "Computer wins: " << computerWins << " Computer draws: " << computerDraws << " Computer losses: " << computerLosses << std::endl;
    return 0;
}

