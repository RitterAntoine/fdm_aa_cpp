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

## Eigen

This project require Eigen 3.4.0. Eigen is a C++ numerical analysis library consisting of template headers, developed by Benoît Jacob and Gaël Guennebaud at INRIA. It is open-source software under the MPL2 license and is multi-platform.

# Exemples Usages

## Contour Extraction

here is an exemple of code for contour extraction

```
#include
```

# Folder Organisation

- [`tools`](tools/): Contain tools
- [`src`](src/): Contain the source code
- [`tests`](tests/): Contain the tests of the library

# Unit Tests

For this project I used GTest(Google test). All the test are in the folder `test`. Most of the functions have at least one test. 

## How to run the tests

To run the unit tests...