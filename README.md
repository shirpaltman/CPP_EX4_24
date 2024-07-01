# 🌳 Tree Visualization and Traversal Library 🌳

## Author Information

- **Author**: Shir Altman
- **ID**: 325168870
- **Email**: shirpaltman@gmail.com

---

## Overview

This C++ library provides a comprehensive solution for creating, visualizing, and traversing general trees. The library includes functionalities for node addition, tree traversal, visualization using SFML, and heapification.

---

## Project Structure


markdown

# 🌳 Tree Visualization and Traversal Library 🌳

## Author Information

- **Author**: Shir Altman
- **ID**: 325168870
- **Email**: shirpaltman@gmail.com

---

## Overview

This C++ library provides a comprehensive solution for creating, visualizing, and traversing general trees. The library includes functionalities for node addition, tree traversal, visualization using SFML, and heapification.

---

## Project Structure

.
├── src
│ ├── tree.cpp
│ ├── node.cpp
│ ├── Demo.cpp
│ ├── Test.cpp
│ └── TreeVisualizer.cpp
├── include
│ ├── tree.hpp
│ ├── node.hpp
│ ├── TreeVisualizer.hpp
├── Makefile
├── README.md
└── .gitignore


---

## Features

- **Tree Construction**: Create trees with a configurable number of children per node.
- **Node Management**: Add root and sub-nodes.
- **Traversal Iterators**: Includes Pre-order, In-order, Post-order, BFS, and DFS iterators.
- **Visualization**: Visualize the tree structure using SFML.
- **Heapification**: Convert the tree into a heap.

---

## Classes and Their Responsibilities

### `Tree`

The `Tree` class is responsible for managing the tree structure, including adding nodes and traversing the tree.

#### Key Methods:

- `add_root(const T& data)`: Adds the root node.
- `get_root()`: Returns the root node.
- `add_sub_node(shared_ptr<Node<T>>& parent_node, const T& data)`: Adds a sub-node to the specified parent node.
- `printTree()`: Prints the tree.
- `heapify(shared_ptr<Node<T>> node)`: Heapifies the subtree.
- `myHeap()`: Heapifies the entire tree.

### Iterators

- **PreOrderIterator**: Traverse the tree in pre-order.
- **InOrderIterator**: Traverse the tree in in-order.
- **PostOrderIterator**: Traverse the tree in post-order.
- **BFSIterator**: Traverse the tree in breadth-first order.
- **DFSIterator**: Traverse the tree in depth-first order.

### `TreeVisualizer`

The `TreeVisualizer` class is responsible for visualizing the tree structure using the SFML library.

#### Key Methods:

- `showTree(const shared_ptr<Node<T>>& root, RenderWindow& window, const Font& font)`: Visualizes the tree starting from the root.
- `drawTree(RenderWindow& window, shared_ptr<Node<T>> node, const Font& font, int x, int y, int level)`: Recursively draws the tree nodes and edges.

---

