# MiniWasalni 🚗📺

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

```
/MiniWasalni/
├── src/
│   ├── main.cpp
│   ├── graph.cpp / .h
│   ├── ui/
│   │   ├── login.ui
│   │   ├── home.ui
│   │   └── graph.ui
├── assets/
│   ├── icons/
│   └── styles/
├── data/
│   ├── users.dat
│   └── graphs/
├── README.md
```
---

## 📦 Technologies Used

- **C++ (Standard Library, STL)**
- **Qt (GUI toolkit)** – [https://www.qt.io](https://www.qt.io)
- **Graph Algorithms**: BFS, DFS, Dijkstra, Tarjan
- **File I/O** for persistence

---

## 🚀 Getting Started

### Prerequisites

- **Qt (5.x or 6.x)**  
- **C++17+ compiler**

### Build Instructions

```bash
git clone https://github.com/yourusername/miniwasalni.git
cd miniwasalni
qmake MiniWasalni.pro
make
./MiniWasalni
```

---

## 🔐 Login System Details

- New users must choose a unique username
- Login errors include:
  - Missing fields
  - Invalid credentials
  - Duplicate usernames during signup
- Stored securely in local files

---

## 📚 Resources and References

- Qt Documentation: https://doc.qt.io
- Dijkstra’s Algorithm: https://brilliant.org/wiki/dijkstras-short-path-finder/
- Tarjan’s Algorithm (Bridge-Finding): https://cp-algorithms.com/graph/bridge-searching.html
- DFS & BFS: https://visualgo.net/en/dfsbfs

---

## 💼 Contributors
- Hossam El-Nemr
- Rehab Sobhy
- Rawan Ahmed
- Zeyad Sabry
- Remon Ehab
- Hussein Yahia
- Anas Elwkel
