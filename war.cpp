#include "GameManager.h"
#include <iostream>

int main() {
    std::cout << "Welcome to War\n";
    std::cout << "Starting game with 2 Players\n";
    GameManager game(2); // Start a game with 2 players
    game.playGame();
    return 0;
}


