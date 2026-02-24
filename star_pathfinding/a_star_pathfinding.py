# a_star_pathfinding_2024.py
# Personal algorithm practice after CS50 – 2024
# Implementing A* to find shortest path in a maze/grid

import heapq
import matplotlib.pyplot as plt
import numpy as np

# Simple 10x10 maze (0 = walkable, 1 = wall)
grid = np.array([
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 1, 1, 1, 0, 1, 1, 1, 1, 0],
    [0, 0, 0, 1, 0, 0, 0, 0, 1, 0],
    [0, 1, 0, 1, 1, 1, 1, 0, 1, 0],
    [0, 1, 0, 0, 0, 0, 1, 0, 1, 0],
    [0, 1, 1, 1, 1, 0, 1, 0, 1, 0],
    [0, 0, 0, 0, 1, 0, 0, 0, 1, 0],
    [0, 1, 1, 0, 1, 1, 1, 1, 1, 0],
    [0, 1, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 1, 1, 1, 1, 1, 1, 0]
])

start = (0, 0)
goal = (9, 9)

# Heuristic: Manhattan distance
def heuristic(a, b):
    return abs(a[0] - b[0]) + abs(a[1] - b[1])

# A* algorithm
def a_star(grid, start, goal):
    rows, cols = grid.shape
    open_set = []
    heapq.heappush(open_set, (0, start))  # (priority, position)

    came_from = {}
    g_score = {start: 0}
    f_score = {start: heuristic(start, goal)}

    directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]  # up, down, left, right

    while open_set:
        current_f, current = heapq.heappop(open_set)

        if current == goal:
            # Reconstruct path
            path = []
            while current in came_from:
                path.append(current)
                current = came_from[current]
            path.append(start)
            path.reverse()
            return path

        for d in directions:
            neighbor = (current[0] + d[0], current[1] + d[1])

            if 0 <= neighbor[0] < rows and 0 <= neighbor[1] < cols and grid[neighbor] == 0:
                tentative_g = g_score[current] + 1

                if neighbor not in g_score or tentative_g < g_score[neighbor]:
                    came_from[neighbor] = current
                    g_score[neighbor] = tentative_g
                    f_score[neighbor] = tentative_g + heuristic(neighbor, goal)
                    heapq.heappush(open_set, (f_score[neighbor], neighbor))

    return None  # No path found

# Run A*
path = a_star(grid, start, goal)

# Visualization
plt.figure(figsize=(8, 8))
plt.imshow(grid, cmap='binary', origin='upper')

if path:
    path_array = np.array(path)
    plt.plot(path_array[:, 1], path_array[:, 0], 'r-', linewidth=3, marker='o')
    plt.title('A* Pathfinding Result (Red path from start to goal)')
else:
    plt.title('No path found')

plt.grid(True, color='gray', alpha=0.3)
plt.xticks(range(grid.shape[1]))
plt.yticks(range(grid.shape[0]))
plt.savefig('a_star_pathfinding.png', dpi=150)
plt.show()
