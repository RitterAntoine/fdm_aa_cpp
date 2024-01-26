#include "scalar.h"

// Define the grid_edge_point_scalars function
Eigen::ArrayXf grid_edge_point_scalars(
    const Eigen::ArrayXi& edge_ndindex,
    int edge_axis,
    const Eigen::ArrayXf& grid_scalars_flattened,
    const Eigen::ArrayXi& grid_cell_ndcount) {
    // Create a zero array with the same size as edge_ndindex
    Eigen::ArrayXi shift = Eigen::ArrayXi::Zero(edge_ndindex.size());
    // Set the element at the edge_axis index to 1
    shift[edge_axis] = 1;
    // Create a 2D array for the edge vertex indices
    Eigen::ArrayXXi edge_vertex_ndindices(2, edge_ndindex.size());
    // Set the first row to the edge index
    edge_vertex_ndindices.row(0) = edge_ndindex;
    // Set the second row to the edge index plus the shift
    edge_vertex_ndindices.row(1) = edge_ndindex + shift;
    // Calculate the flattened indices of the edge vertices
    Eigen::ArrayXi edge_vertex_flattened_indices(2);
    edge_vertex_flattened_indices[0] = index1_from_ndindex(edge_vertex_ndindices.row(0), grid_cell_ndcount);
    edge_vertex_flattened_indices[1] = index1_from_ndindex(edge_vertex_ndindices.row(1), grid_cell_ndcount);
    // Get the scalars at the edge vertices
    Eigen::ArrayXf edge_scalars(2);
    for (int i = 0; i < 2; ++i) {
        edge_scalars[i] = grid_scalars_flattened[edge_vertex_flattened_indices[i]];
    }
    // Return the scalars
    return edge_scalars;
}