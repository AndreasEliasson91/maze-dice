#include "item.h"


Item::Item(std::string label, std::string description, std::vector<std::string> actions, std::string storage, std::pair<int, int> pos, bool container)
    : label {label}, description {description}, storage {storage}, position {pos}
{
    for (const auto &action : actions)
        this->actions.push_back(action);
    
    if (container) // TODO: Remove the hard-coded value
        contains = new std::vector<Item*>;
    else
        contains = nullptr;
}

Item::Item(const Item& other)
    : label(other.label), description(other.description), storage(other.storage), actions(other.actions), 
      position(other.position), container(other.container)
{
    if (other.contains)
    {
        contains = new std::vector<Item*>;

        for (Item* item : *(other.contains))
            contains->push_back(new Item(*item));
    }
    else
        contains = nullptr;
}

Item::Item(Item&& other) noexcept
    : label {std::move(other.label)}, description {std::move(other.description)}, storage {std::move(other.storage)},
      actions {std::move(other.actions)}, position {std::move(other.position)}, container {other.container}, contains {other.contains}
{
    other.contains = nullptr;
}

Item::~Item()
{
    if (contains)
    {
        for (Item* item : *contains)
            delete item;

        delete contains;
    }
}


Item& Item::operator=(const Item& other)
{
    if (this != &other)
    {
        label = other.label;
        description = other.description;
        storage = other.storage;
        actions = other.actions;
        position = other.position;
        container = other.container;

        if (other.contains)
        {
            contains = new std::vector<Item*>;

            for (Item* item : *(other.contains))
                contains->push_back(new Item(*item));

        } 
        else
            contains = nullptr;
            
    }
    return *this;
}

// std::string inspect_item(const Cell &current_location, std::string label)
// {
//     if (current_location.got_item())
//     {
//         Item item = curre
//     }
// }
// void pick_up_item(Player &player, std::string label, Cell &current_location)
// {

// }
// void drop_item(Player &player, std::string label, Cell &current_location)
// {

// }