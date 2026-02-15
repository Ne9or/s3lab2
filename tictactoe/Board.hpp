#pragma once

#include "../sequence/ArraySequence.hpp"
#include <utility>

class Board {
private:
    static const int SIZE = 5;
    char cells[SIZE][SIZE];

public:
    Board();

    bool makeMove(int row, int col, char player);
    void undoMove(int row, int col);
    bool isFree(int row, int col) const;
    bool isFull() const;
    bool isDeadPosition() const;

    char checkWinner() const;
    int evaluate() const;

    char getCell(int row, int col) const;


    ArraySequence<std::pair<int,int>> getAvailableMoves() const;

    int size() const { return SIZE; }
};
