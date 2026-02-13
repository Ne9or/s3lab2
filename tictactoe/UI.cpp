#include <iostream>
#include <limits>
#include "UI.hpp"
#include "GameTree.hpp"

using namespace std;

UI::UI(int depth) {
    maxDepth = depth;
}

void UI::printBoard() const {

    cout << "\n      0   1   2   3   4\n";
    cout << "    +---+---+---+---+---+\n";

    for (int i = 0; i < 5; i++) {

        cout << "  " << i << " |";

        for (int j = 0; j < 5; j++) {
            cout << " " << board.getCell(i, j) << " |";
        }

        cout << "\n";
        cout << "    +---+---+---+---+---+\n";
    }

    cout << endl;
}


void UI::playerMove() {

    int row, col;

    while (true) {

        cout << "Ваш ход (строка столбец): ";

        cin >> row >> col;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Некорректный ввод! Введите два числа.\n";
            continue;
        }

        if (row < 0 || row >= 5 || col < 0 || col >= 5) {
            cout << "Координаты вне диапазона 0–4.\n";
            continue;
        }

        if (!board.isFree(row, col)) {
            cout << "Клетка занята!\n";
            continue;
        }

        board.makeMove(row, col, 'X');
        break;
    }
}


void UI::computerMove() {

    GameTree tree(board, maxDepth);

    int bestRow = -1;
    int bestCol = -1;

    tree.findBestMove(bestRow, bestCol);

    if (bestRow != -1 && bestCol != -1)
        board.makeMove(bestRow, bestCol, 'O');
}

void UI::start() {

    while (true) {

        printBoard();

        playerMove();

        if (board.checkWinner() == 'X') {
            printBoard();
            cout << "Вы выиграли!\n";
            break;
        }

        if (board.isFull()) {
            printBoard();
            cout << "Ничья!\n";
            break;
        }

        computerMove();

        if (board.checkWinner() == 'O') {
            printBoard();
            cout << "Компьютер выиграл!\n";
            break;
        }

        if (board.isFull()) {
            printBoard();
            cout << "Ничья!\n";
            break;
        }
    }
}
