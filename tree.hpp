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
    shared_ptr<Node<T>> root; ///< The root node of the tree.
    size_t max_children; ///< Maximum number of children each node can have.

public:
    

    /**
     * @brief Constructor to initialize the tree with a given number of maximum children per node.
     * @param k The maximum number of children per node. Default is 2.
     */
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


    /**
     * @brief Adds a child node to a given parent node.
     * @param parent_node The parent node to which the child will be added.
     * @param data The data to be stored in the child node.
     * @return True if the child node was added successfully, false otherwise.
     */
    bool add_sub_node( shared_ptr<Node<T>>& parent_node,  const T& data) {
        if(parent_node && parent_node-> children.size()<max_children){
            parent_node->children.push_back(make_shared<Node<T>>(data));
            return true;
        }
        return false;
    }

    /**
     * @brief Prints the tree in a level-order fashion.
     */
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
    
    /**
     * @brief Recursively heapifies the tree starting from a given node.
     * @param node The starting node for heapification.
     */

    void heapify(shared_ptr<Node<T>> node){
        if (!node) return;
        for(auto child : node->children){
            heapify(child);
            if(child->data < node->data){
                swap(child->data, node->data);
            }
        }
    }


    /**
     * @brief Heapifies the entire tree.
     */
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

    
// PreOrderIterator class to traverse the tree in pre-order
class PreOrderIterator {
    stack<shared_ptr<Node<T>>> nodeStack;   ///< Stack to manage nodes during traversal.

public:

    /**
     * @brief Constructor initializes the iterator with the root node.
     * @param root The root node of the tree.
     */
    explicit PreOrderIterator(shared_ptr<Node<T>> root) {
        if (root) nodeStack.push(root);
    }


    /**
    * @brief Inequality operator to compare two iterators.
    * @param other The other iterator to compare with.
    * @return True if the iterators are not equal, false otherwise.
    */
    bool operator!=(const PreOrderIterator& other) const {
        return !(nodeStack.empty() && other.nodeStack.empty());
    }


    /**
    * @brief Prefix increment operator to advance the iterator.
    * @return A reference to the advanced iterator.
    */
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


    /**
    * @brief Dereference operator to access the data of the current node.
    * @return The data of the current node.
    */
     const T& operator*() const {
        return nodeStack.top()->get_data();
    }
};


// BFSIterator class to traverse the tree in breadth-first order
class BFSIterator{
private:
    queue<shared_ptr<Node<T>>> nodeQueue;   ///< Queue to manage nodes during traversal.

public:


    /**
     * @brief Constructor initializes the iterator with the root node.
     * @param root The root node of the tree.
    */
    BFSIterator(shared_ptr<Node<T>> root){
        if(root) nodeQueue.push(root);
    }


    /**
     * @brief Inequality operator to compare two iterators.
     * @param other The other iterator to compare with.
     * @return True if the iterators are not equal, false otherwise.
    */
    bool operator != (const BFSIterator& other) const{
        return !nodeQueue.empty() || !other.nodeQueue.empty();
    }




    /**
     * @brief Prefix increment operator to advance the iterator.
     * @return A reference to the advanced iterator.
    */
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


    /**
     * @brief Dereference operator to access the data of the current node.
     * @return The data of the current node.
    */
    T& operator*() const{
        return nodeQueue.front()->data;
    }

};



// PostOrderIterator class to traverse the tree in post-order
class PostOrderIterator {
    private:
    stack<shared_ptr<Node<T>>> stack1, stack2; ///< Stacks to manage nodes during traversal.
    shared_ptr<Node<T>> current; ///< The current node.

    public:

        /**
         * @brief Constructor initializes the iterator with the root node.
         * @param root The root node of the tree.
         */
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

        /**
         * @brief Inequality operator to compare two iterators.
         * @param other The other iterator to compare with.
         * @return True if the iterators are not equal, false otherwise.
         */   
        bool operator!=(const PostOrderIterator& other) const {
            return current != other.current;
        }



        /**
         * @brief Prefix increment operator to advance the iterator.
         * @return A reference to the advanced iterator.
         */
        PostOrderIterator& operator++() {
            if (!stack2.empty()) {
                current = stack2.top();
                stack2.pop();
            } else {
                current = nullptr;
            }
            return *this;
        }


