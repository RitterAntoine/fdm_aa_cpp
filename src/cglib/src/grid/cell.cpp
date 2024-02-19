#include "cell.h"

Eigen::MatrixXi corner_vertex_2dindices(const Eigen::Array<int, 2, 1> cell_2dindex)
{
    int n = 2;
    int corner_count = 1 << n;
    Eigen::Array<int, 2, 1> corner_cell_2dcount = Eigen::Array<int, 2, 1>::Constant(n, 2);
    Eigen::MatrixXi corner_2dindices(n, corner_count);
    for (int i = 0; i < corner_count; ++i)
    {
        corner_2dindices.col(i) = index2d_from_1dindex(i, corner_cell_2dcount) + cell_2dindex;
    }
    return corner_2dindices.transpose();
}

int index1_from_2dindex(const Eigen::Array<int, 2, 1> cell_2dindex,
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

bool index2d_is_valid(const Eigen::Array<int, 2, 1> grid_cell_2dindex,
                      const Eigen::Array<int, 2, 1> grid_cell_2dcount)
{
    return ((grid_cell_2dindex >= 0).all() && (grid_cell_2dindex < grid_cell_2dcount).all());
}