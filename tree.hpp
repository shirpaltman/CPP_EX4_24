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

    ~Tree(){
        root.reset();
    }
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



class BFSIterator{
private:
    queue<shared_ptr<Node<T>>> nodeQueue;

public:
    BFSIterator(shared_ptr<Node<T>> root){
        if(root) nodeQueue.push(root);
    }

    bool operator != (const BFSIterator& other) const{
        return !nodeQueue.empty() || !other.nodeQueue.empty();
    }


    BFSIterator& operator++(){
        if (!nodeQueue.empty()){
            auto node = nodeQueue.front();
            nodeQueue.pop();
            for(auto& child : node -> children){
                nodeQueue.push(child);
            }
        }
        return *this;
    }

    T& operator*() const{
        return nodeQueue.front()->data;
    }

};




class PostOrderIterator {
    private:
    stack<shared_ptr<Node<T>>> stack1, stack2;
    shared_ptr<Node<T>> current;

    public:
        PostOrderIterator(std::shared_ptr<Node<T>> root) {
            if (root) {
                stack1.push(root);
                while (!stack1.empty()) {
                    auto node = stack1.top();
                    stack1.pop();
                    stack2.push(node);
                    for (auto& child : node->children) {
                        stack1.push(child);
                    }
                }
                if (!stack2.empty()) {
                    current = stack2.top();
                    stack2.pop();
                } else {
                    current = nullptr;
                }
            } else {
                current = nullptr;
            }
        }

        bool operator!=(const PostOrderIterator& other) const {
            return current != other.current;
        }

        PostOrderIterator& operator++() {
            if (!stack2.empty()) {
                current = stack2.top();
                stack2.pop();
            } else {
                current = nullptr;
            }
            return *this;
        }

        T& operator*() const {
            return current->data;
        }
    };





    class InOrderIterator {
    private:
        std::stack<std::shared_ptr<Node<T>>> stack;
        std::shared_ptr<Node<T>> currentNode;

    public:
        InOrderIterator(std::shared_ptr<Node<T>> node) : currentNode(node) {
            pushLeftMost(node); // Initially push all left children to stack
        }

        void pushLeftMost(std::shared_ptr<Node<T>> node) {
            // Push all left children to the stack
            while (node != nullptr) {
                stack.push(node);
                if (!node->children.empty()) {
                    node = node->children[0]; // Assuming left child is always the first child
                } else {
                    break; // No more children, stop the loop
                }
            }
        }

        bool operator!=(const InOrderIterator& other) const {
            return !stack.empty(); // Continue until stack is not empty
        }

        InOrderIterator& operator++() {
            shared_ptr<Node<T>> node = stack.top();
            stack.pop();
            if (node->children.size() > 1) {
                pushLeftMost(node->children[1]); // Assuming right child is the second child
            }
            return *this;
        }

        T& operator*() const {
            return stack.top()->data;
        }
    
};


class DFSIterator{
    private:
        stack<shared_ptr<Node<T>>> nodeStack;
    public:
        DFSIterator(shared_ptr<Node<T>> root){
            if(root) nodeStack.push(root);
        }

        bool operator != (const DFSIterator& other )const{
            return !nodeStack.empty();
        }

        DFSIterator& operator++(){
            if(!nodeStack.empty()){
                auto node = nodeStack.top();
                nodeStack.pop();
                for(auto it = node->children.rbegin();it !=node->children.rend(); ++it){
                    nodeStack.push(*it);
                }
            }
            return *this;
        }

        T& operator*() const{
            return nodeStack.top()->data;
        }
    };




PreOrderIterator begin_pre_order(){ return PreOrderIterator(root);}
PreOrderIterator end_pre_order(){return PreOrderIterator(nullptr);}
  
BFSIterator begin_bfs_scan(){return BFSIterator(root);}
BFSIterator end_bfs_scan(){return BFSIterator(nullptr);}

PostOrderIterator begin_post_order(){return PostOrderIterator(root);}
PostOrderIterator end_post_order(){return PostOrderIterator(nullptr);}

InOrderIterator begin_in_order() { return InOrderIterator(root); }
InOrderIterator end_in_order() { return InOrderIterator(nullptr); }


DFSIterator begin_dfs_scan() { return DFSIterator(root); }
DFSIterator end_dfs_scan() { return DFSIterator(nullptr); }

};  
#endif // TREE_HPP