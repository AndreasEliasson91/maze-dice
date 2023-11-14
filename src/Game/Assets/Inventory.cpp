#include "Inventory.h"


IInventory::IInventory()
    : m_RightHand {nullptr}, m_LeftHand {nullptr}
{
    m_Pouch = new IPouch();
}

IInventory::~IInventory()
{
    m_Pouch->ClearPouch();
    
    delete m_Pouch;
    delete m_RightHand;
    delete m_LeftHand;
}

const IItem* IInventory::getItemFromPouch(std::string id) const
{
    if (ItemInInventory(id))
    {
        if (m_RightHand->getItem()->getID() == id)
            return m_RightHand->getItem();
        if (m_LeftHand->getItem()->getID() == id)
            return m_LeftHand->getItem();

        return m_Pouch->getItem(id);
    }

    return nullptr;  // TODO: Prevent this, if not item in inventory then... Maybe move if item in invtory out to ProcessInput?
}
// TODO: Fix all nested if-else
bool IInventory::InventoryFull(const IItem& item, std::string hand)
{
    if (item.getType() == "pouch" && m_Pouch->getNumItems() >= m_Pouch->getMaxLimit())
    {
        std::cout << "Your pouch is full\nYou can't pick up " << item.getLabel() 
                  << " before you drop something from your pouch!\n";  // TODO: Move text out from methods
        return true;
    }
    else if (item.getType() == "hand" && hand != "")
    {
        const std::vector<std::string> validHandCommands = {
            "left", "left hand", "right", "right hand"
        };

        if (m_LeftHand != nullptr && m_RightHand != nullptr)
        {
            std::cout << "Your hands are full\nYou can't pick up " << item.getLabel() 
                  << " before you drop something from your hands!\n";
            return true;
        }
        if ((hand == "left" || hand == "left hand") && m_LeftHand != nullptr)
        {
            std::cout << "Your left hand is full\nTry pick up " << item.getLabel() 
                  << " with your right hand or before you drop the item in your hand first!\n";
            return true;
        }
        else if ((hand == "right" || hand == "right hand") && m_RightHand != nullptr)
        {
            std::cout << "Your right hand is full\nTry pick up " << item.getLabel() 
                  << " with your left hand or before you drop the item in your hand first!\n";
            return true;
        }
        else if (std::find(validHandCommands.begin(), validHandCommands.end(), hand) == validHandCommands.end())
        {
            std::cout << "Invalid command\n";
            return true;
        }
    }
    return false;
}
bool IInventory::ItemInInventory(std::string id) const
{
    if ((m_RightHand != nullptr && m_RightHand->getItem()->getID() == id) ||
        (m_LeftHand != nullptr && m_LeftHand->getItem()->getID() == id))
        return true;

    for (const auto& it : m_Pouch->getItems())
    {
        if (it->getID() == id)
            return true;
    }

    return false;
}
// void IInventory::process_item_pickup(IItem item, MCell current_location)
// {
//     if (std::find(item.get_actions().begin(), item.get_actions().end(), "get") != item.get_actions().end())
//     {
//         std::cout << "It seems impossible to pick up the " << item.get_description(\n);
//     }
//     else if (item.get_storage_type() == "pouch" && !inventory_full(item))
//     {
//         std::cout << "You pick up the " << item.get_description() << "!\n";
//         pouch.push_back(item);

//         // delete current_location.item;
//         current_location.set_got_item(false);
//     }
//     else if (item.get_storage_type() == "hand")
//     {
//         std::string hand {};
//         std::cout << "Which hand do you want to pick up the " << item.get_description() << "with: ";
//         std::cin >> hand;

//         if (!inventory_full(item, hand))
//         {
//             std::cout << "You picke up the " << item.get_description() << " in your " << hand << " hand!\n";
//             if (hand == "right")
//                 right_hand_label = item.get_label();
//             else
//                 left_hand_label = item.get_label();
//         }
//     }
//     else
//     {
//         std::cout << "Your inventory is full!\n";
//     }
// }


// TODO: Format this nicely
void IInventory::PrintInventory() const
{
    if (m_Pouch->getNumItems() == 0 && m_RightHand == nullptr && m_LeftHand == nullptr)
    {
        std::cout << "Your inventory is empty\n";
    }
    else
    {
        std::cout << "INVENTORY\n";

        if (m_Pouch->getNumItems() > 0)
        {
            for (const auto& item : m_Pouch->getItems())
                std::cout << "* " << item->getLabel() << "\n";
        }
        else
        {
            std::cout << "Your pouch is empty\n\n";
        }

        std::cout << "Left hand: " << m_LeftHand->getItemLabel() << "\n";
        std::cout << "Right hand: " << m_RightHand->getItemLabel() << "\n";
    }
}

IHand::IHand(IItem* item) : m_Item {item}
{ }

IHand::~IHand()
{
    delete m_Item;
}


IPouch::IPouch() : m_MaxLimit {DEFAULT_LIMIT}
{ }

IPouch::~IPouch()
{
    for (int i = 0; i < m_Items.size(); i++) 
    {
        delete m_Items[i];
    }
}


const std::vector<std::string> IPouch::getItemLabels() const
{
    std::vector<std::string> labels;

    for (const auto& item : m_Items)
        labels.push_back(item->getLabel());

    return labels;
}


const IItem* IPouch::getItem(std::string id) const
{
    for (auto &item : getItems())
    {
        if (id == item->getID())
            return item;
    }
    return nullptr;
}

bool IPouch::AddItem(IItem* it)
{
    if (m_Items.size() != getMaxLimit())
    {
        m_Items.push_back(it);
        return true;
    }
    return false;
}

void IPouch::ClearPouch()
{
    for (int i = 0; i < m_Items.size(); i++) 
    {
        delete m_Items[i];
    }
}
// TODO: Implement this!
// bool IPouch::RemoveItem(std::string id)
// {
//     for (auto item = m_Items.begin(); item != m_Items.end();)
//     {
//         if (id == *item.getID())
//         {
//             item = m_Items.erase(item);
//             return true;
//         }
//         else
//         {
//             item++;
//         }
//     }
//     return false;
// }
