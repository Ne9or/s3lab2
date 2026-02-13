#pragma once

class Board {
private:
    static const int SIZE = 5;
    char cells[SIZE][SIZE];

public:
    Board();

    bool makeMove(int row, int col, char player);
    bool isFree(int row, int col) const;
    bool isFull() const;

    char checkWinner() const;
    int evaluate() const;

    char getCell(int row, int col) const;
};
