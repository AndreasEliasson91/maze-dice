#include "level.h"
#include "utils.h"

// #include "controller/api.h"

// TODO: std::vector<Enemy> get_enemies(int num_enemies);
GameLevel::GameLevel(int difficulty, Player &player)
    : difficulty {difficulty}, player {player}
    {
        maze_size = {5,5};
        enemies = {
            Enemy("skeleton", 1, 0, 5, 0),
            Enemy("ghoul", 2, 0, 10, 0),
            Enemy("skeleton", 1, 0, 5, 0)
        };  // temp enemies
        maze = Maze(maze_size, get_level_items(2), enemies);
        level_complete = false;
    }

// TODO: Implement based on instream file
std::vector<Item> GameLevel::get_level_items(int num_items)
{
    std::vector<Item> temp = {
        Item("key", "golden key", {"get", "drop", "check", "investigate"}, "pouch", {0,0}),
        Item("sword", "short sword", {"get", "drop", "check", "investigate"}, "hand", {0,0})
    };
    return temp;
}

void GameLevel::run()
{
    print_maze_info();
    
    while (!level_complete && player.still_alive())
    {
        process_user_input(*this);
    }
}