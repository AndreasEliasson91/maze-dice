#include "maze.h"


// Move to a util file?
void write_map(const Maze& maze, const std::string& out_file) {
    // Define a lambda function to write a wall line to the SVG file
    auto writeWall = [](std::ofstream& wallFile, double x1, double y1, double x2, double y2) {
        wallFile << "<line x1=\"" << x1 << "\" y1=\"" << y1 << "\" x2=\"" << x2 << "\" y2=\"" << y2 << "\"/>\n";
    };

    double aspect_ratio = static_cast<double>(maze.get_num_cells_x()) / maze.get_num_cells_y();
    double padding = 10.0;
    int height = 500;
    int width = static_cast<int>(height * aspect_ratio);

    double scale_y = static_cast<double>(height) / maze.get_num_cells_y();
    double scale_x = static_cast<double>(width) / maze.get_num_cells_x();

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
            if (maze.get_cell({x, y}).get_walls()["south"]) {
                double x1 = x * scale_x;
                double y1 = (y + 1) * scale_y;
                double x2 = (x + 1) * scale_x;
                double y2 = (y + 1) * scale_y;
                writeWall(os, x1, y1, x2, y2);
            }
            if (maze.get_cell({x, y}).get_walls()["east"]) {
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


Cell::Cell(std::pair<int, int> xy)
    : x {xy.first}, y {xy.second}
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
    std::vector<std::pair<std::string, Cell>> neighbours;

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

        int neighbour_idx {rand() % neighbours.size()};
        std::pair<std::string, Cell> neighbour {neighbours.at(neighbour_idx)};
        std::string direction {neighbour.first};
        Cell next_cell {neighbour.second};

        current_cell.remove_wall(next_cell, direction);
        cell_stack.push_back(std::make_pair(current_cell.get_x(), current_cell.get_y()));

        current_cell = next_cell;
        created_cells++;
    }
}
std::vector<std::pair<std::string, Cell>> Maze::get_valid_neighbours(Cell cell)
{
    const std::map<std::string, std::pair<uint8_t, uint8_t>> directions = {
        {"north", {0, -1}},
        {"south", {0, 1}},
        {"east", {1, 0}},
        {"west", {-1, 0}}
    };

    std::vector<std::pair<std::string, Cell>> neighbours;
    int neighbour_x {}, neighbour_y {};

    for (auto const& [direction, val] : directions)
    {
        neighbour_x = cell.get_x() + val.first;
        neighbour_y = cell.get_y() + val.second;

        if (0 <= neighbour_x < num_cells_x && 0 <= neighbour_y < num_cells_y)
        {
            Cell neighbour = get_cell({neighbour_x, neighbour_y});
            if (neighbour.surrounded_by_walls())
                neighbours.push_back(std::make_pair(direction, neighbour));
        }

        return neighbours;
    }

}
void Maze::setup_items_and_enemies(std::vector<Enemy> enemies, std::vector<Item> items)
{

}

// std::vector<std::pair<int, int>> generate_unique_locations(std::vector<Enemy> enemies, std::vector<Item> items);