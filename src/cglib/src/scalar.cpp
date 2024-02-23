#include "scalar.h"
#include <iostream>

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
    Eigen::Array<float, 2, 1> grid_edge_root_point_val  = grid_edge_root_point(edge,
                                                                    flattened_scalar_field,
                                                                    grid) + grid.cell_sides_length * 0.5;

    // Edge adjacency computation is less trivial.
    Eigen::Array<int, 2, 1> contour_grid_cell_2dcount;
    contour_grid_cell_2dcount << grid.cell_2dcount[0] - 1, grid.cell_2dcount[1] - 1;

    Eigen::Array<int, 2, 2> edge_2dcount = count2_per_axis(contour_grid_cell_2dcount);

    // Get the visible neighbors
    MaskedArray visible_neighbors_ndindices = neighboring_2dindices_direct(edge, contour_grid_cell_2dcount, Neighboring2Type::VISIBLE);

    // Compute the edge root existence
    bool edge_root_existence_h1;
    bool edge_root_existence_h2;
    bool edge_root_existence_h3;
    bool edge_root_existence_h4;
    bool edge_root_existence_v1;
    bool edge_root_existence_v2;
    bool edge_root_existence_v3;
    bool edge_root_existence_v4;

    if (visible_neighbors_ndindices.mask[0]) {edge_root_existence_h1 = false;}
    else {Edge2D edge_h1 = Edge2D(visible_neighbors_ndindices.array.row(0), 0);edge_root_existence_h1 = grid_edge_root_existence(edge_h1, flattened_scalar_field, grid);}

    if (visible_neighbors_ndindices.mask[1]) {edge_root_existence_h2 = false;}
    else {Edge2D edge_h2 = Edge2D(visible_neighbors_ndindices.array.row(1), 0);edge_root_existence_h2 = grid_edge_root_existence(edge_h2, flattened_scalar_field, grid);}

    if (visible_neighbors_ndindices.mask[2]) {edge_root_existence_h3 = false;}
    else {Edge2D edge_h3 = Edge2D(visible_neighbors_ndindices.array.row(2), 0);edge_root_existence_h3 = grid_edge_root_existence(edge_h3, flattened_scalar_field, grid);}

    if (visible_neighbors_ndindices.mask[3]) {edge_root_existence_h4 = false;}
    else {Edge2D edge_h4 = Edge2D(visible_neighbors_ndindices.array.row(3), 0);edge_root_existence_h4 = grid_edge_root_existence(edge_h4, flattened_scalar_field, grid);}

    if (visible_neighbors_ndindices.mask[4]) {edge_root_existence_v1 = false;}
    else {Edge2D edge_v1 = Edge2D(visible_neighbors_ndindices.array.row(4), 1);edge_root_existence_v1 = grid_edge_root_existence(edge_v1, flattened_scalar_field, grid);}

    if (visible_neighbors_ndindices.mask[5]) {edge_root_existence_v2 = false;}
    else {Edge2D edge_v2 = Edge2D(visible_neighbors_ndindices.array.row(5), 1);edge_root_existence_v2 = grid_edge_root_existence(edge_v2, flattened_scalar_field, grid);}

    if (visible_neighbors_ndindices.mask[6]) {edge_root_existence_v3 = false;}
    else {Edge2D edge_v3 = Edge2D(visible_neighbors_ndindices.array.row(6), 1);edge_root_existence_v3 = grid_edge_root_existence(edge_v3, flattened_scalar_field, grid);}

    if (visible_neighbors_ndindices.mask[7]) {edge_root_existence_v4 = false;}
    else {Edge2D edge_v4 = Edge2D(visible_neighbors_ndindices.array.row(7), 1);edge_root_existence_v4 = grid_edge_root_existence(edge_v4, flattened_scalar_field, grid);}


    Eigen::Array<bool, 8, 1> edge_root_existence;
    edge_root_existence << edge_root_existence_h1,
                           edge_root_existence_h2,
                           edge_root_existence_h3,
                           edge_root_existence_h4,
                           edge_root_existence_v1,
                           edge_root_existence_v2,
                           edge_root_existence_v3,
                           edge_root_existence_v4;

    

    // Reorder the edge root existence
    Eigen::Array<bool, 2, 3> root_exist_config;
    if (edge.edge_axis == 0)
    {
        root_exist_config.row(0) << edge_root_existence[0], edge_root_existence[4], edge_root_existence[5];
        root_exist_config.row(1) << edge_root_existence[1], edge_root_existence[6], edge_root_existence[7];
    }
    else
    {
        root_exist_config.row(0) << edge_root_existence[4], edge_root_existence[0], edge_root_existence[1];
        root_exist_config.row(1) << edge_root_existence[5], edge_root_existence[2], edge_root_existence[3];
    }
    

    // Compute the edge adjacent cells ndindices
    Eigen::Array<int, 2, 1> cell_shift = Eigen::Array<int, 2, 1>::Zero();
    Eigen::Array<int, 2, 2> edge_adjacent_cells_2dindices = Eigen::Array<int, 2, 2>::Zero();
    if (edge.edge_axis == 0) 
    {
        // First row is for the bottom
        if (root_exist_config(0, 0) * root_exist_config(0, 1) * root_exist_config(0, 2) == 0)
        {
            if (root_exist_config(0, 0))
            {
                cell_shift << 0, -1;
                edge_adjacent_cells_2dindices.row(0) = edge.edge_2dindex + cell_shift;
            }
            if (root_exist_config(0, 1))
            {
                cell_shift << 0, -1;
                edge_adjacent_cells_2dindices.row(0) = edge.edge_2dindex + cell_shift;
            }
            if (root_exist_config(0, 2))
            {
                cell_shift << 1, -1;
                edge_adjacent_cells_2dindices.row(0) = edge.edge_2dindex + cell_shift;
            }
        }
        else
        {
            cell_shift << 0, -1;
            edge_adjacent_cells_2dindices.row(0) = edge.edge_2dindex + cell_shift;
        }

        // Second row is for the top
        if (root_exist_config(1, 0) * root_exist_config(1, 1) * root_exist_config(1, 2) == 0)
        {
            if (root_exist_config(1, 0))
            {
                cell_shift << 0, 1;
                edge_adjacent_cells_2dindices.row(1) = edge.edge_2dindex + cell_shift;
            }
            if (root_exist_config(1, 1))
            {
                cell_shift << 0, 0;
                edge_adjacent_cells_2dindices.row(1) = edge.edge_2dindex + cell_shift;
            }
            if (root_exist_config(1, 2))
            {
                cell_shift << 1, 0;
                edge_adjacent_cells_2dindices.row(1) = edge.edge_2dindex + cell_shift;
            }
        }
        else
        {
            cell_shift << 1, 0;
            edge_adjacent_cells_2dindices.row(1) = edge.edge_2dindex + cell_shift;
        }
    }
    else // edge.axis == 1
    {
        // First row is for the left
        if (root_exist_config(0, 0) * root_exist_config(0, 1) * root_exist_config(0, 2) == 0)
        {
            if (root_exist_config(0, 0))
            {
                cell_shift << -1, 0;
                edge_adjacent_cells_2dindices.row(0) = edge.edge_2dindex + cell_shift;
            }
            if (root_exist_config(0, 1))
            {
                cell_shift << -1, 0;
                edge_adjacent_cells_2dindices.row(0) = edge.edge_2dindex + cell_shift;
            }
            if (root_exist_config(0, 2))
            {
                cell_shift << -1, 1;
                edge_adjacent_cells_2dindices.row(0) = edge.edge_2dindex + cell_shift;
            }
        }
        else
        {
            cell_shift << 0, -1;
            edge_adjacent_cells_2dindices.row(0) = edge.edge_2dindex + cell_shift;
        }

        // Second row is for the right
        if (root_exist_config(1, 0) * root_exist_config(1, 1) * root_exist_config(1, 2) == 0)
        {
            if (root_exist_config(1, 0))
            {
                cell_shift << 1, 0;
                edge_adjacent_cells_2dindices.row(1) = edge.edge_2dindex + cell_shift;
            }
            if (root_exist_config(1, 1))
            {
                cell_shift << 0, 0;
                edge_adjacent_cells_2dindices.row(1) = edge.edge_2dindex + cell_shift;
            }
            if (root_exist_config(1, 2))
            {
                cell_shift << 0, 1;
                edge_adjacent_cells_2dindices.row(1) = edge.edge_2dindex + cell_shift;
            }
        }
        else
        {
            cell_shift << 1, 0;
            edge_adjacent_cells_2dindices.row(1) = edge.edge_2dindex + cell_shift;
        }
    }
    
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

    // Compute the grid corner vertex ndindices
    Eigen::Array<int, 4, 2> grid_corner_vertex_2dindices_top = corner_vertex_2dindices(edge_adjacent_cells_2dindices.row(0));
    Eigen::Array<int, 4, 2> grid_corner_vertex_2dindices_bottom = corner_vertex_2dindices(edge_adjacent_cells_2dindices.row(1));
    if (edge.edge_axis == 1)
    {
        Eigen::Array<int, 2, 1> shift;
        shift << 0, -1;
        grid_corner_vertex_2dindices_bottom.row(0) += shift;
        grid_corner_vertex_2dindices_bottom.row(1) += shift;
        grid_corner_vertex_2dindices_bottom.row(2) += shift;
        grid_corner_vertex_2dindices_bottom.row(3) += shift;
    }

    // Compute the grid corner 1dindices
    Eigen::Array<int, 4, 1> grid_corner_1dindices_top = Eigen::Array<int, 4, 1>::Zero();
    Eigen::Array<int, 4, 1> grid_corner_1dindices_bottom = Eigen::Array<int, 4, 1>::Zero();
    for (int i = 0; i < grid_corner_vertex_2dindices_top.rows(); ++i)
    {
        grid_corner_1dindices_top[i] = index1_from_2dindex(grid_corner_vertex_2dindices_top.row(i), grid.cell_2dcount);
        grid_corner_1dindices_bottom[i] = index1_from_2dindex(grid_corner_vertex_2dindices_bottom.row(i), grid.cell_2dcount);
    }

    // Compute the corner scalars
    Eigen::Array<float, 4, 1> corner_scalars_top = Eigen::Array<float, 4, 1>::Zero();
    Eigen::Array<float, 4, 1> corner_scalars_bottom = Eigen::Array<float, 4, 1>::Zero();
    for (int i = 0; i < corner_scalars_top.size(); ++i)
    {
        corner_scalars_top[i] = flattened_scalar_field[grid_corner_1dindices_top[i]];
        corner_scalars_bottom[i] = flattened_scalar_field[grid_corner_1dindices_bottom[i]];
    }

    // Compute the average scalar
    float average_scalar_top = corner_scalars_top.mean();
    float average_scalar_bottom = corner_scalars_bottom.mean();

    // Compute the same side corner and center
    bool same_side_corner_and_center_top = average_scalar_top * flattened_scalar_field[index1_from_2dindex(edge.edge_2dindex, grid.cell_2dcount)] >= 0;
    bool same_side_corner_and_center_bottom = average_scalar_bottom * flattened_scalar_field[index1_from_2dindex(edge.edge_2dindex, grid.cell_2dcount)] >= 0;

    // autopep8: off
    // axis == 0 ->
    // We are currently computing the adjacency of a horizontal edge.
    //
    //     side == 0 -> find adjacency with visible bottom edges
    //
    //      001          010          100          111          111
    //   _ _ _ _o_    _o_ __ _     _ _ _o_ _    _o_ _ _ _    _ _ _ _o_
    //  |        \|  |/        |  |     |   |  |/        |  |        \|
    //  |         o  o         |  |     |   |  o         o  o         o
    //  |         |  |         |  |     |   |  |        /|  |\        |
    //  |_________|  |_________|  |_____o___|  |______ o_|  |_o_______|
    //
    //                                 ||
    //                        Flip Y   ||
    //                                 \/
    //     side == 1 -> find adjacency with top visible edges
    //
    //      001          010          100          111          111
    //   _________    _________    _____o___    ______ o_    _o_______
    //  |         |  |         |  |     |   |  |        \|  |/        |
    //  |         o  o         |  |     |   |  o         o  o         o
    //  |        /|  |\        |  |     |   |  |\        |  |        /|
    //  |_ _ _ _o_|  |_o_ __ _ |  |_ _ _o_ _|  |_o_ _ _ _|  |_ _ _ _o_|
    //
    // axis == 1 ->
    // We are currently computing the adjacency of a vertical edge.
    //
    //     side == 0 -> find adjacency with visible left edges
    //
    //      001          010          100          111          111
    //  
    //   _ _ _ _ _    _ _ _ _o_    _ _ _ _ _  
    //  |         |  |        \|  |         |
    //  |         o  |         o  o- - - - -o
    //  |        /|  |         |  |         |
    //  |_ _ _ _o_|  |_ _ _ _ _|  |_ _ _ _ _|


    // Compute the edge adjacency
    Eigen::Array<unsigned int, 2, 1> case_index = Eigen::Array<unsigned int, 2, 1>::Zero();

    int case_index_val_top = 0;
    int case_index_val_bottom = 0;
    case_index_val_top = root_exist_config(1, 0) * 4 + root_exist_config(1, 1) * 2 + root_exist_config(1, 2);
    case_index_val_bottom = root_exist_config(0, 0) * 4 + root_exist_config(0, 1) * 2 + root_exist_config(0, 2);
    case_index << case_index_val_bottom, case_index_val_top;

    Eigen::Array<unsigned int, 2, 1> adjacency_array = Eigen::Array<unsigned int, 2, 1>::Zero();
    Edge2D edge_adj_1 = Edge2D(Eigen::Array<int, 2, 1>::Zero(), 0);
    Edge2D edge_adj_2 = Edge2D(Eigen::Array<int, 2, 1>::Zero(), 0);
    Eigen::Array<int, 2, 1> edge_shift;

    if (edge.edge_axis == 0)
    {
        if (case_index[0] == 1)
        {
            edge_adj_1.edge_2dindex = edge_adjacent_cells_2dindices.row(0);
            edge_adj_1.edge_axis = 1;
        }
        if (case_index[0] == 2)
        {
            edge_adj_1.edge_2dindex = edge_adjacent_cells_2dindices.row(0);
            edge_adj_1.edge_axis = 1;
        }
        if (case_index[0] == 4)
        {
            edge_adj_1.edge_2dindex = edge_adjacent_cells_2dindices.row(0);
            edge_adj_1.edge_axis = 0;
        }

        if (case_index[1] == 1)
        {
            edge_adj_2.edge_2dindex = edge_adjacent_cells_2dindices.row(1);
            edge_adj_2.edge_axis = 1;
        }
        if (case_index[1] == 2)
        {
            edge_adj_2.edge_2dindex = edge_adjacent_cells_2dindices.row(1);
            edge_adj_2.edge_axis = 1;
        }
        if (case_index[1] == 4)
        {
            edge_adj_2.edge_2dindex = edge_adjacent_cells_2dindices.row(1);
            edge_adj_2.edge_axis = 0;
        }
    }
    else
    {
        if (case_index[0] == 1)
        {
            edge_adj_1.edge_2dindex = edge_adjacent_cells_2dindices.row(0);
            edge_adj_1.edge_axis = 0;
        }
        if (case_index[0] == 2)
        {
            edge_adj_1.edge_2dindex = edge_adjacent_cells_2dindices.row(0);
            edge_adj_1.edge_axis = 0;
        }
        if (case_index[0] == 4)
        {
            edge_adj_1.edge_2dindex = edge_adjacent_cells_2dindices.row(0);
            edge_adj_1.edge_axis = 1;
        }

        if (case_index[1] == 1)
        {
            edge_adj_2.edge_2dindex = edge_adjacent_cells_2dindices.row(1);
            edge_adj_2.edge_axis = 0;
        }
        if (case_index[1] == 2)
        {
            edge_adj_2.edge_2dindex = edge_adjacent_cells_2dindices.row(1);
            edge_adj_2.edge_axis = 0;
        }
        if (case_index[1] == 4)
        {
            edge_adj_2.edge_2dindex = edge_adjacent_cells_2dindices.row(1);
            edge_adj_2.edge_axis = 1;
        }
    }

    adjacency_array[0] = index1_from_2dindex(edge_adj_1, edge_2dcount);
    adjacency_array[1] = index1_from_2dindex(edge_adj_2, edge_2dcount);

    // Convert the adjacency array to float
    for (int i = 0; i < adjacency_array.size(); ++i)
    {
        if (adjacency_array[i] == INT_MAX)
        {
            adjacency_array[i] = std::nan("");
        }
    }

    Eigen::ArrayX2f list_point = Eigen::ArrayX2f(1, 2);
    Eigen::ArrayX2i list_adjacency = Eigen::ArrayX2i(1, 2);
    return PointAdjacency(list_point, list_adjacency, grid_edge_root_point_val, adjacency_array);
}

