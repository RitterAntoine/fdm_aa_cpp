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
         Eigen::Array<int, 2 ,2> edge_2dcount;
         bool same_side_bottom_left_corner_and_center;

        GetEdgeAdjacencyParams(Edge2D edge, int edge_side, Eigen::Array<int, 2 ,2> edge_2dcount, bool same_side_bottom_left_corner_and_center);
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

unsigned int convert_edge_shift_to_adjacency(Eigen::Array<int, 2, 1> shift,
                                             const GetEdgeAdjacencyParams params,
                                             int adjacent_edge_axis);

unsigned int get_edge_adjacency_case_001(const GetEdgeAdjacencyParams params);

unsigned int get_edge_adjacency_case_010(const GetEdgeAdjacencyParams params);

unsigned int get_edge_adjacency_case_100(const GetEdgeAdjacencyParams params);

unsigned int get_edge_adjacency_case_111(const GetEdgeAdjacencyParams params);