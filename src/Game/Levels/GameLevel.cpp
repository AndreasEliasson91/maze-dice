#include "level.h"
#include "utils.h"

// #include "controller/api.h"

// TODO: std::vector<Enemy> get_enemies(int num_enemies);
GameLevel::GameLevel(int difficulty, Player &player)
    : difficulty {difficulty}, player {player}
    {
        maze_size = std::make_pair(5, 5);
        enemies = set_level_enemies(3);
        items = set_level_items(2);
        maze = Maze(maze_size.first, maze_size.second, enemies, items);
        level_complete = false;
    }

// TODO: Implement based on instream file
std::vector<Enemy> GameLevel::set_level_enemies(int num_enemies)
{
    std::vector<Enemy> temp = {
            Enemy("skeleton", 1, 0, 5, 0),
            Enemy("ghoul", 2, 0, 10, 0),
            Enemy("skeleton", 1, 0, 5, 0)
        };
    return temp;
}
std::vector<Item> GameLevel::set_level_items(int num_items)
{
    std::vector<Item> temp = {
        Item("key", "golden key", {"get", "drop", "check", "investigate"}, "pouch", {0,0}),
        Item("sword", "short sword", {"get", "drop", "check", "investigate"}, "hand", {0,0})
    };
    return temp;
}

Enemy GameLevel::get_enemy_by_label(std::string label)
{
    for (const auto& enemy : enemies)
    {
        if (enemy.get_name() == label)
            return enemy;
    }
    return;
}
Item GameLevel::get_item_by_label(std::string label)
{
    for (const auto& item : items)
    {
        if (item.get_label() == label)
            return item;
    }
    return;
}

// TODO: process_user_input() merge with run()?
// TODO: Write "FOR YOUR INFORMATION..." as game tips
void GameLevel::run()
{
    print_maze_info();
    
    while (!level_complete && player.still_alive())
        process_user_input(*this);

    if (player.still_alive())
        std::cout << "You enter a new maze. Your current score is " << player.get_score()
                  << ", well done!\n\n" << "FOR YOUR INFORMATION: Your pouch will lose it's belongings, but the items in your hands will remain."
                  << "You will also gain some extra health points for your journey. Good luck!" << std::endl;
}

// TODO: Move print funcs to a output-handler
void GameLevel::print_maze_info(std::string came_from)
{
    if (came_from != "")
        std::cout << "You came from " << came_from << std::endl;
    
    // if (this->player.get_inventory().item_in_inventory("lantern"))
    // {
    //     std::cout << "You've got the lantern. It lights up your surroundings.\n You can go: " << std::endl;
    //     for (auto &direction : this->maze.get_cell(this->player.get_position()).get_walls())
    //         std::cout << "* " << direction << std::endl;
    //     if (this->maze.get_cell(this->player.get_position()).got_item())
    //         std::cout << "Ther is a " << this->maze.get_cell_item(this->player.get_position()).get_description() 
    //                   << " in here, maybe CHECK it out?" << std::endl;
    // }
    // else
    // {
    //     std::cout << "The area is very dark!" << std::endl;
    //     if (this->maze.get_cell(this->player.get_position()).got_item())
    //         std::cout << "There is something in here, maybe CHECK it out?" << std::endl;
    // }
}