PointAdjacency grid2_contour(Eigen::ArrayXd grid_scalars_flattened,
                             Eigen::Array<int, 2, 1> scalar_field_cell_2dcount,
                             Grid scalar_field_grid) 
{
    // This function will apply uniform_grid_edge_root_point_and_adjacency for every edge of the grid
    // and return the result as a PointAdjacency object.
    int count = 0;
    Eigen::Array<int, 2, 2> edge_2dcount = count2_per_axis(scalar_field_cell_2dcount);
    int size = (scalar_field_cell_2dcount[0] -1) * scalar_field_cell_2dcount[1] + (scalar_field_cell_2dcount[1] -1) * scalar_field_cell_2dcount[0];
    Eigen::ArrayX2f list_point(size, 2); // Assuming list_point is a 2D array with 'size' rows and 2 columns
    Eigen::ArrayX2i list_adjacency(size, 2); // Assuming list_adjacency is a 2D array with 'size' rows and 2 columns

    // First all the horizontal edges
    for (int i = 0; i < scalar_field_cell_2dcount[0] -1; ++i)
    {
        for (int j = 0; j < scalar_field_cell_2dcount[1]; ++j)
        {
            Eigen::Array<int, 2, 1> edge_2dindex;
            edge_2dindex << i, j;
            Edge2D edge_h = Edge2D(edge_2dindex, 0);
            PointAdjacency edge_point_adjacency = uniform_grid_edge_root_point_and_adjacency(edge_h, grid_scalars_flattened, scalar_field_grid);
            // Add the new point_adjacency to the list
            list_point.row(count) = edge_point_adjacency.getPoint().cast<float>();
            list_adjacency.row(count) = edge_point_adjacency.getAdjacency().cast<int>();
            count++;
        }
    }

    // Then all the vertical edges
    for (int i = 0; i < scalar_field_cell_2dcount[1] -1; ++i)
    {
        for (int j = 0; j < scalar_field_cell_2dcount[0]; ++j)
        {
            Eigen::Array<int, 2, 1> edge_2dindex;
            edge_2dindex << j, i;
            Edge2D edge_v = Edge2D(edge_2dindex, 1);
            // PointAdjacency edge_point_adjacency = uniform_grid_edge_root_point_and_adjacency(edge_v, grid_scalars_flattened, scalar_field_grid);
            // Add the new point_adjacency to the list
            // list_point.row(count) = edge_point_adjacency.getPoint();
            // list_adjacency.row(count) = edge_point_adjacency.getAdjacency();
            count++;
        }
    }

    return PointAdjacency(list_point, list_adjacency, Eigen::Array<float, 2, 1>::Zero(), Eigen::Array<unsigned int, 2, 1>::Zero());
}