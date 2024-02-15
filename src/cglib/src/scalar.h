#include <Eigen/Dense>
#include "grid/cell.h"
#include "math.h"
#include "grid/edge.h"
#include "point_adjacency.h"

class GetEdgeAdjacencyParams 
{
     public:
         Edge2D edge;
         int edge_side;
         Eigen::Array<int, 2 ,1> edge_cell_2dcount;
         bool same_side_corner_and_center;

        GetEdgeAdjacencyParams(Edge2D edge, int edge_side, Eigen::Array<int, 2 ,1> edge_cell_2dcount, bool same_side_corner_and_center);
};

Eigen::Array<double, 2, 1> grid_edge_point_scalars(const Edge2D& edge,
                                                   const Eigen::ArrayXd& grid_scalars_flattened,
                                                   const Eigen::Array<int, 2 ,1> grid_cell_ndcount);

bool grid_edge_root_existence(const Edge2D& edge,
                              const Eigen::ArrayXd& flattened_scalar_field,
                              const Grid& grid);

Eigen::ArrayXf grid_edge_root_point(const Edge2D& edge,
                                    const Eigen::ArrayXd& flattened_scalar_field,
                                    const Grid& grid);

unsigned int get_edge_adjacency_no_extraction_case(const GetEdgeAdjacencyParams params);