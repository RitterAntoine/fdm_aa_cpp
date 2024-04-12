import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import time
import ast
import tkinter as tk
from tkinter import filedialog

# Function to create a grid and display it
def create_and_display_grid(grid): # viridice
    plt.style.use('_mpl-gallery-nogrid')  # Use a style without grid
    fig, ax = plt.subplots(figsize=(10, 7))  # Create a figure and a set of subplots
    ax.set_xlim(0, len(grid[0]))  # Set the x-limits of the current axes
    ax.set_ylim(0, len(grid))  # Set the y-limits of the current axes
    ax.set_aspect('equal')  # Set the aspect of the axis scaling
    ax.grid(which='both')  # Configure the grid lines
    ax.set_xticks(np.arange(0, len(grid[0]), 1), minor=True)  # Set the x-ticks of the current tick locations and labels
    ax.set_yticks(np.arange(0, len(grid), 1))  # Set the y-ticks of the current tick locations and labels
    ax.set_yticks(np.arange(0, len(grid), 1), minor=True)  # Set the y-ticks of the current tick locations and labels
    ax.axis('off')  # Hide the axes
    return fig, ax

# Function to display the scalar values of each cell in the grid
def display_scalar_values(ax, grid, fontsize=24, color='k'):
    for i in range(len(grid)):
        for j in range(len(grid[0])):
            ax.text(j+0.5, i+0.5, str(grid[i][j]), ha='center', va='center', fontsize=fontsize, color=color)

# Function to remove the scalar values from the grid
def remove_scalar_values(ax):
    for text in ax.texts:
        text.set_visible(False)

# Function to display colors based on the scalar values
def display_scalar_colors(ax, grid, cmap='viridis'):
    im = ax.imshow(np.flipud(grid), cmap=cmap, interpolation='none', extent=[0, len(grid[0]), 0, len(grid)])
    return im

# Function to display grid
def display_grid(ax, grid, color='black', linewidth=1):
    for i in range(len(grid)):
        for j in range(len(grid[0])):
            ax.plot([j + 1, j + 1], [i, i + 1], color, linewidth=linewidth)
            ax.plot([j, j + 1], [i + 1, i + 1], color, linewidth=linewidth)
            ax.plot([j, j], [i, i + 1], color, linewidth=linewidth)
            ax.plot([j, j + 1], [i, i], color, linewidth=linewidth)


# Function to display another grid on top of the existing grid with all the center of each cell
def display_edge_grid(ax, grid, color='red', linewidth=2):
    shift = 0.5
    for i in range(len(grid) - 1):
        for j in range(len(grid[0]) - 1):
            ax.plot([j + 1 + shift, j+1 + shift], [i + shift, i+1 + shift], color, linewidth=linewidth)
            ax.plot([j + shift, j+1 + shift], [i+1 + shift, i+1 + shift], color, linewidth=linewidth)
            ax.plot([j + shift, j+shift], [i + shift, i+1 + shift], color, linewidth=linewidth)
            ax.plot([j + shift, j+1 + shift], [i + shift, i + shift], color, linewidth=linewidth)

# Function to remove the edge grid
def remove_edge_grid(ax):
    for line in ax.lines:
        line.set_visible(False)

# Function to add a line to the grid with a contour
def add_line(ax, point1, point2, color='teal', linewidth=12, contour_color='black', contour_width=14):
    # Draw the contour line (bigger width)
    ax.plot([point1[0], point2[0]], [point1[1], point2[1]], contour_color, linewidth=contour_width)
    # Draw the actual line (smaller width)
    ax.plot([point1[0], point2[0]], [point1[1], point2[1]], color, linewidth=linewidth)

# Function to display a point on the grid
def display_point(ax, points, color='teal', edgecolor='black', marker='o', markersize=1000):
    scatter = ax.scatter(points[0], points[1], color=color, edgecolor=edgecolor, marker=marker, s=markersize)
    scatter.set_zorder(5)

