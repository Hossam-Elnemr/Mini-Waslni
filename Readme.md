# MiniWasalni 🚗🗺️

MiniWasalni is a C++ smart navigation system inspired by apps like **Wasalni**, designed to simulate city maps and routing using graph algorithms. It features a graphical interface built with **Qt**, enabling users to manage graphs, explore routes, and track path history.

---

## 🛠️ Features

- **Graphical User Interface (Qt)**:
  - Login & Sign-up system
  - Home page for graph selection & creation
  - Visual graph display and interaction tools
- **Graph Operations**:
  - Add/Delete Cities (Nodes)
  - Add/Delete Roads (Edges)
  - Undo last modification (city or road addition/removal)
- **Algorithms Implemented**:
  - **BFS (Breadth-First Search)**: City traversal
  - **DFS (Depth-First Search)**: Longest exploration tour
  - **Dijkstra’s Algorithm**: For shortest and fastest paths
  - **Tarjan’s Algorithm**: To find all bridges in the graph
- **Persistent Storage**:
  - Graphs and user data saved to files
  - Full search and modification history per user

---

## 📸 UI Snapshots

- **Login/Signup Page**: Username/password validation and error handling
- **Home Page**: View, create, or select personal/system graphs
- **Graph Page**: Perform search, traversal, and manage cities/roads visually
- **History Page**: Undo actions and view previous path searches

---

## 📂 File Structure Overview

/MiniWasalni/
├── src/
│ ├── main.cpp
│ ├── graph.cpp / .h
│ ├── ui/
│ │ ├── login.ui
│ │ ├── home.ui
│ │ └── graph.ui
├── assets/
│ ├── icons/
│ └── styles/
├── data/
│ ├── users.dat
│ └── graphs/
├── README.md
