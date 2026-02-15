#include "AlphaBeta.hpp"
#include "../sequence/ArraySequence.hpp"
#include <limits>
#include <algorithm>


int alphaBeta(Board& board,
              int depth,
              int maxDepth,
              int alpha,
              int beta,
              bool maximizingPlayer)
{
    char winner = board.checkWinner();

    if (winner == 'O')       
        return 100 - depth;

    if (winner == 'X')      
        return -100 + depth;

    if (board.isFull())
        return 0;

    if (depth >= maxDepth)
        return board.evaluate();


    ArraySequence<std::pair<int,int>> moves =
        board.getAvailableMoves();


    if (maximizingPlayer)
    {
        int bestValue = std::numeric_limits<int>::min();

        for (int i = 0; i < moves.get_size(); i++)
        {
            auto move = moves.get(i);

            board.makeMove(move.first, move.second, 'O');

            int value = alphaBeta(board,
                                  depth + 1,
                                  maxDepth,
                                  alpha,
                                  beta,
                                  false);

            board.undoMove(move.first, move.second);

            bestValue = std::max(bestValue, value);
            alpha = std::max(alpha, value);

            if (beta <= alpha)
                break;
        }

        return bestValue;
    }
    else
    {
        int bestValue = std::numeric_limits<int>::max();

        for (int i = 0; i < moves.get_size(); i++)
        {
            auto move = moves.get(i);

            board.makeMove(move.first, move.second, 'X');

            int value = alphaBeta(board,
                                  depth + 1,
                                  maxDepth,
                                  alpha,
                                  beta,
                                  true);

            board.undoMove(move.first,move.second);

            bestValue = std::min(bestValue, value);
            beta = std::min(beta, value);

            if (beta <= alpha)
                break; 
        }

        return bestValue;
    }
}

std::pair<int,int> findBestMove(Board& board,
                                int maxDepth)
{
    int bestValue = std::numeric_limits<int>::min();
    std::pair<int,int> bestMove{-1, -1};

    ArraySequence<std::pair<int,int>> moves =
        board.getAvailableMoves();

    for (int i = 0; i < moves.get_size(); i++)
    {
        auto move = moves.get(i);

        board.makeMove(move.first, move.second,'O');

        int value = alphaBeta(board,
                              1,
                              maxDepth,
                              std::numeric_limits<int>::min(),
                              std::numeric_limits<int>::max(),
                              false);

        board.undoMove(move.first,move.second);

        if (value > bestValue)
        {
            bestValue = value;
            bestMove = move;
        }
    }

    return bestMove;
}
