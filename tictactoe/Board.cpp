
#include "Board.hpp"

Board::Board() : cells(9) {
    for (int i = 0; i < 9; i++) {
        cells.set(i, Cell::Empty);
    }
}

Cell Board::get(int row, int col) const {
    return cells.get(row * 3 + col);
}

void Board::set(int row, int col, Cell value) {
    cells.set(row * 3 + col, value);
}

bool Board::is_full() const {
    for (int i = 0; i < 9; i++) {
        if (cells.get(i) == Cell::Empty)
            return false;
    }
    return true;
}

Cell Board::winner() const {
    static int lines[8][3] = {
        {0,1,2},{3,4,5},{6,7,8},
        {0,3,6},{1,4,7},{2,5,8},
        {0,4,8},{2,4,6}
    };

    for (auto& line : lines) {
        Cell a = cells.get(line[0]);
        if (a != Cell::Empty &&
            a == cells.get(line[1]) &&
            a == cells.get(line[2])) {
            return a;
        }
    }
    return Cell::Empty;
}

ArraySequence<Move>* Board::available_moves() const {
    auto* moves = new ArraySequence<Move>();

    for (int i = 0; i < 9; i++) {
        if (cells.get(i) == Cell::Empty) {
            moves->append({ i / 3, i % 3 });
        }
    }

    return moves;
}
