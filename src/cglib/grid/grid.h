#include <vector>

class Grid {
public:
    Grid(const std::vector<int>& cell_ndcount, const std::vector<int>& origin, double cell_sides_length);

    std::vector<int> getCellNdCount() const;
    void setCellNdCount(const std::vector<int>& cell_ndcount);

    std::vector<int> getOrigin() const;
    void setOrigin(const std::vector<int>& origin);

    double getCellSidesLength() const;
    void setCellSidesLength(double cell_sides_length);

private:
    std::vector<int> cell_ndcount_;
    std::vector<int> origin_;
    double cell_sides_length_;
};