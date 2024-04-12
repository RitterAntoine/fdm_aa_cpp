#include <cycle.h>

// Constructor
Cycle::Cycle(Graph list_point_adjacency,
             Eigen::Array<bool, Eigen::Dynamic, 1> visited_points,
             Eigen::ArrayX3i cycle_points_data,
             Eigen::ArrayX2i cycle_data,
             unsigned int cycle_count)
    : list_point_adjacency_(list_point_adjacency), visited_points_(visited_points), cycle_points_data_(cycle_points_data), cycle_data_(cycle_data), cycle_count_(cycle_count) {}

// Getters
Graph Cycle::getListPointAdjacency() const { return list_point_adjacency_; }
Eigen::Array<bool, Eigen::Dynamic, 1> Cycle::getVisitedPoints() const { return visited_points_; }
Eigen::ArrayX3i Cycle::getCyclePointsData() const { return cycle_points_data_; }
Eigen::ArrayX2i Cycle::getCycleData() const { return cycle_data_; }
unsigned int Cycle::getCycleCount() const { return cycle_count_; }

// Setters
void Cycle::setVisitedPoints(Eigen::Array<bool, Eigen::Dynamic, 1> visited_points) { visited_points_ = visited_points; }
void Cycle::setCyclePointsData(Eigen::ArrayX3i cycle_points_data) { cycle_points_data_ = cycle_points_data; }
void Cycle::setCycleData(Eigen::ArrayX2i cycle_data) { cycle_data_ = cycle_data; }
void Cycle::setCycleCount(unsigned int cycle_count) { cycle_count_ = cycle_count; }

void save_cycle(const std::string& file, const Cycle& cycle) {
    Eigen::ArrayX2f points = cycle.getListPointAdjacency().getListPoint();
    Eigen::ArrayX2i list_adjacency = cycle.getListPointAdjacency().getListAdjacency();
    Eigen::Array<bool, Eigen::Dynamic, 1> visited_points = cycle.getVisitedPoints();
    Eigen::ArrayX3i cycle_points_data = cycle.getCyclePointsData();
    Eigen::ArrayX2i cycle_data = cycle.getCycleData();
    unsigned int cycle_count = cycle.getCycleCount();

    std::ofstream out(file);
    out << "points" << std::endl;
    for (int i = 0; i < points.rows(); i++) {
        out << points(i, 0) << " " << points(i, 1) << std::endl;
    }
    out << "list_adjacency" << std::endl;
    for (int i = 0; i < list_adjacency.rows(); i++) {
        out << list_adjacency(i, 0) << " " << list_adjacency(i, 1) << std::endl;
    }
    out << "visited_points" << std::endl;
    for (int i = 0; i < visited_points.rows(); i++) {
        out << visited_points(i) << std::endl;
    }
    out << "cycle_points_data" << std::endl;
    for (int i = 0; i < cycle_points_data.rows(); i++) {
        out << cycle_points_data(i, 0) << " " << cycle_points_data(i, 1) << " " << cycle_points_data(i, 2) << std::endl;
    }
    out << "cycle_data" << std::endl;
    for (int i = 0; i < cycle_data.rows(); i++) {
        out << cycle_data(i, 0) << " " << cycle_data(i, 1) << std::endl;
    }
    out << "cycle_count" << std::endl;
    out << cycle_count << std::endl;
    out.close();
}

