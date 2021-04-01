#include <iostream>
#include <vector>
#include <conio.h>
#include <time.h>
#include <windows.h>

bool gameOver = false;
bool boardFull = false;

HANDLE col = GetStdHandle( STD_OUTPUT_HANDLE );

class board {
    int arrSize = 3;
    char array[3][3];
    char currentPlayer;
    std::vector<char> players = {'X', 'O'};
    void playingBoardArray();
    void startScreen();

    public:
    char winner;
    // constructor
    board() {
        startScreen();
        playingBoardArray();
        selectPlayer();
    }

    void getStartScreen();
    void onMove();
    void draw();
    void selectPlayer();
    void changePlayer();
    void usersChoice(bool& endGame);
    void logic();
    void bFull();
};

void board::playingBoardArray() {
    for (int i = 0; i < arrSize; i++) {
        for (int j = 0; j < arrSize; j++) {
            array[i][j] = ' ';
        }
    }
}

void board::startScreen() {
    SetConsoleTextAttribute(col, 5);
    std::cout << "\n\n";
    std::cout << "***********************************************\n";
    std::cout << "***********************************************\n";
    std::cout << "******                                   ******\n";
    std::cout << "****** - T  I  C -- T  A  C -- T  O  E - ******\n";
    std::cout << "******                                   ******\n";
    std::cout << "***********************************************\n";
    std::cout << "***********************************************\n\n";

    SetConsoleTextAttribute(col, 6);
    std::cout << "\nto exit press ESC or ENTER\n\n";
    SetConsoleTextAttribute(col, 2);
    std::cout << "     |     |     " << "\n"; 
    std::cout << "  1  |  2  |  3  " << "\n";
    std::cout << "_____|_____|_____" << "\n";
    std::cout << "     |     |     " << "\n";
    std::cout << "  4  |  5  |  6  " << "\n";
    std::cout << "_____|_____|_____" << "\n";
    std::cout << "     |     |     " << "\n";
    std::cout << "  7  |  8  |  9  " << "\n";
    std::cout << "     |     |     " << "\n";
    std::cout << "\n";
}

void board::getStartScreen() {
    return this->startScreen();
}

void board::onMove() {
    SetConsoleTextAttribute(col, 6);
    std::cout << "\n\nPlayer " << currentPlayer << " on move\n\n";
}

void board::draw() {
    SetConsoleTextAttribute(col, 4);
    // rows
    for (int j = 0; j < 9; j++) {
        // columns
        for (int i = 0; i < 17; i++) {
            if (j == 2 || j == 5) {
                if (i == 5 || i == 11) {
                    std::cout << "|";
                }
                else {
                    std::cout << "_";
                }
            }
            else if (j == 1 || j == 4 || j == 7) {
                if ( j == 1 && i == 2) {SetConsoleTextAttribute(col, 6); std::cout << array[0][0]; SetConsoleTextAttribute(col, 4);}
                else if ( j == 1 && i == 8) {SetConsoleTextAttribute(col, 6); std::cout << array[0][1]; SetConsoleTextAttribute(col, 4);}
                else if ( j == 1 && i == 14) {SetConsoleTextAttribute(col, 6); std::cout << array[0][2]; SetConsoleTextAttribute(col, 4);}
                else if ( j == 4 && i == 2) {SetConsoleTextAttribute(col, 6); std::cout << array[1][0]; SetConsoleTextAttribute(col, 4);}
                else if ( j == 4 && i == 8) {SetConsoleTextAttribute(col, 6); std::cout << array[1][1]; SetConsoleTextAttribute(col, 4);}
                else if ( j == 4 && i == 14) {SetConsoleTextAttribute(col, 6); std::cout << array[1][2]; SetConsoleTextAttribute(col, 4);}
                else if ( j == 7 && i == 2) {SetConsoleTextAttribute(col, 6); std::cout << array[2][0]; SetConsoleTextAttribute(col, 4);}
                else if ( j == 7 && i == 8) {SetConsoleTextAttribute(col, 6); std::cout << array[2][1]; SetConsoleTextAttribute(col, 4);}
                else if ( j == 7 && i == 14) {SetConsoleTextAttribute(col, 6); std::cout << array[2][2]; SetConsoleTextAttribute(col, 4);}
                else if (i == 5 || i == 11) {
                    std::cout << "|";
                }
                else {
                    std::cout << " ";
                }
                }
            else {
                if (i == 5 || i == 11) {
                    std::cout << "|";
                }
                else {
                    std::cout << " ";
                }
            }
        }
        std::cout << "\n";
    }
}

