#pragma once

#include "../game/levels/GameLevel.h"

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
static std::map<std::string, ValidCommands> s_MapCommands {
    {"go", go},
    {"get", get},
    {"check", check},
    {"drop", drop},
    {"open", open},
    {"inspect", inspect}
};
const std::map<std::string, std::string> s_OppositeDirections = {
    {"north", "south"},
    {"south", "north"},
    {"east", "west"},
    {"west", "east"}
};


// TODO: Fix this properly
void ProcessUserInput(GameLevel &level)
{
    std::string cameFrom {}, command {};
    MCell* currentLocation = level.getMaze().getCell(level.getPlayer().getPosition());
    std::cout << ">> "; std::getline(std::cin, command);

    switch (s_MapCommands[command])
    {
    case go:
        std::cout << "You go, girl!\n";
        break;
    case get:
        std::cout << "You get that thingy-ma-bow!\n";
        break;
    case check:
        std::cout << "Check it out!\n";
        break;
    case drop:
        std::cout << "Drop that, all on the floor!\n";
        break;
    case open:
        std::cout << "Open up!\n";
        break;
    case inspect:
        std::cout << "Du-du-du-dudu Inspector Gadget, Du-dudu-dudu-du-du!\n";
        break;
    default:
        break;
    }

    delete currentLocation;
}