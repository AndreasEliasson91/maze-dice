// #include "game.h"
#include "./assets/actor.h"
#include "./assets/maze.h"
#include "./mechanics/level.h"

#include <iostream>

int main()
{

    // Player default_player;
    // Player player = Player("Player One", 10, 10, 10, 1, {1, 1});

    // std::cout << "Inventory " << default_player.get_name() << " : "; default_player.get_inventory().print_inventory();
    // std::cout << "Inventory " << player.get_name() << " : "; player.get_inventory().print_inventory();
    // std::cout << std::endl;

    // std::cout << player.get_score() << std::endl;
    // player.reset_and_update();
    // std::cout << player.get_score() << std::endl;


    Maze maze01 = Maze(5, 5, "maze01");
    Maze maze02 = Maze(5, 5, "maze02");
    Maze maze03 = Maze(5, 5, "maze03");
    Maze maze04 = Maze(5, 5, "maze04");

    return 0;
}