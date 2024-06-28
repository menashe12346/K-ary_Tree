#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include "Tree.hpp"

using namespace std;

// פונקציה לציור העץ על GUI
void draw_tree(QGraphicsScene &scene, std::shared_ptr<Node<double>> node, int x, int y, int h_gap, int v_gap, bool is_left = true) {
    if (!node) return;

    int radius = 20; // רדיוס הצומת
    scene.addEllipse(x - radius, y - radius, 2 * radius, 2 * radius, QPen(Qt::black), QBrush(Qt::green));
    QGraphicsTextItem* text = scene.addText(QString::number(node->get_value()));
    text->setPos(x - radius / 2, y - radius / 2);

    int num_children = node->children.size();
    int total_width = (num_children - 1) * h_gap;
    int child_x = x - total_width / 2;

    for (auto &child : node->children) {
        if (node->children.size() == 1) {
            // התאמת מיקום עבור צומת עם ילד אחד בלבד
            child_x = is_left ? x - h_gap / 2 : x + h_gap / 2;
        }
        scene.addLine(x, y + radius, child_x, y + v_gap - radius, QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        draw_tree(scene, child, child_x, y + v_gap, h_gap, v_gap, &child == &node->children.front());
        child_x += h_gap;
    }
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QGraphicsScene scene;
    QGraphicsView view(&scene);

    Node<double> root_node(1.1);
    Tree<double> tree; // Binary tree that contains doubles.
    tree.add_root(root_node);
    Node<double> n1(1.2);
    Node<double> n2(1.3);
    Node<double> n3(1.4);
    Node<double> n4(1.5);
    Node<double> n5(1.6);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        cout << node->get_value() << ", ";
    } // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6
    cout << "\n" << endl;

    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
    {
        cout << node->get_value() << endl;
    } // prints: 1.4, 1.5, 1.2, 1.6, 1.3, 1.1

    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    {
        cout << node->get_value() << endl;
    } // prints: 1.4, 1.2, 1.5, 1.1, 1.6, 1.3

    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
    {
        cout << node->get_value() << endl;
    } // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6

    for (auto node : tree)
    {
        cout << node.get_value() << endl;
    } // same as BFS: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6

    // קביעת מרווחים אופקיים ואנכיים בין הצמתים
    int h_gap = 200; // מרווח אופקי ראשוני
    int v_gap = 100; // מרווח אנכי

    // ציור העץ ב-GUI
    draw_tree(scene, tree.get_root(), 400, 50, h_gap, v_gap);

    view.setWindowTitle("Tree Visualization");
    view.resize(800, 600);
    view.show();

    return app.exec();
}
