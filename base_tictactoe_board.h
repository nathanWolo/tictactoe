#ifndef BASE_TICTACTOE_BOARD_H
#define BASE_TICTACTOE_BOARD_H
#pragma once
class BaseTicTacToeBoard {
    private:
        char board[3][3];
        char sideToMove;
    public:
        BaseTicTacToeBoard();
        void makeMove(int index);
        void unmakeMove(int index);
        void makeMoveSubGame(int index, char sideToMove);
        void unmakeMoveSubGame(int index);
        std::vector<int> getLegalMoves();
        char checkWinner();
        bool isDrawn();
        void displayBoard();
        char getSideToMove();
        void displayBoardSubgame(int row, bool newLine, std::string colorCode);
        std::vector<char> getBoard();
};

#endif // BASE_TICTACTOE_BOARD_H
