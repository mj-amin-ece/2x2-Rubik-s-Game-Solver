# 2x2 Rubik's Game Solver

**Instructor:** Dr. Amir Jahanshahi  
**Course:** Advanced Programming - Midterm Project  
**Deadline:** Friday, 29 Farvardin - 23:00  

This project is a Rubik's Cube solver for a 2x2 Rubik's game, developed as part of the Advanced Programming midterm project. The project implements five different search algorithms to solve the game:

- **Breadth-First Search (BFS)**  
- **Depth-First Search (DFS)**  
- **Depth-Limited Search (DLS)**  
- **Iterative-Deepening Search (IDS)**  
- **Bidirectional Search**

The task involves simulating and solving the cube using search algorithms for the solution.

---

## How to Play

The user specifies the color of each part of the cube. Once the game starts, the program determines the solution to solve the Rubik's cube and displays the sequence of moves required.

There are 12 possible rotation modes (clockwise and counter-clockwise), and the user can switch between these modes while playing. The program will also detect unsolvable configurations and inform the user if no solution is possible.

---

## Algorithms Implemented

### 1. Breadth-First Search (BFS)
BFS explores all nodes level by level. It is an uninformed search algorithm used to find the shortest path to the solution.

### 2. Depth-First Search (DFS)
DFS explores as far as possible down a branch before backtracking. It may not guarantee the shortest path but is efficient for deep exploration.

### 3. Depth-Limited Search (DLS)
DLS is a variant of DFS where the depth of exploration is limited. This helps avoid going too deep when the solution is likely within a certain depth range.

### 4. Iterative-Deepening Search (IDS)
IDS combines the benefits of BFS and DFS. It performs DFS with increasing depth limits, ensuring an optimal solution while conserving memory.

### 5. Bidirectional Search
Bidirectional Search runs two simultaneous searches—one forward from the start and one backward from the goal—until the searches meet. This method reduces the search space, making it more efficient for large graphs.

---

## Requirements
- C++ compiler (g++, clang++, etc.)

---

