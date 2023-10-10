#include "actor.h"

Actor::Actor(std::string name, int ap, int dp, int hp, int level, std::array<int, 2> pos)
    : name {name}, attack_points {ap}, defend_points {dp}, health_points {hp}, level {level}, position {ActorPosition(pos[0], pos[1])}
    { }

void Actor::update_position(std::array<int, 2> new_pos)
{
    if (new_pos == Player::start_position)
    {
        position = ActorPosition(0,0);
    }
    else
    {
        position.x_coord += new_pos[0];
        position.y_coord += new_pos[1];
    }
}


Player::Player(std::string name, int ap, int dp, int hp, int level, std::array<int, 2> pos)
    : Actor(name, ap, dp, hp, level, pos)
    {
        score = 0;
        inventory = Inventory();
        dices = {Dice(), Dice(), Dice()};
        alive = true;
    }

