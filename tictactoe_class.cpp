#include <iostream>
#include <vector>
#include <stdlib.h>
class TicTacToeBoard {
    private:
        char board[3][3] = {{'0','1','2'},
                            {'3','4','5'},
                            {'6','7','8'}};
        char sideToMove = 'X';

    public:
        TicTacToeBoard() {
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; j++) {
                    board[i][j] = std::to_string(i * 3 + j)[0];
                }
            }
        }

        void makeMove(int index) {
            int row = index / 3;
            int col = index % 3;
            board[row][col] = sideToMove;
            if (sideToMove == 'X') {
                sideToMove = 'O';
            } else {
                sideToMove = 'X';
            }
        }

        void unmakeMove(int index) {
            int row = index / 3;
            int col = index % 3;
            board[row][col] = std::to_string(index)[0];
            if (sideToMove == 'X') {
                sideToMove = 'O';
            } else {
                sideToMove = 'X';
            }
        }

        std::vector<int> getLegalMoves() {
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

        char getSideToMove() {
            return sideToMove;
        }

        char checkWinner() {
            // Check rows
            for (int i = 0; i < 3; ++i) {
                if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
                    return board[i][0];
                }
            }
            // Check columns
            for (int i = 0; i < 3; ++i) {
                if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
                    return board[0][i];
                }
            }
            // Check diagonals
            if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
                return board[0][0];
            }
            if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
                return board[0][2];
            }
            return ' ';
        }
    
        bool isDrawn() {
            return checkWinner() == ' ' && getLegalMoves().size() == 0;
        }

        //method for drawing board to console
        void display_board(){
            system("clear");
            std::cout << "\n\n\tTic Tac Toe\n\n";
            std::cout << "Player1 [X] \nPlayer2 [O]\n\n";
            std::cout << "     |     |     \n";
            std::cout << "  " << board[0][0] << "  |  " << board[0][1] << "  |  " << board[0][2] << "\n";
            std::cout << "_____|_____|_____\n";
            std::cout << "     |     |     \n";
            std::cout << "  " << board[1][0] << "  |  " << board[1][1] << "  |  " << board[1][2] << "\n";
            std::cout << "_____|_____|_____\n";
            std::cout << "     |     |     \n";
            std::cout << "  " << board[2][0] << "  |  " << board[2][1] << "  |  " << board[2][2] << "\n";
            std::cout << "     |     |     \n";
        }
};

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