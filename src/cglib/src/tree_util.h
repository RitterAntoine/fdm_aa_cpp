#include <Eigen/Dense>
#include <vector>

struct Tree
{
    Eigen::VectorXf values;
    Eigen::VectorXf bools;
};

Tree concatenate(const std::vector<Tree>& trees);