void board::selectPlayer() {
    srand(time(NULL));
    int random = rand() % 2;
    currentPlayer = players[random];
}

void board::changePlayer() {
    if (currentPlayer == 'X') {
        currentPlayer = 'O';
    }
    else { currentPlayer = 'X'; }
}

void board::usersChoice(bool& endGame) {
    bool endLoop = false;
    SetConsoleTextAttribute(col, 6);
    std::cout << "\nESC to exit\n";
    while (!endLoop) {
        char choice = getch();
        if (choice == 27) {
            endGame = true;
            break;
        }
        // while loop ends when you press 1 - 9
        else if (choice >= 49 && choice <= 57) {
            choice = choice - 49;
            if ((choice >= 0 && choice <= 2) && array[0][choice] == ' ') {
                array[0][choice] = currentPlayer;
                endLoop = !endLoop;
            }
            else if ((choice >= 3 && choice <= 5) && array[1][choice - 3] == ' ') {
                array[1][choice - 3] = currentPlayer;
                endLoop = !endLoop;
            }
            else if ((choice >= 6 && choice <= 8) && array[2][choice - 6] == ' ') {
                array[2][choice - 6] = currentPlayer;
                endLoop = !endLoop;
            }
        }    
    }
    if (!endGame) {
        system("cls");
        startScreen();
    }
    else {
        std::cout << "\nTHANK YOU FOR PLAYING\n";
        system("pause");
    }
}

void board::logic() {
    // ROWS
    int max = 2;
    for (int row = 0; row <= max; row++) {
        char first = array[row][0];
        for (int col = 1; col <= max; col++) {  // ce prvi ni enak, ga brejka in gre v novo vrstico
            if (first != array[row][col]) {
                break;
            }
            else if (col == max && first != ' ') {    // ce pa sta enaka, pa dvignes column
                gameOver = true;
                // changePlayer();
                winner = currentPlayer;
                exit;
            }
        }
    }

    // COLUMNS
    for (int col = 0; col <= max; col++) {
        char first = array[0][col];
        for (int row = 1; row <= max; row++) {
            if (first != array[row][col]) {
                break;
            }
            else if(row == max && first != ' ') {
                gameOver = true;
                winner = currentPlayer;
                exit;
            }
        }
    }

    // DIAGONALS left -> right
    for (int i = 1; i <= max; i++) {
        char first = array[0][0];
        if (first != array[i][i]) {
            break;
        }
        else if (i == max && first != ' ') {
            gameOver = true;
            winner = currentPlayer;
            exit;
        }
    }

    // DIAGONALS right -> left
    int col = max;
    int row = 0;
    int first = array[0][col];
    while (row <= col) {
        col--;  // 2 --> 1 --> 0
        row++;  // 0 --> 1 --> 2
        if (first != array[row][col]) {
            break;
        }
        else if (row == max && first != ' ') {
            gameOver = true;
            winner = currentPlayer;
            exit;
        }
    }
}

void board::bFull() {
    for (int row = 0; row <= 2; row++) {
        for (int col = 0; col <= 2; col++) {
            if (array[row][col] == ' ') {
                return;
            }
        }
    }
    boardFull = true;
    SetConsoleTextAttribute(col, 6);
    std::cout << "\n\nThe board is FULL. Tie Game\n\n";
    draw();
    SetConsoleTextAttribute(col, 6);
    std::cout << "\nTHANK YOU FOR PLAYING\n\n";
}