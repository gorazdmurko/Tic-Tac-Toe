#include "ticTacToe.h"


int main() {

    board board;
    while (!gameOver && !boardFull) {
        board.onMove();
        board.draw();
        board.usersChoice(gameOver);
        board.logic();
        board.bFull();
        board.changePlayer();
    }

    if (board.winner == 'X' || board.winner == 'O') {
        SetConsoleTextAttribute(col, 6);
        std::cout << "\n\nPlayer " << board.winner << " is the winner\n\n";
        board.draw();
    }
    SetConsoleTextAttribute(col, 7);

    return 0;
}