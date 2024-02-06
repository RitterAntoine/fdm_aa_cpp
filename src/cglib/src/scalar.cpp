#include "scalar.h"

Eigen::ArrayXd grid_edge_point_scalars(
    const Eigen::ArrayXi& edge_ndindex,
    int edge_axis,
    const Eigen::ArrayXd& grid_scalars_flattened,
    const Eigen::ArrayXi& grid_cell_ndcount) {
    
    Eigen::ArrayXi shift = Eigen::ArrayXi::Zero(edge_ndindex.size());
    shift[edge_axis] = 1;
    
    Eigen::ArrayXXi edge_vertex_ndindices(2, edge_ndindex.size());
    edge_vertex_ndindices.row(0) = edge_ndindex;
    edge_vertex_ndindices.row(1) = edge_ndindex + shift;
    
    Eigen::ArrayXi edge_vertex_flattened_indices(edge_vertex_ndindices.rows());
    for (int i = 0; i < edge_vertex_ndindices.rows(); ++i) {
        edge_vertex_flattened_indices[i] = index1_from_ndindex(edge_vertex_ndindices.row(i), grid_cell_ndcount);
    }
    
    Eigen::ArrayXd edge_scalars(edge_vertex_flattened_indices.size());
    for (int i = 0; i < edge_vertex_flattened_indices.size(); ++i) {
        edge_scalars[i] = grid_scalars_flattened[edge_vertex_flattened_indices[i]];
    }
    
    return edge_scalars;
}