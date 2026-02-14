#include "GameTree.hpp"

GameTree::GameTree(const Board& initial, int depth) {

    root = new Node();
    root->state = initial;
    root->depth = 0;
    root->maximizing = true;

    maxDepth = depth;

    nodesVisited = 0;

    buildTree(root);
}

GameTree::~GameTree() {
    delete root;
}

void GameTree::buildTree(Node* node) {

    if (node->depth == maxDepth)
        return;

    if (node->state.checkWinner() != ' ')
        return;

    if (node->state.isFull())
        return;

    char player = node->maximizing ? 'O' : 'X';

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {

            if (node->state.isFree(i, j)) {

                Node* child = new Node();

                child->state = node->state;
                child->state.makeMove(i, j, player);

                child->depth = node->depth + 1;
                child->maximizing = !node->maximizing;

                child->moveRow = i;
                child->moveCol = j;

                node->children.append(child);

                buildTree(child);
            }
        }
    }
}

int GameTree::alphaBeta(Node* node, int alpha, int beta) {

    nodesVisited++;

    if (node->children.get_size() == 0) {
        node->value = node->state.evaluate();
        return node->value;
    }

    if (node->maximizing) {

        int value = -1000000;

        for (int i = 0; i < node->children.get_size(); i++) {

            int childValue = alphaBeta(node->children.get(i), alpha, beta);

            if (childValue > value)
                value = childValue;

            if (value > alpha)
                alpha = value;

            if (beta <= alpha)
                break;
        }

        node->value = value;
        return value;
    }
    else {

        int value = 1000000;

        for (int i = 0; i < node->children.get_size(); i++) {

            int childValue = alphaBeta(node->children.get(i), alpha, beta);

            if (childValue < value)
                value = childValue;

            if (value < beta)
                beta = value;

            if (beta <= alpha)
                break;
        }

        node->value = value;
        return value;
    }
}


void GameTree::findBestMove(int& row, int& col) {

    int bestValue = -1000000;

    int alpha = -1000000;
    int beta = 1000000;

    for (int i = 0; i < root->children.get_size(); i++) {

        Node* child = root->children.get(i);

        int val = alphaBeta(child, alpha, beta);

        if (val > bestValue) {
            bestValue = val;
            row = child->moveRow;
            col = child->moveCol;
        }

        if (val > alpha)
            alpha = val;
    }
}

int GameTree::getVisitedNodes() const {
    return nodesVisited;
}

