#include "Minimax.hpp"
#include <algorithm>

static int lines[8][3] = {
    {0,1,2},{3,4,5},{6,7,8},
    {0,3,6},{1,4,7},{2,5,8},
    {0,4,8},{2,4,6}
};

int evaluate(const Board& board) {
    Cell w = board.winner();
    if (w == Cell::O) return 10;
    if (w == Cell::X) return -10;
    return 0;
}

int heuristic(const Board& board) {
    int score = 0;

    for (auto& line : lines) {
        int o_count = 0;
        int x_count = 0;

        for (int i = 0; i < 3; i++) {
            Cell c = board.get(line[i] / 3, line[i] % 3);
            if (c == Cell::O) o_count++;
            else if (c == Cell::X) x_count++;
        }

        if (o_count > 0 && x_count == 0)
            score += o_count;
        else if (x_count > 0 && o_count == 0)
            score -= x_count;
    }

    return score;
}

int minimax(Board& board, int depth, int max_depth, bool is_maximizing) {
    int score = evaluate(board);

    // терминальное состояние
    if (score != 0)
        return score - depth; // быстрее выиграть — лучше

    if (board.is_full())
        return 0;

    // 🔹 ограничение глубины
    if (depth >= max_depth)
        return heuristic(board);

    if (is_maximizing) {
        int best = -1000;
        auto* moves = board.available_moves();

        for (int i = 0; i < moves->get_size(); i++) {
            Move m = moves->get(i);
            board.set(m.row, m.col, Cell::O);

            best = std::max(
                best,
                minimax(board, depth + 1, max_depth, false)
            );

            board.set(m.row, m.col, Cell::Empty);
        }

        delete moves;
        return best;
    } else {
        int best = 1000;
        auto* moves = board.available_moves();

        for (int i = 0; i < moves->get_size(); i++) {
            Move m = moves->get(i);
            board.set(m.row, m.col, Cell::X);

            best = std::min(
                best,
                minimax(board, depth + 1, max_depth, true)
            );

            board.set(m.row, m.col, Cell::Empty);
        }

        delete moves;
        return best;
    }
}

Move find_best_move(Board& board, int max_depth) {
    int best_value = -1000;
    Move best_move{-1, -1};

    auto* moves = board.available_moves();

    for (int i = 0; i < moves->get_size(); i++) {
        Move m = moves->get(i);
        board.set(m.row, m.col, Cell::O);

        int value = minimax(board, 0, max_depth, false);

        board.set(m.row, m.col, Cell::Empty);

        if (value > best_value) {
            best_value = value;
            best_move = m;
        }
    }

    delete moves;
    return best_move;
}
