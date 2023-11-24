#pragma once

#include "../character/Character.h"
#include "../inventory/Item.h"

#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <string>


class MCell
{
public:
    MCell(std::pair<short int, short int> xy);
    ~MCell();

    MCell(const MCell& other);
    MCell(MCell&& other) noexcept;

    MCell& operator=(const MCell& other);

    const short int getX() const { return m_X; }
    const short int getY() const { return m_Y; }
    const CEnemy *getEnemy() const  { return m_Enemy; }
    const IItem *getItem() const  { return m_Item; }
    const std::pair<short int, short int> getMazePosition() const { return {m_X, m_Y}; }
    std::map<std::string, bool> getWalls() const { return m_Walls; }

    void setEnemy(std::string id, std::string name, int ap, int dp, int hp, int level, std::pair<short int, short int> pos);
    void setItem(std::string id, std::string label, std::string descr, std::vector<std::string> actions, std::string type, std::pair<short int, short int> pos);
    void setPosition(int x, int y) { m_X = x; m_Y = y; }
    void setWall(std::string wall, bool val) { m_Walls[wall] = val; }

    bool GotEnemy() const { return (m_Enemy != nullptr); }
    bool GotItem() const { return (m_Item != nullptr); }

    bool SurroundedByWalls() const;
    void RemoveWall(MCell &other, std::string wall);

private:
    short int m_X, m_Y;
    std::map<std::string, bool> m_Walls;
    IItem* m_Item;
    CEnemy* m_Enemy;

};

class MMaze
{
public:
    MMaze(short int numCellsX, short int numCellsY, std::vector<CEnemy> enemies, std::vector<IItem> items);
    ~MMaze();

    MCell* getCell(std::pair<short int, short int> pos) const { return m_Maze.at(pos.first).at(pos.second); }
    const std::pair<short int, short int> getMazeSize() const { return m_MazeEnd; }
    const short int getNumCellsX() const { return m_NumCellsX; }
    const short int getNumCellsY() const { return m_NumCellsY; }

    void CreateMaze();
    std::vector<std::pair<std::string, MCell*>> getValidNeighbors(const MCell &cell);
    void SetupEnemiesAndItems(std::vector<std::string> enemyIDs, std::vector<std::string> itemIDs);


private:
    int m_NumCellsX, m_NumCellsY;
    int m_StartX, m_StartY;
    std::pair<short int, short int> m_MazeEnd;
    std::vector<std::vector<MCell*>> m_Maze;

};

void WriteMap(MMaze& maze, const std::string& outFile);