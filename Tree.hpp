#ifndef TREE_HPP
#define TREE_HPP

#include "Node.hpp"
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <sstream>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>

/// A generic k-ary tree class with various traversal methods and GUI printing.
template <typename T, int K = 2>
class Tree {
    struct TreeNode {
        Node<T> data;
        std::vector<TreeNode*> children;
        TreeNode(Node<T> val) : data(val) {}
    };

    TreeNode* root;

public:
    /// Constructor to initialize the tree with no root.
    Tree() : root(nullptr) {}

    /// Destructor to clear the tree.
    ~Tree() {
        clear(root);
    }

    /// Add or replace the root node.
    /// @param val The value of the root node.
    void add_root(Node<T> val) {
        if (root) {
            root->data = val;
        } else {
            root = new TreeNode(val);
        }
    }

    /// Add a child node to a specified parent node.
    /// @param parent_val The value of the parent node.
    /// @param child_val The value of the child node.
    void add_sub_node(Node<T> parent_val, Node<T> child_val) {
        TreeNode* parent = find(root, parent_val);
        if (parent && parent->children.size() < K) {
            parent->children.push_back(new TreeNode(child_val));
        }
    }

    /// Pre-order traversal iterator.
    class PreOrderIterator {
        std::stack<TreeNode*> nodes;
    public:
        PreOrderIterator(TreeNode* root) {
            if (root) nodes.push(root);
        }

        bool operator!=(const PreOrderIterator& other) const {
            return !nodes.empty();
        }

        Node<T>& operator*() const {
            return nodes.top()->data;
        }

