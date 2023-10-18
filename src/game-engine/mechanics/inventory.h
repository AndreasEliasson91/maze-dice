#pragma once

#include "../assets/item.h"
// #include "../assets/maze.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class Inventory
{
public:
    Inventory();
    ~Inventory() = default;

    std::string get_item_form_pouch(std::string label);
    bool inventory_full(Item item, std::string hand = "");
    bool item_in_inventory(Item item); // TODO: Rename this
    // void process_item_pickup(Item item, Cell current_location);
    void clear_pouch() { pouch.clear(); }
    void print_inventory() const;
    void remove_pouch_item(std::string label);

private:
    std::vector<Item> pouch;
    std::string right_hand_label, left_hand_label;  // TODO: better implementation than strings? map? pair<string, string>?
    int pouch_limit {3};

};