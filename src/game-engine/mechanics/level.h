#pragma once

#include "../assets/actor.h"
#include "../assets/item.h"
#include "../assets/maze.h"


#include <array>
#include <iostream>
#include <vector>

class GameLevel
{
public:
    GameLevel(int difficulty, Player &player);
    ~GameLevel() = default;

    std::pair<int, int> get_maze_size() const { return maze_size; }
    void update_maze_size();
    Player get_player() const { return player; }
    Maze get_maze() const { return maze; }

    std::vector<Enemy> set_level_enemies(int num_enemies);
    std::vector<Enemy> get_enemies() const { return enemies; }
    std::vector<Item> set_level_items(int num_items);
    std::vector<Item> get_items() const { return items; }
    
    Enemy get_enemy_by_label(std::string label); // TODO: Move this
    Item get_item_by_label(std::string label); // TODO: Move this

    void run();
    void print_maze_info(std::string came_from = "");

private:
    std::pair<int, int> maze_size;
    Maze maze;
    std::vector<Enemy> enemies;
    std::vector<Item> items;
    Player player;
    int difficulty;
    bool level_complete;

};