        PreOrderIterator& operator++() {
            TreeNode* node = nodes.top();
            nodes.pop();
            for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
                nodes.push(*it);
            }
            return *this;
        }
    };

    /// Begin pre-order traversal.
    /// @return PreOrderIterator at the start.
    PreOrderIterator begin_pre_order() {
        return PreOrderIterator(root);
    }

    /// End pre-order traversal.
    /// @return PreOrderIterator at the end.
    PreOrderIterator end_pre_order() {
        return PreOrderIterator(nullptr);
    }

    /// Post-order traversal iterator.
    class PostOrderIterator {
        std::stack<TreeNode*> nodes;
        std::stack<TreeNode*> output;
    public:
        PostOrderIterator(TreeNode* root) {
            if (root) {
                nodes.push(root);
                while (!nodes.empty()) {
                    TreeNode* node = nodes.top();
                    nodes.pop();
                    output.push(node);
                    for (auto child : node->children) {
                        nodes.push(child);
                    }
                }
            }
        }

        bool operator!=(const PostOrderIterator& other) const {
            return !output.empty();
        }

        Node<T>& operator*() const {
            return output.top()->data;
        }

        PostOrderIterator& operator++() {
            output.pop();
            return *this;
        }
    };

    /// Begin post-order traversal.
    /// @return PostOrderIterator at the start.
    PostOrderIterator begin_post_order() {
        return PostOrderIterator(root);
    }

    /// End post-order traversal.
    /// @return PostOrderIterator at the end.
    PostOrderIterator end_post_order() {
        return PostOrderIterator(nullptr);
    }

    /// In-order traversal iterator.
    class InOrderIterator {
        std::stack<TreeNode*> nodes;
        TreeNode* current;
    public:
        InOrderIterator(TreeNode* root) : current(root) {
            while (current && !current->children.empty()) {
                nodes.push(current);
                current = current->children.front();
            }
        }

        bool operator!=(const InOrderIterator& other) const {
            return current != nullptr;
        }

        Node<T>& operator*() const {
            return current->data;
        }

        InOrderIterator& operator++() {
            if (current->children.size() > 1) {
                current = current->children[1];
                while (current && !current->children.empty()) {
                    nodes.push(current);
                    current = current->children.front();
                }
            } else {
                if (nodes.empty()) {
                    current = nullptr;
                } else {
                    current = nodes.top();
                    nodes.pop();
                }
            }
            return *this;
        }
    };

    /// Begin in-order traversal.
    /// @return InOrderIterator at the start.
    InOrderIterator begin_in_order() {
        return InOrderIterator(root);
    }

    /// End in-order traversal.
    /// @return InOrderIterator at the end.
    InOrderIterator end_in_order() {
        return InOrderIterator(nullptr);
    }

    /// BFS traversal iterator.
    class BFSIterator {
        std::queue<TreeNode*> nodes;
    public:
        BFSIterator(TreeNode* root) {
            if (root) nodes.push(root);
        }

        bool operator!=(const BFSIterator& other) const {
            return !nodes.empty();
        }

        Node<T>& operator*() const {
            return nodes.front()->data;
        }

        BFSIterator& operator++() {
            TreeNode* node = nodes.front();
            nodes.pop();
            for (auto child : node->children) {
                nodes.push(child);
            }
            return *this;
        }
    };

    /// Begin BFS traversal.
    /// @return BFSIterator at the start.
    BFSIterator begin_bfs_scan() {
        return BFSIterator(root);
    }

    /// End BFS traversal.
    /// @return BFSIterator at the end.
    BFSIterator end_bfs_scan() {
        return BFSIterator(nullptr);
    }

    /// Iterable to support range-based for loop.
    /// @return BFSIterator at the start.
    BFSIterator begin() {
        return begin_bfs_scan();
    }

    /// End of range-based for loop support.
    /// @return BFSIterator at the end.
    BFSIterator end() {
        return end_bfs_scan();
    }

    /// DFS traversal iterator.
    class DFSIterator {
        std::stack<TreeNode*> nodes;
    public:
        DFSIterator(TreeNode* root) {
            if (root) nodes.push(root);
        }

        bool operator!=(const DFSIterator& other) const {
            return !nodes.empty();
        }

        Node<T>& operator*() const {
            return nodes.top()->data;
        }

        DFSIterator& operator++() {
            TreeNode* node = nodes.top();
            nodes.pop();
            for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
                nodes.push(*it);
            }
            return *this;
        }
    };

    /// Begin DFS traversal.
    /// @return DFSIterator at the start.
    DFSIterator begin_dfs() {
        return DFSIterator(root);
    }

    /// End DFS traversal.
    /// @return DFSIterator at the end.
    DFSIterator end_dfs() {
        return DFSIterator(nullptr);
    }

    /// Heap traversal iterator.
    class HeapIterator {
        std::vector<Node<T>> heap;
        size_t index;
    public:
        HeapIterator(TreeNode* root) : index(0) {
            if (root) {
                toHeap(root);
                std::make_heap(heap.begin(), heap.end(), std::greater<Node<T>>());
                std::sort_heap(heap.begin(), heap.end(), std::greater<Node<T>>());
            }
        }

        bool operator!=(const HeapIterator& other) const {
            return index != heap.size();
        }

        Node<T>& operator*() {
            return heap[index];
        }

        HeapIterator& operator++() {
            ++index;
            return *this;
        }

    private:
        /// Convert the tree to a heap.
        /// @param node The root node of the subtree to convert.
        void toHeap(TreeNode* node) {
            if (node) {
                heap.push_back(node->data);
                for (auto child : node->children) {
                    toHeap(child);
                }
            }
        }
    };

    /// Begin heap traversal.
    /// @return HeapIterator at the start.
    HeapIterator begin_heap() {
        return HeapIterator(root);
    }

    /// End heap traversal.
    /// @return HeapIterator at the end.
    HeapIterator end_heap() {
        return HeapIterator(nullptr);
    }

    /// Convert the tree into a heap structure.
    void myHeap() {
        if (!root) return;

        std::vector<TreeNode*> nodes;
        toHeapVector(root, nodes);

        std::sort(nodes.begin(), nodes.end(), [](TreeNode* a, TreeNode* b) {
            return a->data < b->data;
        });

        for (size_t i = 0; i < nodes.size(); ++i) {
            nodes[i]->children.clear();
            if (2 * i + 1 < nodes.size()) {
                nodes[i]->children.push_back(nodes[2 * i + 1]);
            }
            if (2 * i + 2 < nodes.size()) {
                nodes[i]->children.push_back(nodes[2 * i + 2]);
            }
        }

        root = nodes[0];
    }

    /// Print the tree using a GUI.
    /// @param os The output stream to print to.
    /// @param tree The tree to print.
    friend std::ostream& operator<<(std::ostream& os, const Tree& tree) {
        tree.printTreeGUI();
        return os;
    }

    /// Print the tree in a graphical user interface.
    void printTreeGUI() const {
        // Create the scene
        QGraphicsScene scene;

        // Start drawing the tree from the top middle of the screen
        int startX = 750; // Adjust this based on your screen width
        int startY = 0;  // Start from the top
        int hGap = 200;   // Horizontal gap between nodes
        int vGap = 100;   // Vertical gap between levels

        drawNode(scene, root, startX, startY, hGap, vGap);

        // Create a view to visualize the scene
        QGraphicsView view(&scene);
        view.setRenderHint(QPainter::Antialiasing);
        view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
        view.setBackgroundBrush(QColor(43, 43, 43)); // Set the background color to dark gray
        view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Tree Visualization"));

        // Set the size of the view
        view.setFixedSize(1600, 900); // Width x Height
        scene.setSceneRect(0, 0, 1500, 800); // Set the scene rectangle to match the view size

        view.show();

        // Start the Qt event loop
        QApplication::exec();
    }

