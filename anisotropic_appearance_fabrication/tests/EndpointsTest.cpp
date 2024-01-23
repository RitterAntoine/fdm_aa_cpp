// EndpointsTest.cpp
#include "../grid/grid.h"
#include "../grid/edge.h"
#include <iostream>

bool testEndpoints() {
    Grid grid(LibSL::Math::v2i(10, 10), LibSL::Math::v2i(0, 0), 1.0f);
    LibSL::Math::v2i edge_ndindex(5, 5);
    int edge_axis = 0;
    auto result = endpoints(edge_ndindex, edge_axis, grid);
    auto expected = std::make_pair(LibSL::Math::v2f(5.0f, 5.0f), LibSL::Math::v2f(6.0f, 5.0f));
    return result == expected;
}

int main() {
    if (testEndpoints()) {
        std::cout << "EndpointsTest: TestEndpoints passed\n";
        return 0; // retourne 0 si le test réussit
    } else {
        std::cout << "EndpointsTest: TestEndpoints failed\n";
        return 1; // retourne 1 si le test échoue
    }
}