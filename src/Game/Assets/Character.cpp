#include "Character.h"

CActor::CActor(std::string name, int ap, int dp, int hp, int level, std::pair<short int, short int> pos)
    : m_Name {name}, m_AttackPoints {ap}, m_DefendPoints {dp}, m_HealthPoints {hp}, m_Level {level}, m_Position {ActorPosition(pos.first, pos.second)}
{ }

void CActor::UpdatePosition(std::pair<short int, short int> newPos)
{
    if (newPos == START_POSITION)
        m_Position = ActorPosition(0,0);
    else
        m_Position.UpdatePosition(newPos);
}

int CActor::getStatFromKey(std::string key) const
{
    std::map<std::string, int> stats {
        {"ap", m_AttackPoints},
        {"dp", m_DefendPoints},
        {"hp", m_HealthPoints},
        {"level", m_Level}
    };
    return stats[key];
}


CPlayer::CPlayer(std::string name, int ap, int dp, int hp, int level, std::pair<short int, short int> pos)
    : CActor {name, ap, dp, hp, level, pos}
{
    m_Score = 0;
    m_Inventory = new IInventory();
    // m_Dices = {Dice(), Dice(), Dice()};
    m_Alive = true;
}

CPlayer::~CPlayer()
{
    delete m_Inventory;
}


void CPlayer::Move(std::string direction)
{
    const std::map<std::string, std::pair<int, int>> directions = {
        {"north", {0, -1}},
        {"south", {0, 1}},
        {"east", {1, 0}},
        {"west", {-1, 0}}
    };

    for (auto const& [key, val] : directions)
    {
        if (direction == key)
        {
            UpdatePosition(val);
            break;
        }
    }
}

void CPlayer::UpdateStats()
{
    UpdatePosition({0,0});
    m_Inventory->getPouch()->ClearPouch();
    m_Score += (50 * getStatFromKey("level"));
    setHealthPoints(getStatFromKey("hp") + 10);
    LevelUp();
}

CEnemy::CEnemy(std::string id, std::string name, int ap, int dp, int hp, int level, std::pair<short int, short int> pos)
    : CActor {name, ap, dp, hp, level, pos}, m_ID {id}
{ }