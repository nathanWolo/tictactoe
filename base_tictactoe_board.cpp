#include <iostream>
#include <vector>
#include <stdlib.h>
#include "base_tictactoe_board.h"

BaseTicTacToeBoard::BaseTicTacToeBoard() {
    // Initialize class member board
    board[0][0] = '0'; board[0][1] = '1'; board[0][2] = '2';
    board[1][0] = '3'; board[1][1] = '4'; board[1][2] = '5';
    board[2][0] = '6'; board[2][1] = '7'; board[2][2] = '8';
    
    // Initialize class member sideToMove
    sideToMove = 'X';
}

    std::vector<char> BaseTicTacToeBoard::getBoard() {
        std::vector<char> boardVector;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; j++) {
                boardVector.push_back(board[i][j]);
            }
        }
        return boardVector;
    }
    void BaseTicTacToeBoard::makeMove(int index) {
        int row = index / 3;
        int col = index % 3;
        if (board[row][col] == 'X' || board[row][col] == 'O') {
            std::cout << "Illegal move!\n";
            exit(1);
        }
        board[row][col] = sideToMove;
        if (sideToMove == 'X') {
            sideToMove = 'O';
        } else {
            sideToMove = 'X';
        }
    }

    void BaseTicTacToeBoard::unmakeMove(int index) {
        int row = index / 3;
        int col = index % 3;
        board[row][col] = std::to_string(index)[0];
        if (sideToMove == 'X') {
            sideToMove = 'O';
        } else {
            sideToMove = 'X';
        }
    }

    void BaseTicTacToeBoard::makeMoveSubGame(int index, char sideToMove) {
        int row = index / 3;
        int col = index % 3;
        if (board[row][col] == 'X' || board[row][col] == 'O') {
            std::cout << "Illegal move!\n";
            exit(1);
        }
        board[row][col] = sideToMove;
    }

    void BaseTicTacToeBoard::unmakeMoveSubGame(int index) {
        int row = index / 3;
        int col = index % 3;
        board[row][col] = std::to_string(index)[0];
    }

    std::vector<int> BaseTicTacToeBoard::getLegalMoves() {
        std::vector<int> legalMoves;
        for (int i = 0; i < 9; ++i) {
            int row = i / 3;
            int col = i % 3;
            if (board[row][col] != 'X' && board[row][col] != 'O') {
                legalMoves.push_back(i);
            }
        }
        return legalMoves;
    }

    char BaseTicTacToeBoard::getSideToMove() {
        return sideToMove;
    }

    char BaseTicTacToeBoard::checkWinner() {
        // Check rows
        for (int i = 0; i < 3; ++i) {
            if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && (board[i][0] == 'X' || board[i][0] == 'O')) {
                return board[i][0];
            }
        }
        // Check columns
        for (int i = 0; i < 3; ++i) {
            if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && (board[0][i] == 'X' || board[0][i] == 'O')) {
                return board[0][i];
            }
        }
        // Check diagonals
        if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && (board[0][0] == 'X' || board[0][0] == 'O')) {
            return board[0][0];
        }
        if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && (board[0][2] == 'X' || board[0][2] == 'O')) {
            return board[0][2];
        }
        return ' ';
    }

    char BaseTicTacToeBoard::checkTwoInARowSubgame() {
        //returns X if just X has a two in a row, O if just O has a two in a row, ' ' if neither and 'B' if both
        //only counts as a two in a row if its not blocked, i.e next move could win the game
        char players[2] = {'X', 'O'};
        int xCount = 0;
        int oCount = 0;
        for(int player = 0; player < 2; ++player) {
            sideToMove=players[player];
            std::vector<int> legalMoves = getLegalMoves();
            for(int move = 0; move < legalMoves.size(); move++) {
                makeMoveSubGame(legalMoves[move], sideToMove);
                if(checkWinner() == sideToMove) {
                    if (sideToMove == 'X') {
                        xCount++;
                    }
                    else {
                        oCount++;
                    }
                }
                unmakeMoveSubGame(legalMoves[move]);
            }
        }
        if (xCount > 0 && oCount > 0) {
            return 'B';
        }
        else if (xCount > 0) {
            return 'X';
        }
        else if (oCount > 0) {
            return 'O';
        }
        else {
            return ' ';
        }

    }

    bool BaseTicTacToeBoard::isDrawn() {
        return checkWinner() == ' ' && getLegalMoves().size() == 0;
    }

    //method for drawing board to console
    void BaseTicTacToeBoard::displayBoard(){
        system("clear");
        std::cout << "\n\n\tTic Tac Toe\n\n";
        std::cout << "Player1 [X] \nPlayer2 [O]\n\n";
        std::cout << " | | \n";
        std::cout << board[0][0] << "|" << board[0][1] << "|" << board[0][2] << "\n";
        std::cout << "_|_|_\n";
        std::cout << " | | \n";
        std::cout << board[1][0] << "|" << board[1][1] << "|" << board[1][2] << "\n";
        std::cout << "_|_|_\n";
        std::cout << " | | \n";
        std::cout << board[2][0] << "|" << board[2][1] << "|" << board[2][2] << "\n";
    }

    void BaseTicTacToeBoard::displayBoardSubgame(int row, bool newLine, std::string colorCode) {
        if (row < 0 || row > 2) {
            std::cout << "Invalid row!\n";
            exit(1);
        }
        std::vector<std::string> rowIndexColors;

        //if the square is occupied by X set the color to blue, if it is occupied by O set the color to red, else white

        //check if passed color code is default color code
        if (colorCode == "\033[0m") {
            for (int i = 0; i < 3; ++i) {
                if (board[row][i] == 'X') {
                    rowIndexColors.push_back("\033[1;34m");
                }
                else if (board[row][i] == 'O') {
                    rowIndexColors.push_back("\033[1;31m");
                }
                else {
                    rowIndexColors.push_back("\033[0m");
                }
            }
            if (newLine) {
                std::cout << rowIndexColors[0] << board[row][0] << "\033[0m" 
                << "|" << rowIndexColors[1] << board[row][1] << "\033[0m"
                << "|" << rowIndexColors[2] << board[row][2] << "\033[0m" << "\n";
            }
            else {
                // std::cout << colorCode << board[row][0] << "|" << board[row][1] << "|" << board[row][2] << ' ' << "\033[0m";
                std::cout << rowIndexColors[0] << board[row][0] << "\033[0m"
                << "|" << rowIndexColors[1] << board[row][1] << "\033[0m"
                << "|" << rowIndexColors[2] << board[row][2] << "\033[0m" << ' ';
            }
        }
        else {
            if (newLine) {
                std::cout << colorCode << board[row][0] << "|" << board[row][1] << "|" << board[row][2] << "\n" << "\033[0m";
            }
            else {
                std::cout << colorCode << board[row][0] << "|" << board[row][1] << "|" << board[row][2] << ' ' << "\033[0m";
            }
        }

    }