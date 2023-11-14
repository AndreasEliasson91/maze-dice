#pragma once

#include <string>
#include <vector>

class IItem
{
public:
    IItem( std::string id, std::string label, std::string descr, std::vector<std::string> actions, std::string type, std::pair<short int, short int> pos);
    ~IItem();

    IItem(const IItem& other);
    IItem(IItem&& other) noexcept;

    IItem& operator=(const IItem& other);

    const std::string getID() const { return m_ID; }
    const std::string getLabel() const { return m_Label; }
    const std::string getDescription() const { return m_Description; }
    const std::string getType() const { return m_Type; }
    const std::vector<std::string> getActions() const { return m_Actions; }

    void UpdatePosition(std::pair<short int, short int> newPos) { m_Position = newPos; }
    
private:
    std::string m_Label, m_Description, m_Type, m_ID;
    std::vector<std::string> m_Actions;
    std::pair<short int, short int> m_Position;

    // TODO: Fix chest implementation (Maybe own class with IItem inheritance?)
    // bool m_Container;
    // std::vector<IItem*> m_Contains; // If chest etc.

};
