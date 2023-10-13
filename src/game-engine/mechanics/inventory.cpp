#include "inventory.h"


Inventory::Inventory()
{
    right_hand_label = "";
    left_hand_label = "";
}

std::string Inventory::get_item_form_pouch(std::string label)
{
    for (auto &item : pouch)
    {
        if (label == item.get_label())
            return item.get_description();
    }
}
// TODO: Fix all nested if-else
// TODO: Figure out a better hand functionality 
bool Inventory::inventory_full(Item item, std::string hand)
{
    if (item.get_storage_type() == "pouch" && pouch.size() >= pouch_limit)
    {
        std::cout << "Your pouch is full\nYou can't pick up " << item.get_description() 
                  << " before you drop something from your pouch!" << std::endl;
        return true;
    }
    else if (item.get_storage_type() == "hand" && hand != "")
    {
        const std::vector<std::string> valid_hand_commands = {"left", "left hand", "right", "right hand"};

        if (left_hand_label != "" && right_hand_label != "")
        {
            std::cout << "Your hands are full\nYou can't pick up " << item.get_description() 
                  << " before you drop something from your hands!" << std::endl;
            return true;
        }
        if ((hand == "left" || hand == "left hand") && left_hand_label != "")
        {
            std::cout << "Your left hand is full\nTry pick up " << item.get_description() 
                  << " with your right hand or before you drop the item in your hand first!" << std::endl;
            return true;
        }
        else if ((hand == "right" || hand == "right hand") && right_hand_label != "")
        {
            std::cout << "Your right hand is full\nTry pick up " << item.get_description() 
                  << " with your left hand or before you drop the item in your hand first!" << std::endl;
            return true;
        }
        else if (std::find(valid_hand_commands.begin(), valid_hand_commands.end(), hand) == valid_hand_commands.end())
        {
            std::cout << "Invalid command" << std::endl;
            return true;
        }
    }
    return false;
}
bool Inventory::item_in_inventory(Item item)
{
    if (right_hand_label != "" && (right_hand_label == item.get_label() || right_hand_label == item.get_description()))
        return true;
    if (left_hand_label != "" && (left_hand_label == item.get_label() || left_hand_label == item.get_description()))
        return true;

    for (const auto& it : pouch)
    {
        if (it.get_description() == item.get_description())
            return true;
    }

    return false;
}
void Inventory::process_item_pickup(Item item, Cell current_location)
{
    if (std::find(item.get_actions().start(), item.get_actions().end(), "get") != item.get_actions().end())
    {
        std::cout << "It seems impossible to pick up the " << item.get_description() << std::endl;
    }
    else if (item.get_storage_type() == "pouch" && !inventory_full(item))
    {
        std::cout << "You pick up the " << item.get_description() << "!" << std::endl;
        pouch.push_back(item);

        // delete current_location.item;
        current_location.set_got_item(false);
    }
    else if (item.get_storage_type() == "hand")
    {
        std::string hand {};
        std::cout << "Which hand do you want to pick up the " << item.get_description() << "with: ";
        std::cin >> hand;

        if (!inventory_full(item, hand))
        {
            std::cout << "You picke up the " << item.get_description() << " in your " << hand << " hand!" << std::endl;
            if hand == "right":
                right_hand_label = item.get_label();
            else
                left_hand_label = item.get_label();
        }
    }
    else
    {
        std::cout << "Your inventory is full!" << std::endl;
    }
}
// TODO: Format this nicely
void Inventory::print_inventory() const
{
    if (pouch.size() == 0 && right_hand_label != "" && left_hand_label != "")
    {
        std::cout << "Your inventory is empty" << std::endl;
    }
    else
    {
        std::cout << "INVENTORY" << std::endl;

        if (pouch.size() > 0)
        {
            for (const auto& item : pouch)
                std::cout << "* " << item.get_description() << std::endl;
        }
        else
        {
            std::cout << "Your pouch is empty" << std::endl;
        }
        std::cout << std::endl;

        std::cout << "Left hand: " << left_hand_label << std::endl;
        std::cout << "Right hand: " << right_hand_label << std::endl;
    }
}
// TODO: Test if this work properly
void Inventory::remove_pouch_item(std::string label)
{
    for (auto item = pouch.begin(); item != pouch.end();)
    {
        if (label == *item.get_label())
        {
            item = pouch.erase(item);
        }
        else
        {
            item++;
        }
    }
}