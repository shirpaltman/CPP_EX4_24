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
    size_t max_children;
public:
    
    Tree(size_t k=2) : root(nullptr) ,max_children(k) {}

    void add_root(const T& data) {
        root = make_shared<Node<T>>(data);
    }

    shared_ptr<Node<T>>& get_root(){
        return root;
    }

    const shared_ptr<Node<T>>& get_root()const{
        return root;
    }

    bool add_sub_node( shared_ptr<Node<T>>& parent_node,  const T& data) {
        if(parent_node && parent_node-> children.size()<max_children){
            parent_node->children.push_back(make_shared<Node<T>>(data));
            return true;
        }
        return false;
    }

    void printTree() {
        if (!root) {
            std::cout << "The tree is empty." << std::endl;
            return;
        }

        queue<shared_ptr<Node<T>>> queue;
        queue.push(root);
        while (!queue.empty()) {
            int levelSize = queue.size();
            for (int i = 0; i < levelSize; ++i) {
                auto node = queue.front();
                queue.pop();
                std::cout << node->data << " has children: ";
                for (auto& child : node->children) {
                    std::cout << child->data << " ";
                    queue.push(child);
                }
                std::cout << std::endl;
            }
            std::cout << "-----" << std::endl;
        }
    }
    


    void heapify(shared_ptr<Node<T>> node){
        if (!node) return;
        for(auto child : node->children){
            heapify(child);
            if(child->data < node->data){
                swap(child->data, node->data);
            }
        }
    }

    void myHeap(){
        if (!root) return;
        queue<shared_ptr<Node<T>>> queue;
        queue.push(root);
        while(!queue.empty()){
            auto node = queue.front();
            queue.pop();
            heapify(node);
            for(auto child : node->children){
                queue.push(child);
            }
        }
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

     const T& operator*() const {
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
        stack<shared_ptr<Node<T>>> stack;
        shared_ptr<Node<T>> currentNode;


    public:
        InOrderIterator(shared_ptr<Node<T>> node):currentNode(node)  {
            pushLeftMost(node); // Initially push all left children to stack
       
        }

        void pushLeftMost(shared_ptr<Node<T>> node) {
            auto n = node;
            while (n != nullptr) {
                stack.push(n);
                if (!n->children.empty()) {
                    n = n->children[0];  // Push leftmost children to the stack
                } else {
                    break;
                }
            }
        }

        

        bool operator!=(const InOrderIterator& other) const {
            return !stack.empty(); // Continue until stack is not empty        
            }

        InOrderIterator& operator++() {
            if (stack.empty()) return *this;

            auto node = stack.top();
            stack.pop();

            if (node->children.size() > 1) {
                pushLeftMost(node->children[1]);  // Push the leftmost nodes of the right subtree
            }

            return *this;
        }
        const T& operator*() const {
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