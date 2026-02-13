#include "tictactoe/UI.hpp"

int main() {

    int depth = 3;   // глубина поиска

    UI ui(depth);
    ui.start();

    return 0;
}
