#pragma once

#include "Item.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class IHand
{
public:
    IHand(IItem* it = nullptr);
    ~IHand();

    const IItem* getItem() const { return m_Item; }
    const std::string getItemLabel() const { return m_Item->getLabel(); }

    void setItem(IItem* it) { m_Item = it; }

    void DropItem() { m_Item = nullptr; }

private:
    IItem* m_Item;

};

class IPouch
{
public:
    IPouch();
    ~IPouch();

    const IItem* getItem(std::string id) const;
    const std::vector<IItem*> getItems() const { return m_Items; }
    const std::vector<std::string> getItemLabels() const;
    const int getNumItems() const { return m_Items.size(); }
    const int getMaxLimit() const { return m_MaxLimit; }

    bool AddItem(IItem* it);
    void ClearPouch();
    bool RemoveItem(std::string id);

private:
    int m_MaxLimit;
    std::vector<IItem*> m_Items;

    static constexpr int DEFAULT_LIMIT = 3;
};

class IInventory
{
public:
    IInventory();
    ~IInventory();

    const IItem* getItemFromPouch(std::string id) const;
    IPouch* getPouch() const { return m_Pouch; }
    const IHand* getRightHand() const { return m_RightHand; }
    const IHand* getLeftHand() const { return m_LeftHand; }

    bool InventoryFull(const IItem& item, std::string hand = "");
    bool ItemInInventory(std::string id) const;
    // void process_item_pickup(IItem item, MCell current_location);
    void PrintInventory() const;

private:
    IPouch* m_Pouch;
    IHand* m_RightHand;
    IHand* m_LeftHand;

};
