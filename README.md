# Anisotropic Appearance Fabrication - Trajectory Extraction in C++

This repository contains the C++ source code for a portion of the project:

**[Orientable Dense Cyclic Infill for Anisotropic Appearance Fabrication](https://xavierchermain.github.io/fdm_aa/)**

The goal of this project is to reproduce the trajectory extraction algorithm from the original project using the C++ programming language.

## Our Algorithm

Our code allows you to reproduce the results of the [original paper](https://xavierchermain.github.io/fdm_aa/), whose objective is to fabricate anisotropic appearances with a filament printer and a glossy filament.

Our algorithm generates a continuous trajectory from an orientation field, a 2D shape, and spacing from adjacent paths. In other words, our algorithm fills a closed 2D space with an orientable cycle.

The generated continuous trajectory is then given to a filament printer, which fabricates a 2D plate with oriented extruded filaments. The 2D object has an anisotropic appearance if a glossy filament is used.