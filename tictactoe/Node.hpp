#pragma once
#include "Board.hpp"
#include "../sequence/ArraySequence.hpp"

struct Node {

    Board state;
    ArraySequence<Node*> children;

    int value;
    bool maximizing;
    int depth;

    int moveRow;
    int moveCol;

    Node() {
        value = 0;
        maximizing = true;
        depth = 0;
        moveRow = -1;
        moveCol = -1;
    }

    ~Node() {
        for (int i = 0; i < children.get_size(); i++)
            delete children.get(i);
    }
};
