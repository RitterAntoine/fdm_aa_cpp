#include <gtest/gtest.h>
#include "src/tree_util.h"

// This test checks the functionality of the 'concatenate' function.
// The 'concatenate' function is expected to concatenate the input trees into a single tree.
// The input trees are defined by their values and bools.
// The expected result is a Tree object with the concatenated values and bools.
// The input trees are:
// Tree 1:
// values: [0, 1]
// bools: [1, 0]
// Tree 2:
// values: [2, 3]
// bools: [0, 1]
// The expected result is a Tree object with the following values and bools:
// values: [0, 1, 2, 3]
// bools: [1, 0, 0, 1]

TEST(TreeUtilTest, Concatenate)
{
    std::vector<Tree> trees;
    trees.push_back(Tree{Eigen::Vector<float, 2>(), Eigen::Vector<float, 2>()});
    trees[0].values << 0, 1;
    trees[0].bools << 1, 0;
    trees.push_back(Tree{Eigen::Vector<float, 2>(), Eigen::Vector<float, 2>()});
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