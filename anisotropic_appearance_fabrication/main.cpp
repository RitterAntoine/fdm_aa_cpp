#include <iostream>
#include <vector>

using namespace std;

class Grid {
public:
    Grid(vector<int> cell_ndcount, vector<int> origin, float cell_sides_length)
                   : cell_ndcount_(cell_ndcount), origin_(origin), cell_sides_length_(cell_sides_length) {}

    vector<int> getCellNdcount() const {return cell_ndcount_;}
    vector<int> getOrigin() const {return origin_;}
    float       getCellSidesLength() const {return cell_sides_length_;}

private:
    vector<int> cell_ndcount_;
    vector<int> origin_;
    float       cell_sides_length_;
};

std::vector<std::vector<float>> endpoints(std::vector<int> edge_ndindex, int edge_axis, const Grid& grid) {
    // Dimension
    int n = grid.getCellNdcount().size();

    // Increment of cell sides length along edge_axis
    std::vector<float> increment(n, 0.0);
    increment[edge_axis] = grid.getCellSidesLength();

    // Calculate endpoints
    std::vector<float> v0, v1;
    for (int i = 0; i < n; ++i) {
        v0.push_back(edge_ndindex[i] * grid.getCellSidesLength() + grid.getOrigin()[i]);
        v1.push_back(v0[i] + increment[i]);
    }

    return { v0, v1 };
}


int main() {
    
}