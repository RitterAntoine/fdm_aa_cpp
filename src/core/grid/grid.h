#pragma once

#include <LibSL>

class Grid {
public:
    Grid(LibSL::Math::v2i cellCount, LibSL::Math::v2i gridOrigin, float cellSideLength);

    LibSL::Math::v2i getCellCount() const;
    LibSL::Math::v2i getGridOrigin() const;
    float getCellSideLength() const;

private:
    LibSL::Math::v2i cellCount_;
    LibSL::Math::v2i gridOrigin_;
    float cellSideLength_;
};