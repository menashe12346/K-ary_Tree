#ifndef TREE_HPP
#define TREE_HPP

#include "Node.hpp"
#include "Complex.hpp"
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

using namespace std;

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

    /// Pre-order traversal iterator. dfs output = pre_order output here
    class PreOrderIterator {
        std::stack<TreeNode*> nodes;
    public:
        PreOrderIterator(TreeNode* root) {
            if (root) nodes.push(root);
        }

        // using this only to check inequality with the PreOrderIterator(nullptr)
        bool operator!=(const PreOrderIterator& other) const {
            (void)other; // Explicitly mark as unused
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

    /// Post-order traversal iterator. run dfs if non binary
    class PostOrderIterator {
        std::stack<TreeNode*> nodes;
        std::stack<TreeNode*> output;
    public:
        PostOrderIterator(TreeNode* root) {
            if(K==2){
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
            } else{
                if (root) nodes.push(root);
            }
        }
        // using this only to check inequality with the PreOrderIterator(nullptr)
        bool operator!=(const PostOrderIterator& other) const {
            (void)other; // Explicitly mark as unused
            if(K==2){
            return !output.empty();
            } else {
                return !nodes.empty();
            }
        }

        Node<T>& operator*() const {
            if(K==2){
                return output.top()->data;
            } else {
                return nodes.top()->data;
            }
        }

        PostOrderIterator& operator++() {
            if(K==2){
                output.pop();
            }else{
                TreeNode* node = nodes.top();
                nodes.pop();
                for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
                nodes.push(*it);
                }
            }
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

    /// In-order traversal iterator. run dsf if non binary
    class InOrderIterator {
        std::stack<TreeNode*> nodes;
        TreeNode* current;
    public:
        InOrderIterator(TreeNode* root) : current(root) {
            if(K==2){
                while (current && !current->children.empty()) {
                    nodes.push(current);
                    current = current->children.front();
                }
            } else{
                if (root) nodes.push(root);
            }
        }

        // using this only to check inequality with the PreOrderIterator(nullptr)
        bool operator!=(const InOrderIterator& other) const {
            (void)other; // Explicitly mark as unused
            if(K ==2){
                return current != nullptr;
            } else{
                return !nodes.empty();
            }
        }

        Node<T>& operator*() const {
            if(K==2){
                return current->data;
            } else {
                return nodes.top()->data;
            }
        }

        InOrderIterator& operator++() {
            if(K==2){
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
            }else{
                TreeNode* node = nodes.top();
                nodes.pop();
                for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
                nodes.push(*it);
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

        // using this only to check inequality with the PreOrderIterator(nullptr)
        bool operator!=(const BFSIterator& other) const {
            (void)other; // Explicitly mark as unused
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

        // using this only to check inequality with the PreOrderIterator(nullptr)
        bool operator!=(const DFSIterator& other) const {
            (void)other; // Explicitly mark as unused
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
    DFSIterator begin_dfs_scan() {
        return DFSIterator(root);
    }

    /// End DFS traversal.
    /// @return DFSIterator at the end.
    DFSIterator end_dfs_scan() {
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
                // std::greater<Node<T>>: A comparison function that ensures a min-heap is created.
                std::make_heap(heap.begin(), heap.end(), std::less<Node<T>>()); // organize the elements in the heap vector into a heap structure
                std::sort_heap(heap.begin(), heap.end(), std::less<Node<T>>()); // To sort the elements of the heap in ascending order.
            }
        }

        // using this only to check inequality with the PreOrderIterator(nullptr)
        bool operator!=(const HeapIterator& other) const {
            (void)other; // Explicitly mark as unused
            return index != heap.size();
        }

        Node<T>& operator*() {
            return heap[index];
        }

        HeapIterator& operator++() {
            ++index;
            return *this;
        }

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

    /// Convert the tree to a vector of nodes.
    /// @param node The root node of the subtree to convert.
    /// @param nodes The vector to store the nodes.
    void toHeapVector(TreeNode* node, std::vector<TreeNode*>& nodes) {
        if (node) {
            nodes.push_back(node);
            for (auto child : node->children) {
                toHeapVector(child, nodes);
            }
        }
    }

    /// Convert a binary tree into a heap structure.
    void myHeap() {
        if(K==2){
            // If the tree is empty, return immediately.
            if (!root) return;

            // Create a vector to store nodes.
            std::vector<TreeNode*> nodes;
            // Populate the vector with nodes from the tree.
            toHeapVector(root, nodes);

            // Sort the nodes in ascending order based on their values.
            std::sort(nodes.begin(), nodes.end(), [](TreeNode* a, TreeNode* b) {
                return a->data < b->data;
            });

            // Clear the children of each node and reassign them according to heap order.
            for (size_t i = 0; i < nodes.size(); ++i) {
                nodes[i]->children.clear();
                if (2 * i + 1 < nodes.size()) {
                    nodes[i]->children.push_back(nodes[2 * i + 1]);
                }
                if (2 * i + 2 < nodes.size()) {
                    nodes[i]->children.push_back(nodes[2 * i + 2]);
                }
            }

            // Set the first element of the sorted vector as the new root of the tree.
            root = nodes[0];
        }else{
            cout<< "tree is not binary"<< endl;
        }
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
        int startY = 50;  // Start slightly from the top for better visibility
        int hGap = 200 * (K - 1); // Horizontal gap between nodes
        int vGap = 100; // Vertical gap between levels

        drawNode(scene, root, startX, startY, hGap, vGap);

        // Create a view to visualize the scene
        QGraphicsView view(&scene);
        // Enable antialiasing for smoother rendering of graphics.
        view.setRenderHint(QPainter::Antialiasing);

        // Set the viewport update mode to optimize performance for larger scenes.
        view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

        // Set a gradient background for a more professional look.
        QLinearGradient gradient(0, 0, 0, 800);
        gradient.setColorAt(0, QColor(60, 60, 60)); // Darker gray at the top.
        gradient.setColorAt(1, QColor(30, 30, 30)); // Even darker gray at the bottom.
        view.setBackgroundBrush(gradient);

        // Set the window title for the graphics view.
        view.setWindowTitle("Tree Visualization");

        // Define the fixed size of the view window.
        view.setFixedSize(1600, 900);
        scene.setSceneRect(0, 0, 1500, 800); // Set the scene's rectangle size to match the view.

        // Display the view.
        view.show();

        // Start the Qt event loop to handle user interaction and updates.
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

        // Add a rectangle around the text item with the determined border color and set background color
        QRectF rect = textItem->boundingRect();
        QColor backgroundColor(85, 85, 90); // Set the background color to match the provided image (dark gray)
        QGraphicsRectItem* rectItem = scene.addRect(rect.adjusted(-25, -10, 25, 10), QPen(borderColor, 2), QBrush(backgroundColor));
        rectItem->setPos(x - rect.width() / 2 - 25, y - rect.height() / 2 - 10); // Adjust position to align with text item
        // Calculate the rectangle's center position
        int rectCenterX = x - rect.width() / 2 - 25;
        int rectCenterY = y - rect.height() / 2 - 10;
        // Set the position of the text item to be in the center of the rectangle
        textItem->setPos(rectCenterX + rect.width() / 2 - textItem->boundingRect().width() / 2,
                        rectCenterY + rect.height() / 2 - textItem->boundingRect().height() / 2);

        int screen_padding = 10;
        int childY = y + vGap; // Adjust vertical gap
        int numChildren = node->children.size();
        int childXLow=0; // for left nodes
        int childXHigh=x - screen_padding + hGap; // for right nodes
        if (numChildren > 0) {
            int totalWidth;
            if(numChildren%2!=0){ // if num of children is odd
                totalWidth = ((numChildren-1) * hGap) / 2; // so i wont count the one on the middle
            } else{
                totalWidth = (numChildren * hGap) / 2;
            }
            childXLow = x - totalWidth - screen_padding;
        }

        int numOfChild = 0;
        for (TreeNode* child : node->children) 
        {
            if (child) {
                if(numOfChild < numChildren/2 || K == 1){
                    // Use the edge color for the line
                    scene.addLine(x - screen_padding - rect.width() / 2, y + rect.height() / 2,
                                childXLow - rect.width()  , childY - rect.height() / 2 - screen_padding, QPen(edgeColor, 2));
                    drawNode(scene, child, childXLow, childY, hGap - hGap/3, vGap, depth + 1);
                    childXLow += hGap;
                } else if(numOfChild >= numChildren/2){
                    if(!(numChildren%2!=0 && numOfChild == numChildren/2) || numChildren==1){// if the node in the middle
                        scene.addLine(x - screen_padding - rect.width() / 2, y + rect.height() / 2,
                        childXHigh + rect.width()/2, childY - rect.height() / 2 - screen_padding, QPen(edgeColor, 2));
                        drawNode(scene, child, childXHigh  ,childY, hGap - hGap/3 , vGap, depth + 1);
                    childXHigh += hGap;
                    } else{
                        scene.addLine(x - screen_padding - rect.width() / 2, y + rect.height() / 2,
                                    x - screen_padding - rect.width() / 2 , childY - rect.height() / 2 - screen_padding, QPen(edgeColor, 2));
                        drawNode(scene, child, x, childY, hGap - hGap/3, vGap, depth + 1);
                    }
                }
            }
        numOfChild++;
        }
    }
};

#endif
