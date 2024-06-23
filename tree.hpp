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
    shared_ptr<Node<T>> root;

public:
    Tree() : root(nullptr) {}

    void add_root(const T& value) {
        root = make_shared<Node<T>>(value);
    }

    shared_ptr<Node<T>>& get_root(){
        return root;
    }

    const shared_ptr<Node<T>>& get_root()const{
        return root;
    }

    void add_sub_node( shared_ptr<Node<T>>& parent_node,  const T& value) {
        if (!parent_node) return;
        auto child= make_shared<Node<T>>(value);
        parent_node->add_child(child);
    }

  

template<typename T>
class PreOrderIterator {
    stack<shared_ptr<Node<T>>> stack;

public:
    PreOrderIterator(shared_ptr<Node<T>> root) {
        if (root){
            stack.push(root);
        } 
    }
    bool operator!=(const PreOrderIterator& other) const {
        return!(this* ==other);

    }


    PreOrderIterator& operator++(){
        if(stack.empty()) return *this;
        auto current_node = stack.top();
        stack.pop();
        auto children = node->get_children();
        for (auto it = children.rbegin(); it != children.rend(); ++it) {
            stack.push(*it);
        }
    }
    bool operator ==(const PreOrderIterator& other)const{
        return(other.stack.empty()&&stack.empty())  || (!other.stack.empty() !stack.empty() && other.stack.top ==stack.top());
        
    }
    T operator*()const{
        return stack.top()->get_value();
    }

    bool has_next() const {
        return !stack.empty();
    }

    std::shared_ptr<Node<T>> next() {
        if (stack.empty()) throw std::out_of_range("Iterator out of range");
        auto node = stack.top();
        stack.pop();
        const auto& children = node->get_children();
        for (auto it = children.rbegin(); it != children.rend(); ++it) {
            stack.push(*it);
        }
        return node;
    }

    PreOrderIterator begin_pre_order() { return PreOrderIterator(root); }
    PreOrderIterator end_pre_order() { return PreOrderIterator(nullptr); }

};
};

#endif // TREE_HPP