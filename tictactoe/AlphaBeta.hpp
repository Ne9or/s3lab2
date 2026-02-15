#pragma once

#include "Board.hpp"
#include <utility>

int alphaBeta(Board& board, int depth, int maxDepth, int alpha, int beta, bool maximizingPlayer);

std::pair<int,int> findBestMove(Board& board, int maxDepth);
