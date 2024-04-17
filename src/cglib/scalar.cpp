#include "scalar.h"

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
        edge_vertex_flattened_indices[i] = index1_from_2dindex_cell(edge_vertex_ndindices.row(i), grid_cell_2dcount);
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
    return mask ? Eigen::ArrayXf::Constant(root_point.size(), INT_MAX) : root_point;
}

float get_scalar(const Eigen::ArrayXd& flattened_scalar_field, int index) {
    if (index < 0 || index >= flattened_scalar_field.size()) {
        return INT_MAX;
    } else {
        return flattened_scalar_field[index];
    }
}

Eigen::Array<float, 2, 1> process_edge_point(const Edge2D& edge,
                                             const Eigen::ArrayXd& flattened_scalar_field,
                                             const Grid& grid)
{
    Eigen::Array<float, 2, 1> edge_point = grid_edge_root_point(edge, flattened_scalar_field, grid);
    return edge_point + grid.cell_sides_length * 0.5;
}

Eigen::Array<int, 2, 1> process_edge_adjacency(const Edge2D& edge,
                                               const Eigen::ArrayXd& flattened_scalar_field,
                                               const Grid& grid)
{
    Eigen::Array<int, 2, 1> adjacency; // Index 1D of the two adjacent points
    Edge2D adjacent_edge_0 = edge;
    Edge2D adjacent_edge_1 = edge;

    // The first step is to check if the edge has a root
    if (!grid_edge_root_existence(edge, flattened_scalar_field, grid)) {
        adjacency << INT_MAX, INT_MAX;
        return adjacency;
    }
    
    // Get the visible edge neighbors
    Eigen::Array<int, 2, 1> contour_grid_cell_2dcount;
    contour_grid_cell_2dcount << grid.cell_2dcount[0] - 1, grid.cell_2dcount[1] - 1;
    Eigen::Array<int, 2, 2> edge_2dcount = count2_per_axis(contour_grid_cell_2dcount);
    MaskedArray visible_neighbors = neighboring_2dindices_direct(edge, contour_grid_cell_2dcount, Neighboring2Type::VISIBLE);
    Eigen::Array<int, 8, 2> visible_neighbors_ndindices = visible_neighbors.array;
    Eigen::Array<bool, 8, 1> visible_neighbors_mask = visible_neighbors.mask;

    // Create an edge2D object for each visible neighbor
    Edge2D neighbor_edge_horizontal_0 = Edge2D(visible_neighbors_ndindices.row(0), 0);
    Edge2D neighbor_edge_horizontal_1 = Edge2D(visible_neighbors_ndindices.row(1), 0);
    Edge2D neighbor_edge_horizontal_2 = Edge2D(visible_neighbors_ndindices.row(2), 0);
    Edge2D neighbor_edge_horizontal_3 = Edge2D(visible_neighbors_ndindices.row(3), 0);
    Edge2D neighbor_edge_vertical_0 = Edge2D(visible_neighbors_ndindices.row(4), 1);
    Edge2D neighbor_edge_vertical_1 = Edge2D(visible_neighbors_ndindices.row(5), 1);
    Edge2D neighbor_edge_vertical_2 = Edge2D(visible_neighbors_ndindices.row(6), 1);
    Edge2D neighbor_edge_vertical_3 = Edge2D(visible_neighbors_ndindices.row(7), 1);

    // For each visible neighbor, check if the edge has a root
    bool neighbor_horizontal_0 = false;
    bool neighbor_horizontal_1 = false;
    bool neighbor_horizontal_2 = false;
    bool neighbor_horizontal_3 = false;
    bool neighbor_vertical_0 = false;
    bool neighbor_vertical_1 = false;
    bool neighbor_vertical_2 = false;
    bool neighbor_vertical_3 = false;

    if (visible_neighbors_mask[0] == 0) {neighbor_horizontal_0 = grid_edge_root_existence(neighbor_edge_horizontal_0, flattened_scalar_field, grid);}
    if (visible_neighbors_mask[1] == 0) {neighbor_horizontal_1 = grid_edge_root_existence(neighbor_edge_horizontal_1, flattened_scalar_field, grid);}
    if (visible_neighbors_mask[2] == 0) {neighbor_horizontal_2 = grid_edge_root_existence(neighbor_edge_horizontal_2, flattened_scalar_field, grid);}
    if (visible_neighbors_mask[3] == 0) {neighbor_horizontal_3 = grid_edge_root_existence(neighbor_edge_horizontal_3, flattened_scalar_field, grid);}
    if (visible_neighbors_mask[4] == 0) {neighbor_vertical_0 = grid_edge_root_existence(neighbor_edge_vertical_0, flattened_scalar_field, grid);}
    if (visible_neighbors_mask[5] == 0) {neighbor_vertical_1 = grid_edge_root_existence(neighbor_edge_vertical_1, flattened_scalar_field, grid);}
    if (visible_neighbors_mask[6] == 0) {neighbor_vertical_2 = grid_edge_root_existence(neighbor_edge_vertical_2, flattened_scalar_field, grid);}
    if (visible_neighbors_mask[7] == 0) {neighbor_vertical_3 = grid_edge_root_existence(neighbor_edge_vertical_3, flattened_scalar_field, grid);}

    Eigen::Array<int, 2, 1> index2d_bottom_left_cell;
    Eigen::Array<int, 2, 1> index2d_bottom_right_cell;
    Eigen::Array<int, 2, 1> index2d_top_left_cell;
    Eigen::Array<int, 2, 1> index2d_top_right_cell;



    // code it the hard way
    if (edge.edge_axis == 0) 
    {
        if (neighbor_horizontal_0 && !neighbor_vertical_0 && !neighbor_vertical_1)
        {
            adjacent_edge_0.edge_2dindex[1] = edge.edge_2dindex[1] - 1;
        }
        else if (!neighbor_horizontal_0 && neighbor_vertical_0 && !neighbor_vertical_1)
        {
            adjacent_edge_0.edge_2dindex[1] = edge.edge_2dindex[1] - 1;
            adjacent_edge_0.edge_axis = 1;
        }
        else if (!neighbor_horizontal_0 && !neighbor_vertical_0 && neighbor_vertical_1)
        {
            adjacent_edge_0.edge_2dindex[0] = edge.edge_2dindex[0] + 1;
            adjacent_edge_0.edge_2dindex[1] = edge.edge_2dindex[1] - 1;
            adjacent_edge_0.edge_axis = 1;
        }
        else if (neighbor_horizontal_0 && neighbor_vertical_0 && neighbor_vertical_1)
        {
            // Get the 2d indices of the 4 cells
            index2d_bottom_left_cell = edge.edge_2dindex[0], edge.edge_2dindex[1] - 1;
            index2d_bottom_right_cell = edge.edge_2dindex[0] + 1, edge.edge_2dindex[1] - 1;
            index2d_top_left_cell = edge.edge_2dindex;
            index2d_top_right_cell = edge.edge_2dindex[0] + 1, edge.edge_2dindex[1];

            // Get the 1d indices of the 4 cells
            int index1_bottom_left_cell = index1_from_2dindex_cell(index2d_bottom_left_cell, grid.cell_2dcount);
            int index1_bottom_right_cell = index1_from_2dindex_cell(index2d_bottom_right_cell, grid.cell_2dcount);
            int index1_top_left_cell = index1_from_2dindex_cell(index2d_top_left_cell, grid.cell_2dcount);
            int index1_top_right_cell = index1_from_2dindex_cell(index2d_top_right_cell, grid.cell_2dcount);

            // Get the scalar values of the 4 cells
            float scalar_bottom_left_cell = get_scalar(flattened_scalar_field, index1_bottom_left_cell);
            float scalar_bottom_right_cell = get_scalar(flattened_scalar_field, index1_bottom_right_cell);
            float scalar_top_left_cell = get_scalar(flattened_scalar_field, index1_top_left_cell);
            float scalar_top_right_cell = get_scalar(flattened_scalar_field, index1_top_right_cell);

            // Make the average of the 4 scalar values
            float average_scalar = (scalar_bottom_left_cell + scalar_bottom_right_cell + scalar_top_left_cell + scalar_top_right_cell) / 4.0;

            if (float_same_sign(average_scalar, scalar_top_left_cell))
            {
                adjacent_edge_0.edge_axis = 1;
            }
            else 
            {
                adjacent_edge_0.edge_2dindex[0] = edge.edge_2dindex[0] + 1;
                adjacent_edge_0.edge_2dindex[1] = edge.edge_2dindex[1] - 1;
                adjacent_edge_0.edge_axis = 1;
            }
        }
    
        if (neighbor_horizontal_1 && !neighbor_vertical_2 && !neighbor_vertical_3)
        {
            adjacent_edge_1.edge_2dindex[1] = edge.edge_2dindex[1] + 1;
        }
        else if (!neighbor_horizontal_1 && neighbor_vertical_2 && !neighbor_vertical_3)
        {
            adjacent_edge_1.edge_axis = 1;
        }
        else if (!neighbor_horizontal_1 && !neighbor_vertical_2 && neighbor_vertical_3)
        {
            adjacent_edge_1.edge_2dindex[0] = edge.edge_2dindex[0] + 1;
            adjacent_edge_1.edge_axis = 1;
        }
        else if (neighbor_horizontal_1 && neighbor_vertical_2 && neighbor_vertical_3)
        {
            // Get the 2d indices of the 4 cells
            index2d_bottom_left_cell = edge.edge_2dindex;
            index2d_bottom_right_cell = edge.edge_2dindex[0] + 1, edge.edge_2dindex[1];
            index2d_top_left_cell = edge.edge_2dindex[0], edge.edge_2dindex[1] + 1;
            index2d_top_right_cell = edge.edge_2dindex[0] + 1, edge.edge_2dindex[1] + 1;

            // Get the 1d indices of the 4 cells
            int index1_bottom_left_cell = index1_from_2dindex_cell(index2d_bottom_left_cell, grid.cell_2dcount);
            int index1_bottom_right_cell = index1_from_2dindex_cell(index2d_bottom_right_cell, grid.cell_2dcount);
            int index1_top_left_cell = index1_from_2dindex_cell(index2d_top_left_cell, grid.cell_2dcount);
            int index1_top_right_cell = index1_from_2dindex_cell(index2d_top_right_cell, grid.cell_2dcount);

            // Get the scalar values of the 4 cells
            float scalar_bottom_left_cell = get_scalar(flattened_scalar_field, index1_bottom_left_cell);
            float scalar_bottom_right_cell = get_scalar(flattened_scalar_field, index1_bottom_right_cell);
            float scalar_top_left_cell = get_scalar(flattened_scalar_field, index1_top_left_cell);
            float scalar_top_right_cell = get_scalar(flattened_scalar_field, index1_top_right_cell);

            // Make the average of the 4 scalar values
            float average_scalar = (scalar_bottom_left_cell + scalar_bottom_right_cell + scalar_top_left_cell + scalar_top_right_cell) / 4.0;

            if (float_same_sign(average_scalar, scalar_bottom_left_cell))
            {
                adjacent_edge_1.edge_axis = 1;
            }
            else 
            {
                adjacent_edge_1.edge_2dindex[0] = edge.edge_2dindex[0] + 1;
                adjacent_edge_1.edge_axis = 1;
            }
        }
    }
    else 
    {
        if (neighbor_vertical_0 && !neighbor_horizontal_0 && !neighbor_horizontal_1)
        {
            adjacent_edge_0.edge_2dindex[0] = edge.edge_2dindex[0] - 1;
        }
        else if (!neighbor_vertical_0 && neighbor_horizontal_0 && !neighbor_horizontal_1)
        {
            adjacent_edge_0.edge_2dindex[0] = edge.edge_2dindex[0] - 1;
            adjacent_edge_0.edge_axis = 0;
        }
        else if (!neighbor_vertical_0 && !neighbor_horizontal_0 && neighbor_horizontal_1)
        {
            adjacent_edge_0.edge_2dindex[0] = edge.edge_2dindex[0] - 1;
            adjacent_edge_0.edge_2dindex[1] = edge.edge_2dindex[1] + 1;
            adjacent_edge_0.edge_axis = 0;
        }
        else if (neighbor_vertical_0 && neighbor_horizontal_0 && neighbor_horizontal_1)
        {
            // Get the 2d indices of the 4 cells
            index2d_bottom_left_cell = edge.edge_2dindex[0] - 1, edge.edge_2dindex[1];
            index2d_bottom_right_cell = edge.edge_2dindex;
            index2d_top_left_cell = edge.edge_2dindex[0] - 1, edge.edge_2dindex[1] + 1;
            index2d_top_right_cell = edge.edge_2dindex[0], edge.edge_2dindex[1] + 1;

            // Get the 1d indices of the 4 cells
            int index1_bottom_left_cell = index1_from_2dindex_cell(index2d_bottom_left_cell, grid.cell_2dcount);
            int index1_bottom_right_cell = index1_from_2dindex_cell(index2d_bottom_right_cell, grid.cell_2dcount);
            int index1_top_left_cell = index1_from_2dindex_cell(index2d_top_left_cell, grid.cell_2dcount);
            int index1_top_right_cell = index1_from_2dindex_cell(index2d_top_right_cell, grid.cell_2dcount);

            // Get the scalar values of the 4 cells
            float scalar_bottom_left_cell = get_scalar(flattened_scalar_field, index1_bottom_left_cell);
            float scalar_bottom_right_cell = get_scalar(flattened_scalar_field, index1_bottom_right_cell);
            float scalar_top_left_cell = get_scalar(flattened_scalar_field, index1_top_left_cell);
            float scalar_top_right_cell = get_scalar(flattened_scalar_field, index1_top_right_cell);

            // Make the average of the 4 scalar values
            float average_scalar = (scalar_bottom_left_cell + scalar_bottom_right_cell + scalar_top_left_cell + scalar_top_right_cell) / 4.0;

            if (float_same_sign(average_scalar, scalar_bottom_right_cell))
            {
                adjacent_edge_0.edge_axis = 0;
            }
            else 
            {
                adjacent_edge_0.edge_2dindex[0] = edge.edge_2dindex[0] - 1;
                adjacent_edge_0.edge_2dindex[1] = edge.edge_2dindex[1] + 1;
                adjacent_edge_0.edge_axis = 0;
            }
        }
    
        if (neighbor_vertical_1 && !neighbor_horizontal_2 && !neighbor_horizontal_3)
        {
            adjacent_edge_1.edge_2dindex[0] = edge.edge_2dindex[0] + 1;
        }
        else if (!neighbor_vertical_1 && neighbor_horizontal_2 && !neighbor_horizontal_3)
        {
            adjacent_edge_1.edge_axis = 0;
        }
        else if (!neighbor_vertical_1 && !neighbor_horizontal_2 && neighbor_horizontal_3)
        {
            adjacent_edge_1.edge_2dindex[1] = edge.edge_2dindex[1] + 1;
            adjacent_edge_1.edge_axis = 0;
        }
        else if (neighbor_vertical_1 && neighbor_horizontal_2 && neighbor_horizontal_3)
        {
            // Get the 2d indices of the 4 cells
            index2d_bottom_left_cell = edge.edge_2dindex;
            index2d_bottom_right_cell = edge.edge_2dindex[0], edge.edge_2dindex[1] + 1;
            index2d_top_left_cell = edge.edge_2dindex[0] + 1, edge.edge_2dindex[1];
            index2d_top_right_cell = edge.edge_2dindex[0] + 1, edge.edge_2dindex[1] + 1;

            // Get the 1d indices of the 4 cells
            int index1_bottom_left_cell = index1_from_2dindex_cell(index2d_bottom_left_cell, grid.cell_2dcount);
            int index1_bottom_right_cell = index1_from_2dindex_cell(index2d_bottom_right_cell, grid.cell_2dcount);
            int index1_top_left_cell = index1_from_2dindex_cell(index2d_top_left_cell, grid.cell_2dcount);
            int index1_top_right_cell = index1_from_2dindex_cell(index2d_top_right_cell, grid.cell_2dcount);

            // Get the scalar values of the 4 cells
            float scalar_bottom_left_cell = get_scalar(flattened_scalar_field, index1_bottom_left_cell);
            float scalar_bottom_right_cell = get_scalar(flattened_scalar_field, index1_bottom_right_cell);
            float scalar_top_left_cell = get_scalar(flattened_scalar_field, index1_top_left_cell);
            float scalar_top_right_cell = get_scalar(flattened_scalar_field, index1_top_right_cell);

            // Make the average of the 4 scalar values
            float average_scalar = (scalar_bottom_left_cell + scalar_bottom_right_cell + scalar_top_left_cell + scalar_top_right_cell) / 4.0;

            if (float_same_sign(average_scalar, scalar_bottom_left_cell))
            {
                adjacent_edge_1.edge_axis = 0;
            }
            else 
            {
                adjacent_edge_1.edge_2dindex[0] = edge.edge_2dindex[0] + 1;
                adjacent_edge_1.edge_axis = 0;
            }
        }
    }

    // Now that we have the 2d indices of the adjacent edges, we can get the 1d indices
    adjacency[0] = index1_from_2dindex_edge(adjacent_edge_0, edge_2dcount);
    adjacency[1] = index1_from_2dindex_edge(adjacent_edge_1, edge_2dcount);

    return adjacency;
}

