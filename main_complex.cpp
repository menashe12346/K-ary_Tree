#include <iostream>
#include <string>
#include <QApplication>
#include "Tree.hpp"
#include "Complex.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    // Initializes a Qt application
    QApplication app(argc, argv);

    Node<Complex> root_node = Node<Complex>(Complex(1.1, 1.1));
    Tree<Complex> tree; // Binary tree that contains complex numbers.
    tree.add_root(root_node);

    Node<Complex> n1 = Node<Complex>(Complex(1.2, 1.2));
    Node<Complex> n2 = Node<Complex>(Complex(1.3, 1.3));
    Node<Complex> n3 = Node<Complex>(Complex(1.4, 1.4));
    Node<Complex> n4 = Node<Complex>(Complex(1.5, 1.5));
    Node<Complex> n5 = Node<Complex>(Complex(1.6, 1.6));

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    // The tree should look like:
    /**
     *       root = (1.1, 1.1)
     *     /       \
     *   (1.2, 1.2)  (1.3, 1.3)
     *   /  \        /
     * (1.4, 1.4) (1.5, 1.5) (1.6, 1.6)
     */

    bool first = true;
    cout << "Pre-Order Traversal:\n";
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node) {
        if (!first) {
            cout << ", ";
        }
        cout << (*node).get_value();
        first = false;
    }
    cout << endl;

    first = true;
    cout << "Post-Order Traversal:\n";
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node) {
        if (!first) {
            cout << ", ";
        }
        cout << (*node).get_value();
        first = false;
    }
    cout << endl;

    first = true;
    cout << "In-Order Traversal:\n";
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node) {
        if (!first) {
            cout << ", ";
        }
        cout << (*node).get_value();
        first = false;
    }
    cout << endl;

    first = true;
    cout << "BFS Traversal:\n";
    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node) {
        if (!first) {
            cout << ", ";
        }
        cout << (*node).get_value();
        first = false;
    }
    cout << endl;

    first = true;
    cout << "DFS Traversal:\n";
    for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node) {
        if (!first) {
            cout << ", ";
        }
        cout << (*node).get_value();
        first = false;
    }
    cout << endl;

    cout << tree;

    Tree<Complex, 3> three_ary_tree; // 3-ary tree.
    three_ary_tree.add_root(root_node);
    three_ary_tree.add_sub_node(root_node, n1);
    three_ary_tree.add_sub_node(root_node, n2);
    three_ary_tree.add_sub_node(root_node, n3);
    three_ary_tree.add_sub_node(n1, n4);
    three_ary_tree.add_sub_node(n2, n5);

    // The tree should look like:
    /**
     *       root = (1.1, 1.1)
     *     /       |      \
     *  (1.2, 1.2)(1.3, 1.3)(1.4, 1.4)
     *   /        |
     * (1.5, 1.5) (1.6, 1.6)
     */

    // Starts the Qt event loop, which processes events like user interactions, updates, and window management.
    // This loop runs continuously, keeping the application responsive until it is closed.
    // It returns an exit code when the application terminates, which can be used for debugging or handling application shutdown procedures.
    return app.exec();
}
