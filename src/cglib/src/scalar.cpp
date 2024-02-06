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

Eigen::ArrayXf grid_edge_root_point(
    const Eigen::ArrayXi& edge_ndindex,
    int edge_axis,
    const Eigen::ArrayXd& flattened_scalar_field,
    const Grid& grid) {
    
    Eigen::ArrayXXf edge_endpoints_val = endpoints(edge_ndindex, edge_axis, grid);
    Eigen::ArrayXd edge_point_scalars_val = grid_edge_point_scalars(
        edge_ndindex,
        edge_axis,
        flattened_scalar_field,
        grid.cell_ndcount);
    bool mask = float_same_sign(edge_point_scalars_val[0], edge_point_scalars_val[1]);
    float u = solve_linear_interpolation_equation(
        edge_point_scalars_val[0], edge_point_scalars_val[1]);
    float epsilon = 0.01;
    u = clamp(u, epsilon, 1. - epsilon);
    Eigen::ArrayXf root_point = (1. - u) * edge_endpoints_val.row(0) + u * edge_endpoints_val.row(1);
    return mask ? Eigen::ArrayXf::Constant(root_point.size(), std::nan("")) : root_point;
}