# Function to display points from a polyline on the grid
def display_points_from_polyline(ax, polyline):
    for point in polyline:
        display_point(ax, point, color='teal', edgecolor='black', marker='o', markersize=300)

# Function to add a polyline to the grid
def add_polyline(ax, polyline, color='teal', linewidth=8, contour_color='black', contour_width=10):
    for i in range(len(polyline) - 1):
        add_line(ax, polyline[i], polyline[i+1], color, linewidth, contour_color, contour_width)
    add_line(ax, polyline[-1], polyline[0], color, linewidth, contour_color, contour_width)

def read_grid_from_file():
    root = tk.Tk()
    root.withdraw()  # Hide the main window
    file_path = filedialog.askopenfilename()  # Open the file dialog
    grid = []
    with open(file_path, 'r') as f:
        for line in f:
            # Remove newline character, split by comma, convert to double and add to grid
            grid.append(tuple(float(x) for x in line.strip().split(',')))
    return grid

def read_polylines_from_file():
    root = tk.Tk()
    root.withdraw()  # Hide the main window
    file_path = filedialog.askopenfilename()  # Open the file dialog
    polylines = []
    with open(file_path, 'r') as f:
        for line in f:
            # Remove newline character, split by comma, convert to tuple of int and add to polylines
            polyline = [tuple(map(float, point.split(','))) for point in line.strip().split(' ')]
            polylines.append(polyline)
    return polylines

def demo(grid, scalar_values, scalar_colors, edge_grid, single_point, polylines, polylines_step):
    Grid = [(1, 1, 1, 1),
            (1, -1, -1, 1),
            (1, -1, -1, 1),
            (1, 1, 1, 1)]
    Polylines = [[(1, 1.5), (1.5, 1), (2.5, 1), (3, 1.5), (3, 2.5), (2.5, 3), (1.5, 3), (1, 2.5)]]
    fig, ax = create_and_display_grid(Grid)
    if grid == True:
        display_grid(ax, Grid)
    if scalar_values == True:
        display_scalar_values(ax, Grid)
    if scalar_colors == True:
        im = display_scalar_colors(ax, Grid)
        cbar = plt.colorbar(im, ax=ax, orientation='vertical')
        cbar.ax.tick_params(labelsize=14)
    if edge_grid == True:
        display_edge_grid(ax, Grid)
    if single_point == True:
        display_point(ax, (1, 1.5))
    if all_points == True:
        for i in range(len(Polylines[0])):
            display_point(ax, Polylines[0][i])
    if single_point_adjacency_1 == True:
        add_line(ax, [1, 1.5], [1, 2.5])
    if single_point_adjacency_2 == True:
        add_line(ax, [1, 1.5], [1.5, 1])
    if polylines == True:
        for polyline in Polylines:
            add_polyline(ax, polyline)
    if polylines_step != 0:
        for i in range(0, polylines_step):
            add_line(ax, Polylines[0][i], Polylines[0][i+1])
    plt.show()

def main():
    grid = read_grid_from_file()
    polylines = read_polylines_from_file()
    fig, ax = create_and_display_grid(grid)
    display_grid(ax, grid)
    im = display_scalar_colors(ax, grid)
    cbar = plt.colorbar(im, ax=ax, orientation='vertical')
    cbar.ax.tick_params(labelsize=14)
    display_edge_grid(ax, grid)
    for polyline in polylines:
        display_points_from_polyline(ax, polyline)
    for polyline in polylines:
        add_polyline(ax, polyline)
    plt.show()


# Main function to execute the code
if __name__ == "__main__":
    grid = True
    scalar_values = False
    scalar_colors = True
    edge_grid = True
    single_point = False
    all_points = True
    single_point_adjacency_1 = False
    single_point_adjacency_2 = False
    polylines = True
    polylines_step = 0
    demo(grid, scalar_values, scalar_colors, edge_grid, single_point, polylines, polylines_step)

    #main()