Cycle load_cycle(const std::string& file) {
    std::ifstream in(file);
    std::string line;
    std::string mode;
    Eigen::ArrayX2f points;
    Eigen::ArrayX2i list_adjacency;
    Eigen::Array<bool, Eigen::Dynamic, 1> visited_points;
    Eigen::ArrayX3i cycle_points_data;
    Eigen::ArrayX2i cycle_data;
    unsigned int cycle_count;
    while (std::getline(in, line)) {
        if (line == "points") {
            mode = "points";
            continue;
        }
        if (line == "list_adjacency") {
            mode = "list_adjacency";
            continue;
        }
        if (line == "visited_points") {
            mode = "visited_points";
            continue;
        }
        if (line == "cycle_points_data") {
            mode = "cycle_points_data";
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
        if (mode == "list_adjacency") {
            std::istringstream iss(line);
            int next_point, previous_point;
            iss >> next_point >> previous_point;
            list_adjacency.conservativeResize(list_adjacency.rows() + 1, 2);
            list_adjacency(list_adjacency.rows() - 1, 0) = next_point;
            list_adjacency(list_adjacency.rows() - 1, 1) = previous_point;
        }
        if (mode == "visited_points") {
            std::istringstream iss(line);
            bool visited_point;
            iss >> visited_point;
            visited_points.conservativeResize(visited_points.rows() + 1);
            visited_points(visited_points.rows() - 1) = visited_point;
        }
        if (mode == "cycle_points_data") {
            std::istringstream iss(line);
            int point, next_point, cycle;
            iss >> point >> next_point >> cycle;
            cycle_points_data.conservativeResize(cycle_points_data.rows() + 1, 3);
            cycle_points_data(cycle_points_data.rows() - 1, 0) = point;
            cycle_points_data(cycle_points_data.rows() - 1, 1) = next_point;
            cycle_points_data(cycle_points_data.rows() - 1, 2) = cycle;
        }
        if (mode == "cycle_data") {
            std::istringstream iss(line);
            int starting_point, nb_points;
            iss >> starting_point >> nb_points;
            cycle_data.conservativeResize(cycle_data.rows() + 1, 2);
            cycle_data(cycle_data.rows() - 1, 0) = starting_point;
            cycle_data(cycle_data.rows() - 1, 1) = nb_points;
        }
        if (mode == "cycle_count") {
            std::istringstream iss(line);
            iss >> cycle_count;
        }
    }
    in.close();
    Graph list_point_adjacency(points, list_adjacency);
    return Cycle(list_point_adjacency, visited_points, cycle_points_data, cycle_data, cycle_count);
}

void delete_file(const std::string& file) {
    std::remove(file.c_str());
}
int number_of_points_in_cycle_points_data(const Eigen::ArrayX3i& cycle_points_data) {
    return (cycle_points_data.col(0) != INT_MAX).count();
}

void process_point(Cycle& cycle, int& current_point, int& next_point, int& previous_point, int cycle_count) {
    Eigen::Array<bool, Eigen::Dynamic, 1> visited_points = cycle.getVisitedPoints();
    Eigen::ArrayX3i cycle_points_data = cycle.getCyclePointsData();

    visited_points(current_point) = true;
    cycle.setVisitedPoints(visited_points);
    cycle_points_data(current_point, 0) = current_point;
    cycle_points_data(current_point, 1) = next_point;
    cycle_points_data(current_point, 2) = cycle_count;
    cycle.setCyclePointsData(cycle_points_data);
}

void graph_flood_from_point(Cycle& cycle, int point) {
    Cycle cycle_copy = cycle;
    int current_point = point;
    int temp_current_point = current_point;
    auto listAdjacency = cycle.getListPointAdjacency().getListAdjacency();
    int next_point = listAdjacency(current_point, 0);
    int previous_point = listAdjacency(current_point, 1);
    int cycle_count = cycle.getCycleCount();

    while (!cycle.getVisitedPoints()(current_point)) {
        process_point(cycle, current_point, next_point, previous_point, cycle_count);
        current_point = next_point;
        next_point = listAdjacency(current_point, 0);
        if (next_point == temp_current_point) {
            next_point = listAdjacency(current_point, 1);
        }
        previous_point = temp_current_point;
        temp_current_point = current_point;

        // Check if next_point or previous_point is INT_MAX
        if (next_point == INT_MAX || previous_point == INT_MAX) {
            cycle = cycle_copy;
            break;
        }
    }
}

int number_of_points_in_cycle(const Cycle& cycle, int cycle_number) {
    return (cycle.getCyclePointsData().col(2) == cycle_number).count();
}

// The logic of the following function is simple, we first create a list of the valid points with a boolean for each point if we have already visited it.
// Then for each point, we check if we have already visited it, if not we start a new cycle and we visit all the points that are connected to the current point.
// If we find a point that we have already visited, we stop the cycle and we store the cycle in the list of cycles.

Cycle create_from_graph(const Graph& graph) {
    int number_of_points = graph.getListPoint().rows();

    Eigen::Array<bool, Eigen::Dynamic, 1> visited_points = Eigen::Array<bool, Eigen::Dynamic, 1>::Zero(number_of_points);
    Eigen::ArrayX3i cycle_points_data = Eigen::ArrayX3i(number_of_points, 3);
    cycle_points_data.fill(INT_MAX);

    Eigen::ArrayX2i cycle_data = Eigen::ArrayX2i(number_of_points, 2);
    cycle_data.fill(INT_MAX);

    unsigned int cycle_count = 0;

    Cycle cycle(graph, visited_points, cycle_points_data, cycle_data, cycle_count);

    auto listAdjacency = graph.getListAdjacency();
    auto cycleVisitedPoints = cycle.getVisitedPoints();
    auto cycleData = cycle.getCycleData();

    for (int i = 0; i < number_of_points; i++) {
        if (listAdjacency(i, 0) == INT_MAX || listAdjacency(i, 1) == INT_MAX) {
            continue;
        }

        int next_point = listAdjacency(i, 0);
        int previous_point = listAdjacency(i, 1);

        if (!cycleVisitedPoints(i) && next_point != INT_MAX && previous_point != INT_MAX) {
            cycleVisitedPoints(i) = true;

            Cycle cycle_copy = cycle;
            graph_flood_from_point(cycle, i);

            if ((cycle.getVisitedPoints().array() == cycle_copy.getVisitedPoints().array()).all()) {
                continue;
            }

            cycleData = cycle.getCycleData();
            cycleData(cycle_count, 0) = i;
            cycleData(cycle_count, 1) = number_of_points_in_cycle(cycle, cycle_count);
            cycle.setCycleData(cycleData);

            cycle_count++;
            cycle.setCycleCount(cycle_count);
        }
    }

    return cycle;
}

Polyline cycle_to_polyline(const Cycle& cycle, int cycle_number) {
    // This function is used to convert a cycle to a polyline

    // We extract the points and the cycle_points_data from the cycle
    Eigen::ArrayX2f points = cycle.getListPointAdjacency().getListPoint();
    Eigen::ArrayX3i cycle_points_data = cycle.getCyclePointsData();
    Eigen::ArrayX2i cycle_data = cycle.getCycleData();

    // We extract the number of points in the cycle
    int number_of_points = cycle_data(cycle_number, 1);

    // We create a list of the points that are in the cycle
    Eigen::ArrayX2f cycle_points = Eigen::ArrayX2f(number_of_points, 2);

    // We iterate over the cycle_points_data to extract the points that are in the cycle in the right order
    int current_point = cycle_data(cycle_number, 0);
    for (int i = 0; i < number_of_points; i++) {
        cycle_points(i, 0) = points(current_point, 0);
        cycle_points(i, 1) = points(current_point, 1);
        current_point = cycle_points_data(current_point, 1);
    }

    // We create a polyline object with the data that we have created
    Polyline polyline(cycle_points);

    return polyline;
}