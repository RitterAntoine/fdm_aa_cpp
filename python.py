import numpy as np
import matplotlib.pyplot as plt
import time

# Function to create a grid and display it
def create_and_display_grid(grid):
    plt.style.use('_mpl-gallery-nogrid')  # Use a style without grid
    fig, ax = plt.subplots(figsize=(10, 7))  # Create a figure and a set of subplots
    ax.set_xlim(0, len(grid[0]))  # Set the x-limits of the current axes
    ax.set_ylim(0, len(grid))  # Set the y-limits of the current axes
    ax.set_aspect('equal')  # Set the aspect of the axis scaling
    ax.grid(which='both')  # Configure the grid lines
    ax.set_xticks(np.arange(0, len(grid[0]), 1), minor=True)  # Set the x-ticks of the current tick locations and labels
    ax.set_yticks(np.arange(0, len(grid), 1))  # Set the y-ticks of the current tick locations and labels
    ax.set_yticks(np.arange(0, len(grid), 1), minor=True)  # Set the y-ticks of the current tick locations and labels
    return fig, ax

# Function to display the scalar values of each cell in the grid
def display_scalar_values(ax, grid, fontsize=12, color='k'):
    for i in range(len(grid)):
        for j in range(len(grid[0])):
            ax.text(j+0.5, i+0.5, str(grid[i][j]), ha='center', va='center', fontsize=fontsize, color=color)

# Function to remove the scalar values from the grid
def remove_scalar_values(ax):
    for text in ax.texts:
        text.set_visible(False)

# Function to display colors based on the scalar values
def display_scalar_colors(ax, grid, cmap='Wistia'):
    ax.imshow(np.flipud(grid), cmap=cmap, interpolation='none', extent=[0, len(grid[0]), 0, len(grid)])

# Function to display another grid on top of the existing grid with all the center of each cell
def display_edge_grid(ax, grid, color='blue', linewidth=1):
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

# Function to add a line to the grid
def add_line(ax, x, y, color='k', linewidth=1):
    ax.plot(x, y, color, linewidth=linewidth)

# Function to display a point on the grid
def display_point(ax, points, color='k', marker='o', markersize=5):
    ax.plot(points[0], points[1], color, marker=marker, markersize=markersize)

# Function to display points from a polyline on the grid
def display_points_from_polyline(ax, polyline, color='k', marker='o', markersize=5):
    for point in polyline:
        display_point(ax, point, color, marker, markersize)

# Function to add a polyline to the grid
def add_polyline(ax, polyline, color='k', linewidth=2):
    for i in range(len(polyline) - 1):
        add_line(ax, [polyline[i][0], polyline[i+1][0]], [polyline[i][1], polyline[i+1][1]], color, linewidth)
    add_line(ax, [polyline[-1][0], polyline[0][0]], [polyline[-1][1], polyline[0][1]], color, linewidth)

# Main function to execute the code
if __name__ == "__main__":
    delay = .5 # seconds
    grid = [(1, 1, 1, 1, 1, 1, 1, 1), (1, -1, -1, 1, 1, -1, -1, 1), (1, -1, -1, 1, 1, -1, -1, 1), (1, 1, 1, 1, 1, 1, 1, 1)]
    polylines = [
        [(1, 1.5), (1.5, 1), (2.5, 1), (3, 1.5), (3, 2.5), (2.5, 3), (1.5, 3), (1, 2.5)],
        [(5, 1.5), (5.5, 1), (6.5, 1), (7, 1.5), (7, 2.5), (6.5, 3), (5.5, 3), (5, 2.5)]
    ]
    fig, ax = create_and_display_grid(grid)
    #plt.pause(delay)
    #display_scalar_values(ax, grid)
    #plt.pause(delay)
    display_scalar_colors(ax, grid)
    #plt.pause(delay)
    #remove_scalar_values(ax)
    #plt.pause(delay)
    display_edge_grid(ax, grid)
    #plt.pause(delay)
    for polyline in polylines:
        display_points_from_polyline(ax, polyline)
        plt.pause(delay)
    for polyline in polylines:
        add_polyline(ax, polyline)
        plt.pause(delay)
    #remove_edge_grid(ax)
    #display_scalar_values(ax, grid)
    #for polyline in polylines:
    #    display_points_from_polyline(ax, polyline)
    #    add_polyline(ax, polyline)
    plt.show()  # Display the figure