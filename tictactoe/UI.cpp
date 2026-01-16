#include "UI.hpp"
#include <iostream>
#include <limits>

static char cell_to_char(Cell c) {
    if (c == Cell::X) return 'X';
    if (c == Cell::O) return 'O';
    return '.';
}

void print_board(const Board& board) {
    std::cout << "\nCurrent board:\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << cell_to_char(board.get(i, j)) << " ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

bool read_player_move(Board& board) {
    int row, col;

    std::cout << "Enter your move (row col): ";

    // 🔹 Проверка: ввели ли именно числа
    if (!(std::cin >> row >> col)) {
        std::cout << "Invalid input. Please enter two numbers.\n";

        // очистка потока
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }

    // 🔹 Проверка диапазона
    if (row < 0 || row > 2 || col < 0 || col > 2) {
        std::cout << "Coordinates must be between 0 and 2.\n";
        return false;
    }

    // 🔹 Проверка занятости клетки
    if (board.get(row, col) != Cell::Empty) {
        std::cout << "This cell is already occupied.\n";
        return false;
    }

    board.set(row, col, Cell::X);
    return true;
}
