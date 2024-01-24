#include "edge.h"

std::pair<LibSL::Math::v2f, LibSL::Math::v2f> endpoints(LibSL::Math::v2i edgeIndex, int edgeAxis, const Grid& grid) {
    int dimension = 2;

    LibSL::Math::v2f increment(0.0);
    increment[edgeAxis] = grid.getCellSideLength();

    LibSL::Math::v2f startPoint, endPoint;
    for (int i = 0; i < dimension; ++i) {
        startPoint[i] = edgeIndex[i] * grid.getCellSideLength() + grid.getGridOrigin()[i];
        endPoint[i] = startPoint[i] + increment[i];
    }

    return std::make_pair(startPoint, endPoint);
}