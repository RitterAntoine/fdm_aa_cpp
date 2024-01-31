#include "tree_util.h"

Tree concatenate(const std::vector<Tree>& trees) {
    int tree_count = trees.size();

    Eigen::VectorXf values = trees[0].values;
    Eigen::VectorXf bools = trees[0].bools;

    for (int i = 1; i < tree_count; ++i) {
        int old_size = values.size();
        values.conservativeResize(old_size + trees[i].values.size());
        values.segment(old_size, trees[i].values.size()) = trees[i].values;

        old_size = bools.size();
        bools.conservativeResize(old_size + trees[i].bools.size());
        bools.segment(old_size, trees[i].bools.size()) = trees[i].bools;
    }

    return Tree{values, bools};
}