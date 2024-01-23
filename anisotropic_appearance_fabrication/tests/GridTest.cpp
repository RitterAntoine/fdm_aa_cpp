// GridTest.cpp
#include "../grid/grid.h"

#include <iostream>

bool testCellNdcount() {
    Grid grid(LibSL::Math::v2i(10, 10), LibSL::Math::v2i(0, 0), 1.0f);
    return grid.getCellNdcount() == LibSL::Math::v2i(10, 10);
}

int main() {
    if (testCellNdcount()) {
        std::cout << "GridTest: TestCellNdcount passed\n";
        return 0; // retourne 0 si le test réussit
    } else {
        std::cout << "GridTest: TestCellNdcount failed\n";
        return 1; // retourne 1 si le test échoue
    }
}