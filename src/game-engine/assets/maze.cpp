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