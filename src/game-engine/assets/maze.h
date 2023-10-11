#pragma once

#include "actor.h"
#include "item.h"

#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

void write_map(const Maze& maze, const std::string& outFileName);

class Cell
{
public:
    Cell(std::array<int, 2> xy);
    ~Cell() = default;

    void set_item(Item item);
    void set_enemy(Enemy enemy);
    std::array<int, 2> get_maze_position() const { return {x, y}; }

    bool surrounded_by_walls() const;
    void remove_wall(Cell other_cell, std::string wall);
    

private:
    int x, y;
    std::map<std::string, bool> walls;
    Item item;
    Enemy enemy;

};

// TODO: Move set_enemies/items here
class Maze
{

};