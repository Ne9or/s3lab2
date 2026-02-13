#include <gtest/gtest.h>

#include "tictactoe/Board.hpp"
#include "tictactoe/GameTree.hpp"


TEST(BoardTest, DetectWinRow) {

    Board board;

    for (int i = 0; i < 5; i++)
        board.makeMove(0, i, 'X');

    EXPECT_TRUE(board.checkWinner());
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

TEST(GameTreeTest, FindImmediateWin) {

    Board board;

    for (int i = 0; i < 4; i++)
        board.makeMove(0, i, 'X');

    GameTree tree(board, 2);

    int row = -1;
    int col = -1;

    tree.findBestMove(row, col);

    EXPECT_EQ(row, 0);
    EXPECT_EQ(col, 4);
}

TEST(GameTreeTest, BlockOpponentWin) {

    Board board;

    for (int i = 0; i < 4; i++)
        board.makeMove(0, i, 'O');

    GameTree tree(board, 3);

    int row = -1;
    int col = -1;

    tree.findBestMove(row, col);

    EXPECT_EQ(row, 0);
    EXPECT_EQ(col, 4);
}


TEST(GameTreeTest, NodesVisitedPositive) {

    Board board;

    GameTree tree(board, 2);

    int row, col;
    tree.findBestMove(row, col);

    EXPECT_GT(tree.getVisitedNodes(), 0);
}



