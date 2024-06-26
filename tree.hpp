#ifndef TREE_HPP
#define TREE_HPP

#include "node.hpp"
#include <iostream>
#include <memory>
#include <queue>
#include <stack>
#include <iterator>
#include <vector>

template<typename T>
class Tree {
private:
    shared_ptr<Node<T>> root;

public:
    Tree() : root(nullptr) {}

    void add_root(const T& data) {
        root = make_shared<Node<T>>(data);
    }

    shared_ptr<Node<T>>& get_root(){
        return root;
    }

    const shared_ptr<Node<T>>& get_root()const{
        return root;
    }

    void add_sub_node( shared_ptr<Node<T>>& parent_node,  T data) {
        if (!parent_node) return;
        auto child= make_shared<Node<T>>(data);
        parent_node->add_child(child);
    }

class PreOrderIterator {
    stack<shared_ptr<Node<T>>> nodeStack;

public:
    explicit PreOrderIterator(shared_ptr<Node<T>> root) {
        if (root) nodeStack.push(root);
    }

    bool operator!=(const PreOrderIterator& other) const {
        return !(nodeStack.empty() && other.nodeStack.empty());
    }

    PreOrderIterator& operator++() {
        if (nodeStack.empty()) return *this;
        auto node = nodeStack.top();
        nodeStack.pop();
         const auto& children = node->get_children();
        for (auto rit = children.rbegin(); rit != children.rend(); ++rit) {
            nodeStack.push(*rit);
        }
        return *this;
    }

    T operator*() const {
        return nodeStack.top()->get_data();
    }
};

PreOrderIterator begin_pre_order(){ return PreOrderIterator(root);}
PreOrderIterator end_pre_order(){return PreOrderIterator(nullptr);}
  



};

#endif // TREE_HPP