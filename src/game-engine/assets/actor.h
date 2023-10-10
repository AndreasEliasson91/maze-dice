#pragma once

#include "dice.h"
#include "mechanics/inventory.h"

#include <array>
#include <string>
#include <vector>

struct ActorPosition
{
    int x_coord, y_coord;
    inline ActorPosition(int x, int y)
    {
        x_coord = x;
        y_coord = y;
    }
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

    void move(std::string direction);
    bool in_battle(std::array<int, 2> current_pos) const;
    void update_stats();
    
    static constexpr std::array<int, 2> start_position = {0, 0};
    
protected:
    int score;
    Inventory inventory;
    std::vector<Dice> dices;
    bool alive;

private:
    static constexpr const char* default_name = "Sir Dice-A-Lot";

};

