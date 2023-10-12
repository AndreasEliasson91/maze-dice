#include "maze.h"



// Move to a util file?
void write_map(const Maze& maze, const std::string& out_file) {
    // Define a lambda function to write a wall line to the SVG file
    auto writeWall = [](std::ofstream& wallFile, double x1, double y1, double x2, double y2) {
        wallFile << "<line x1=\"" << x1 << "\" y1=\"" << y1 << "\" x2=\"" << x2 << "\" y2=\"" << y2 << "\"/>\n";
    };

    double aspect_ratio = static_cast<double>(maze.get_num_of_cells_x()) / maze.get_num_cells_y();
    double padding = 10.0;
    int height = 500;
    int width = static_cast<int>(height * aspect_atio);

    double scale_y = static_cast<double>(height) / maze.get_num_cells_y();
    double scale_x = static_cast<double>(width) / maze.get_num_of_cells_x();

    std::ofstream os(out_file + ".svg");

    if (!os.is_open()) {
        std::cerr << "Failed to open output file" << std::endl;
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
    for (int x = 0; x < maze.get_num_cells_x(); ++x) {
        for (int y = 0; y < maze.get_num_cells_y(); ++y) {
            if (maze.get_cell(x, y).walls["south"]) {
                double x1 = x * scale_x;
                double y1 = (y + 1) * scale_y;
                double x2 = (x + 1) * scale_x;
                double y2 = (y + 1) * scale_y;
                writeWall(os, x1, y1, x2, y2);
            }
            if (maze.get_cell(x, y).walls["east"]) {
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


Cell::Cell(std::array<int, 2> xy)
    : x {xy[0]}, y {xy[1]}
    {
        walls = {
            {"north", true},
            {"south", true},
            {"east", true},
            {"west", true}
        };
        got_item = false;
    }

bool Cell::surrounded_by_walls() const
{
    for (const auto &wall : walls)
    {
        if (!wall.second)
            return false;
    }
    return true;
}
void Cell::remove_wall(Cell &other_cell, std::string wall)
{
    const std::map<std::string, std::string> opposite_directions = {
        {"north", "south"},
        {"south", "north"},
        {"east", "west"},
        {"west", "east"}
    };

    walls.at(wall) = false;
    other_cell.walls.at(opposite_directions.at(wall)) = false;
}

Maze::Maze(int num_cells_x, int num_cells_y, std::vector<Enemy> enemies, std::vector<Item> items)
    : num_cells_x {num_cells_x}, num_cells_y {num_cells_y}
    {
        start_x = 0;
        start_y = 0;
        maze_end = {num_cells_x - 1, num_cells_y - 1};

        maze.resize(num_cells_x, std::vector<Cell>(num_cells_y));
        create_maze();

        // setup_items_and_enemies(enemies, items);
        write_map(*this, "maze");
    }

void Maze::create_maze()
{
    int total_cells {num_cells_x * num_cells_y}, created_cells {0};
    std::vector<Cell> cell_stack;
    std::vector<std::array<int, 2>> neighbours;

    Cell current_cell = get_cell({start_x, start_y});
    created_cells++;

    while (created_cells < total_cells)
    {
        neighbours = get_valid_neighbours(current_cell);

        if (neighbours.empty())
        {
            current_cell = cell_stack.back();
            cell_stack.pop_back();
            continue;
        }

        int ra
    }
}
std::vector<std::pair<std::string, Cell>> Maze::get_valid_neighbours(Cell cell)
{

}
void Maze::setup_items_and_enemies(std::vector<Enemy> enemies, std::vector<Item> items)
{

}

    // Maze(int num_of_cells_x, int num_of_cells_y, int items, int enemies, int start_cell_x = 0, int start_cell_y = 0)
    //     : num_of_cells_x(num_of_cells_x), num_of_cells_y(num_of_cells_y),
    //       start_x(start_cell_x), start_y(start_cell_y),
    //       maze_end(num_of_cells_x - 1, num_of_cells_y - 1) {
    //     maze.resize(num_of_cells_x, std::vector<Cell>(num_of_cells_y));
    //     createMaze();
    //     setItemsAndEnemiesInLocation(generateLocations(items, enemies), items, enemies);
    //     writeMap(*this, "maze");
    // }


    // std::vector<std::array<int, 2>> generate_unique_locations(std::vector<Enemy> enemies, std::vector<Item> items);