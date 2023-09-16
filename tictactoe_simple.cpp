#include <iostream>
#include <stdlib.h>

//array for the board
char board[3][3] = {{'1','2','3'},{'4','5','6'},{'7','8','9'}};

int choice, row, column;
char turn = 'X';
bool draw = false;

//function to show the board

void display_board(){
    system("cls");
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


//function to get the player input and update the board

void player_turn(){
    if(turn == 'X'){
        std::cout << "\nPlayer1 [X] turn: ";
    }
    else if(turn == 'O'){
        std::cout << "\nPlayer2 [O] turn: ";
    }
    std::cin >> choice;

    switch(choice){
        case 1: row = 0; column = 0; break;
        case 2: row = 0; column = 1; break;
        case 3: row = 0; column = 2; break;
        case 4: row = 1; column = 0; break;
        case 5: row = 1; column = 1; break;
        case 6: row = 1; column = 2; break;
        case 7: row = 2; column = 0; break;
        case 8: row = 2; column = 1; break;
        case 9: row = 2; column = 2; break;
        default:
            std::cout << "Invalid choice\n";
            break;
    }

    if(turn == 'X' && board[row][column] != 'X' && board[row][column] != 'O'){
        board[row][column] = 'X';
        turn = 'O';
    }
    else if(turn == 'O' && board[row][column] != 'X' && board[row][column] != 'O'){
        board[row][column] = 'O';
        turn = 'X';
    }
    else{
        std::cout << "Box already filled!\nPlease try again!!\n\n";
        player_turn();
    }
    display_board();
}

//function to check the status of the game

bool gameover(){
    //check win
    for(int i = 0; i < 3; i++){
        if(board[i][0] == board[i][1] && board[i][0] == board[i][2] || board[0][i] == board[1][i] && board[0][i] == board[2][i]){
            return false;
        }
    }
    if(board[0][0] == board[1][1] && board[0][0] == board[2][2] || board[0][2] == board[1][1] && board[0][2] == board[2][0]){
        return false;
    }
    //if there is any box not filled
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            //if there is any box not filled
            if(board[i][j] != 'X' && board[i][j] != 'O'){
                return true;
            }
        }
    }
    //draw
    draw = true;
    return false;
}

int main(){
    while(gameover()){
        display_board();
        player_turn();
        gameover();
    }
    if(turn == 'X' && draw == false){
        std::cout << "Player2 [O] Wins!! Congratulations\n";
    }
    else if(turn == 'O' && draw == false){
        std::cout << "Player1 [X] Wins!! Congratulations\n";
    }
    else{
        std::cout << "Game Draw!!\n";
    }
    return 0;
}