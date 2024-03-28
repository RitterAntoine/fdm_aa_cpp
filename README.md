# Orientable Dense Cyclic Infill for Anisotropic Appearance Fabrication - C++ Code

This README provides an overview of the implementation of certain parts of the project "Orientable Dense Cyclic Infill for Anisotropic Appearance Fabrication" in C++. The project, initially presented by Chermain Xavier at the SIGGRAPH 2023 conference, serves as the foundation for the work described [here](https://github.com/mfx-inria/anisotropic_appearance_fabrication).

## Project Objective
The primary goal of this project is to facilitate the use of the algorithm by migrating its code from Python to C++. This transition is crucial for the team due to two key reasons: some members conduct experiments in C++ rather than Python, and the team's software, IceSL, is developed in C++. The ultimate aim is to translate the algorithm into C++ to make it directly usable within the IceSL environment, thus meeting the team's specific needs and ensuring better integration into their workflow.


# Outline

- [Features](#features)
- [Installation](#installation)
- [Exemple Usage](#exemple-usage)
- [Folder Organisation](#folder-organisation)
- [Unit Tests](#unit-tests)

# Features

This project contains a C++ library. This library extracts contours from scalar fields, cycles them and then creates polylines.

There are also multiples executables that can be used individualy.

# Installation

## Requirements

This projectrequire:
- C++ 11
- CMake 3.28.1 (or later)
- Eigen 3.4.0

## Clone the Repository

```
git clone https://github.com/RitterAntoine/fdm_aa_cpp.git
```

## CMake

This project uses CMake and require the version 3.28.1 minimum.

Here is the oficial website: [here](https://cmake.org/)

If you want to build the project yourself using cmake, enter this command into your terminal

```
cmake --build . --config Release
```

## Eigen

This project require Eigen 3.4.0. Eigen is a C++ numerical analysis library consisting of template headers, developed by Benoît Jacob and Gaël Guennebaud at INRIA. It is open-source software under the MPL2 license and is multi-platform.

# Exemples Usages

## Tools

### Cycle_Creator

Cycle_Creator is an executable to extract Cycles from a scalar field
To use it you just need to...

To use this Function, you need to have a proper input. The input is the dimension of your scalar field (rows and colomns) in the first row, then all the values (between -1 and 1).

here is an exemple of InputFile.txt:
```
4 4
1 1 1 1 
1 -1 -1 1 
1 -1 -1 1
1 1 1 1
```

After the installation run this in you terminal where the executable is located

```
./Cycle_Creator.exe InputFile.txt OutputFile.txt
```

This will write in the OutputFile all the information that has been created using your Scalar Field.

## Code

### Contour Extraction

here is an exemple of code for contour extraction

```
#include <cglib/scalar.h>

Eigen::Array<int, 2, 1> cell_2dcount(2);
cell_2dcount << cols, rows;

Eigen::Array<int, 2, 1> origin(2);
origin << 0, 0;

float cell_sides_length = 1;

Grid grid(cell_2dcount, origin, cell_sides_length);

Eigen::Array<double, Eigen::Dynamic, 1> flattened_scalar_field = graph.cast<double>().matrix().transpose();

Graph res = grid2_contour(flattened_scalar_field, cell_2dcount, grid);

Eigen::Array<float, Eigen::Dynamic, 2> list_point = res.getListPoint();
Eigen::Array<int, Eigen::Dynamic, 2> list_adjacency = res.getListAdjacency();

```

# Folder Organisation

- [`tools`](tools/): Contain tools
- [`src`](src/): Contain the source code
- [`tests`](tests/): Contain the tests of the library

# Unit Tests

For this project I used GTest(Google test). All the test are in the folder `test`. Most of the functions have at least one test. 

## How to run the tests

To run the unit tests...