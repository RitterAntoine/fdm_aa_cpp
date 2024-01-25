#include <iostream>
#include "grid/grid.h"

int main() {
    std::vector<int> cell_ndcount = {1, 2, 3};
    std::vector<int> origin = {4, 5, 6};
    double cell_sides_length = 7.0;
    Grid grid(cell_ndcount, origin, cell_sides_length);
    std::cout << "cell_ndcount: " << grid.getCellNdCount()[0] << ", " << grid.getCellNdCount()[1] << ", " << grid.getCellNdCount()[2] << std::endl;
    std::cout << "origin: " << grid.getOrigin()[0] << ", " << grid.getOrigin()[1] << ", " << grid.getOrigin()[2] << std::endl;
    std::cout << "cell_sides_length: " << grid.getCellSidesLength() << std::endl;

    return 0;
}