#include <iostream>
#include <vector>
#include <stdlib.h>
#include "utt_board.h"
#include "base_tictactoe_board.h"

MoveStack::MoveStack() {
    stack = std::vector<std::vector<int>>();
}

void MoveStack::push(std::vector<int> move) {
    stack.push_back(move);
}

std::vector<int> MoveStack::pop() {
    std::vector<int> move = stack.back();
    stack.pop_back();
    return move;
}

std::vector<int> MoveStack::peek() {
    return stack.back();
}

bool MoveStack::isEmpty() {
    return stack.size() == 0;
}



UltimateTicTacToeBoard::UltimateTicTacToeBoard() {
    sideToMove = 'X';
    //stack of previous moves to help determine which sub-board to play in
    moveStack = MoveStack();
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; j++) {
            ultimateBoard[i][j] = BaseTicTacToeBoard();
        }
    }
}

void UltimateTicTacToeBoard::makeMove(int metaIndex, int subIndex) {
    if (!moveStack.isEmpty()) {
        int legalMetaIndex = moveStack.peek()[1];
        if (metaIndex != legalMetaIndex 
                && ultimateBoard[legalMetaIndex / 3][legalMetaIndex % 3].checkWinner() != 'X' 
                && ultimateBoard[legalMetaIndex / 3][legalMetaIndex % 3].checkWinner() != 'O'
                && !ultimateBoard[legalMetaIndex / 3][legalMetaIndex % 3].isDrawn()) {
            std::cout << "Illegal move! Must play in sub-board " << legalMetaIndex << std::endl;
            exit(1);
        }
    }
    int metaRow = metaIndex / 3;
    int metaCol = metaIndex % 3;
    ultimateBoard[metaRow][metaCol].makeMoveSubGame(subIndex, sideToMove);
    if (sideToMove == 'X') {
        sideToMove = 'O';
    } else {
        sideToMove = 'X';
    }
    moveStack.push({metaIndex, subIndex});
}
void UltimateTicTacToeBoard::unmakeMove(int metaIndex, int subIndex) {
    int metaRow = metaIndex / 3;
    int metaCol = metaIndex % 3;
    ultimateBoard[metaRow][metaCol].unmakeMoveSubGame(subIndex);
    if (sideToMove == 'X') {
        sideToMove = 'O';
    } else {
        sideToMove = 'X';
    }
    moveStack.pop();
}

std::vector<std::vector<int>> UltimateTicTacToeBoard::getLegalMoves() {
    std::vector<std::vector<int>> legalMoves;
    if (moveStack.isEmpty()) {
        // if the move stack is empty, then all sub-boards are legal
        for (int i = 0; i < 9; ++i) {
            int metaRow = i / 3;
            int metaCol = i % 3;

            // if this subgame has already ended, then continue
            if (ultimateBoard[metaRow][metaCol].checkWinner() == 'X' || ultimateBoard[metaRow][metaCol].checkWinner() == 'O' || ultimateBoard[metaRow][metaCol].isDrawn()) {
                continue;
            }

            std::vector<int> subLegalMoves = ultimateBoard[metaRow][metaCol].getLegalMoves();
            for (int j = 0; j < subLegalMoves.size(); ++j) {
                legalMoves.push_back({i, subLegalMoves[j]});
            }
        }
    } else {
        // otherwise, only the sub-board corresponding to the last move is legal
        std::vector<int> lastMove = moveStack.peek();
        int metaRow = lastMove[1] / 3;
        int metaCol = lastMove[1] % 3;

        //if the board corresponding to the last move is full, then all boards are legal
        if (ultimateBoard[metaRow][metaCol].checkWinner() == 'X' || ultimateBoard[metaRow][metaCol].checkWinner() == 'O' || ultimateBoard[metaRow][metaCol].isDrawn()) {
            for (int i = 0; i < 9; ++i) {
                int metaRow = i / 3;
                int metaCol = i % 3;

                // if this subgame has already ended, then continue
                if (ultimateBoard[metaRow][metaCol].checkWinner() == 'X' || ultimateBoard[metaRow][metaCol].checkWinner() == 'O' || ultimateBoard[metaRow][metaCol].isDrawn()) {
                    continue;
                }

                std::vector<int> allSubLegalMoves = ultimateBoard[metaRow][metaCol].getLegalMoves();
                for (int j = 0; j < allSubLegalMoves.size(); ++j) {
                    legalMoves.push_back({i, allSubLegalMoves[j]});
                }
            }
        }
        else {
            std::vector<int> subLegalMoves = ultimateBoard[metaRow][metaCol].getLegalMoves();
            for (int j = 0; j < subLegalMoves.size(); ++j) {
                legalMoves.push_back({lastMove[1], subLegalMoves[j]});
            }
        }
    }
    return legalMoves;
}

