#ifndef NODE_HPP
#define NODE_HPP

template <typename T>
class Node {
    T value;
public:
    Node(T val) : value(val) {}

    T get_value() const { return value; }
    void set_value(T val) { value = val; }

    bool operator==(const Node& other) const {
        return value == other.value;
    }
};

#endif // NODE_HPP
