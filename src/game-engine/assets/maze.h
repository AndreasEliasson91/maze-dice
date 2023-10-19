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
    ~Cell();

    Cell(const Cell& other);
    Cell(Cell&& other) noexcept;

    Cell& operator=(const Cell& other);

    int get_x() const { return x; }
    int get_y() const { return y; }
    Enemy *get_enemy() const  { return enemy; }
    Item *get_item() const  { return item; }
    std::pair<int, int> get_maze_position() const { return {x, y}; }
    std::map<std::string, bool> get_walls() const { return walls; }

    void set_enemy(std::string name, int ap, int dp, int hp, int level);
    void set_item(std::string label, std::string desc, std::vector<std::string> actions, std::string storage, std::pair<int, int> pos);
    void set_position(int x, int y) { this->x = x; this->y = y; }
    void set_wall(std::string wall, bool val) { this->walls[wall] = val; }

    bool got_item() const { return item != nullptr; }
    bool surrounded_by_walls() const;
    void remove_wall(Cell &other_cell, std::string wall);

    void print_walls() const;  // Debug tool, TODO: Remove or move to utils

private:
    int x, y;
    std::map<std::string, bool> walls;
    Item *item;
    Enemy *enemy;

};

class Maze
{
public:
    Maze(int num_cells_x, int num_cells_y, std::vector<std::string> enemy_ids, std::vector<std::string> item_ids);
    ~Maze();

    Cell* get_cell(std::pair<int, int> pos) const { return maze.at(pos.first).at(pos.second); }
    std::pair<int, int> get_maze_size() const { return maze_end; }
    int get_num_cells_x() const { return num_cells_x; }
    int get_num_cells_y() const { return num_cells_y; }

    void create_maze();
    std::vector<std::pair<std::string, Cell*>> get_valid_neighbours(const Cell &cell);
    void setup_items_and_enemies(std::vector<std::string> enemy_ids, std::vector<std::string> item_ids);


private:
    int num_cells_x, num_cells_y;
    int start_x, start_y;
    std::pair<int, int> maze_end;
    std::vector<std::vector<Cell*>> maze;

};

void write_map(Maze& maze, const std::string& out_file);