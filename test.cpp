#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Tree.hpp"

// Function to create a sample binary tree
Tree<double> createSampleBinaryTree() {
    Node<double> root_node(34.7);
    Tree<double> tree; // Binary tree that contains doubles.
    tree.add_root(root_node);

    Node<double> n1(45.9);
    Node<double> n2(56.8);
    Node<double> n3(78.2);
    Node<double> n4(89.1);
    Node<double> n5(100.5);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    return tree;
}

// Function to create a sample 3-ary tree
Tree<double, 3> createSampleThreeAryTree() {
    Node<double> root_node(34.7);
    Tree<double, 3> tree; // 3-ary tree.
    tree.add_root(root_node);

    Node<double> n1(45.9);
    Node<double> n2(56.8);
    Node<double> n3(78.2);
    Node<double> n4(89.1);
    Node<double> n5(100.5);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(root_node, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    return tree;
}

TEST_CASE("Testing Pre-Order Iterator") {
    Tree<double> tree = createSampleBinaryTree();

    std::vector<double> expected = {34.7, 45.9, 78.2, 89.1, 56.8, 100.5};
    std::vector<double> result;
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node) {
        result.push_back((*node).get_value());
    }

    CHECK(result == expected);
}

TEST_CASE("Testing Post-Order Iterator") {
    Tree<double> tree = createSampleBinaryTree();

    std::vector<double> expected = {78.2, 89.1, 45.9, 100.5, 56.8, 34.7};
    std::vector<double> result;
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node) {
        result.push_back((*node).get_value());
    }

    CHECK(result == expected);
}

TEST_CASE("Testing In-Order Iterator") {
    Tree<double> tree = createSampleBinaryTree();

    std::vector<double> expected = {78.2, 45.9, 89.1, 34.7, 100.5, 56.8};
    std::vector<double> result;
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node) {
        result.push_back((*node).get_value());
    }

    CHECK(result == expected);
}

TEST_CASE("Testing BFS Iterator") {
    Tree<double> tree = createSampleBinaryTree();

    std::vector<double> expected = {34.7, 45.9, 56.8, 78.2, 89.1, 100.5};
    std::vector<double> result;
    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node) {
        result.push_back((*node).get_value());
    }

    CHECK(result == expected);
}

TEST_CASE("Testing DFS Iterator") {
    Tree<double> tree = createSampleBinaryTree();

    std::vector<double> expected = {34.7, 45.9, 78.2, 89.1, 56.8, 100.5};
    std::vector<double> result;
    for (auto node = tree.begin_dfs(); node != tree.end_dfs(); ++node) {
        result.push_back((*node).get_value());
    }

    CHECK(result == expected);
}

TEST_CASE("Testing Heap Iterator") {
    Tree<double> tree = createSampleBinaryTree();

    std::vector<double> expected = {34.7, 45.9, 56.8, 78.2, 89.1, 100.5}; // Assuming min-heap
    std::vector<double> result;
    for (auto node = tree.begin_heap(); node != tree.end_heap(); ++node) {
        result.push_back((*node).get_value());
    }

    CHECK(result == expected);
}

TEST_CASE("Testing 3-Ary Tree DFS, In-Order, Post-Order, Pre-Order Iterators") {
    Tree<double, 3> tree = createSampleThreeAryTree();

    std::vector<double> expected = {34.7, 45.9, 89.1, 56.8, 100.5, 78.2};
    std::vector<double> result1;
    std::vector<double> result2;
    std::vector<double> result3;
    std::vector<double> result4;

    for (auto node = tree.begin_dfs(); node != tree.end_dfs(); ++node) {
        result1.push_back((*node).get_value());
    }

    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node) {
        result2.push_back((*node).get_value());
    }

    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node) {
        result3.push_back((*node).get_value());
    }

    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node) {
        result4.push_back((*node).get_value());
    }

    CHECK(result1 == expected);
    CHECK(result2 == expected);
    CHECK(result3 == expected);
    CHECK(result4 == expected);
}

TEST_CASE("Testing 3-Ary Tree Heap Iterator") {
    Tree<double, 3> tree = createSampleThreeAryTree();

    std::vector<double> expected = {34.7, 45.9, 56.8, 78.2, 89.1, 100.5}; // Assuming min-heap
    std::vector<double> result;
    for (auto node = tree.begin_heap(); node != tree.end_heap(); ++node) {
        result.push_back((*node).get_value());
    }

    CHECK(result == expected);
}

TEST_CASE("Testing myHeap Function") {
    Tree<double> tree = createSampleBinaryTree();

    // Transform the tree into a heap
    tree.myHeap();

    // Assuming min-heap
    std::vector<double> expected = {34.7, 45.9, 56.8, 78.2, 89.1, 100.5};
    std::vector<double> result;

    // Use the HeapIterator to traverse the heap
    for (auto node = tree.begin_heap(); node != tree.end_heap(); ++node) {
        result.push_back((*node).get_value());
    }

    // Check that the result matches the expected values
    CHECK(result == expected);
}
