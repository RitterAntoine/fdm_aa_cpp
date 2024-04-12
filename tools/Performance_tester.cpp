#include <iostream>
#include <Eigen/Dense>
#include <cglib/cycle.h>
#include <vector>
#include <chrono>
#include <fstream>
#include <thread>

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
    std::vector<int> sizes;  // Vector to store the sizes
    std::vector<double> times;  // Vector to store the times

    // Open a CSV file for writing
    std::ofstream csv_file;
    csv_file.open("times.csv");

    // Loop from 5 to 100
    for (int size = 5; size <= 100; size++) {
        // Start the total time clock
        auto total_start = std::chrono::high_resolution_clock::now();

        // Use the size as the number of rows and columns
        int rows = size;
        int cols = size;

        // Generate a scalar field with random values
        //auto start = std::chrono::high_resolution_clock::now();
        Eigen::Array<double, Eigen::Dynamic, 1> scalar_field = Scalar_Field_Generator(cols, rows);
        //auto stop = std::chrono::high_resolution_clock::now();
        //auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        //std::cout << "Scalar_Field_Generator time: " << duration.count() << " milliseconds" << std::endl;

        // Define the Grid object
        Eigen::Array<int, 2, 1> cell_2dcount(2);
        cell_2dcount << cols, rows;
        Eigen::Array<int, 2, 1> origin(2);
        origin << 0, 0;
        float cell_sides_length = 1;
        Grid grid(cell_2dcount, origin, cell_sides_length);

        // Convert the scalar field to a Graph object
        //start = std::chrono::high_resolution_clock::now();
        Graph res = grid2_contour(scalar_field, cell_2dcount, grid);
        //stop = std::chrono::high_resolution_clock::now();
        //duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        //std::cout << "grid2_contour time: " << duration.count() << " milliseconds" << std::endl;

        // Create the cycles from the graph
        //start = std::chrono::high_resolution_clock::now();
        Cycle cycle = create_from_graph(res);
        //stop = std::chrono::high_resolution_clock::now();
        //duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        //std::cout << "create_from_graph time: " << duration.count() << " milliseconds" << std::endl;

        // Transform the cycles to polylines
        //start = std::chrono::high_resolution_clock::now();
        std::vector<Polyline> polylines;
        for (int i = 0; i < cycle.getCycleCount(); i++) {
            Polyline polyline = cycle_to_polyline(cycle, i);
            polylines.push_back(polyline);
        }
        //stop = std::chrono::high_resolution_clock::now();
        //duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        //std::cout << "cycle_to_polyline time: " << duration.count() << " milliseconds" << std::endl;

        // Stop the total time clock and calculate the total time
        auto total_stop = std::chrono::high_resolution_clock::now();
        auto total_duration = std::chrono::duration_cast<std::chrono::milliseconds>(total_stop - total_start);
        std::cout << "Total time taken for size " << size << ": " << total_duration.count() << " milliseconds" << std::endl;

        // Store the size and time
        sizes.push_back(size);
        times.push_back(total_duration.count());

        // Write the size and time to the CSV file
        csv_file << size << "," << total_duration.count() << "\n";

        // Pause for 1 second
        // std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // Close the CSV file
    csv_file.close();

    return 0;
}