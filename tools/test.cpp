#include <iostream>
#include <Eigen/Dense>
#include <cglib/scalar.h>

int main(int argc, char* argv[])
{
    // Check if the correct number of arguments was passed
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <parameter>" << std::endl;
        return 1;
    }

    // Use the first argument as the parameter
    std::string parameter = argv[1];

    // Now you can use the parameter in your program
    std::cout << "The parameter is: " << parameter << std::endl;

    return 0;
}