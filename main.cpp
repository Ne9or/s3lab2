#include "tictactoe/UI.hpp"
#include <iostream>

int main() {

    std::cout<<"Input depth of search";

    int depth;
    
    std::cin >> depth;

    UI ui(depth);
    ui.start();

    return 0;
}
