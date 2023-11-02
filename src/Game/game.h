#pragma once

#include "Assets/Character.h"
#include "Levels/GameLevel.h"

class Game 
{
public:
    Game();
    ~Game() = default;

    int getDifficulty() const { return m_DifficultyLevel; }
    int getNumLevelsCompleted() const { return m_LevelsCompleted; }

    void setDifficulty(int difficulty) { m_DifficultyLevel = difficulty; }
    void setNumLevelsCompleted(int levCompl) { m_LevelsCompleted = levCompl; }

    void updateDifficulty() 
    {
        if (m_LevelsCompleted % 5 == 0)
            m_DifficultyLevel++;
    }
    void run() 
    {
        while (m_Player.PlayerStillAlive()) {            
            updateDifficulty();
            m_GameLevel = GameLevel(m_DifficultyLevel, m_Player, m_MazeX, m_MazeY);
            m_GameLevel.Run();
            if (m_Player.PlayerStillAlive())
                m_Player.UpdateStats();
        }

    }

private:
    CPlayer m_Player;
    short int m_MazeX, m_MazeY;
    int m_DifficultyLevel, m_LevelsCompleted;
    GameLevel m_GameLevel;

};