#include "GameManager.h"
#include <iostream>
#include <string>

int main() {
    std::cout << " #     #                                              #######           #     # \n " <<
                "#  #  # ###### #       ####   ####  #    # ######       #     ####     #  #  #   ##   #####  \n " <<
                "#  #  # #      #      #    # #    # ##  ## #            #    #    #    #  #  #  #  #  #    # \n " <<
                "#  #  # #####  #      #      #    # # ## # #####        #    #    #    #  #  # #    # #    # \n " <<
                "#  #  # #      #      #      #    # #    # #            #    #    #    #  #  # ###### #####  \n " <<
                "#  #  # #      #      #    # #    # #    # #            #    #    #    #  #  # #    # #   #  \n " <<
                " ## ##  ###### ######  ####   ####  #    # ######       #     ####      ## ##  #    # #    # \n";
    std::cout << "Press Enter to start game with 2 Players\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    GameManager game(2); // Start a game with 2 players
    game.playGame();
    return 0;
}


