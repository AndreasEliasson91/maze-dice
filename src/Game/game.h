#pragma once

#include "Assets/Character.h"
#include "Levels/GameLevel.h"

class Game 
{
public:
    Game();
    ~Game();

    int getDifficulty() const { return m_DifficultyLevel; }
    int getNumLevelsCompleted() const { return m_LevelsCompleted; }

    void setDifficulty(int difficulty) { m_DifficultyLevel = difficulty; }
    void setNumLevelsCompleted(int levCompl) { m_LevelsCompleted = levCompl; }

    void UpdateDifficulty(); 
    // {
    //     if (m_LevelsCompleted % 5 == 0)
    //         m_DifficultyLevel++;
    // }
    void Run();
    // {
    //     while (m_Player.PlayerStillAlive()) {            
    //         UpdateDifficulty();
    //         m_ptr_GameLevel = new GameLevel(m_DifficultyLevel, m_Player, m_MazeX, m_MazeY);
    //         m_ptr_GameLevel->Run();
    //         if (m_Player.PlayerStillAlive())
    //             m_Player.UpdateStats();
    //     }

    // }
    void GameOver();

private:
    short int m_MazeX, m_MazeY;
    int m_DifficultyLevel, m_LevelsCompleted;

    CPlayer* m_Player;
    GameLevel* m_ptr_GameLevel;

};
