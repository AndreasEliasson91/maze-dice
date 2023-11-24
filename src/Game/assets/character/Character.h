#pragma once

#include "../inventory/Dice.h"
#include "../inventory/Inventory.h"

#include <algorithm>
#include <array>
#include <limits>
#include <map>
#include <string>
#include <vector>

// TODO: Move this to Character/Utils.h
struct ActorPosition
{
    short int m_XCoord;
    short int m_YCoord;

    explicit ActorPosition(short int x, short int y) : m_XCoord {x}, m_YCoord {y} {}
    ~ActorPosition() = default;

    const std::pair<int, int> getActorPosition() const { return {m_XCoord, m_YCoord}; }

    void UpdatePosition(std::pair<short int, short int> newPos);
};

class CActor
{
public:
    CActor(std::string name, int ap, int dp, int hp, int level, std::pair<short int, short int> pos);
    virtual ~CActor() = default;

    const std::string getName() const { return m_Name; }
    const int getLevel() const { return m_Level; }
    const int getAttackPoints() const { return m_AttackPoints; }
    const int getDefendPoints() const { return m_DefendPoints; }
    const int getHealthPoints() const { return m_HealthPoints; }
    const std::pair<short int, short int> getPosition() const { return m_Position.getActorPosition(); }

    void setName(std::string name) { m_Name = name; }
    void setLevel(int lev) { m_Level = lev; }
    void setAttackPoints(int ap) { m_AttackPoints = ap; }
    void setDefendPoints(int dp) { m_DefendPoints = dp; }
    void setHealthPoints(int hp) { m_HealthPoints = hp; }
    void LevelUp() { m_Level++; }
    void UpdatePosition(std::pair<short int, short int> newPos);

private:
    std::string m_Name;
    ActorPosition m_Position;
    int m_AttackPoints, m_DefendPoints, m_HealthPoints, m_Level;
    
    static constexpr std::pair<short int, short int> START_POSITION = {0, 0};

};

class CPlayer : public CActor
{
public:
    // TODO: Fix a better solution for default start values
    CPlayer(std::string name = DEFAULT_NAME, int ap = 0, int dp = 0, int hp = 20, int level = 1, std::pair<short int, short int> pos = START_POSITION);
    virtual ~CPlayer();

    const int getScore() const { return m_Score; }
    const IInventory* getInventory() const {  return m_Inventory; }
    const bool PlayerStillAlive() const { return m_Alive; }

    void setScore(int s) { m_Score = s; }
    void KillPlayer() { m_Alive = false; }

    void Move(std::string direction);
    // bool in_battle(MCell current_pos) const { return current_pos.engage(); }
    void ResetStats();  // TODO: In game level -> if player alive Update else Player = new CPlayer() aka GameOver func?
    void UpdateStats();

private:
    int m_Score;
    IInventory* m_Inventory;
    // std::vector<Dice>* m_Dices;
    bool m_Alive;

    static constexpr const char* DEFAULT_NAME = "Sir Dice-A-Lot";
    static constexpr std::pair<short int, short int> START_POSITION = {0, 0};

};

class CEnemy : public CActor
{
public:
    CEnemy(std::string id, std::string name, int ap, int dp, int hp, int level, std::pair<short int, short int> pos = START_POSITION);
    virtual ~CEnemy() = default;  // TODO: When added item, change this to non_default and delete item ptr

    const std::string getID() const { return m_ID; }

private:
    std::string m_ID;
    // IItem* m_Item;

    static constexpr std::pair<short int, short int> START_POSITION = {0, 0};

};