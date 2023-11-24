#include "Item.h"


IItem::IItem(std::string id, std::string label, std::string descr, std::vector<std::string> actions, std::string type, std::pair<short int, short int> pos)
    : m_ID {id}, m_Label {label}, m_Description {descr}, m_Type {type}, m_Position {pos}
{
    for (const auto &action : actions)
        m_Actions.push_back(action);
}

IItem::IItem(const IItem& other)
    : m_ID(other.m_ID), m_Label(other.m_Label), m_Description(other.m_Description), m_Type(other.m_Type), m_Actions(other.m_Actions), m_Position(other.m_Position)
{ }

IItem::IItem(IItem&& other) noexcept
    : m_ID {std::move(other.m_ID)}, m_Label {std::move(other.m_Label)}, m_Description {std::move(other.m_Description)}, m_Type {std::move(other.m_Type)}, m_Actions {std::move(other.m_Actions)}, m_Position {std::move(other.m_Position)}
{ }

IItem::~IItem()
{ }


IItem& IItem::operator=(const IItem& other)
{
    if (this != &other)
    {
        m_Label = other.m_Label;
        m_Description = other.m_Description;
        m_Type = other.m_Type;
        m_Actions = other.m_Actions;
        m_Position = other.m_Position;
            
    }
    return *this;
}
