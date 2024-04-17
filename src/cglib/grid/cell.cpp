#include "cell.h"

Eigen::Array<int, 4, 2> corner_vertex_2dindices(const Eigen::Array<int, 2, 1> cell_2dindex)
{
    int n = 2;
    int corner_count = 4;
    Eigen::Array<int, 4, 2> corner_vertex_2dindex(corner_count, 2);
    for (int i = 0; i < corner_count; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            corner_vertex_2dindex(i, j) = cell_2dindex[j] + (i >> j) % 2;
        }
    }
    return corner_vertex_2dindex;
}

int index1_from_2dindex_cell(const Eigen::Array<int, 2, 1> cell_2dindex,
                             const Eigen::Array<int, 2, 1> cell_2dcount)
{
    int size = cell_2dcount.size();
    int cell_1dindex = cell_2dindex[0];
    for (int i = 1; i < size; ++i)
    {
        int shift = cell_2dcount.head(i).prod();
        cell_1dindex += cell_2dindex[i] * shift;
    }
    return cell_1dindex;
}

Eigen::Array<int, 2, 1> index2d_from_1dindex(int cell_1dindex,
                                             const Eigen::Array<int, 2, 1> cell_2dcount)
{
    Eigen::Array<int, 2, 1> cell_2dindex = Eigen::Array<int, 2, 1>::Zero();
    cell_2dindex[0] = cell_1dindex % cell_2dcount[0];
    for (int i = 1; i < 2; ++i)
    {
        int shift = cell_2dcount.head(i).prod();
        cell_2dindex[i] = (cell_1dindex / shift) % cell_2dcount[i];
    }
    return cell_2dindex;
}

bool index2d_is_valid(const Eigen::Array<int, 2, 1> edge_2dindex,
                      const Eigen::Array<int, 2, 1> grid_cell_2dcount)
{
    Eigen::Array<int, 2 ,2> edge_2dcount(2, 2);
    edge_2dcount << grid_cell_2dcount[0], grid_cell_2dcount[1] + 1,
                    grid_cell_2dcount[0] + 1, grid_cell_2dcount[1];
    
    if (edge_2dindex[0] < 0 || edge_2dindex[0] > edge_2dcount(0, 0) - 1 ||
        edge_2dindex[1] < 0 || edge_2dindex[1] > edge_2dcount(0, 1) - 1)
    {
        return false;
    }
    return true;
}