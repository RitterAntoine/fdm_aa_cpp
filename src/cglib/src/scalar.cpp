#include "scalar.h"

GetEdgeAdjacencyParams::GetEdgeAdjacencyParams(Edge2D edge, int edge_side, Eigen::Array<int, 2 ,1> edge_cell_2dcount, bool same_side_corner_and_center):
    edge(edge), edge_side(edge_side), edge_cell_2dcount(edge_cell_2dcount), same_side_corner_and_center(same_side_corner_and_center) {}

Eigen::Array<double, 2, 1> grid_edge_point_scalars(const Edge2D& edge,
                                                   const Eigen::ArrayXd& grid_scalars_flattened,
                                                   const Eigen::Array<int, 2 ,1> grid_cell_2dcount)
{
    
    Eigen::Array<int, 2 ,1> shift = Eigen::Array<int, 2 ,1>::Zero(edge.edge_2dindex.size());
    shift[edge.edge_axis] = 1;
    
    Eigen::ArrayXXi edge_vertex_ndindices(2, edge.edge_2dindex.size());
    edge_vertex_ndindices.row(0) = edge.edge_2dindex;
    edge_vertex_ndindices.row(1) = edge.edge_2dindex + shift;
    
    Eigen::Array<int, 2 ,1> edge_vertex_flattened_indices(edge_vertex_ndindices.rows());
    for (int i = 0; i < edge_vertex_ndindices.rows(); ++i)
    {
        edge_vertex_flattened_indices[i] = index1_from_2dindex(edge_vertex_ndindices.row(i), grid_cell_2dcount);
    }
    
    Eigen::Array<double, 2, 1> edge_scalars(edge_vertex_flattened_indices.size());
    for (int i = 0; i < edge_vertex_flattened_indices.size(); ++i)
    {
        edge_scalars[i] = grid_scalars_flattened[edge_vertex_flattened_indices[i]];
    }
    
    return edge_scalars;
}

bool grid_edge_root_existence(const Edge2D& edge,
                              const Eigen::ArrayXd& flattened_scalar_field,
                              const Grid& grid) 
{
    
    Eigen::ArrayXd edge_point_scalars_val = grid_edge_point_scalars(edge,
                                                                    flattened_scalar_field,
                                                                    grid.cell_2dcount);

    return !float_same_sign(edge_point_scalars_val[0], edge_point_scalars_val[1]);
}

Eigen::ArrayXf grid_edge_root_point(const Edge2D& edge,
                                    const Eigen::ArrayXd& flattened_scalar_field,
                                    const Grid& grid)
{
    Eigen::ArrayXXf edge_endpoints_val = endpoints(edge, grid);
    Eigen::ArrayXd edge_point_scalars_val = grid_edge_point_scalars(edge,
                                                                    flattened_scalar_field,
                                                                    grid.cell_2dcount);
    bool mask = float_same_sign(edge_point_scalars_val[0],
                                edge_point_scalars_val[1]);
    float u = solve_linear_interpolation_equation(edge_point_scalars_val[0],
                                                  edge_point_scalars_val[1]);
    float epsilon = 0.01;
    u = clamp(u,
              epsilon,
              1. - epsilon);
    Eigen::ArrayXf root_point = (1. - u) * edge_endpoints_val.row(0) + u * edge_endpoints_val.row(1);
    return mask ? Eigen::ArrayXf::Constant(root_point.size(), std::nan("")) : root_point;
}

unsigned int get_edge_adjacency_no_extraction_case(const GetEdgeAdjacencyParams params)
{
    return INT_MAX;
}




PointAdjacency uniform_grid_edge_root_point_and_adjacency(const Edge2D& edge,
                                                          Eigen::ArrayXd flattened_scalar_field,
                                                          Grid grid)
{
    Eigen::ArrayXf grid_edge_root_point_val  = grid_edge_root_point(edge,
                                                                    flattened_scalar_field,
                                                                    grid) + grid.cell_sides_length * 0.5;
                                                                    

    //Fake return to test
    PointAdjacency point_adjacency(Eigen::ArrayXXf::Zero(2, 2), Eigen::ArrayXXi::Zero(2, 2));
    return point_adjacency;
}

PointAdjacency grid2_contour(Eigen::ArrayXf grid_scalars_flattened,
                             Eigen::Array<int, 2, 1> scalar_field_cell_2dcount,
                             Grid scalar_field_grid) 
{
    // Fake return to test
    PointAdjacency point_adjacency(Eigen::ArrayXXf::Zero(2, 2), Eigen::ArrayXXi::Zero(2, 2));
    return point_adjacency;
}