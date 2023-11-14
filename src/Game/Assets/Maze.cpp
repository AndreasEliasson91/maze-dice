#include "Maze.h"


MCell::MCell(std::pair<short int, short int> xy) : m_X {xy.first}, m_Y {xy.second}
{
    m_Walls = {
        {"north", true},
        {"south", true},
        {"east", true},
        {"west", true}
    };

    m_Item = nullptr;
    m_Enemy = nullptr;
}

MCell::MCell(const MCell& other) : m_X {other.m_X}, m_Y {other.m_Y}, m_Walls {other.m_Walls}, m_Enemy {nullptr}, m_Item {nullptr}
{
    if (other.m_Enemy != nullptr)
        m_Enemy = new CEnemy(*(other.m_Enemy));

    if (other.m_Item != nullptr)
        m_Item = new IItem(*(other.m_Item));   
}

MCell::MCell(MCell&& other) noexcept : m_X(other.m_X), m_Y(other.m_Y), m_Walls(std::move(other.m_Walls)), m_Item(other.m_Item), m_Enemy(other.m_Enemy)
{
    other.m_Item = nullptr;
    other.m_Enemy = nullptr;
}

MCell::~MCell()
{
    delete m_Item;
    delete m_Enemy;
}


MCell& MCell::operator=(const MCell& other)
{
    if (this != &other)
    {
        m_X = other.m_X;
        m_Y = other.m_Y;
        m_Walls = other.m_Walls;

        if (other.m_Item != nullptr) 
        {
            if (m_Item == nullptr)
                m_Item = new IItem(*(other.m_Item));
            else
                *m_Item = *(other.m_Item);
        }
        else 
        {
            delete m_Item;
            m_Item = nullptr;
        }

        if (other.m_Enemy != nullptr) 
        {
            if (m_Enemy == nullptr)
                m_Enemy = new CEnemy(*(other.m_Enemy));
            else
                *m_Enemy = *(other.m_Enemy);
        }
        else 
        {
            delete m_Enemy;
            m_Enemy = nullptr;
        }
    }

    return *this;
}


void MCell::setEnemy(std::string id, std::string name, int ap, int dp, int hp, int level, std::pair<short int, short int> pos)
{
    if (m_Enemy != nullptr)
        delete m_Enemy;

    m_Enemy = new CEnemy(id, name, ap, dp, hp, level, pos);
}

void MCell::setItem(std::string id, std::string label, std::string descr, std::vector<std::string> actions, std::string type, std::pair<short int, short int> pos)
 {
    if (m_Item != nullptr)
        delete m_Item;

    m_Item = new IItem(id, label, descr, actions, type, pos); 
}

bool MCell::SurroundedByWalls() const
{
    for (const auto &wall : m_Walls)
    {
        if (!wall.second)
            return false;
    }
    return true;
}

void MCell::RemoveWall(MCell &other, std::string wall)
{
    const std::map<std::string, std::string> oppositeDirections = {
        {"north", "south"},
        {"south", "north"},
        {"east", "west"},
        {"west", "east"}
    };

    setWall(wall, false);
    other.setWall(oppositeDirections.at(wall), false);;
}

// void MCell::print_walls() const
// {
//     std::cout << std::boolalpha;
//     std::cout << "MCell (" << get_x() << "," << get_y() << "): ";
//     for (auto &wall : walls)
//     {
//         std::cout << wall.first << ": " << wall.second << " : ";
//     }
//     std::cout << "\n";
// }


MMaze::MMaze(short int numCellsX, short int numCellsY, std::vector<CEnemy> enemies, std::vector<IItem> items)
    : m_NumCellsX {numCellsX}, m_NumCellsY {numCellsY}
{
    m_StartX = 0;
    m_StartY = 0;
    m_MazeEnd = {m_NumCellsX - 1, m_NumCellsY - 1};

    for (int x = 0; x < m_NumCellsX; x++)
    {
        m_Maze.push_back(std::vector<MCell*>());

        for (int y = 0; y < m_NumCellsY; y++)
        {
            m_Maze[x].push_back(new MCell(std::make_pair(x, y)));
        }
    }

    CreateMaze();
    // setup_items_and_enemies(enemy_ids, item_ids);
    WriteMap(*this, "maze");
}

MMaze::~MMaze()
{
    for (int x = 0; x < m_NumCellsX; x++)
    {
        for (int y = 0; y < m_NumCellsY; y++) 
        {
            delete m_Maze[x][y];
        }
    }
}

