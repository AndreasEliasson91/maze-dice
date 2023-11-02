#pragma once

#include <string>
#include <vector>

class IItem
{
public:
    IItem( std::string id, std::string label, std::string descr, std::vector<std::string> actions, std::string type, std::pair<short int, short int> pos, bool container = false);
    ~IItem();

    IItem(const IItem& other);
    IItem(IItem&& other) noexcept;

    IItem& operator=(const IItem& other);

    std::string getID() const { return m_ID; }
    std::string getLabel() const { return m_Label; }
    std::string getDescription() const { return m_Description; }
    std::string getType() const { return m_Type; }
    std::vector<std::string> getActions() const { return m_Actions; }

    void UpdatePosition(std::pair<short int, short int> newPos) { m_Position = newPos; }
    
private:
    std::string m_Label, m_Description, m_Type, m_ID;
    std::vector<std::string> m_Actions;
    std::pair<short int, short int> m_Position;

    // TODO: Fix chest implementation (Maybe own calss with IItem inheritance?)
    // bool m_Container;
    // std::vector<IItem*> m_Contains; // If chest etc.

};

// TODO: Move this to a item_utils.h?
// std::string inspect_item(const MCell &current_location, std::string label);
// void pick_up_item(Player &player, std::string label, MCell &current_location);
// void drop_item(Player &player, std::string label, MCell &current_location);