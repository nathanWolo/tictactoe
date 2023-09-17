#ifndef UTT_BOARD_H
#define UTT_BOARD_H
#include "base_tictactoe_board.h"
#pragma once
class MoveStack {
    private:
        std::vector<std::vector<int>> stack;
    public:
        MoveStack();
        void push(std::vector<int> move);
        std::vector<int> pop();
        std::vector<int> peek();
        bool isEmpty();
};

class UltimateTicTacToeBoard {
    private:
        BaseTicTacToeBoard ultimateBoard[3][3];
        char sideToMove;
        //stack of previous moves to help determine which sub-board to play in
        MoveStack moveStack;
    public:
        UltimateTicTacToeBoard();
        void makeMove(int metaIndex, int subIndex);
        void unmakeMove(int metaIndex, int subIndex);
        std::vector<std::vector<int>> getLegalMoves();
        char getSideToMove();
        char checkWinner();
        bool isDrawn();
        char checkWinnerSubGame(int metaRow, int metaCol);
        void displayBoard();
};

#endif 
