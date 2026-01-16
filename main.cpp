#include <iostream>
#include "Board.hpp"
#include "Minimax.hpp"
#include "UI.hpp"

int main() {
    int max_depth = 4;
    Board board;

    std::cout << "Tic-Tac-Toe\n";
    std::cout << "You play as X, computer plays as O\n";
    std::cout << "Coordinates: row col (0..2)\n";

    print_board(board);

    while (true) {
        // ход игрока
        while (!read_player_move(board)) {
            // повтор ввода
        }

        print_board(board);

        if (board.winner() == Cell::X) {
            std::cout << "You win!\n";
            break;
        }

        if (board.is_full()) {
            std::cout << "Draw!\n";
            break;
        }

        // ход компьютера
        Move ai_move = find_best_move(board, max_depth);
        board.set(ai_move.row, ai_move.col, Cell::O);

        std::cout << "Computer move: "
                  << ai_move.row << " "
                  << ai_move.col << "\n";

        print_board(board);

        if (board.winner() == Cell::O) {
            std::cout << "Computer wins!\n";
            break;
        }

        if (board.is_full()) {
            std::cout << "Draw!\n";
            break;
        }
    }

    return 0;
}
