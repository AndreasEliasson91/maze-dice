#include "level.h"

GameLevel::GameLevel(int difficulty, Player &player)
    : difficulty {difficulty}, player {player}
    {
        maze_size = {5,5};
        
        complete = false;
    }