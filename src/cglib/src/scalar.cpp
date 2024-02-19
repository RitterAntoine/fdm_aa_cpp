#include "scalar.h"

GetEdgeAdjacencyParams::GetEdgeAdjacencyParams(Edge2D edge, int edge_side, Eigen::Array<int, 2 ,2> edge_2dcount, bool same_side_bottom_left_corner_and_center):
    edge(edge), edge_side(edge_side), edge_2dcount(edge_2dcount), same_side_bottom_left_corner_and_center(same_side_bottom_left_corner_and_center) {}



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

Eigen::Array<float, 2, 1> grid_edge_root_point(const Edge2D& edge,
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

unsigned int convert_edge_shift_to_adjacency(Eigen::Array<int, 2, 1> shift,
                                             const GetEdgeAdjacencyParams params,
                                             int adjacent_edge_axis)
{
    if (params.edge.edge_axis == 1)
    {
        shift = shift.reverse();
    }
    Eigen::Array<int, 2, 1> adjacent_edge_ndindex = params.edge.edge_2dindex + shift;
    Edge2D adjacent_edge_ndindex_edge(adjacent_edge_ndindex, adjacent_edge_axis);
    return index1_from_2dindex(adjacent_edge_ndindex_edge,
                               params.edge_2dcount);
}


unsigned int get_edge_adjacency_case_001(const GetEdgeAdjacencyParams params)
{
    Eigen::Array<int, 2, 1> shift;
    shift << 1, -1 + params.edge_side;
    int adjacent_edge_axis = (params.edge.edge_axis + 1) % 2;
    return convert_edge_shift_to_adjacency(shift, params, adjacent_edge_axis);
}

unsigned int get_edge_adjacency_case_010(const GetEdgeAdjacencyParams params)
{
    Eigen::Array<int, 2, 1> shift;
    shift << 0, -1 + params.edge_side;
    int adjacent_edge_axis = (params.edge.edge_axis + 1) % 2;
    return convert_edge_shift_to_adjacency(shift, params, adjacent_edge_axis);
}

unsigned int get_edge_adjacency_case_100(const GetEdgeAdjacencyParams params)
{
    Eigen::Array<int, 2, 1> shift;
    shift << 0, -1 + 2 * params.edge_side;
    int adjacent_edge_axis = (params.edge.edge_axis + 1) % 2;
    return convert_edge_shift_to_adjacency(shift, params, adjacent_edge_axis);
}

unsigned int get_edge_adjacency_case_111(const GetEdgeAdjacencyParams params)
{
    return params.same_side_bottom_left_corner_and_center ? get_edge_adjacency_case_001(params) : get_edge_adjacency_case_010(params);
}


PointAdjacency uniform_grid_edge_root_point_and_adjacency(const Edge2D& edge,
                                                          Eigen::ArrayXd flattened_scalar_field,
                                                          Grid grid)
{
    // Grid edge root vertex computation is trivial
    Eigen::ArrayXf grid_edge_root_point_val  = grid_edge_root_point(edge,
                                                                    flattened_scalar_field,
                                                                    grid) + grid.cell_sides_length * 0.5;
    
    // Edge adjacency computation is less trivial.
    Eigen::Array<int, 2, 1> contour_grid_cell_2dcount;
    contour_grid_cell_2dcount << grid.cell_2dcount[0] - 1, grid.cell_2dcount[1] - 1;
    Eigen::Array<int, 2, 2> edge_2dcount = count2_per_axis(contour_grid_cell_2dcount);

    // Get the visible neighbors
    MaskedArray visible_neighbors_ndindices = neighboring_2dindices_direct(edge, contour_grid_cell_2dcount, Neighboring2Type::VISIBLE);

    // Compute the edge root existence
    Eigen::Array<bool, 2, 2> edge_root_existence;
    for (int i_axis = 0; i_axis < 2; ++i_axis)
    {
        Eigen::Array<int, 1, Eigen::Dynamic> visible_neighbors_ndindices_array = visible_neighbors_ndindices.array.row(i_axis);
        Eigen::Array<bool, 1, Eigen::Dynamic> edge_root_existence_i_axis = Eigen::Array<bool, 1, Eigen::Dynamic>::Zero(visible_neighbors_ndindices_array.size());
        for (int i = 0; i < visible_neighbors_ndindices_array.size(); ++i)
        {
            edge_root_existence_i_axis[i] = grid_edge_root_existence(edge, flattened_scalar_field, grid);
        }
        edge_root_existence_i_axis = edge_root_existence_i_axis && !visible_neighbors_ndindices.mask.row(i_axis);
        edge_root_existence.row(i_axis) = edge_root_existence_i_axis;
    }


    // Reorder the edge root existence
    Eigen::Array<bool, 2, 3> root_exist_config;
    int next_edge_axis = (edge.edge_axis + 1) % 2;
    root_exist_config << edge_root_existence(edge.edge_axis, 0), edge_root_existence(next_edge_axis, 0), edge_root_existence(next_edge_axis, 1),
                         edge_root_existence(edge.edge_axis, 1), edge_root_existence(next_edge_axis, 2), edge_root_existence(next_edge_axis, 3);

    // Compute the edge adjacent cells ndindices
    Eigen::Array<int, 2, 1> cell_shift = Eigen::Array<int, 2, 1>::Zero();
    if (edge.edge_axis == 0) {cell_shift << 0, -1;}
    else {cell_shift << -1, 0;}
    Eigen::Array<int, 2, 2> edge_adjacent_cells_2dindices = Eigen::Array<int, 2, 2>::Zero();
    edge_adjacent_cells_2dindices.row(0) = edge.edge_2dindex + cell_shift;
    edge_adjacent_cells_2dindices.row(1) = edge.edge_2dindex;
    
    Eigen::Array<bool, 2, 2> edge_adjacent_cells_2dindices_mask = Eigen::Array<bool, 2, 2>::Zero();
    for (int i = 0; i < edge_adjacent_cells_2dindices.rows(); ++i)
    {
        edge_adjacent_cells_2dindices_mask.row(i) = !index2d_is_valid(edge_adjacent_cells_2dindices.row(i), contour_grid_cell_2dcount);
    }

    for (int i = 0; i < edge_adjacent_cells_2dindices.rows(); ++i)
    {
        for (int j = 0; j < edge_adjacent_cells_2dindices.cols(); ++j)
        {
            if (edge_adjacent_cells_2dindices_mask(i, j))
            {
                edge_adjacent_cells_2dindices(i, j) = 0;
            }
        }
    }

    Eigen::Array<int, 2, 1> edge_adjacent_cells_1dindices = Eigen::Array<int, 2, 1>::Zero();
    for (int i = 0; i < edge_adjacent_cells_2dindices.size(); ++i)
    {
        edge_adjacent_cells_1dindices[i] = index1_from_2dindex(edge_adjacent_cells_2dindices.row(i), contour_grid_cell_2dcount);
    }

    // Compute the grid corner vertex ndindices
    Eigen::MatrixXi grid_corner_vertex_ndindices(edge_adjacent_cells_2dindices.size(), 4);
    for (int i = 0; i < edge_adjacent_cells_2dindices.size(); ++i)
    {
        grid_corner_vertex_ndindices.row(i) = corner_vertex_2dindices(edge_adjacent_cells_2dindices.row(i)).transpose();
    }

    // Compute the grid corner 1dindices
    Eigen::Array<int, 2, 1> grid_corner_1dindices = Eigen::Array<int, 2, 1>::Zero();
    for (int i = 0; i < grid_corner_vertex_ndindices.rows(); ++i)
    {
        grid_corner_1dindices[i] = index1_from_2dindex(grid_corner_vertex_ndindices.row(i), grid.cell_2dcount);
    }

    // Compute the corner scalars
    Eigen::Array<float, 2, 4> corner_scalars = Eigen::Array<float, 2, 4>::Zero();
    for (int i = 0; i < grid_corner_1dindices.size(); ++i)
    {
        for (int j = 0; j < corner_scalars.cols(); ++j)
        {  
            corner_scalars(i, j) = flattened_scalar_field[grid_corner_1dindices[i]];
        }
    }

    // Compute the average scalar
    Eigen::Array<float, 2, 1> average_scalar = corner_scalars.rowwise().mean();

    // Compute the same side corner and center
    Eigen::Array<bool, 2, 1> same_side_corner_and_center = Eigen::Array<bool, 2, 1>::Zero();
    for (int i = 0; i < same_side_corner_and_center.size(); ++i)
    {
        same_side_corner_and_center[i] = average_scalar[i] * flattened_scalar_field[index1_from_2dindex(edge.edge_2dindex, grid.cell_2dcount)] >= 0;
    }

    // Compute the case index
    Eigen::Array<int, 2, 1> case_index = Eigen::Array<int, 2, 1>::Zero();
    case_index[0] = 4 * root_exist_config(0, 0) + 2 * root_exist_config(0, 1) + 1 * root_exist_config(0, 2);
    case_index[1] = 4 * root_exist_config(1, 0) + 2 * root_exist_config(1, 1) + 1 * root_exist_config(1, 2);

    // Compute the branches
    Eigen::Array<unsigned int, 2, 1> branches = Eigen::Array<unsigned int, 2, 1>::Zero();
    branches[0] = get_edge_adjacency_no_extraction_case(GetEdgeAdjacencyParams(edge, 0, edge_2dcount, same_side_corner_and_center[0]));
    branches[1] = get_edge_adjacency_no_extraction_case(GetEdgeAdjacencyParams(edge, 1, edge_2dcount, same_side_corner_and_center[1]));

    // Compute the adjacency list
    Eigen::Array<unsigned int, 2, 1> adjacency_list = Eigen::Array<unsigned int, 2, 1>::Zero();
    for (int i = 0; i < 2; ++i)
    {
        GetEdgeAdjacencyParams get_edge_adjacency_params_i(edge, i, edge_2dcount, same_side_corner_and_center[i]);
        adjacency_list[i] = branches[i];
    }

    // Compute the adjacency array
    Eigen::Array<unsigned int, 2, 1> adjacency_array = Eigen::Array<unsigned int, 2, 1>::Zero();
    for (int i = 0; i < adjacency_list.size(); ++i)
    {
        if (adjacency_list[i] == INT_MAX)
        {
            adjacency_array[i] = std::nan("");
        }
        else
        {
            adjacency_array[i] = adjacency_list[i];
        }
    }

    return PointAdjacency(grid_edge_root_point_val, adjacency_array);
}

PointAdjacency grid2_contour(Eigen::ArrayXf grid_scalars_flattened,
                             Eigen::Array<int, 2, 1> scalar_field_cell_2dcount,
                             Grid scalar_field_grid) 
{
    // 



    // Fake return to test
    PointAdjacency point_adjacency(Eigen::ArrayXf::Zero(2), Eigen::Array<unsigned int, 2, 1>::Zero());
    return point_adjacency;
}