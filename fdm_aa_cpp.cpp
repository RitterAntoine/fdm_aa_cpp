#include <iostream>
#include <Eigen/Dense>
#include <grid/grid.h>

using Eigen::MatrixXd;

void eigen_test()
{
	MatrixXd m(2, 2);
	m(0, 0) = 3;
	m(1, 0) = 2.5;
	m(0, 1) = -1;
	m(1, 1) = m(1, 0) + m(0, 1);
	std::cout << m << std::endl;
}

void cglib_test()
{
	std::vector<int> cell_ndcount = { 1, 2, 3 };
	std::vector<int> origin = { 4, 5, 6 };
	double cell_sides_length = 7.0;
	Grid grid(cell_ndcount, origin, cell_sides_length);
	std::cout << "cell_ndcount: " << grid.getCellNdCount()[0] << ", " << grid.getCellNdCount()[1] << ", " << grid.getCellNdCount()[2] << std::endl;
	std::cout << "origin: " << grid.getOrigin()[0] << ", " << grid.getOrigin()[1] << ", " << grid.getOrigin()[2] << std::endl;
	std::cout << "cell_sides_length: " << grid.getCellSidesLength() << std::endl;

}

int main()
{
	eigen_test();
	cglib_test();


	return 0;
}