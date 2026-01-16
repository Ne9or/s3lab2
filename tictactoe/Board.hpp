#pragma once

#include "../sequence/ArraySequence.hpp"
#include "Cell.hpp"
#include "Move.hpp"

class Board {
private:
    ArraySequence<Cell> cells; // 3x3 => 9 элементов

public:
    Board();

    Cell get(int row, int col) const;
    void set(int row, int col, Cell value);

    bool is_full() const;
    Cell winner() const;

    ArraySequence<Move>* available_moves() const;
};
