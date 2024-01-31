#include <gtest/gtest.h>
#include "src/tree_util.h"

TEST(TreeUtilTest, Concatenate) {
    std::vector<Tree> trees;
    trees.push_back(Tree{Eigen::VectorXf(2), Eigen::VectorXf(2)});
    trees[0].values << 0, 1;
    trees[0].bools << 1, 0;
    trees.push_back(Tree{Eigen::VectorXf(2), Eigen::VectorXf(2)});
    trees[1].values << 2, 3;
    trees[1].bools << 0, 1;

    Tree res = concatenate(trees);

    Eigen::VectorXf exp_values(4);
    exp_values << 0, 1, 2, 3;
    Eigen::VectorXf exp_bools(4);
    exp_bools << 1, 0, 0, 1;

    ASSERT_TRUE(res.values.isApprox(exp_values));
    ASSERT_TRUE(res.bools.isApprox(exp_bools));
}