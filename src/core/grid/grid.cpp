#include "grid.h"

Grid::Grid(LibSL::Math::v2i cellCount, LibSL::Math::v2i gridOrigin, float cellSideLength)
    : cellCount_(cellCount), gridOrigin_(gridOrigin), cellSideLength_(cellSideLength) {}

LibSL::Math::v2i Grid::getCellCount() const {
    return cellCount_;
}

LibSL::Math::v2i Grid::getGridOrigin() const {
    return gridOrigin_;
}

float Grid::getCellSideLength() const {
    return cellSideLength_;
}