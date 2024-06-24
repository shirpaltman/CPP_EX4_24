#ifndef TREE_ITERATORS_HPP
#define TREE_ITERATORS_HPP

#include "tree.hpp"
#include <stack>
#include <queue>

// Define PreOrderIterator inside the Tree class definition
template<typename T>
class Tree<T>::PreOrderIterator {
    std::stack<std::shared_ptr<Node<T>>> nodeStack;

public:
    explicit PreOrderIterator(std::shared_ptr<Node<T>> root) {
        if (root) nodeStack.push(root);
    }

    bool operator!=(const PreOrderIterator& other) const {
        return !(*this == other);
    }

    PreOrderIterator& operator++() {
        if (nodeStack.empty()) return *this;
        auto node = nodeStack.top();
        nodeStack.pop();
        auto& children = node->get_children();
        for (auto it = children.rbegin(); it != children.rend(); ++it) {
            nodeStack.push(*it);
        }
        return *this;
    }

    T operator*() const {
        return nodeStack.top()->get_value();
    }
};

// Implement other iterators similarly...

#endif // TREE_ITERATORS_HPP