private:
    /// Clear the tree recursively.
    /// @param node The node to clear.
    void clear(TreeNode* node) {
        if (node) {
            for (auto child : node->children) {
                clear(child);
            }
            delete node;
        }
    }

    /// Find a node with a specific value.
    /// @param node The starting node.
    /// @param val The value to find.
    /// @return The found node or nullptr if not found.
    TreeNode* find(TreeNode* node, Node<T> val) {
        if (!node) return nullptr;
        if (node->data == val) return node;
        for (auto child : node->children) {
            TreeNode* found = find(child, val);
            if (found) return found;
        }
        return nullptr;
    }

    /// Draw a node and its children in the scene.
    /// @param scene The graphics scene.
    /// @param node The node to draw.
    /// @param x The x-coordinate.
    /// @param y The y-coordinate.
    /// @param hGap The horizontal gap between nodes.
    /// @param vGap The vertical gap between levels.
    /// @param depth The depth of the node in the tree.
    void drawNode(QGraphicsScene& scene, TreeNode* node, int x, int y, int hGap, int vGap, int depth = 0) const {
        if (!node) return;

        std::ostringstream oss;
        oss << node->data.getValue();
        QGraphicsTextItem* textItem = scene.addText(QString::fromStdString(oss.str()));
        textItem->setDefaultTextColor(Qt::white);  // Set the text color to white
        textItem->setZValue(1);  // Ensure the text is drawn on top

        // Determine the rectangle border color and edge color based on the depth
        QColor borderColor, edgeColor;
        edgeColor = borderColor = QColor(29, 35, 189);

        int leftPadding = 25;
        int rightPadding = 25;
        int topPadding = 10;
        int bottomPadding = 10;

        int screen_padding = 10;
        int screen_side_padding = 30;

        // Add a rectangle around the text item with the determined border color and set background color
        QRectF rect = textItem->boundingRect();
        QColor backgroundColor(85, 85, 90); // Set the background color to match the provided image (dark gray)
        QGraphicsRectItem* rectItem = scene.addRect(rect.adjusted(-25, -10, 25, 10), QPen(borderColor, 2), QBrush(backgroundColor));
        rectItem->setPos(x - rect.width() / 2 - 25, y - rect.height() / 2 - 10); // Adjust position to align with text item
        textItem->setPos(x - textItem->boundingRect().width() / 2, y - textItem->boundingRect().height() / 2);

        int childX = x - screen_padding - rect.width() - hGap * (node->children.size() - 1) / 2; // Adjust starting position
        int childY = y + vGap; // Adjust vertical gap

        for (TreeNode* child : node->children) {
            if (child) {
                // Use the edge color for the line
                scene.addLine(x - screen_padding - rect.width() / 2, y + rect.height() / 2,
                              childX , childY - rect.height() / 2, QPen(edgeColor, 2));
                drawNode(scene, child, childX, childY, hGap, vGap, depth + 1);
                childX += hGap;
            }
        }
    }
};

#endif // TREE_HPP
