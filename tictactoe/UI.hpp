#pragma once
#include "Board.hpp"

class UI {
private:
    Board board;
    int maxDepth;

    void printBoard() const;
    void playerMove();
    void computerMove();

public:
    UI(int depth);
    void start();
};
