#include <iostream>
#include <Eigen/Dense>
#include <cglib/cycle.h>

int main(int argc, char* argv[])
{
    // Check if the correct number of arguments was passed (2 arguments are expected)
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return 1;
    }

    // Use the first argument as the input file
    std::string input_file = argv[1];
    // Use the second argument as the output file
    std::string output_file = argv[2];

    // Check if the input file exists
    std::ifstream file(input_file);
    if (!file) {
        std::cerr << "Error: file " << input_file << " not found" << std::endl;
        return 1;
    }

    // Read the size of the graph from the input file
    int cols, rows;
    file >> cols >> rows;

    // Initialize the graph with the correct size
    Eigen::MatrixXi graph(rows, cols);

    // Read the graph from the input file
    for (int i = 0; i < graph.rows(); i++) {
        for (int j = 0; j < graph.cols(); j++) {
            file >> graph(i, j);
        }
    }

    // Convert the graph to a Graph object
    // First the grid
    Eigen::Array<int, 2, 1> cell_2dcount(2);
    cell_2dcount << cols, rows;
    Eigen::Array<int, 2, 1> origin(2);
    origin << 0, 0;
    float cell_sides_length = 1;
    Grid grid(cell_2dcount, origin, cell_sides_length);

    // Then the scalar field
    Eigen::Array<double, Eigen::Dynamic, 1> flattened_scalar_field = graph.cast<double>().matrix().transpose();

    Graph res = grid2_contour(flattened_scalar_field, cell_2dcount, grid);

    Eigen::Array<float, Eigen::Dynamic, 2> list_point = res.getListPoint();
    Eigen::Array<int, Eigen::Dynamic, 2> list_adjacency = res.getListAdjacency();

    // Create the cycles from the graph
    Cycle cycle = create_from_graph(res);

    // Write the cycles to the output file
    save_cycle(output_file, cycle);

    return 0;
}