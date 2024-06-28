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

template <typename T, int K = 2>
class Tree {
    struct TreeNode {
        Node<T> data;
        std::vector<TreeNode*> children;
        TreeNode(Node<T> val) : data(val) {}
    };

    TreeNode* root;

public:
    Tree() : root(nullptr) {}

    ~Tree() {
        clear(root);
    }

    void add_root(Node<T> val) {
        if (root) {
            root->data = val;
        } else {
            root = new TreeNode(val);
        }
    }

    void add_sub_node(Node<T> parent_val, Node<T> child_val) {
        TreeNode* parent = find(root, parent_val);
        if (parent && parent->children.size() < K) {
            parent->children.push_back(new TreeNode(child_val));
        }
    }

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

    PreOrderIterator begin_pre_order() {
        return PreOrderIterator(root);
    }

    PreOrderIterator end_pre_order() {
        return PreOrderIterator(nullptr);
    }

    class PostOrderIterator {
        std::stack<TreeNode*> nodes;
        std::stack<bool> visited;
    public:
        PostOrderIterator(TreeNode* root) {
            if (root) {
                nodes.push(root);
                visited.push(false);
            }
        }

        bool operator!=(const PostOrderIterator& other) const {
            return !nodes.empty();
        }

        Node<T>& operator*() const {
            return nodes.top()->data;
        }

        PostOrderIterator& operator++() {
            TreeNode* node = nodes.top();
            if (visited.top()) {
                nodes.pop();
                visited.pop();
            } else {
                visited.top() = true;
                for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
                    nodes.push(*it);
                    visited.push(false);
                }
            }
            return *this;
        }
    };

    PostOrderIterator begin_post_order() {
        return PostOrderIterator(root);
    }

    PostOrderIterator end_post_order() {
        return PostOrderIterator(nullptr);
    }

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

    InOrderIterator begin_in_order() {
        return InOrderIterator(root);
    }

    InOrderIterator end_in_order() {
        return InOrderIterator(nullptr);
    }

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

    BFSIterator begin_bfs_scan() {
        return BFSIterator(root);
    }

    BFSIterator end_bfs_scan() {
        return BFSIterator(nullptr);
    }

    // Iterable to support range-based for loop
    BFSIterator begin() {
        return begin_bfs_scan();
    }

    BFSIterator end() {
        return end_bfs_scan();
    }

    friend std::ostream& operator<<(std::ostream& os, const Tree& tree) {
tree.printTreeGUI();
return os;
    }

void printTreeGUI() const {
    if (!root) return;

    QGraphicsScene* scene = new QGraphicsScene();
    QGraphicsView* view = new QGraphicsView(scene);

    std::queue<std::pair<TreeNode*, QPointF>> nodes;
    nodes.push({root, QPointF(0, 0)});

    while (!nodes.empty()) {
        auto [node, pos] = nodes.front();
        nodes.pop();

        QGraphicsTextItem* item = scene->addText(QString::number(node->data.get_value()));
        item->setPos(pos);

        float offset = 50.0; // adjust the offset as needed
        for (size_t i = 0; i < node->children.size(); ++i) {
            nodes.push({node->children[i], QPointF(pos.x() + (i - node->children.size() / 2) * offset, pos.y() + 50)});
        }
    }

    view->show();
    QCoreApplication::exec(); // Start the Qt event loop
}


private:
    void clear(TreeNode* node) {
        if (node) {
            for (auto child : node->children) {
                clear(child);
            }
            delete node;
        }
    }

    TreeNode* find(TreeNode* node, Node<T> val) {
        if (!node) return nullptr;
        if (node->data == val) return node;
        for (auto child : node->children) {
            TreeNode* found = find(child, val);
            if (found) return found;
        }
        return nullptr;
    }
};

#endif // TREE_HPP
