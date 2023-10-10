#pragma once

#include "assets/actor.h"
#include "assets/item.h"
#include "assets/maze.h"


#include <array>
#include <iostream>
#include <vector>

class GameLevel
{
public:
    GameLevel(int difficulty, Player &player);
    ~GameLevel() = default;

    std::array<int, 2> get_maze_size() const { return maze_size; }
    void update_maze_size();
    Player get_player() const { return player; }
    Maze get_maze() const { return maze; }

    std::vector<Item> get_level_items(int num_items);
    void run();
    void print_maze_info(std::string came_from = nullptr);

private:
    std::array<int, 2> maze_size;
    Maze maze;
    std::vector<Enemy> enemies;
    Player player;
    int difficulty;
    bool level_complete;

};