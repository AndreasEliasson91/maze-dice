// #include "game.h"
#include "./game/assets/character/Character.h"
#include "./game/assets/maze/Maze.h"
// #include "./game/levels/GameLevel.h"

#include <iostream>
#include <algorithm>
#include <limits>

int main()
{
    CPlayer player = CPlayer("Player One", 10, 10, 10, 1, {1, 1});

    // std::cout << "Inventory " << player.getName() << " : "; player.getInventory()->PrintInventory();
    // std::cout << std::endl;

    // std::cout << std::boolalpha << player.getName() << " alive status: " << player.PlayerStillAlive() << std::endl;

    std::cout << "Position: (" << player.getPosition().first << "," << player.getPosition().second << ")" << std::endl;

    // std::string direction = "north";
    std::string direction = "south";
    // std::string direction = "east";
    // std::string direction = "west";

    std::cout << "Moving " << direction << std::endl;
    player.Move(direction);

    std::cout << "New Position: (" << player.getPosition().first << "," << player.getPosition().second << ")" << std::endl;

    // std::cout << "Stats:" << std::endl;
    // std::cout << "LEVEL: " << player.getStatFromKey("level") << std::endl;
    // std::cout << "HP: " << player.getStatFromKey("hp") << std::endl;
    // std::cout << "DMG: " << player.getStatFromKey("ap") << std::endl;
    // std::cout << "ARM: " << player.getStatFromKey("dp") << std::endl;

    // std::cout << "Score: " << player.getScore() << std::endl << std::endl;

    // player.UpdateStats();
    // std::cout << "Stats:" << std::endl;
    // std::cout << "LEVEL: " << player.getStatFromKey("level") << std::endl;
    // std::cout << "HP: " << player.getStatFromKey("hp") << std::endl;
    // std::cout << "DMG: " << player.getStatFromKey("ap") << std::endl;
    // std::cout << "ARM: " << player.getStatFromKey("dp") << std::endl;


    // MMaze maze01 = MMaze(4, 4, {"skeleton", "banana-man", "Joe Rogan"}, {"door", "key", "flying carpet"});

    return 0;
}