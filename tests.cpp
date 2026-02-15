#include <gtest/gtest.h>

#include "tictactoe/Board.hpp"
#include "tictactoe/AlphaBeta.hpp"


TEST(BoardTest, DetectWinRow) {

    Board board;

    for (int i = 0; i < 5; i++)
        board.makeMove(0, i, 'X');

    EXPECT_NE(board.checkWinner(), ' ');
}


TEST(BoardTest, DeadPositionDetection) {

    Board board;

    char data[5][5] = {
        {'X','O','O','O','O'},
        {'O','O','O','X',' '},
        {'O','X','X','X','X'},
        {'O','X','X',' ',' '},
        {'X',' ',' ','O','X'}
    };

    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (data[i][j] != ' ')
                board.makeMove(i, j, data[i][j]);

    EXPECT_TRUE(board.isDeadPosition());
}

TEST(AlphaBetaTest, FindImmediateWin) {

    Board board;

    for (int i = 0; i < 4; i++)
        board.makeMove(0, i, 'O');

    auto bestMove = findBestMove(board, 2);

    EXPECT_EQ(bestMove.first, 0);
    EXPECT_EQ(bestMove.second, 4);
}


TEST(AlphaBetaTest, BlockOpponentWin) {

    Board board;

    for (int i = 0; i < 4; i++)
        board.makeMove(0, i, 'X');

    auto bestMove = findBestMove(board, 3);

    EXPECT_EQ(bestMove.first, 0);
    EXPECT_EQ(bestMove.second, 4);
}


TEST(AlphaBetaTest, ReturnsValidMove) {

    Board board;

    auto bestMove = findBestMove(board, 2);

    EXPECT_TRUE(bestMove.first >= 0);
    EXPECT_TRUE(bestMove.second >= 0);
}
