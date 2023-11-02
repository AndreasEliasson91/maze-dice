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
    ~Inventory();

    bool inventory_full(Item item, std::string hand = "");
    bool item_in_inventory(Item item); // TODO: Rename this
    // void process_item_pickup(Item item, Cell current_location);
    void print_inventory() const;

private:
    Pouch* pouch;
    Hand* right_hand;
    Hand* left_hand;

};

class Hand
{
public:
    Hand(Item* it = nullptr);
    ~Hand();

    Item* get_item() const { return item; }
    std::string get_item_label() const { return item->get_label(); }

    void set_item(Item* it) { item = it; }
    void drop_item() { item = nullptr; }

private:
    Item* item;

};
class Pouch
{
public:
    Pouch();
    ~Pouch();

    Item* get_item(std::string id) const;
    std::vector<Item*> get_items() const { return items; }
    int get_num_items() const { return items.size(); }

    void add_item(Item* it);
    void clear_pouch();
    void remove_item(std::string id);

private:
    std::vector<Item*> items;
    int limit;

    static constexpr int default_limit = 3;

};