#pragma once

#include "../assets/character/Character.h"
#include "../assets/inventory/Item.h"
#include "../assets/maze/Maze.h"


#include <array>
#include <iostream>
#include <vector>

class GameLevel
{
public:
    GameLevel(int difficulty, CPlayer &player, short int sizeX, short int sizeY);
    ~GameLevel() = default;  // TODO: When ptrs are added, implemnt this

    std::pair<int, int> getMazeSize() const { return m_MazeSize; }
    CPlayer getPlayer() const { return m_Player; }
    MMaze getMaze() const { return m_Maze; }
    std::vector<CEnemy> getEnemies() const { return m_Enemies; }
    std::vector<IItem> getItems() const { return m_Items; }
    CEnemy getEnemyFromID(std::string id); // TODO: Move this
    IItem getItemFromID(std::string id); // TODO: Move this

    void updateMazeSize();
    std::vector<CEnemy> CreateLevelEnemis(int numEnemies);
    std::vector<IItem> CreateLevelItems(int numItems);
    
    void Run();
    void PrintMazeInfo(std::string cameFrom = "");

private:
    std::pair<short int, short int> m_MazeSize;
    MMaze m_Maze; // TODO: Make ptrs
    std::vector<CEnemy> m_Enemies;
    std::vector<IItem> m_Items;
    CPlayer m_Player; // TODO: Make ptrs
    int m_DifficultyLevel;
    bool m_LevelComplete;

};