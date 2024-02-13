#include <Eigen/Dense>
#include "grid/cell.h"
#include "math.h"
#include "grid/edge.h"
#include "point_adjacency.h"

class GetEdgeAdjacencyParams 
{
     public:
         Eigen::Array<int, 2 ,1> edge_ndindex;
         int edge_axis;
         int edge_side;
         Eigen::Array<int, 2 ,1> edge_cell_ndcount;
         bool same_side_corner_and_center;
};

Eigen::Array<double, 2, 1> grid_edge_point_scalars(const Eigen::Array<int, 2 ,1> edge_ndindex,
                                                   int edge_axis,
                                                   const Eigen::ArrayXd& grid_scalars_flattened,
                                                   const Eigen::Array<int, 2 ,1> grid_cell_ndcount);

bool grid_edge_root_existence(const Eigen::Array<int, 2 ,1> edge_ndindex,
                              int edge_axis,
                              const Eigen::ArrayXd& flattened_scalar_field,
                              const Grid& grid);

Eigen::ArrayXf grid_edge_root_point(const Eigen::Array<int, 2 ,1> edge_ndindex,
                                    int edge_axis,
                                    const Eigen::ArrayXd& flattened_scalar_field,
                                    const Grid& grid);

unsigned int get_edge_adjacency_no_extraction_case(const GetEdgeAdjacencyParams params);