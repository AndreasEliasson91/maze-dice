#include "GameLevel.h"
#include "Utils.h"

// #include "controller/api.h"

// TODO: std::vector<Enemy> get_enemies(int num_enemies);
GameLevel::GameLevel(int difficulty, CPlayer &player, short int sizeX, short int sizeY)
    : m_DifficultyLevel {difficulty}, m_Player {player}
{
    m_MazeSize = std::make_pair(sizeX, sizeY);
    m_Enemies = CreateLevelEnemis(3);
    m_Items = CreateLevelItems(2);
    m_Maze = MMaze(sizeX, sizeY, m_Enemies, m_Items);
    m_LevelComplete = false;
}

// TODO: Implement based on instream file
std::vector<CEnemy> GameLevel::CreateLevelEnemis(int numEnemies)
{
    std::vector<CEnemy> temp = {
            CEnemy("abc123", "skeleton", 1, 0, 5, 0, {2,2}),
            CEnemy("haffla21", "ghoul", 2, 0, 10, 0, {1, 2}),
            CEnemy("gais231", "skeleton", 1, 0, 5, 0, {0,2})
        };
    return temp;
}
std::vector<IItem> GameLevel::CreateLevelItems(int numItems)
{
    std::vector<IItem> temp = {
        IItem("farsd1223", "key", "golden key", {"get", "drop", "check", "investigate"}, "pouch", {0,0}),
        IItem("datanerd2", "sword", "short sword", {"get", "drop", "check", "investigate"}, "hand", {0,0})
    };
    return temp;
}

CEnemy GameLevel::getEnemyFromID(std::string id)
{
    for (const auto& enemy : m_Enemies)
    {
        if (enemy.getID() == id)
            return enemy;
    }
    return;
}
IItem GameLevel::getItemFromID(std::string id)
{
    for (const auto& item : m_Items)
    {
        if (item.getID() == id)
            return item;
    }
    return;
}

// TODO: process_user_input() merge with run()?
// TODO: Write "FOR YOUR INFORMATION..." as game tips
void GameLevel::Run()
{
    PrintMazeInfo();
    
    while (!m_LevelComplete && m_Player.PlayerStillAlive())
        ProcessUserInput(*this);

    if (m_Player.PlayerStillAlive())
        std::cout << "You enter a new maze. Your current score is " << m_Player.getScore()
                  << ", well done!\n\n" << "FOR YOUR INFORMATION: Your pouch will lose it's belongings, but the items in your hands will remain."
                  << "You will also gain some extra health points for your journey. Good luck!" << std::endl;
}

// TODO: Move print funcs to a output-handler
void GameLevel::PrintMazeInfo(std::string cameFrom)
{
    if (cameFrom != "")
        std::cout << "You came from " << cameFrom << std::endl;
    
    // if (this->player.get_inventory().item_in_inventory("lantern"))
    // {
    //     std::cout << "You've got the lantern. It lights up your surroundings.\n You can go: " << std::endl;
    //     for (auto &direction : this->maze.get_cell(this->player.get_position()).get_walls())
    //         std::cout << "* " << direction << std::endl;
    //     if (this->maze.get_cell(this->player.get_position()).got_item())
    //         std::cout << "Ther is a " << this->maze.get_cell_item(this->player.get_position()).get_description() 
    //                   << " in here, maybe CHECK it out?" << std::endl;
    // }
    // else
    // {
    //     std::cout << "The area is very dark!" << std::endl;
    //     if (this->maze.get_cell(this->player.get_position()).got_item())
    //         std::cout << "There is something in here, maybe CHECK it out?" << std::endl;
    // }
}