#include "Character.h"

void ActorPosition::UpdatePosition(std::pair<short int, short int> newPos)
{
    if (newPos.first > 0 && m_XCoord > SHRT_MAX - newPos.first)
        m_XCoord = SHRT_MAX;
    else if (newPos.first < 0 && m_XCoord < SHRT_MIN - newPos.first)
        m_XCoord = SHRT_MIN;
    else
        m_XCoord += newPos.first;

    if (newPos.second > 0 && m_YCoord > SHRT_MAX - newPos.second)
        m_YCoord = SHRT_MAX;
    else if (newPos.second < 0 && m_YCoord < SHRT_MIN - newPos.second)
        m_YCoord = SHRT_MIN;
    else
        m_YCoord += newPos.second;

    m_XCoord = std::clamp<short int>(m_XCoord, 0, SHRT_MAX);
    m_YCoord = std::clamp<short int>(m_YCoord, 0, SHRT_MAX);
}


CActor::CActor(std::string name, int ap, int dp, int hp, int level, std::pair<short int, short int> pos)
    : m_Name {name}, m_AttackPoints {ap}, m_DefendPoints {dp}, m_HealthPoints {hp}, m_Level {level}, m_Position {ActorPosition(pos.first, pos.second)}
{ }

void CActor::UpdatePosition(std::pair<short int, short int> newPos)
{
    if (newPos == START_POSITION)
        m_Position = ActorPosition(newPos.first, newPos.second);
    else
        m_Position.UpdatePosition(newPos);
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
    const std::map<std::string, std::pair<int, int>> DIRECTIONS = {
        {"north", {0, -1}},
        {"south", {0, 1}},
        {"east", {1, 0}},
        {"west", {-1, 0}}
    };

    for (auto const& [key, val] : DIRECTIONS)
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
    m_Score += (50 * getLevel());
    setHealthPoints(getHealthPoints() + 10);
    LevelUp();
}

CEnemy::CEnemy(std::string id, std::string name, int ap, int dp, int hp, int level, std::pair<short int, short int> pos)
    : CActor {name, ap, dp, hp, level, pos}, m_ID {id}
{ }