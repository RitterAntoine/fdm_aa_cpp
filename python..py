import numpy as np
import matplotlib.pyplot as plt
import time

# Create a grid
def create_and_display_grid(grid):
    plt.style.use('_mpl-gallery-nogrid')
    fig, ax = plt.subplots(figsize=(10, 7))
    ax.set_xlim(0, len(grid[0]))
    ax.set_ylim(0, len(grid))
    ax.set_aspect('equal')
    ax.grid(which='both')
    ax.set_xticks(np.arange(0, len(grid[0]), 1), minor=True)
    ax.set_yticks(np.arange(0, len(grid), 1))  # Set major y-ticks every 1 unit
    ax.set_yticks(np.arange(0, len(grid), 1), minor=True)  # Set minor y-ticks every 1 unit
    return fig, ax

# Will display the scalar values of each cell in the grid
def display_scalar_values(ax, grid, fontsize=12, color='k'):
    for i in range(len(grid)):
        for j in range(len(grid[0])):
            ax.text(j+0.5, i+0.5, str(grid[i][j]), ha='center', va='center', fontsize=fontsize, color=color)

def remove_scalar_values(ax):
    for text in ax.texts:
        text.set_visible(False)

# Put colors based on the scalar values
def display_scalar_colors(ax, grid, cmap='Wistia'):
    ax.imshow(np.flipud(grid), cmap=cmap, interpolation='none', extent=[0, len(grid[0]), 0, len(grid)])

# This function will display another grid on top of the existing grid with all the center of each cell, so this grid will be 1 unit smaller than the original grid and will be shifted by 0.5 unit
def display_edge_grid(ax, grid, color='blue', linewidth=1):
    shift = 0.5
    for i in range(len(grid) - 1):
        for j in range(len(grid[0]) - 1):
            ax.plot([j + 1 + shift, j+1 + shift], [i + shift, i+1 + shift], color, linewidth=linewidth)
            ax.plot([j + shift, j+1 + shift], [i+1 + shift, i+1 + shift], color, linewidth=linewidth)
            ax.plot([j + shift, j+shift], [i + shift, i+1 + shift], color, linewidth=linewidth)
            ax.plot([j + shift, j+1 + shift], [i + shift, i + shift], color, linewidth=linewidth)

def remove_edge_grid(ax):
    for line in ax.lines:
        line.set_visible(False)

def add_line(ax, x, y, color='k', linewidth=1):
    ax.plot(x, y, color, linewidth=linewidth)

def add_polyline(ax, polyline, color='k', linewidth=2):
    for i in range(len(polyline) - 1):
        add_line(ax, [polyline[i][0], polyline[i+1][0]], [polyline[i][1], polyline[i+1][1]], color, linewidth)
    add_line(ax, [polyline[-1][0], polyline[0][0]], [polyline[-1][1], polyline[0][1]], color, linewidth)

import matplotlib.pyplot as plt
import time

# Your functions here...

if __name__ == "__main__":
    grid = [(1, 1, 1, 1, 1, 1, 1, 1), (1, -1, -1, 1, 1, -1, -1, 1), (1, -1, -1, 1, 1, -1, -1, 1), (1, 1, 1, 1, 1, 1, 1, 1)]
    polyline_1 = [(1, 1.5), (1.5, 1), (2.5, 1), (3, 1.5), (3, 2.5), (2.5, 3), (1.5, 3), (1, 2.5)]
    Polyline_2 = [(5, 1.5), (5.5, 1), (6.5, 1), (7, 1.5), (7, 2.5), (6.5, 3), (5.5, 3), (5, 2.5)]
    fig, ax = create_and_display_grid(grid)
    plt.pause(2)  # Pause for 2 seconds
    display_scalar_values(ax, grid)
    plt.pause(2)  # Pause for 2 seconds
    display_scalar_colors(ax, grid)
    plt.pause(2)  # Pause for 2 seconds
    remove_scalar_values(ax)
    plt.pause(2)  # Pause for 2 seconds
    display_edge_grid(ax, grid)
    plt.pause(2)  # Pause for 2 seconds
    add_polyline(ax, polyline_1)
    plt.pause(2)  # Pause for 2 seconds
    add_polyline(ax, Polyline_2)
    plt.pause(2)  # Pause for 2 seconds
    remove_edge_grid(ax)
    display_scalar_values(ax, grid)
    add_polyline(ax, polyline_1)
    add_polyline(ax, Polyline_2)
    plt.show()