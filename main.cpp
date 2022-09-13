#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

struct Coords {
    short x;
    short y;
};

void printBoard(char board[3][3]) {
    cout << "\033[2J\033[1;1H";
    cout << "   1       2       3\n";
    for (int y = 0; y < 3; y++) {
        cout << "       |       |       \n";
        cout << y + 1 << "   " << board[y][0] << "  |   " << board[y][1] << "   |   " << board[y][2] << endl;
        cout << "       |       |       \n";
        if (y != 2) {
            cout << " ------+-------+-------\n";
        }
    }

}

Coords getPlayerMove(short player) {

    Coords coords;

    while (true) {
        cout << "P" << player << " - Enter move (x y): ";
        cin >> coords.x >> coords.y;

        //Checks if move valid
        short validMoves[] = { 1,2,3 };
        bool xIsValid = false;
        bool yIsValid = false;
        for (short i = 0; i < 3; i++) {
            if (coords.x == validMoves[i])
            {
                xIsValid = true;

            }
            if (coords.y == validMoves[i]) {
                yIsValid = true;

            }
            if (xIsValid == true && yIsValid == true) {
                coords.x--;
                coords.y--;
                return coords;
            }
        }

    }

}

bool isSpaceEmpty(short x, short y, char board[3][3]) {

    if (board[y][x] == ' ') {
        return true;
    }

    cout << "Space Taken\n";
    return false;
}

void placeMove(Coords coords, short player, char playerOneSymbol, char playerTwoSymbol, char board[3][3]) {

    if (player == 1) {
        board[coords.y][coords.x] = playerOneSymbol;
    }
    else if (player == 2) {
        board[coords.y][coords.x] = playerTwoSymbol;
    }
    //return board;
}

bool won(char board[3][3]) {
    for (short i = 0; i < 3; i++) {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][0] == board[i][2]) { // vertical
            return true;
        }
        else if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[0][i] == board[2][i]) { // horizontal
            return true;
        }
    }

    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
        return true;
    }
    else if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
        return true;
    }

    return false;
}

bool playAgain() {
    char option;
    while (true) {
        cout << "Do you want to play again (y/n)? ";
        cin >> option;

        if (option == 'y' || option == 'n') {
            break;
        }
    }

    if (option == 'y') {
        return true;
    }
    else if (option == 'n') {
        return false;
    }
}

void resetBoard(char board[3][3]) {
    for (short y = 0; y < 3; y++) {
        for (short x = 0; x < 3; x++) {
            board[y][x] = ' ';
        }
    }
}

short menu() {
    cout << "\033[2J\033[1;1H";
    cout << "-- Tic Tac Toe --\n";
    cout << "Menu\n";
    cout << "1) Single Player\n2) 2 Player\n3) Exit\n";
    short mode;

    while (true) {
        cout << "\n>> ";
        cin >> mode;
        if (mode == 1 || mode == 2 || mode == 3) {
            return mode;
        }
    }
}

Coords getBotMove(char board[3][3], char playerSymbol, char botSymbol) {
    char symbols[] = { botSymbol, playerSymbol };
    Coords coords;
    for (int i = 0; i < 2; i++) { //run once for blocks, then win possiblities

        for (int z = 0; z < 3; z++) { // for each layer

            // horizontal
            if (board[z][0] == symbols[i] && board[z][1] == symbols[i] && board[z][2] == ' ') {
                coords.x = 2;
                coords.y = z;
                return coords;

            }
            else if (board[z][2] == symbols[i] && board[z][0] == symbols[i] && board[z][1] == ' ') {
                coords.x = 1;
                coords.y = z;
                return coords;
            }
            else if (board[z][1] == symbols[i] && board[z][2] == symbols[i] && board[z][0] == ' ') {
                coords.x = 0;
                coords.y = z;
                return coords;
            }

            // vertical
            if (board[0][z] == symbols[i] && board[1][z] == symbols[i] && board[2][z] == ' ') {
                coords.x = z;
                coords.y = 2;
                return coords;

            }
            else if (board[2][z] == symbols[i] && board[0][z] == symbols[i] && board[1][z] == ' ') {
                coords.x = z;
                coords.y = 1;
                return coords;
            }
            else if (board[1][z] == symbols[i] && board[2][z] == symbols[i] && board[0][z] == ' ') {
                coords.x = z;
                coords.y = 0;
                return coords;
            }
        }
        
        // top left to bottem right
        if (board[0][0] == symbols[i] && board[1][1] == symbols[i] && board[2][2] == ' ') {
            coords.x = 2;
            coords.y = 2;
            return coords;
        
        }
        else if (board[2][2] == symbols[i] && board[0][0] == symbols[i] && board[1][1] == ' ') {
            coords.x = 1;
            coords.y = 1;
            return coords;
        }
        else if (board[1][1] == symbols[i] && board[2][2] == symbols[i] && board[0][0] == ' ') {
            coords.x = 0;
            coords.y = 0;
            return coords;
        }


        // top right to bottem left
        if (board[0][2] == symbols[i] && board[1][1] == symbols[i] && board[2][0] == ' ') {
            coords.x = 0;
            coords.y = 2;
            return coords;

        }
        else if (board[2][0] == symbols[i] && board[0][2] == symbols[i] && board[1][1] == ' ') {
            coords.x = 1;
            coords.y = 1;
            return coords;
        }
        else if (board[1][1] == symbols[i] && board[2][0] == symbols[i] && board[0][2] == ' ') {
            coords.x = 2;
            coords.y = 0;
            return coords;
        }
    }

    while (true) {
        srand(time(0));
        short indexY = rand() % 3 + 1;

        srand(time(0));
        short indexX = rand() % 3 + 1;

        if (board[indexY][indexX] == ' ') {
            coords.x = indexX;
            coords.y = indexY;
            return  coords;
        }
    }
    
}

int main() {

    char board[3][3] = {
      {' ', ' ', ' '},
      {' ', ' ', ' '},
      {' ', ' ', ' '},
    };


    char playerOneSymbol = 'X';
    char playerTwoSymbol = 'O';

    Coords coords;
    short player;

    while (true) {
        short mode = menu();
        if (mode == 3) {
            break;
        }
        while (true) {
            for (short rounds = 0; rounds < 9; rounds++) {
                
                player = (rounds % 2) + 1;
                printBoard(board);

                do {
                    if (mode == 2 && (player == 1 || player == 2) || mode == 1 && player == 1) {
                        coords = getPlayerMove(player);
                    }
                    else if (mode == 1 && player == 2) {
                        coords = getBotMove(board, playerOneSymbol, playerTwoSymbol);
                    }

                } while (!isSpaceEmpty(coords.x, coords.y, board));

                placeMove(coords, player, playerOneSymbol, playerTwoSymbol, board);
                printBoard(board);

                if (won(board)) {
                    cout << "Player " << player << " won!\n";
                    break;
                }

                else if (rounds == 8) {
                    cout << "Draw!\n";
                }

            }
            resetBoard(board);
            if (!playAgain()) {
                break;
            }

            
        }
    }
    return 0;
}