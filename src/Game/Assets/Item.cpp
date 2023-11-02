#include "Item.h"


IItem::IItem(std::string id, std::string label, std::string descr, std::vector<std::string> actions, std::string type, std::pair<short int, short int> pos, bool container = false)
    : m_ID {id}, m_Label {label}, m_Description {descr}, m_Type {type}, m_Position {pos}
{
    for (const auto &action : actions)
        m_Actions.push_back(action);
    
    // if (container) // TODO: Remove the hard-coded value
    //     m_Contains.push_back(new IItem());
}

IItem::IItem(const IItem& other)
    : m_ID(other.m_ID), m_Label(other.m_Label), m_Description(other.m_Description), m_Type(other.m_Type), m_Actions(other.m_Actions), m_Position(other.m_Position)
{
    // if (other.contains)
    // {
    //     contains = new std::vector<IItem*>;

    //     for (IItem* item : *(other.contains))
    //         contains->push_back(new IItem(*item));
    // }
    // else
    //     contains = nullptr;
}

IItem::IItem(IItem&& other) noexcept
    : m_ID {std::move(other.m_ID)}, m_Label {std::move(other.m_Label)}, m_Description {std::move(other.m_Description)}, m_Type {std::move(other.m_Type)}, m_Actions {std::move(other.m_Actions)}, m_Position {std::move(other.m_Position)}
{
    // other.contains = nullptr;
}

IItem::~IItem()
{
    // if (contains)
    // {
    //     for (IItem* item : *contains)
    //         delete item;

    //     delete contains;
    // }
}


IItem& IItem::operator=(const IItem& other)
{
    if (this != &other)
    {
        m_Label = other.m_Label;
        m_Description = other.m_Description;
        m_Type = other.m_Type;
        m_Actions = other.m_Actions;
        m_Position = other.m_Position;
        // container = other.container;

    //     if (other.contains)
    //     {
    //         contains = new std::vector<IItem*>;

    //         for (IItem* item : *(other.contains))
    //             contains->push_back(new IItem(*item));

    //     } 
    //     else
    //         contains = nullptr;
            
    }
    return *this;
}

// std::string inspect_item(const MCell &current_location, std::string label)
// {
//     if (current_location.got_item())
//     {
//         IItem item = curre
//     }
// }
// void pick_up_item(Player &player, std::string label, MCell &current_location)
// {

// }
// void drop_item(Player &player, std::string label, MCell &current_location)
// {

// }