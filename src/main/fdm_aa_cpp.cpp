#include <iostream>
#include "lib/add.h"
#include "lib/subtract.h"

int main() {
    int a = 5;
    int b = 3;

    std::cout << "Sum: " << add(a, b) << std::endl;
    std::cout << "Difference: " << subtract(a, b) << std::endl;

    return 0;
}