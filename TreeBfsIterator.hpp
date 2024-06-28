// TreeBfsIterator.hpp

#ifndef TREEBFSITERATOR_HPP
#define TREEBFSITERATOR_HPP

#include <queue>
#include <memory>
#include "Node.hpp"

template <typename T>
class Tree;

template <typename T, int K = 2>
class BfsIterator {
private:
    std::queue<std::shared_ptr<Node<T>>> queue;

public:
    BfsIterator(std::shared_ptr<Node<T>> root);

    bool operator!=(const BfsIterator &other) const;

    BfsIterator &operator++();

    Node<T> &operator*();

    Node<T> *operator->();
};

#include "TreeBfsIterator.tpp"

#endif // TREEBFSITERATOR_HPP
