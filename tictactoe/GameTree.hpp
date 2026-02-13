#pragma once
#include "Node.hpp"

class GameTree {
private:
    Node* root;
    int maxDepth;

    void buildTree(Node* node);
    int minimax(Node* node);

public:
    GameTree(const Board& initial, int depth);
    ~GameTree();

    void findBestMove(int& row, int& col);
};
