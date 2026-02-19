# Pathfinding

<p align="center">
  <img src="screenshots/screenshot0.png" style="max-width:100%; height:auto;" alt="screenshot0"/>
</p>


A pathfinding visualization tool powered by [raylib](https://www.raylib.com/). This is an educational project designed to visually explore different grid-traversing algorithms. The currently implemented algorithms are:
- Depth-First Search flood fill
- Breadth-First Search flood fill
- Breadth-First Search pathfinding algorithm
- A* pathfinding algorithm


## Features

- 2D grid-based map system
- Simple user interface for selecting an algorithm
- Ability to paint the grid with different wall patterns
- Visualization of the selected algorithm and its traversal through the grid


## Prerequisites

- Linux
- C++ compiler


## Installation

```bash
git clone https://github.com/barlukh/pathfinding.git
cd pathfinding
make
./pathfinding
```


## Functionality

Controls: 
- 1, 2, 3, 4 - Paint different cell on the grid
- Q, W, E, R - Select an algorithm
- Left mouse click + drag - Place cells
- C - Partially reset the grid
- V - Fully reset the grid
- Space - Execute the visualizer
- ESC - Exit
- Various variables can be modified in the config.hpp (advanced users only)


## Comments

### About the Project

This project was created as a way to practice modern C++ while exploring different pathfinding algorithms. The goal was to build everything in C++ from the ground up and gain a deeper understanding of both the language and algorithm design.

One of the first challenges was implementing the user interface. C++ is relatively low-level when it comes to UI development, which makes the process more manual compared to higher-level frameworks. This trade-off was intentional — the purpose of the project was to stay close to the core language. With a more feature-rich framework, creating scalable and resolution-independent UI elements would likely be easier.

The project uses Raylib to handle window creation and the main application loop. Some aspects of the window configuration can be adjusted in config.hpp, but the layout is primarily designed for a 16:9 aspect ratio (originally developed on a 4K monitor).

### Algorithm Implementation

The flood fill algorithms (DFS and BFS) were relatively straightforward to implement. Both are built around the same operational pattern and use a std::deque container:

DFS (Depth-First Search) — uses LIFO behavior

BFS (Breadth-First Search) — uses FIFO behavior

The only difference between them lies in how the next cell is retrieved from the container.

Initially, I planned to implement Dijkstra’s algorithm. However, I realized that Dijkstra’s algorithm is primarily useful for weighted graphs. On a uniformly weighted grid, Dijkstra’s algorithm effectively behaves like BFS, with additional bookkeeping required to reconstruct the path. Therefore, BFS was selected as one of the implemented algorithms.

The last algorithm I implemented was the A* pathfinding algorithm, which uses heuristic-based search and a priority queue to retrieve the next cell with the lowest f-score, making it significantly more efficient than the BFS search method.


## License

**This project** is licensed under the [GNU GPLv3](https://www.gnu.org/licenses/gpl-3.0.en.html).

**Raylib** is licensed under the [zlib/libpng license](https://www.raylib.com/license.html), which is compatible with GPL.

When distributing this project, please ensure:
- You include the full text of the GPLv3 license.
- You retain raylib’s original license notice.
- You clearly mark any modifications made to the original code.


## Credits

- [raylib](https://www.raylib.com/) raylib © 2013–present Ramon Santamaria


## Screenshots

### Breadth-First Search algorithm (pattern #1)
<p align="center">
  <img src="screenshots/screenshot1.png" style="max-width:100%; height:auto;" alt="screenshot1"/>
</p>

### A* algorithm (pattern #1)

<p align="center">
  <img src="screenshots/screenshot2.png" style="max-width:100%; height:auto;" alt="screenshot2"/>
</p>

### Breadth-First Search algorithm (pattern #2)

<p align="center">
  <img src="screenshots/screenshot3.png" style="max-width:100%; height:auto;" alt="screenshot3"/>
</p>

### A* algorithm (pattern #2)

<p align="center">
  <img src="screenshots/screenshot4.png" style="max-width:100%; height:auto;" alt="screenshot4"/>
</p>
