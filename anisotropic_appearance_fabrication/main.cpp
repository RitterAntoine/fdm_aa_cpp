#include <iostream>
#include <vector>

using namespace std;

// Déclaration préalable de la classe Grid
class Grid {
public:
    // Constructeur
    Grid(vector<int> cell_ndcount, vector<int> origin, float cell_sides_length)
        : cell_ndcount_(cell_ndcount), origin_(origin), cell_sides_length_(cell_sides_length) {}

    vector<int> getCellNdcount() const {
        return cell_ndcount_;
    }

    vector<int> getOrigin() const {
        return origin_;
    }

    float getCellSidesLength() const {
        return cell_sides_length_;
    }

private:
    vector<int> cell_ndcount_;
    vector<int> origin_;
    float cell_sides_length_;
};




int main() {
    // Créer un objet de grille
    vector<int> cell_ndcount = {2, 2, 2};
    vector<int> origin = {0, 0, 0};
    float cell_sides_length = 1.0;
    Grid grid(cell_ndcount, origin, cell_sides_length);

    // Obtenir les propriétés de la grille
    vector<int> cell_ndcount_ = grid.getCellNdcount();
    vector<int> origin_ = grid.getOrigin();
    float cell_sides_length_ = grid.getCellSidesLength();

    // Imprimer les propriétés de la grille
    cout << "cell_ndcount: ";
    for (int i = 0; i < cell_ndcount_.size(); i++) {
        cout << cell_ndcount_[i] << " ";
    }
    cout << endl;

    cout << "origin: ";
    for (int i = 0; i < origin_.size(); i++) {
        cout << origin_[i] << " ";
    }
    cout << endl;

    cout << "cell_sides_length: " << cell_sides_length_ << endl;

    return 0;
}