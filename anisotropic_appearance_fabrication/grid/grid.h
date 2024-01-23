// grid.h
#pragma once

#include <LibSL/Math/Vertex.h>

class Grid {
public:
    // Constructor initializes the grid with specified parameters
    Grid(LibSL::Math::v2i cell_ndcount, LibSL::Math::v2i origin, float cell_sides_length)
        : cell_ndcount_(cell_ndcount), origin_(origin), cell_sides_length_(cell_sides_length) {}

    // Getter methods to access private members of the Grid class
    LibSL::Math::v2i getCellNdcount() const { return cell_ndcount_; }
    LibSL::Math::v2i getOrigin() const { return origin_; }
    float getCellSidesLength() const { return cell_sides_length_; }

private:
    // Private members to store grid information
    LibSL::Math::v2i cell_ndcount_;
    LibSL::Math::v2i origin_;
    float cell_sides_length_;
};