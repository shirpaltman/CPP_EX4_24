/**
 * Demo app for Ex4
 */
#include <iostream>
#include <memory>
#include <string>
#include "node.hpp"
#include "tree.hpp"
#include <SFML/Graphics.hpp>
#include "TreeVisualIzer.hpp"

using namespace std;
using namespace sf;


int main()
{

    Tree<double> tree; // Binary tree that contains doubles.
    tree.add_root(1.1);
    auto root = tree.get_root();
    tree.add_sub_node(root, 1.2);
    tree.add_sub_node(root, 1.3);

    auto& children = root->get_children();
    tree.add_sub_node(children[0], 1.4);
    tree.add_sub_node(children[0], 1.5);
    tree.add_sub_node(children[1], 1.6);
    // The tree should look like:
    /**
     *       root = 1.1
     *     /       \
     *    1.2      1.3
     *   /  \      /
     *  1.4  1.5  1.6
     */


    Tree<double> three_ary_tree(3); // Initialize a 3-ary tree
    auto rootH = three_ary_tree.get_root();
    three_ary_tree.add_root(1.1);  // Setting the root
    rootH = three_ary_tree.get_root();

    three_ary_tree.add_sub_node(rootH, 1.2);
    three_ary_tree.add_sub_node(rootH, 1.3);
    three_ary_tree.add_sub_node(rootH, 1.4);


     // The tree should look like:
    /**
     *       root = 1.1
     *     /      |     \
     *    1.2    1.3    1.4
     *   /        |
     *  1.5      1.6
     */

    // Attempt to add a fourth child to the root
    bool added = three_ary_tree.add_sub_node(rootH, 1.5);
    if (!added) {
        cout << "Failed to add more than 3 children to the root node.\n";
    }

    TreeVisualizer<double> visualizer;
    Font font;
    if (!font.loadFromFile("/home/shiraltman/Downloads/Roboto-BoldItalic.ttf")) {
        cerr << "Failed to load font\n";
        return -1;
    }

   // Create a window for the binary tree visualization
    RenderWindow window(VideoMode(800, 600), "Binary Tree Visualization");
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        visualizer.showTree(tree.get_root(),window,font);
        window.display();
    }

    // Create a separate window for the 3-ary tree visualization
    RenderWindow three_ary_window(VideoMode(800, 600), "3-ary Tree Visualization");
    while (three_ary_window.isOpen()) {
        Event event;
        while (three_ary_window.pollEvent(event)) {
            if (event.type == Event::Closed)
                three_ary_window.close();
        }

        three_ary_window.clear(Color::Black);
        visualizer.showTree(three_ary_tree.get_root(),three_ary_window,font);
        three_ary_window.display();
    }
        
    

    for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it){
        cout << *it << " ";
            
            // Optionally, pause or slow down the display here
        }
        cout << endl;

        // Display updates and wait for close
        
    

    //Display post-order traversal
    cout <<"Post-order Traversal of the Binary Tree:" << endl;
    for (auto it = tree.begin_post_order(); it != tree.end_post_order(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl; // prints: 1.4, 1.5, 1.2, 1.6, 1.3, 1.1



    cout <<"In-order Traversal of the Binary Tree:" << endl;

    for (auto it = tree.begin_in_order(); it != tree.end_in_order(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl; // prints: 1.4, 1.2, 1.5, 1.1, 1.6, 1.3


    cout <<"BFS Traversal of the Binary Tree:" << endl;
    for (auto it = tree.begin_bfs_scan(); it != tree.end_bfs_scan(); ++it)
    {
        cout << *it << " ";
    } 
    cout << endl; 
    // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6


    cout << "DFS Traversal of the Binary Tree:" << endl;
    for (auto it = tree.begin_dfs_scan(); it != tree.end_dfs_scan(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    // Expected output: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6




    
    // Print the tree structure
    three_ary_tree.printTree();


 

}







