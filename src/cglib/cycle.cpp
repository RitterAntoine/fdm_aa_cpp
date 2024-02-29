#include <cycle.h>

// Constructor
Cycle::Cycle(ListPointAdjacency list_point_adjacency, 
             Eigen::ArrayX2i cycle_data,
             unsigned int cycle_count)
    : list_point_adjacency_(list_point_adjacency), cycle_data_(cycle_data), cycle_count_(cycle_count) {}

// Getters
ListPointAdjacency Cycle::getListPointAdjacency() const { return list_point_adjacency_; }
Eigen::ArrayX2i Cycle::getCycleData() const { return cycle_data_; }
unsigned int Cycle::getCycleCount() const { return cycle_count_; }

void save(const std::string& file, const Cycle& cycle) {
    Eigen::ArrayX2f points = cycle.getListPointAdjacency().getListPoint();
    Eigen::ArrayX2i cycle_data = cycle.getCycleData();
    unsigned int cycle_count = cycle.getCycleCount();

    std::ofstream out(file);
    out << "points" << std::endl;
    for (int i = 0; i < points.rows(); i++) {
        out << points(i, 0) << " " << points(i, 1) << std::endl;
    }
    out << "cycle_data" << std::endl;
    for (int i = 0; i < cycle_data.rows(); i++) {
        out << cycle_data(i, 0) << " " << cycle_data(i, 1) << std::endl;
    }
    out << "cycle_count" << std::endl;
    out << cycle_count << std::endl;
    out.close();
}

Cycle load(const std::string& file) {
    std::ifstream in(file);
    std::string line;
    std::string mode;
    Eigen::ArrayX2f points;
    Eigen::ArrayX2i cycle_data;
    unsigned int cycle_count;
    while (std::getline(in, line)) {
        if (line == "points") {
            mode = "points";
            continue;
        }
        if (line == "cycle_data") {
            mode = "cycle_data";
            continue;
        }
        if (line == "cycle_count") {
            mode = "cycle_count";
            continue;
        }
        if (mode == "points") {
            std::istringstream iss(line);
            float x, y;
            iss >> x >> y;
            points.conservativeResize(points.rows() + 1, 2);
            points(points.rows() - 1, 0) = x;
            points(points.rows() - 1, 1) = y;
        }
        if (mode == "cycle_data") {
            std::istringstream iss(line);
            int x, y;
            iss >> x >> y;
            cycle_data.conservativeResize(cycle_data.rows() + 1, 2);
            cycle_data(cycle_data.rows() - 1, 0) = x;
            cycle_data(cycle_data.rows() - 1, 1) = y;
        }
        if (mode == "cycle_count") {
            std::istringstream iss(line);
            iss >> cycle_count;
        }
    }
    in.close();
    return Cycle(ListPointAdjacency(points, cycle_data), cycle_data, cycle_count);
}