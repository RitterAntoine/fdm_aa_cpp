#include "cell.h"

Eigen::MatrixXi corner_vertex_ndindices(const Eigen::Array<int, 2, 1> cell_ndindex)
{
    int n = cell_ndindex.size();
    int corner_count = 1 << n;
    Eigen::Array<int, 2, 1> corner_cell_ndcount = Eigen::Array<int, 2, 1>::Constant(n, 2);
    Eigen::MatrixXi corner_ndindices(n, corner_count);
    for (int i = 0; i < corner_count; ++i)
    {
        corner_ndindices.col(i) = ndindex_from_1dindex(i, corner_cell_ndcount) + cell_ndindex;
    }
    return corner_ndindices.transpose();
}

int index1_from_ndindex(const Eigen::Array<int, 2, 1> cell_ndindex,
                        const Eigen::Array<int, 2, 1> cell_ndcount)
{
    int n = cell_ndcount.size();
    int flattened_index = cell_ndindex[0];
    for (int i = 1; i < n; ++i)
    {
        int shift = cell_ndcount.head(i).prod();
        flattened_index += cell_ndindex[i] * shift;
    }
    return flattened_index;
}

Eigen::Array<int, 2, 1> ndindex_from_1dindex(int cell_1dindex,
                                             const Eigen::Array<int, 2, 1> cell_ndcount)
{
    int n = cell_ndcount.size();
    Eigen::Array<int, 2, 1> cell_ndindex = Eigen::Array<int, 2, 1>::Zero();
    cell_ndindex[0] = cell_1dindex % cell_ndcount[0];
    for (int i = 1; i < n; ++i)
    {
        int shift = cell_ndcount.head(i).prod();
        cell_ndindex[i] = (cell_1dindex / shift) % cell_ndcount[i];
    }
    return cell_ndindex;
}

bool ndindex_is_valid(const Eigen::Array<int, 2, 1> grid_cell_ndindex,
                      const Eigen::Array<int, 2, 1> grid_cell_ndcount)
{
    return ((grid_cell_ndindex >= 0).all() && (grid_cell_ndindex < grid_cell_ndcount).all());
}