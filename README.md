# 🌳 Tree Container in C++

## Overview
This project implements a generic k-ary tree container in C++. A k-ary tree is a tree where each node can have up to k children. By default, the tree is binary (k=2). The container can hold keys of various types, including numbers, strings, and user-defined classes.

## Features
- **Generic k-ary Tree**: Allows specification of the maximum number of children (k) for each node.
- **Iterators**:
  - **Pre-Order**: Visits the current node, then the left subtree, followed by the right subtree.
  - **Post-Order**: Visits the left subtree, then the right subtree, followed by the current node.
  - **In-Order**: Visits the left subtree, then the current node, followed by the right subtree.
  - **BFS**: Breadth-First Search, visiting nodes level by level from left to right.
  - **DFS**: Depth-First Search, exploring as far as possible along each branch before backtracking.
  - **Heap Iterator**: Converts the binary tree into a min-heap.

## Usage
1. **Creating a Tree**:
   ```cpp
   tree<int> myTree;
   myTree.add_root(1);
   ```

2. **Adding Nodes**:
   ```cpp
   myTree.add_sub_node(1, 2); // Adds node 2 as a child of node 1.
   ```

3. **Iterating**:
   ```cpp
   for (auto it = myTree.begin_pre_order(); it != myTree.end_pre_order(); ++it) {
       std::cout << *it << " ";
   }
   ```

4. **Printing**:
   A GUI interface is used to print the tree structure. The implementation leverages Qt libraries for graphical output.

## Why Use This? 🌟
The k-ary tree container provides a flexible way to represent hierarchical data structures with various traversal methods. It is particularly useful in applications requiring tree traversal, such as parsing, searching, and sorting algorithms.

## Building the Code 🛠️
1. **Dependencies**: Ensure that you have Qt installed. Follow the [Qt for Beginners](https://wiki.qt.io/Qt_for_Beginners) guide for setup.
2. **Compilation**:
   - Use the provided Makefile.
   - Run `make tree` to build and run the main program.

## Class Structure 🏗️
- **Tree Class**: Represents the k-ary tree container with methods for adding nodes and iterating through the tree.
- **Complex Class**: Demonstrates usage with complex numbers as keys.

## Testing ✔️
Comprehensive tests are included to validate the functionality of the tree container and its iterators. Ensure that all tests pass before using the container in production.

## Contact 📧
For any queries, please contact [menashe7676@example.com].