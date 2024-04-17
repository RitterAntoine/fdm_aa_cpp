#include <iostream>
#include <Eigen/Dense>
#include <cglib/cycle.h>
#include <vector>
#include <chrono>

Eigen::Array<double, Eigen::Dynamic, 1> Scalar_Field_Generator(int cols, int rows)
{
    // Create a 2D array with random values between -1 and 1
    Eigen::ArrayXXd scalar_field = Eigen::ArrayXXd::Random(rows, cols);

    // Set the first and last rows to 1
    scalar_field.row(0) = Eigen::ArrayXd::Ones(cols);
    scalar_field.row(rows - 1) = Eigen::ArrayXd::Ones(cols);

    // Set the first and last columns to 1
    scalar_field.col(0) = Eigen::ArrayXd::Ones(rows);
    scalar_field.col(cols - 1) = Eigen::ArrayXd::Ones(rows);

    // Flatten the 2D array to a 1D array
    return Eigen::Map<Eigen::Array<double, Eigen::Dynamic, 1>>(scalar_field.data(), scalar_field.size());
}

void write_scalar_field_to_file(const Eigen::Array<double, Eigen::Dynamic, 1>& scalar_field, int cols, const std::string& output_file) {
    std::ofstream file(output_file);
    if (!file) {
        std::cerr << "Unable to open file " << output_file << std::endl;
        return;
    }

    for (int i = 0; i < scalar_field.size(); i++) {
        // If it's not the first element of a row, add a comma before the value
        if (i % cols != 0) {
            file << ",";
        }
        file << scalar_field[i];
        if ((i + 1) % cols == 0) {  // If it's the end of a row
            file << std::endl;  // Add a newline character
        }
    }

    file.close();
}

void write_polylines_to_file(const std::vector<Polyline>& polylines, const std::string& output_file) {
    std::ofstream file(output_file);
    if (!file) {
        std::cerr << "Unable to open file " << output_file << std::endl;
        return;
    }

    for (const Polyline& polyline : polylines) {
        for (int i = 0; i < polyline.vertices.rows(); i++) {
            // If it's not the first vertex, add a space before the vertex
            if (i != 0) {
                file << " ";
            }
            file << polyline.vertices(i, 0) << "," << polyline.vertices(i, 1);
        }
        file << std::endl;  // Add a newline character after writing all vertices of a polyline
    }

    file.close();
}

int main(int argc, char* argv[])
{
    // Check if the correct number of arguments was passed (2 arguments are expected)
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <number of rows>> <number of columns> <grid_output_file> <polylines_output_file>" << std::endl;
        // return 1;

        // Fake values for testing
        argc = 4;
        argv[1] = "9";
        argv[2] = "9";
        argv[3] = "demos/grid_output.txt";
        argv[4] = "demos/polylines_output.txt";
    }

    // Start the total time clock
    auto total_start = std::chrono::high_resolution_clock::now();

    // Use the first argument as the number of rows
    int rows = std::stoi(argv[1]);
    // Use the second argument as the number of columns
    int cols = std::stoi(argv[2]);

    // Use the third argument as the output file
    std::string output_file = argv[3];
    // Use the fourth argument as the output file for the polylines
    std::string polylines_output_file = argv[4];

    // Start the clock for the scalar field generation
    auto start = std::chrono::high_resolution_clock::now();
    
    // Generate a scalar field with random values
    Eigen::Array<double, Eigen::Dynamic, 1> scalar_field = Scalar_Field_Generator(cols, rows);

    // FOR DEMO :
    // Eigen::Array<double, Eigen::Dynamic, 1> scalar_field(32);
    // scalar_field << 1, 1, 1, 1, 1, 1, 1, 1, 1, -1, -1, 1, 1, -1, -1, 1, 1, -1, -1, 1, 1, -1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1;

    // Stop the clock and calculate the time for the scalar field generation
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
    std::cout << "Time taken by Scalar_Field_Generator: " << duration.count() << " seconds" << std::endl;

    // Write the scalar field to the output file
    write_scalar_field_to_file(scalar_field, cols, output_file);

    // Define the Grid object
    Eigen::Array<int, 2, 1> cell_2dcount(2);
    cell_2dcount << cols, rows;
    Eigen::Array<int, 2, 1> origin(2);
    origin << 0, 0;
    float cell_sides_length = 1;
    Grid grid(cell_2dcount, origin, cell_sides_length);

    // Start the clock for the grid2_contour function
    start = std::chrono::high_resolution_clock::now();

    // Convert the scalar field to a Graph object
    Graph res = grid2_contour(scalar_field, cell_2dcount, grid);

    Eigen::ArrayX2f list_points = res.getListPoint();
    Eigen::ArrayX2i list_adjacency = res.getListAdjacency();

    // Print the points and adjacency list
    
    std::cout << "Adjacency list: " << std::endl;
    for (int i = 0; i < list_adjacency.rows(); i++) {
        std::cout << i << ": " << list_adjacency(i, 0) << ", " << list_adjacency(i, 1) << std::endl;
    }

    // Stop the clock and calculate the time for the grid2_contour function
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
    std::cout << "Time taken by grid2_contour: " << duration.count() << " seconds" << std::endl;

    // Start the clock for the create_from_graph function
    start = std::chrono::high_resolution_clock::now();

    // Create the cycles from the graph
    Cycle cycle = create_from_graph(res);

    // Print the number of cycles found
    std::cout << "Number of cycles found: " << cycle.getCycleCount() << std::endl;

    // Stop the clock and calculate the time for the create_from_graph function
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
    std::cout << "Time taken by create_from_graph: " << duration.count() << " seconds" << std::endl;

    // Start the clock for the cycle_to_polyline function
    start = std::chrono::high_resolution_clock::now();

    // Transform the cycles to polylines
    std::vector<Polyline> polylines;
    for (int i = 0; i < cycle.getCycleCount(); i++) {
        Polyline polyline = cycle_to_polyline(cycle, i);
        polylines.push_back(polyline);
    }

    // Stop the clock and calculate the time for the cycle_to_polyline function
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
    std::cout << "Time taken by cycle_to_polyline: " << duration.count() << " seconds" << std::endl;

    // Writes the polylines to the output file
    write_polylines_to_file(polylines, polylines_output_file);

    // Stop the total time clock and calculate the total time
    auto total_stop = std::chrono::high_resolution_clock::now();
    auto total_duration = std::chrono::duration_cast<std::chrono::seconds>(total_stop - total_start);
    std::cout << "Total time taken: " << total_duration.count() << " seconds" << std::endl;

    return 0;
}