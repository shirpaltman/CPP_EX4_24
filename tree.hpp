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

    void add_root(const T& data) {
        root = make_shared<Node<T>>(data);
    }

    shared_ptr<Node<T>>& get_root(){
        return root;
    }

    const shared_ptr<Node<T>>& get_root()const{
        return root;
    }

    void add_sub_node( shared_ptr<Node<T>>& parent_node,  const T& data) {
        if (!parent_node) return;
        auto child= make_shared<Node<T>>(data);
        parent_node->add_child(child);
    }

  



};

#endif // TREE_HPP