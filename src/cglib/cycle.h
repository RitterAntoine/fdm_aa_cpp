#ifndef Cycle_H
#define Cycle_H

#include <scalar.h>

class Cycle {
public:
    // Constructor
    Cycle(ListPointAdjacency list_point_adjacency, 
          Eigen::ArrayX2i cycle_data,
          unsigned int cycle_count);

    // Getters
    ListPointAdjacency getListPointAdjacency() const;
    Eigen::ArrayX2i getCycleData() const;
    unsigned int getCycleCount() const;

private:
    ListPointAdjacency list_point_adjacency_;
    Eigen::ArrayX2i cycle_data_;
    unsigned int cycle_count_;
};

#endif