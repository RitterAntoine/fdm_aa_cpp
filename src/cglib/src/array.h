#include <Eigen/Dense>

// MaskedArray is a class that represents an array with masked elements.
// It has two attributes: array and mask.
// The array attribute is an array of items.
// The mask attribute is a boolean array with the same shape of array, where each element indicates if the item of array is masked or not.
class MaskedArray {
    public:
        Eigen::ArrayXi array;
        Eigen::ArrayXi mask;
};