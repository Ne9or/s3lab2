#include <iostream>
#include <limits>

#include "tictactoe/Board.hpp"
#include "tictactoe/Minimax.hpp"
#include "tictactoe/UI.hpp"

int choose_difficulty() {
    int choice;

    while (true) {
        std::cout << "\nChoose AI difficulty:\n";
        std::cout << "1 - Easy\n";
        std::cout << "2 - Medium\n";
        std::cout << "3 - Hard\n";
        std::cout << "Your choice: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Try again.\n";
            continue;
        }

        if (choice >= 1 && choice <= 3)
            return choice;

        std::cout << "Please choose 1, 2 or 3.\n";
    }
}

int depth_from_choice(int choice) {
    if (choice == 1) return 4;
    if (choice == 2) return 5;
    return 7;
}

bool choose_first_player() {
    int choice;

    while (true) {
        std::cout << "\nWho moves first?\n";
        std::cout << "1 - Player (X)\n";
        std::cout << "2 - Computer (O)\n";
        std::cout << "Your choice: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Try again.\n";
            continue;
        }

        if (choice == 1) return true;
        if (choice == 2) return false;

        std::cout << "Please choose 1 or 2.\n";
    }
}

int main() {
    std::cout << "=== Tic-Tac-Toe ===\n";

    int difficulty = choose_difficulty();
    int max_depth = depth_from_choice(difficulty);

    bool player_turn = choose_first_player();

    std::cout << "\nYou play as X\n";
    std::cout << "AI depth: " << max_depth << "\n";

    Board board;
    print_board(board);

    while (true) {
        if (player_turn) {
            while (!read_player_move(board)) {}

            print_board(board);

            if (board.winner() == Cell::X) {
                std::cout << "You win!\n";
                break;
            }
        } else {
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
        }

        if (board.is_full()) {
            std::cout << "Draw!\n";
            break;
        }

        player_turn = !player_turn;
    }

    return 0;
}