char UltimateTicTacToeBoard::getSideToMove() {
    return sideToMove;
}

char UltimateTicTacToeBoard::checkWinner() {
    // std::cout << "checkWinner called" << std::endl;
    // Check rows
    for (int i = 0; i < 3; ++i) {
        if (ultimateBoard[i][0].checkWinner() == ultimateBoard[i][1].checkWinner() 
                    && ultimateBoard[i][1].checkWinner() == ultimateBoard[i][2].checkWinner() 
                    && (ultimateBoard[i][0].checkWinner() == 'X' || ultimateBoard[i][0].checkWinner() == 'O')) {
            
            // std::cout << "checkWinner found a winner: " << ultimateBoard[i][0].checkWinner() << std::endl;
            bool test = ultimateBoard[i][0].checkWinner() != ' ';
            // std::cout << test << std::endl;
            return ultimateBoard[i][0].checkWinner();
        }
    }
    // std::cout << "checkWinner got past rows" << std::endl;
    // Check columns
    for (int i = 0; i < 3; ++i) {
        if (ultimateBoard[0][i].checkWinner() == ultimateBoard[1][i].checkWinner() 
                && ultimateBoard[1][i].checkWinner() == ultimateBoard[2][i].checkWinner() 
                && (ultimateBoard[0][i].checkWinner() == 'X' || ultimateBoard[0][i].checkWinner() == 'O')) {
            
            return ultimateBoard[0][i].checkWinner();
        }
    }
    // std::cout << "checkWinner got past columns" << std::endl;
    // Check diagonals
    if (ultimateBoard[0][0].checkWinner() == ultimateBoard[1][1].checkWinner() 
            && ultimateBoard[1][1].checkWinner() == ultimateBoard[2][2].checkWinner() 
            && (ultimateBoard[0][0].checkWinner() == 'X' || ultimateBoard[0][0].checkWinner() == 'O')) {
        
        return ultimateBoard[0][0].checkWinner();
    }
    // std::cout << "checkWinner got past first diagonal" << std::endl;
    if (ultimateBoard[0][2].checkWinner() == ultimateBoard[1][1].checkWinner() 
            && ultimateBoard[1][1].checkWinner() == ultimateBoard[2][0].checkWinner() && 
            (ultimateBoard[0][2].checkWinner() == 'X' || ultimateBoard[0][2].checkWinner() == 'O')) {
        
        return ultimateBoard[0][2].checkWinner();
    }
    // std::cout << "checkWinner finished with no winner" << std::endl;
    return ' ';
}
bool UltimateTicTacToeBoard::isDrawn() {
    return checkWinner() == ' ' && getLegalMoves().size() == 0;
}

char UltimateTicTacToeBoard::checkWinnerSubGame(int metaRow, int metaCol) {
    return ultimateBoard[metaRow][metaCol].checkWinner();
}

void UltimateTicTacToeBoard::displayBoard() {
    system("clear");
    //set a color code for sub boards that have already been won by X or O, or drawn
    std::string colorCode = "\033[0m";
    // std::cout << "displayBoard called" << std::endl;
    std::cout << "Ultimate Tic-Tac-Toe Board:\n";
    for (int subGameY = 0; subGameY < 3; ++subGameY) {
        for (int row = 0; row < 3; ++row) {
            for (int subGameX = 0; subGameX < 3; ++subGameX) {
                if (ultimateBoard[subGameY][subGameX].checkWinner() == 'X') {
                    colorCode = "\033[34m";
                }
                else if (ultimateBoard[subGameY][subGameX].checkWinner() == 'O') {
                    colorCode = "\033[31m";
                }
                else if (ultimateBoard[subGameY][subGameX].isDrawn()) {
                    colorCode = "\033[33m";
                }
                else {
                    colorCode = "\033[0m";
                }
                ultimateBoard[subGameY][subGameX].displayBoardSubgame(row, subGameX==2, colorCode);
            }
        }
        // std::cout << "---------------";
        // std::cout << "\n";
        std::cout << "--" << subGameY * 3 + 0 << "-----" << subGameY * 3 + 1 << "-----" << subGameY * 3 + 2 << "\n";
    }
}
