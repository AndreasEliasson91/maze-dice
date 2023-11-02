#pragma once

#include "Item.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class IInventory
{
public:
    IInventory();
    ~IInventory();

    IItem* getItemFromPouch(std::string id) const;
    IPouch* getPouch() const { return m_Pouch; }
    IHand* getRightHand() const { return m_RightHand; }
    IHand* getLeftHand() const { return m_LeftHand; }

    bool InventoryFull(const IItem& item, std::string hand = "");
    bool ItemInInventory(std::string id) const;
    // void process_item_pickup(IItem item, MCell current_location);
    void PrintInventory() const;

private:
    IPouch* m_Pouch;
    IHand* m_RightHand;
    IHand* m_LeftHand;

};

class IHand
{
public:
    IHand(IItem* it = nullptr);
    ~IHand();

    IItem* getItem() const { return m_Item; }
    std::string getItemLabel() const { return m_Item->getLabel(); }

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

    IItem* getItem(std::string id) const;
    std::vector<IItem*> getItems() const { return m_Items; }
    std::vector<std::string> getItemLabels() const;
    int getNumItems() const { return m_Items.size(); }
    int getMaxLimit() const { return m_MaxLimit; }

    bool AddItem(IItem* it);
    void ClearPouch();
    bool RemoveItem(std::string id);

private:
    std::vector<IItem*> m_Items;
    int m_MaxLimit;

    static constexpr int DEFAULT_LIMIT = 3;

};