void processEdge(int row, int col, int orientation, int& count, Eigen::ArrayX2f& list_point, Eigen::ArrayX2i& list_adjacency, const Eigen::ArrayXd& grid_scalars_flattened, const Grid& scalar_field_grid) {
    Eigen::Array<int, 2, 1> edge_2dindex;
    edge_2dindex << col, row;
    Edge2D edge = Edge2D(edge_2dindex, orientation);
    list_point.row(count) = process_edge_point(edge, grid_scalars_flattened, scalar_field_grid);
    // Check if the edge has a root
    if (grid_edge_root_existence(edge, grid_scalars_flattened, scalar_field_grid)) {
        list_adjacency.row(count) = process_edge_adjacency(edge, grid_scalars_flattened, scalar_field_grid);
    } else {
        list_adjacency.row(count) << INT_MAX, INT_MAX;
    }
    count++;
}

Graph grid2_contour(const Eigen::ArrayXd& grid_scalars_flattened,
                    const Eigen::Array<int, 2, 1>& scalar_field_cell_2dcount,
                    const Grid& scalar_field_grid) 
{
    int count = 0;
    Eigen::Array<int, 2, 2> edge_2dcount = count2_per_axis(scalar_field_cell_2dcount);
    int size = (scalar_field_cell_2dcount[0] -1) * scalar_field_cell_2dcount[1] + (scalar_field_cell_2dcount[1] -1) * scalar_field_cell_2dcount[0];
    Eigen::ArrayX2f list_point(size, 2);
    Eigen::ArrayX2i list_adjacency(size, 2);

    // Process all the edges
    for (int orientation = 0; orientation < 2; ++orientation)
        for (int row = 0; row < (orientation == 0 ? scalar_field_cell_2dcount[1] : scalar_field_cell_2dcount[1] - 1); ++row)
            for (int col = 0; col < (orientation == 0 ? scalar_field_cell_2dcount[0] - 1 : scalar_field_cell_2dcount[0]); ++col)
                processEdge(row, col, orientation, count, list_point, list_adjacency, grid_scalars_flattened, scalar_field_grid);

    return Graph(list_point, list_adjacency);
}