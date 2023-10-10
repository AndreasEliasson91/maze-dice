#pragma once

#include "dice.h"
#include "maze.h"
#include "mechanics/inventory.h"

#include <array>
#include <map>
#include <string>
#include <vector>

struct ActorPosition
{
public:
    inline ActorPosition(int x, int y)
    {
        x_coord = x;
        y_coord = y;
    }
    void update_position(std::array<int, 2> new_pos)
    {
        x_coord += new_pos[0];
        y_coord += new_pos[1];
    }

private:
    int x_coord, y_coord;

};

class Actor 
{
public:
    Actor();
    Actor(std::string name, int ap, int dp, int hp, int level, std::array<int, 2> pos);
    virtual ~Actor() = default;

    std::string get_name() const { return name; }
    void set_name(std::string name) { this->name = name; }
    int get_level() const { return level; }
    void set_level(int lev) { level = lev; }
    ActorPosition get_position() const { return position; }
    void update_position(std::array<int, 2> new_pos);

protected:
    std::string name;
    ActorPosition position;
    int attack_points, defend_points, health_points, level;

};

class Player : public Actor
{
public:
    Player(std::string name = default_name, int ap = 0, int dp = 0, int hp = 20, int level = 1, std::array<int, 2> pos = start_position);
    virtual ~Player() = default;

    int get_score() const { return score; }
    void set_score(int s) { score = s; } 
    bool still_alive() const { return alive; }

    void move(std::string direction);
    bool in_battle(Cell current_pos) const { Cell::engage(current_pos); }
    void reset_and_update();
    
    static constexpr std::array<int, 2> start_position = {0, 0};

protected:
    int score;
    Inventory inventory;
    std::vector<Dice> dices;
    bool alive;

private:
    static constexpr const char* default_name = "Sir Dice-A-Lot";

};

class Enemy : public Actor
{
public:
    Enemy(std::string name, int ap, int dp, int hp, int level, std::array<int, 2> pos = start_position);
    virtual ~Enemy() = default;

private:
    static constexpr std::array<int, 2> start_position = {0, 0};

}