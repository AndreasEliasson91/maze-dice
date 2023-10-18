#pragma once

#include "dice.h"
#include "../mechanics/inventory.h"

#include <array>
#include <map>
#include <string>
#include <vector>

class ActorPosition
{
public:
    inline ActorPosition(int x, int y)
    {
        x_coord = x;
        y_coord = y;
    }
    ~ActorPosition() = default;

    void update_position(std::pair<int, int> new_pos)
    {
        x_coord += new_pos.first;
        y_coord += new_pos.second;
    }
    std::pair<int, int> get_actor_position() const { return {x_coord, y_coord}; }

private:
    int x_coord, y_coord;

};

class Actor
{
public:
    Actor(std::string name, int ap, int dp, int hp, int level, std::pair<int, int> pos);
    virtual ~Actor() = default;

    std::string get_name() const { return name; }
    void set_name(std::string name) { this->name = name; }
    int get_level() const { return level; }
    void set_level(int lev) { level = lev; }
    std::pair<int, int> get_position() const { return position.get_actor_position(); }
    void update_position(std::pair<int, int> new_pos);

protected:
    std::string name;
    ActorPosition position;
    int attack_points, defend_points, health_points, level;

};

class Player : public Actor
{
public:
    Player(std::string name = default_name, int ap = 0, int dp = 0, int hp = 20, int level = 1, std::pair<int, int> pos = start_position);
    virtual ~Player() = default;

    int get_score() const { return score; }
    void set_score(int s) { score = s; } 
    bool still_alive() const { return alive; }
    Inventory get_inventory() const {  return inventory; }

    void move(std::string direction);
    // bool in_battle(Cell current_pos) const { return current_pos.engage(); }
    void reset_and_update();
    
    static constexpr std::pair<int, int> start_position = {0, 0};

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
    Enemy(std::string name, int ap, int dp, int hp, int level, std::pair<int, int> pos = start_position);
    virtual ~Enemy() = default;

private:
    static constexpr std::pair<int, int> start_position = {0, 0};

};