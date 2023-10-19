#pragma once

#include "actor.h"
#include "item.h"

#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <string>


class Cell
{
public:
    Cell(std::pair<int, int> xy);
    ~Cell() = default;

    Cell(const Cell& other);

    int get_x() const { return x; }
    int get_y() const { return y; }
    std::map<std::string, bool> get_walls() const { return walls; }
    void set_wall(std::string wall, bool val) { this->walls[wall] = val; }
    // Enemy get_enemy() const  { return enemy; }
    // void set_enemy(Enemy en) { enemy = en; }
    // Item get_item() const  { return item; }
    // void set_item(Item it) { item = it; }
    std::pair<int, int> get_maze_position() const { return {x, y}; }
    // bool got_item() const { return item_in_room; }
    void set_position(int x, int y) { this->x = x; this->y = y; }
    void set_got_item(bool got_item) { got_item = got_item; }  // TODO: Make this better

    // bool engage() { return  }
    bool surrounded_by_walls() const;
    void remove_wall(Cell &other_cell, std::string wall);

    void print_walls() const;  // Debug tool, TODO: Remove or move
private:
    int x, y;
    std::map<std::string, bool> walls;
    // bool item_in_room;
    // Item item;
    // Enemy enemy;

};

// TODO: Move set_enemies/items here
class Maze
{
public:
    // Maze(int num_cells_x, int num_cells_y, std::vector<Enemy> enemies, std::vector<Item> items);
    Maze(int num_cells_x, int num_cells_y, std::string out_file);
    ~Maze();

    Cell* get_cell(std::pair<int, int> pos) { return maze.at(pos.first).at(pos.second); }
    std::pair<int, int> get_maze_size() const { return maze_end; }
    int get_num_cells_x() const { return num_cells_x; }
    int get_num_cells_y() const { return num_cells_y; }

    void create_maze();
    std::vector<std::pair<std::string, Cell*>> get_valid_neighbours(const Cell &cell);
    void setup_items_and_enemies(std::vector<Enemy> enemies, std::vector<Item> items);


private:
    int num_cells_x, num_cells_y;
    int start_x, start_y;
    std::pair<int, int> maze_end;
    std::vector<std::vector<Cell*>> maze;

};

void write_map(Maze& maze, const std::string& out_file);