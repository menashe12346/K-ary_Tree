#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <string>
#include <sstream>

/// A template class representing a node in a tree.
template <typename T>
class Node {
    T value; ///< The value of the node.
public:
    /// Constructor to initialize the node with a value.
    /// @param val The value to initialize the node with.
    Node(T val) : value(val) {}

    /// Get the value of the node.
    /// @return The value of the node.
    T getValue() {
        return value;
    }

    /// Convert the node value to a string.
    /// @return The string representation of the node value.
    std::string toString() const {
        std::ostringstream oss;
        oss << value;
        return oss.str();
    }

    /// Get the value of the node (const version).
    /// @return The value of the node.
    T get_value() const { return value; }

    /// Set the value of the node.
    /// @param val The value to set.
    void set_value(T val) { value = val; }

    /// Equality operator to compare two nodes.
    /// @param other The other node to compare with.
    /// @return True if the nodes have the same value, false otherwise.
    bool operator==(const Node& other) const {
        return value == other.value;
    }

    /// Inequality operator to compare two nodes.
    /// @param other The other node to compare with.
    /// @return True if the nodes have different values, false otherwise.
    bool operator!=(const Node& other) const {
        return value != other.value;
    }

    /// Less-than operator to compare two nodes.
    /// @param other The other node to compare with.
    /// @return True if this node's value is less than the other node's value.
    bool operator<(const Node& other) const {
        return value < other.value;
    }

    /// Greater-than operator to compare two nodes.
    /// @param other The other node to compare with.
    /// @return True if this node's value is greater than the other node's value.
    bool operator>(const Node& other) const {
        return value > other.value;
    }

    /// Less-than or equal-to operator to compare two nodes.
    /// @param other The other node to compare with.
    /// @return True if this node's value is less than or equal to the other node's value.
    bool operator<=(const Node& other) const {
        return value <= other.value;
    }

    /// Greater-than or equal-to operator to compare two nodes.
    /// @param other The other node to compare with.
    /// @return True if this node's value is greater than or equal to the other node's value.
    bool operator>=(const Node& other) const {
        return value >= other.value;
    }
};

#endif // NODE_HPP
