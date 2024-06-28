#include <iostream>
#include <string>
#include "Tree.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Node<double> root_node = Node<double>(1.1);
    Tree<double> tree; // Binary tree that contains doubles.
    tree.add_root(root_node);
    Node<double> n1 = Node<double>(1.2);
    Node<double> n2 = Node<double>(1.3);
    Node<double> n3 = Node<double>(1.4);
    Node<double> n4 = Node<double>(1.5);
    Node<double> n5 = Node<double>(1.6);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    // The tree should look like:
    /**
     *       root = 1.1
     *     /       \
     *    1.2      1.3
     *   /  \      /
     *  1.4  1.5  1.6
     */

    bool first = true;
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        if (!first) {
            cout << ", ";
        }
        cout << (*node).get_value();
        first = false;
    }
    cout << endl;
    // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6

    first = true;
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
    {
        if (!first) {
            cout << ", ";
        }
        cout << (*node).get_value();
        first = false;
    }
    cout << endl;
    // prints: 1.4, 1.5, 1.2, 1.6, 1.3, 1.1

    first = true;
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    {
        if (!first) {
            cout << ", ";
        }
        cout << (*node).get_value();
        first = false;
    }
    cout << endl;
    // prints: 1.4, 1.2, 1.5, 1.1, 1.6, 1.3

    first = true;
    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
    {
        if (!first) {
            cout << ", ";
        }
        cout << (*node).get_value();
        first = false;
    }
    cout << endl;
    // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6

    first = true;
    for (auto node : tree)
    {
        if (!first) {
            cout << ", ";
        }
        cout << node.get_value();
        first = false;
    }
    cout << endl;
    // same as BFS: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6

    std::cout << tree;
        
    Tree<double, 3> three_ary_tree; // 3-ary tree.
    three_ary_tree.add_root(root_node);
    three_ary_tree.add_sub_node(root_node, n1);
    three_ary_tree.add_sub_node(root_node, n2);
    three_ary_tree.add_sub_node(root_node, n3);
    three_ary_tree.add_sub_node(n1, n4);
    three_ary_tree.add_sub_node(n2, n5);

        std::cout << three_ary_tree;


    // The tree should look like:
    /**
     *       root = 1.1
     *     /      |     \
     *    1.2    1.3    1.4
     *   /        |
     *  1.5      1.6
     */

    return app.exec();
}
