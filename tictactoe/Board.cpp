#include "Board.hpp"

Board::Board() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            cells[i][j] = ' ';
}

bool Board::makeMove(int row, int col, char player) {
    if (cells[row][col] != ' ')
        return false;

    cells[row][col] = player;
    return true;
}

bool Board::isFree(int row, int col) const {
    return cells[row][col] == ' ';
}

bool Board::isFull() const {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (cells[i][j] == ' ')
                return false;
    return true;
}

char Board::getCell(int row, int col) const {
    return cells[row][col];
}

char Board::checkWinner() const {

    // строки
    for (int i = 0; i < SIZE; i++) {
        char first = cells[i][0];
        if (first == ' ') continue;

        bool win = true;
        for (int j = 1; j < SIZE; j++)
            if (cells[i][j] != first)
                win = false;

        if (win) return first;
    }

    // столбцы
    for (int j = 0; j < SIZE; j++) {
        char first = cells[0][j];
        if (first == ' ') continue;

        bool win = true;
        for (int i = 1; i < SIZE; i++)
            if (cells[i][j] != first)
                win = false;

        if (win) return first;
    }

    // главная диагональ
    char first = cells[0][0];
    if (first != ' ') {
        bool win = true;
        for (int i = 1; i < SIZE; i++)
            if (cells[i][i] != first)
                win = false;
        if (win) return first;
    }

    // побочная диагональ
    first = cells[0][SIZE - 1];
    if (first != ' ') {
        bool win = true;
        for (int i = 1; i < SIZE; i++)
            if (cells[i][SIZE - 1 - i] != first)
                win = false;
        if (win) return first;
    }

    return ' ';
}

int Board::evaluate() const {

    char winner = checkWinner();

    if (winner == 'O') return 10000;
    if (winner == 'X') return -10000;

    int score = 0;

    // строки
    for (int i = 0; i < SIZE; i++) {
        int xCount = 0;
        int oCount = 0;

        for (int j = 0; j < SIZE; j++) {
            if (cells[i][j] == 'X') xCount++;
            if (cells[i][j] == 'O') oCount++;
        }

        if (xCount > 0 && oCount == 0)
            score += xCount * xCount;

        if (oCount > 0 && xCount == 0)
            score -= oCount * oCount;
    }

    // столбцы
    for (int j = 0; j < SIZE; j++) {
        int xCount = 0;
        int oCount = 0;

        for (int i = 0; i < SIZE; i++) {
            if (cells[i][j] == 'X') xCount++;
            if (cells[i][j] == 'O') oCount++;
        }

        if (xCount > 0 && oCount == 0)
            score += xCount * xCount;

        if (oCount > 0 && xCount == 0)
            score -= oCount * oCount;
    }

    return score;
}

bool Board::isDeadPosition() const {

    bool xPossible = false;
    bool oPossible = false;

    auto checkLine = [&](int dx, int dy, int startX, int startY) {

        bool hasX = false;
        bool hasO = false;
        bool hasEmpty = false;

        int x = startX;
        int y = startY;

        for (int i = 0; i < SIZE; i++) {

            if (cells[x][y] == 'X') hasX = true;
            if (cells[x][y] == 'O') hasO = true;
            if (cells[x][y] == ' ') hasEmpty = true;

            x += dx;
            y += dy;
        }

        if (hasEmpty) {
            if (!hasO) xPossible = true;
            if (!hasX) oPossible = true;
        }
    };

    // строки
    for (int i = 0; i < SIZE; i++)
        checkLine(0, 1, i, 0);

    // столбцы
    for (int j = 0; j < SIZE; j++)
        checkLine(1, 0, 0, j);

    // диагонали
    checkLine(1, 1, 0, 0);
    checkLine(1, -1, 0, SIZE - 1);

    return (!xPossible && !oPossible);
}

