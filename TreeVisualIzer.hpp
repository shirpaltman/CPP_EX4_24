#ifndef TREE_VISUALIZER_HPP
#define TREE_VISUALIZER_HPP

#include <SFML/Graphics.hpp>
#include "node.hpp"  

template<typename T>
class TreeVisualizer {
public:
    static void showTree(const std::shared_ptr<Node<T>>& root);
};

#include "TreeVisualizer.tpp" // Template implementation

#endif