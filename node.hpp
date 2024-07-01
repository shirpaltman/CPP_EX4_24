#ifndef NODE_H
#define NODE_H

#include <vector>
#include <memory>
using namespace std;
template<typename T>
class Node {
    
public:

    T data;
    vector<shared_ptr<Node<T>>> children;


    //Constructor
    Node(T data) : data(data){}

    //Method to add a child node
    void add_child(shared_ptr<Node<T>> child){
        children.push_back(child);
    }


     /**
     * @brief Get the data stored in the node (const version).
     * @return The data stored in the node.
     */
     const T& get_data() const {
        return data;
    }

    
    
    /**
     * @brief Get a modifiable list of children.
     * @return The list of child nodes.
     */
    vector<shared_ptr<Node<T>>>& get_children()  {
        return children;
    }


    /**
     * @brief Get a non-modifiable list of children.
     * @return The list of child nodes.
     */
    const vector<shared_ptr<Node<T>>>& get_children()const{
        return children;
    }

   
    
};

#endif // NODE_HPP