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

    int get_x() { return x; }
    int get_y() { return y; }
    // Enemy get_enemy() const  { return enemy; }
    // void set_enemy(Enemy en) { enemy = en; }
    // Item get_item() const  { return item; }
    // void set_item(Item it) { item = it; }
    std::array<int, 2> get_maze_position() const { return {x, y}; }
    void set_position(int x, int y) { x = x; y = y; }

    bool surrounded_by_walls() const;
    void remove_wall(Cell &other_cell, std::string wall);
    

private:
    int x, y;
    std::map<std::string, bool> walls;
    bool got_item;
    // Item item;
    // Enemy enemy;

};

// TODO: Move set_enemies/items here
class Maze
{
public:
    Maze(int num_cells_x, int num_cells_y, std::vector<Enemy> enemies, std::vector<Item> items);
    ~Maze() = default;

    Cell get_cell(std::array<int, 2> pos) { return maze.at(pos[0]).at(pos[1]); }
    std::array<int, 2> get_maze_size() const { return maze_end; }

    void create_maze();
    std::vector<std::pair<std::string, Cell>> get_valid_neighbours(Cell cell);
    void setup_items_and_enemies(std::vector<Enemy> enemies, std::vector<Item> items);


private:
    int num_cells_x, num_cells_y;
    int start_x, start_y;
    std::array<int, 2> maze_end;
    std::vector<std::vector<Cell>> maze;

};