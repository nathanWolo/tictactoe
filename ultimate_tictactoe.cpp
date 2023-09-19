#include <iostream>
#include <vector>
#include <stdlib.h>
#include <unistd.h>
#include "utt_board.h"
#include "base_tictactoe_board.h"
#include "utt_engine.h"

int main() {
    int computerWins = 0;
    int computerLosses = 0;
    int computerDraws = 0;
    int computerLossesAsX = 0;
    int computerWinsAsX = 0;
    int computerDrawsAsX = 0;
    int computerLossesAsO = 0;
    int computerWinsAsO = 0;
    int computerDrawsAsO = 0;
    int computerGamesAsX = 0;
    int computerGamesAsO = 0;
    int gamesToRun = 1000;
    int thinkingTime = 100;
    for (int i = 0; i < gamesToRun; ++i) {
        UltimateTicTacToeBoard board = UltimateTicTacToeBoard();
        RandomEngine random = RandomEngine();
        EngineV0NaiveNegamax v0 = EngineV0NaiveNegamax();
        EngineV1AlphaBeta v1 = EngineV1AlphaBeta();
        EngineV2ImprovedEval v2 = EngineV2ImprovedEval();
        EngineV3AspirationWindows v3 = EngineV3AspirationWindows();
        auto oldEngine = v2;
        auto newEngine = v3;
        int movesMade = 0;
        while(board.checkWinner() == ' ' && !board.isDrawn()) {
            board.displayBoard();
            if (i % 2 == 0) {
                std::cout << "Old version of engine plays X" << std::endl;
            }
            else {
                std::cout << "New version of engine plays X" << std::endl;
            }
            std::cout << "Game " << i + 1 << " of " << gamesToRun << std::endl;
            std::cout << "new version wins: " << computerWins << " new version draws: " << computerDraws << " new version losses: " << computerLosses << std::endl;
            std::cout << "new version wins as X: " << computerWinsAsX << " new version draws as X: " << computerDrawsAsX << " new version losses as X: " << computerLossesAsX << std::endl;
            std::cout << "new version wins as O: " << computerWinsAsO << " new version draws as O: " << computerDrawsAsO << " new version losses as O: " << computerLossesAsO << std::endl;
            double newEngineWinrate = ((double)computerWins + (double)computerDraws/2) / (double)(computerWins + computerDraws + computerLosses);
            std::cout << "new engine winrate: " << newEngineWinrate << std::endl;
            double newEngineWinrateAsX = ((double)computerWinsAsX + (double)computerDrawsAsX/2) / (double)(computerWinsAsX + computerDrawsAsX + computerLossesAsX);
            double newEngineWinrateAsO = ((double)computerWinsAsO + (double)computerDrawsAsO/2) / (double)(computerWinsAsO + computerDrawsAsO + computerLossesAsO);
            std::cout << "new engine winrate as X: " << newEngineWinrateAsX << std::endl;
            std::cout << "new engine winrate as O: " << newEngineWinrateAsO << std::endl;
            
            if (movesMade == 0) {
                board.makeMove(4, 4); //first move is always in the center
                movesMade++;
            }
            else if (movesMade == 1) {
                srand(time(NULL));
                //select the second move randomly to get variation in the games
                std::vector<std::vector<int>> legalMoves = board.getLegalMoves();
                int randomMove = rand() % legalMoves.size();
                board.makeMove(legalMoves[randomMove][0], legalMoves[randomMove][1]);
                movesMade++;

            }
            //old version 
            else if ((board.getSideToMove() == 'X' && i % 2 == 0) || (board.getSideToMove() == 'O' && i % 2 == 1)) {
                char oldEngineSide = board.getSideToMove();
                std::vector<int> bestMove = oldEngine.getBestMove(board, oldEngineSide, thinkingTime);
                board.makeMove(bestMove[0], bestMove[1]);
            }
            //new version
            else {
                char newEngineSide = board.getSideToMove();
                std::vector<int> bestMove = newEngine.getBestMove(board, newEngineSide, thinkingTime);
                board.makeMove(bestMove[0], bestMove[1]);
            }

            //sleep for 500ms
            // usleep(500000);
            
            // board.displayBoard();

            if (board.isDrawn()) {
                // std::cout << "Draw!" << std::endl;
                computerDraws++;
                if (i % 2 == 0) {
                    computerDrawsAsX++;
                }
                else {
                    computerDrawsAsO++;
                }
            } else if (board.checkWinner() != ' '){
                // std::cout << board.checkWinner() << " wins!" << std::endl;
                char winner = board.checkWinner();
                if ((winner == 'X' && i % 2 == 0) || (winner == 'O' && i % 2 == 1)) {
                    if (i % 2 == 0) {
                        computerLossesAsO++;
                    }
                    else {
                        computerLossesAsX++;
                    }
                    computerLosses++;
                }
                else {
                    if(i % 2 == 0) {
                        computerWinsAsO++;
                    }
                    else {
                        computerWinsAsX++;
                    }
                    computerWins++;
                }
            }
            computerGamesAsO = computerWinsAsO + computerLossesAsO + computerDrawsAsO;
            computerGamesAsX = computerWinsAsX + computerLossesAsX + computerDrawsAsX;
        }
        // std::cout << "Game over!" << std::endl;
        //  std::cout << "new version wins: " << computerWins << " new version  draws: " << computerDraws << " new version  losses: " << computerLosses << std::endl;
    }
    // std::cout << "new version wins: " << computerWins << " new version draws: " << computerDraws << " new version losses: " << computerLosses << std::endl;
    return 0;
}

