#pragma once

#include "level.h"

#include <iostream>
#include <map>
#include <string>

enum ValidCommands
{
    go,
    get,
    check,
    drop,
    open,
    inspect,
    inventory,
    quit
};
static std::map<std::string, ValidCommands> s_mapCommands {
    {"go", go},
    {"get", get},
    {"check", check},
    {"drop", drop},
    {"open", open},
    {"inspect", inspect}
};
const std::map<std::string, std::string> opposite_directions = {
    {"north", "south"},
    {"south", "north"},
    {"east", "west"},
    {"west", "east"}
};


// TODO: Fix this properly
void process_user_input(GameLevel &level)
{
    std::string came_from {}, command {};
    Cell* current_location = level.get_maze().get_cell(level.get_player().get_position());
    std::cout << ">> "; std::getline(std::cin, command);

    switch (s_mapCommands[command])
    {
    case go:
        std::cout << "You go, girl!" << std::endl;
        break;
    case get:
        std::cout << "You get that thingy-ma-bow!" << std::endl;
        break;
    case check:
        std::cout << "Check it out!" << std::endl;
        break;
    case drop:
        std::cout << "Drop that, all on the floor!" << std::endl;
        break;
    case open:
        std::cout << "Open up!" << std::endl;
        break;
    case inspect:
        std::cout << "Du-du-du-dudu Inspector Gadget, Du-dudu-dudu-du-du!" << std::endl;
        break;
    default:
        break;
    }

    delete current_location;
}