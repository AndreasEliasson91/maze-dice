#pragma once

#include "Dice.h"
#include "Inventory.h"

#include <array>
#include <map>
#include <string>
#include <vector>

class ActorPosition
{
public:
    inline ActorPosition(int x, int y)
    {
        m_XCoord = x;
        m_YCoord = y;
    }
    ~ActorPosition() = default;

    std::pair<int, int> getActorPosition() const { return {m_XCoord, m_YCoord}; }

    void UpdatePosition(std::pair<short int, short int> newPos)
    {
        m_XCoord += newPos.first;
        m_YCoord += newPos.second;
    }

private:
    short int m_XCoord;
    short int m_YCoord;

};

class CActor
{
public:
    CActor(std::string name, int ap, int dp, int hp, int level, std::pair<short int, short int> pos);
    virtual ~CActor() = default;

    std::string getName() const { return m_Name; }
    std::pair<short int, short int> getPosition() const { return m_Position.getActorPosition(); }
    int getStatFromKey(std::string key) const;

    void setName(std::string name) { m_Name = name; }
    void setLevel(int lev) { m_Level = lev; }
    void setAttackPoints(int ap) { m_AttackPoints = ap; }
    void setDefendPoints(int dp) { m_DefendPoints = dp; }
    void setHealthPoints(int hp) { m_HealthPoints = hp; }
    void LevelUp() { m_Level++; }
    void UpdatePosition(std::pair<short int, short int> newPos);

    static constexpr std::pair<short int, short int> START_POSITION = {0, 0};

private:
    std::string m_Name;
    ActorPosition m_Position;
    int m_AttackPoints, m_DefendPoints, m_HealthPoints, m_Level;  // TODO: Change this to a map with stats?

};

class CPlayer : public CActor
{
public:
    // TODO: Fix a better solution for default start values
    CPlayer(std::string name = DEFAULT_NAME, int ap = 0, int dp = 0, int hp = 20, int level = 1, std::pair<short int, short int> pos = START_POSITION);
    virtual ~CPlayer();

    int getScore() const { return m_Score; }
    IInventory* getInventory() const {  return m_Inventory; }
    bool PlayerStillAlive() const { return m_Alive; }

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

};

class CEnemy : public CActor
{
public:
    CEnemy(std::string id, std::string name, int ap, int dp, int hp, int level, std::pair<short int, short int> pos = START_POSITION);
    virtual ~CEnemy() = default;  // TODO: When added item, change this to non_default and delete item ptr

    std::string getID() const { return m_ID; }

private:
    std::string m_ID;
    // IItem* m_Item;

};