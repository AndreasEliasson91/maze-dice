#include "actor.h"

Actor::Actor(std::string name, int ap, int dp, int hp, int level, std::array<int, 2> pos)
    : name {name}, attack_points {ap}, defend_points {dp}, health_points {hp}, level {level}, position {ActorPosition(pos[0], pos[1])}
    { }

void Actor::update_position(std::array<int, 2> new_pos)
{
    if (new_pos == Player::start_position)
        position = ActorPosition(0,0);
    else
        position.update_position(new_pos);
}


Player::Player(std::string name, int ap, int dp, int hp, int level, std::array<int, 2> pos)
    : Actor(name, ap, dp, hp, level, pos)
    {
        score = 0;
        inventory = Inventory();
        dices = {Dice(), Dice(), Dice()};
        alive = true;
    }

void Player::move(std::string direction)
{
    const std::map<std::string, std::array<int, 2>> directions = {
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
        inventory.clear_pouch();
        health_points += 10;
        score += (50 * get_level());
        level++;
    }
    else
    {
        inventory = Inventory();
        health_points = 20;
        level = 1;
        score = 0;
    }
}

Enemy::Enemy(std::string name, int ap, int dp, int hp, int level, std::array<int, 2> pos)
    : Actor(name, ap, dp, hp, level, pos)
    { }