void MMaze::CreateMaze()
{
    int totalCells {m_NumCellsX * m_NumCellsY};
    int createdCells {0};
    std::vector<MCell*> cellStack;

    MCell *currentCell = getCell({m_StartX, m_StartY});
    createdCells++;

    while (createdCells < totalCells)
    {
        std::vector<std::pair<std::string, MCell*>> neighbors = getValidNeighbors(*currentCell);

        if (neighbors.empty())
        {
            currentCell = cellStack.back();
            cellStack.pop_back();
            continue;
        }

        int neighborIdx {static_cast<int>(rand() % neighbors.size())};

        std::pair<std::string, MCell*> neighbour {neighbors.at(neighborIdx)};
        std::string direction = neighbour.first;
        MCell *nextCell = neighbour.second;

        currentCell->RemoveWall(*nextCell, direction);
        cellStack.push_back(currentCell);

        currentCell = nextCell;
        nextCell = nullptr;

        createdCells++;
    }
}

std::vector<std::pair<std::string, MCell*>> MMaze::getValidNeighbors(const MCell &cell)
{
    const std::map<std::string, std::pair<int, int>> directions = {
        {"north", {0, -1}},
        {"south", {0, 1}},
        {"east", {1, 0}},
        {"west", {-1, 0}}
    };

    std::vector<std::pair<std::string, MCell*>> neighbors;

    for (auto const& [direction, val] : directions)
    {
        int neighborX = cell.getX() + val.first;
        int neighborY = cell.getY() + val.second;

        if (0 <= neighborX && neighborX < m_NumCellsX
            && 0 <= neighborY && neighborY < m_NumCellsY)
        {
            MCell *neighbour = getCell({neighborX, neighborY});
            if (neighbour->SurroundedByWalls())
                neighbors.push_back(std::make_pair(direction, neighbour));
        }
    }
    return neighbors;
}

void MMaze::SetupEnemiesAndItems(std::vector<std::string> enemyIDs, std::vector<std::string> itemIDs)
{

}



void WriteMap(MMaze& maze, const std::string& outFile) {
    // Define a lambda function to write a wall line to the SVG file
    auto writeWall = [](std::ofstream& wallFile, double x1, double y1, double x2, double y2) {
        wallFile << "<line x1=\"" << x1 << "\" y1=\"" << y1 << "\" x2=\"" << x2 << "\" y2=\"" << y2 << "\"/>\n";
    };

    double aspectRatio = static_cast<double>(maze.getNumCellsX()) / maze.getNumCellsY();
    double padding = 10.0;
    int height = 500;
    int width = static_cast<int>(height * aspectRatio);

    double scale_y = static_cast<double>(height) / maze.getNumCellsY();
    double scale_x = static_cast<double>(width) / maze.getNumCellsX();

    std::ofstream os(outFile + ".svg");

    if (!os.is_open()) {
        std::cerr << "Failed to open output file";
        return;
    }

    // SVG preamble and styles
    os << "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
    os << "<svg xmlns=\"http://www.w3.org/2000/svg\"\n";
    os << "    xmlns:xlink=\"http://www.w3.org/1999/xlink\"\n";
    os << "    width=\"" << width + 2 * padding << "\" height=\"" << height + 2 * padding << "\" viewBox=\""
            << -padding << " " << -padding << " " << width + 2 * padding << " " << height + 2 * padding << "\">\n";
    os << "<defs>\n<style type=\"text/css\"><![CDATA[\n";
    os << "line {\n";
    os << "    stroke: #000000;\n    stroke-linecap: square;\n";
    os << "    stroke-width: 5;\n}\n";
    os << "]]></style>\n</defs>\n";

    // Draw the "South" and "East" walls of each cell
    for (int x = 0; x < maze.getNumCellsX(); ++x) 
    {
        for (int y = 0; y < maze.getNumCellsY(); ++y) 
        {
            MCell cell = *maze.getCell({x,y});

            if (cell.getWalls()["south"]) 
            {
                double x1 = x * scale_x;
                double y1 = (y + 1) * scale_y;
                double x2 = (x + 1) * scale_x;
                double y2 = (y + 1) * scale_y;
                writeWall(os, x1, y1, x2, y2);
            }
            if (cell.getWalls()["east"]) 
            {
                double x1 = (x + 1) * scale_x;
                double y1 = y * scale_y;
                double x2 = (x + 1) * scale_x;
                double y2 = (y + 1) * scale_y;
                writeWall(os, x1, y1, x2, y2);
            }
        }
    }

    // Draw the North and West map border
    os << "<line x1=\"0\" y1=\"0\" x2=\"" << width << "\" y2=\"0\"/>\n";
    os << "<line x1=\"0\" y1=\"0\" x2=\"0\" y2=\"" << height << "\"/>\n";
    os << "</svg>\n";

    os.close();
}

// std::vector<std::pair<int, int>> generate_unique_locations(std::vector<Enemy> enemies, std::vector<IItem> items);