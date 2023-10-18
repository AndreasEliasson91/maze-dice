#pragma once

#include <string>
#include <vector>

// TODO: Move this?
class Item
{
public:
    Item(std::string label, std::string description, std::vector<std::string> actions, std::string storage, std::pair<int, int> pos);
    ~Item() = default;

    std::string get_label() const { return label; }
    std::string get_description() const { return description; }
    std::string get_storage_type() const { return storage; }
    std::vector<std::string> get_actions() const { return actions; }
    
private:
    std::string label, description, storage;
    std::vector<std::string> actions;
    std::pair<int, int> position;

};

// class Chest
// {

// };

// TODO: Move this to a item_utils.h?
// std::string inspect_item(const Cell &current_location, std::string label);
// void pick_up_item(Player &player, std::string label, Cell &current_location);
// void drop_item(Player &player, std::string label, Cell &current_location);