        /**
         * @brief Dereference operator to access the data of the current node.
         * @return The data of the current node.
         */
        T& operator*() const {
            return current->data;
        }
    };




    // InOrderIterator class to traverse the tree in in-order
    class InOrderIterator {
    private:
        stack<shared_ptr<Node<T>>> stack; ///< Stack to manage nodes during traversal.
        shared_ptr<Node<T>> currentNode; ///< The current node.


    public:

         /**
         * @brief Constructor initializes the iterator with the root node.
         * @param node The root node of the tree.
         */
        InOrderIterator(shared_ptr<Node<T>> node):currentNode(node)  {
            pushLeftMost(node); // Initially push all left children to stack
       
        }


        /**
         * @brief Pushes all the left children of the node to the stack.
         * @param node The starting node to push leftmost children from.
         */
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

        
        /**
         * @brief Inequality operator to compare two iterators.
         * @param other The other iterator to compare with.
         * @return True if the iterators are not equal, false otherwise.
         */
        bool operator!=(const InOrderIterator& other) const {
            return !stack.empty(); // Continue until stack is not empty        
            }


        /**
         * @brief Prefix increment operator to advance the iterator.
         * @return A reference to the advanced iterator.
         */
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

class DFSIterator {
    private:
        stack<shared_ptr<Node<T>>> nodeStack;  ///< Stack to manage nodes during DFS traversal.

    public:
        /**
         * @brief Constructor initializes the iterator with the root node.
         * @param root The root node of the tree.
         */
        DFSIterator(shared_ptr<Node<T>> root) {
            if (root) nodeStack.push(root);
        }

        /**
         * @brief Inequality operator to compare two iterators.
         * @param other The other iterator to compare with.
         * @return True if the iterators are not equal, false otherwise.
         */
        bool operator!=(const DFSIterator& other) const {
            return !nodeStack.empty();
        }

        /**
         * @brief Prefix increment operator to advance the iterator.
         * Pops the current node from the stack and pushes its children onto the stack in reverse order.
         * @return A reference to the advanced iterator.
         */
        DFSIterator& operator++() {
            if (!nodeStack.empty()) {
                auto node = nodeStack.top();
                nodeStack.pop();
                for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
                    nodeStack.push(*it);
                }
            }
            return *this;
        }

        /**
         * @brief Dereference operator to access the data of the current node.
         * @return The data of the current node.
         */
        T& operator*() const {
            return nodeStack.top()->data;
        }
    };

    // Functions to get iterators for different traversal methods

    /**
     * @brief Returns a PreOrderIterator pointing to the beginning of the tree.
     * @return A PreOrderIterator pointing to the root node.
     */
    PreOrderIterator begin_pre_order() { return PreOrderIterator(root); }

    /**
     * @brief Returns a PreOrderIterator pointing to the end of the tree.
     * Used as a sentinel value.
     * @return A PreOrderIterator pointing to a null node.
     */
    PreOrderIterator end_pre_order() { return PreOrderIterator(nullptr); }

    /**
     * @brief Returns a BFSIterator pointing to the beginning of the tree.
     * @return A BFSIterator pointing to the root node.
     */
    BFSIterator begin_bfs_scan() { return BFSIterator(root); }

    /**
     * @brief Returns a BFSIterator pointing to the end of the tree.
     * Used as a sentinel value.
     * @return A BFSIterator pointing to a null node.
     */
    BFSIterator end_bfs_scan() { return BFSIterator(nullptr); }

    /**
     * @brief Returns a PostOrderIterator pointing to the beginning of the tree.
     * @return A PostOrderIterator pointing to the root node.
     */
    PostOrderIterator begin_post_order() { return PostOrderIterator(root); }

    /**
     * @brief Returns a PostOrderIterator pointing to the end of the tree.
     * Used as a sentinel value.
     * @return A PostOrderIterator pointing to a null node.
     */
    PostOrderIterator end_post_order() { return PostOrderIterator(nullptr); }

    /**
     * @brief Returns an InOrderIterator pointing to the beginning of the tree.
     * @return An InOrderIterator pointing to the root node.
     */
    InOrderIterator begin_in_order() { return InOrderIterator(root); }

    /**
     * @brief Returns an InOrderIterator pointing to the end of the tree.
     * Used as a sentinel value.
     * @return An InOrderIterator pointing to a null node.
     */
    InOrderIterator end_in_order() { return InOrderIterator(nullptr); }

    /**
     * @brief Returns a DFSIterator pointing to the beginning of the tree.
     * @return A DFSIterator pointing to the root node.
     */
    DFSIterator begin_dfs_scan() { return DFSIterator(root); }

    /**
     * @brief Returns a DFSIterator pointing to the end of the tree.
     * Used as a sentinel value.
     * @return A DFSIterator pointing to a null node.
     */
    DFSIterator end_dfs_scan() { return DFSIterator(nullptr); }

};  
#endif // TREE_HPP