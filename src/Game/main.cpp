// #include "game.h"
#include "./assets/actor.h"
#include "./assets/maze.h"
#include "./mechanics/level.h"

#include <iostream>

int main()
{
    Player player = Player("Player One", 10, 10, 10, 1, {1, 1});

    // std::cout << "Inventory " << player.get_name() << " : "; player.get_inventory()->print_inventory();
    // std::cout << std::endl;

    // std::cout << std::boolalpha << player.get_name() << " alive status: " << player.still_alive() << std::endl;

    // std::cout << "Position: (" << player.get_position().first << "," << player.get_position().second << ")" << std::endl;
    // player.update_position({1,1});
    // std::cout << "New Position: (" << player.get_position().first << "," << player.get_position().second << ")" << std::endl;

    // std::cout << "Stats:" << std::endl;
    // std::cout << "LEVEL: " << player.get_stat_by_key("level") << std::endl;
    // std::cout << "HP: " << player.get_stat_by_key("hp") << std::endl;
    // std::cout << "DMG: " << player.get_stat_by_key("ap") << std::endl;
    // std::cout << "ARM: " << player.get_stat_by_key("dp") << std::endl;

    // std::cout << "Score: " << player.get_score() << std::endl << std::endl;

    // player.reset_and_update();
    // std::cout << "Stats:" << std::endl;
    // std::cout << "LEVEL: " << player.get_stat_by_key("level") << std::endl;
    // std::cout << "HP: " << player.get_stat_by_key("hp") << std::endl;
    // std::cout << "DMG: " << player.get_stat_by_key("ap") << std::endl;
    // std::cout << "ARM: " << player.get_stat_by_key("dp") << std::endl;


    // Maze maze01 = Maze(4, 4, {"skeleton", "banana-man", "Joe Rogan"}, {"door", "key", "flying carpet"});

    return 0;
}