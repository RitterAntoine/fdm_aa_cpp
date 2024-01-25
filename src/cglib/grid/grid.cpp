#include "grid.h"

Grid::Grid(const std::vector<int>& cell_ndcount, const std::vector<int>& origin, double cell_sides_length)
    : cell_ndcount_(cell_ndcount), origin_(origin), cell_sides_length_(cell_sides_length) {}

std::vector<int> Grid::getCellNdCount() const {
    return cell_ndcount_;
}

void Grid::setCellNdCount(const std::vector<int>& cell_ndcount) {
    cell_ndcount_ = cell_ndcount;
}

std::vector<int> Grid::getOrigin() const {
    return origin_;
}

void Grid::setOrigin(const std::vector<int>& origin) {
    origin_ = origin;
}

double Grid::getCellSidesLength() const {
    return cell_sides_length_;
}

void Grid::setCellSidesLength(double cell_sides_length) {
    cell_sides_length_ = cell_sides_length;
}