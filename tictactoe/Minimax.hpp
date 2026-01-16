#pragma once

#include "Board.hpp"

int evaluate(const Board& board);
int heuristic(const Board& board);

int minimax(Board& board, int depth, int max_depth, bool is_maximizing);

Move find_best_move(Board& board, int max_depth);
