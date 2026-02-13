#pragma once
#include "Node.hpp"

class GameTree {
private:
    Node* root;
    int maxDepth;

    int nodesVisited;

    void buildTree(Node* node);
    int alphaBeta(Node* node, int alpha, int beta);

public:
    GameTree(const Board& initial, int depth);
    ~GameTree();

    int getVisitedNodes() const; 

    void findBestMove(int& row, int& col);
};
