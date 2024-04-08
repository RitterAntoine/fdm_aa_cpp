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

int main(int argc, char* argv[])
{
    // Loop from 5 to 100
    for (int size = 5; size <= 40; size++) {
        // Start the total time clock
        auto total_start = std::chrono::high_resolution_clock::now();

        // Use the size as the number of rows and columns
        int rows = size;
        int cols = size;
        
        // Generate a scalar field with random values
        Eigen::Array<double, Eigen::Dynamic, 1> scalar_field = Scalar_Field_Generator(cols, rows);

        // Define the Grid object
        Eigen::Array<int, 2, 1> cell_2dcount(2);
        cell_2dcount << cols, rows;
        Eigen::Array<int, 2, 1> origin(2);
        origin << 0, 0;
        float cell_sides_length = 1;
        Grid grid(cell_2dcount, origin, cell_sides_length);

        // Convert the scalar field to a Graph object
        Graph res = grid2_contour(scalar_field, cell_2dcount, grid);

        // Create the cycles from the graph
        Cycle cycle = create_from_graph(res);

        // Transform the cycles to polylines
        std::vector<Polyline> polylines;
        for (int i = 0; i < cycle.getCycleCount(); i++) {
            Polyline polyline = cycle_to_polyline(cycle, i);
            polylines.push_back(polyline);
        }

        // Stop the total time clock and calculate the total time
        auto total_stop = std::chrono::high_resolution_clock::now();
        auto total_duration = std::chrono::duration_cast<std::chrono::milliseconds>(total_stop - total_start);
        std::cout << "Total time taken for size " << size << ": " << total_duration.count() << " milliseconds" << std::endl;
    }

    return 0;
}