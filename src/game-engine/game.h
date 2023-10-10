#pragma once

#include "assets/actor.h"
#include "mechanics/level.h"

class Game 
{
public:
    Game();
    ~Game() = default;

    int get_difficulty() const { return difficulty_level; }
    void set_difficulty(int difficulty) { difficulty_level = difficulty; }
    int get_levels_completed() const { return levels_completed; }
    void set_levels_completed(int levels_completed) { levels_completed = levels_completed; }

    void update_difficulty() 
    {
        if (levels_completed % 5 == 0)
            difficulty_level++;
    }
    void run() 
    {
        while (player.still_alive()) {            
            update_difficulty();
            game_level = GameLevel(difficulty_level, player);
            game_level.run();
            player.update_stats();
        }

    }

private:
    Player player;
    int difficulty_level, levels_completed;
    GameLevel game_level;

};