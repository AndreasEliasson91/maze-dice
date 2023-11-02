#include "actor.h"

Actor::Actor(std::string name, int ap, int dp, int hp, int level, std::pair<int, int> pos)
    : name {name}, attack_points {ap}, defend_points {dp}, health_points {hp}, level {level}, position {ActorPosition(pos.first, pos.second)}
{ }

void Actor::update_position(std::pair<int, int> new_pos)
{
    if (new_pos == Player::start_position)
        position = ActorPosition(0,0);
    else
        position.update_position(new_pos);
}

int Actor::get_stat_by_key(std::string key) const
{
    std::map<std::string, int> stats {
        {"ap", attack_points},
        {"dp", defend_points},
        {"hp", health_points},
        {"level", level}
    };
    return stats[key];
}


Player::Player(std::string name, int ap, int dp, int hp, int level, std::pair<int, int> pos)
    : Actor {name, ap, dp, hp, level, pos}
{
    score = 0;
    inventory = new Inventory();
    dices = {Dice(), Dice(), Dice()};
    alive = true;
}

Player::~Player()
{
    delete inventory;
}


void Player::move(std::string direction)
{
    const std::map<std::string, std::pair<int, int>> directions = {
        {"north", {0, -1}},
        {"south", {0, 1}},
        {"east", {1, 0}},
        {"west", {-1, 0}}
    };

    for (auto const& [key, val] : directions)
    {
        if (direction == key)
        {
            update_position(val);
            break;
        }
    }
}

void Player::reset_and_update()
{
    update_position({0,0});
    if (still_alive())
    {
        inventory->clear_pouch();
        score += (50 * get_stat_by_key("level"));
        set_health_points(get_stat_by_key("hp") + 10);
        level_up();
    }
    else
    {
        inventory =  new Inventory();
        score = 0;
        set_health_points(20);
        set_level(1);
    }
}

Enemy::Enemy(std::string name, int ap, int dp, int hp, int level, std::pair<int, int> pos)
    : Actor {name, ap, dp, hp, level, pos}
{ }