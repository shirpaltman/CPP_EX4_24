/*
Author:Shir Altman
ID:325168870
Email: shirpaltman@gmail.com
*/
#include <iostream>
#include <memory>
#include <string>
#include "node.hpp"
#include "tree.hpp"
#include <SFML/Graphics.hpp>
#include "TreeVisualIzer.hpp"
#include "Complex.hpp" 


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


    // Tree<double> three_ary_tree(3); // Initialize a 3-ary tree
    // auto rootH = three_ary_tree.get_root();
    // three_ary_tree.add_root(1.1);  // Setting the root
    // rootH = three_ary_tree.get_root();

    // three_ary_tree.add_sub_node(rootH, 1.2);
    // three_ary_tree.add_sub_node(rootH, 1.3);
    // three_ary_tree.add_sub_node(rootH, 1.4);



    // Initialize a 3-ary tree
    Tree<double> three_ary_tree(3); 
    three_ary_tree.add_root(1.1);  // Setting the root
    auto rootH = three_ary_tree.get_root();  // Fetch the root node

    // Adding children to the root
    three_ary_tree.add_sub_node(rootH, 1.2);
    three_ary_tree.add_sub_node(rootH, 1.3);
    three_ary_tree.add_sub_node(rootH, 1.4);  // Third child to root

    // Adding children to the first child of the root (1.2)
    auto first_child = rootH->get_children()[0];  // This is node 1.2
    three_ary_tree.add_sub_node(first_child, 1.5);

    // Adding a child to the second child of the root (1.3)
    auto second_child = rootH->get_children()[1];  // This is node 1.3
    three_ary_tree.add_sub_node(second_child, 1.6);


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
    
    
    Tree<int> complexTree(5); // Initialize a 5-ary tree using int

    // Set the root
    complexTree.add_root(1);
    auto rootD = complexTree.get_root();

    // Manually add children to the root
    complexTree.add_sub_node(rootD, 2);
    complexTree.add_sub_node(rootD, 3);
    complexTree.add_sub_node(rootD, 4);
    complexTree.add_sub_node(rootD, 5);
    complexTree.add_sub_node(rootD, 6);

    // Manually add children to Node 2
    auto node2 = rootD->get_children()[0];
    complexTree.add_sub_node(node2, 7);
    complexTree.add_sub_node(node2, 8);
    complexTree.add_sub_node(node2, 9);
    complexTree.add_sub_node(node2, 10);
    complexTree.add_sub_node(node2, 11);

   
    Tree<Complex> complexTreeC;
    complexTreeC.add_root(Complex(1.1, 2.2));
    auto complexRootC = complexTreeC.get_root();
    complexTreeC.add_sub_node(complexRootC, Complex(3.3, 4.4));
    complexTreeC.add_sub_node(complexRootC, Complex(5.5, 6.6));

    // Assuming the Complex class has an operator<< defined
    // Let's print the Complex numbers stored in the tree
    cout << "Pre-Order Traversal of the Complex Tree:" << endl;
    for (auto it = complexTree.begin_pre_order(); it != complexTree.end_pre_order(); ++it) {
        cout << *it << " ";
    }
    cout << endl;





    TreeVisualizer<double> visualizer;
    TreeVisualizer<int> visualizerI;
    TreeVisualizer<Complex> visualizerC;
    
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

    // Create a separate window for the 5-ary tree visualization
    RenderWindow complexTree_window(VideoMode(800, 600), "5-ary Tree Visualization");
    while (complexTree_window.isOpen()) {
        Event event;
        while (complexTree_window.pollEvent(event)) {
            if (event.type == Event::Closed)
                complexTree_window.close();
        }

        complexTree_window.clear(Color::Black);
        visualizerI.showTree(complexTree.get_root(),complexTree_window,font);
        complexTree_window.display();
    }


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

    RenderWindow complex_window(VideoMode(800, 600), "complex Tree Visualization");
    while (complex_window.isOpen()) {
        Event event;
        while (complex_window.pollEvent(event)) {
            if (event.type == Event::Closed)
                complex_window.close();
        }

        complex_window.clear(Color::Black);
        visualizerC.showTree(complexTreeC.get_root(),complex_window,font);
        complex_window.display();
    }
        
    // Pre-order Traversal
    cout << "Pre-order Traversal of the Complex Tree:" << endl;
    for (auto it = complexTreeC.begin_pre_order(); it != complexTreeC.end_pre_order(); ++it){
        cout << *it << "   ";
    }
    cout << endl;

    // Post-order Traversal
    cout << "Post-order Traversal of the Complex Tree:" << endl;
    for (auto it = complexTreeC.begin_post_order(); it != complexTreeC.end_post_order(); ++it) {
        cout << *it << "   ";
    }
    cout << endl;

    // In-order Traversal (for binary trees, if implemented)
    cout << "In-order Traversal of the Complex Tree:" << endl;
    for (auto it = complexTreeC.begin_in_order(); it != complexTreeC.end_in_order(); ++it) {
        cout << *it << "    ";
    }
    cout << endl;

    // BFS Traversal
    cout << "BFS Traversal of the Complex Tree:" << endl;
    for (auto it = complexTreeC.begin_bfs_scan(); it != complexTreeC.end_bfs_scan(); ++it) {
        cout << *it << "   ";
    }
    cout << endl;

    // DFS Traversal
    cout << "DFS Traversal of the Complex Tree:" << endl;
    for (auto it = complexTreeC.begin_dfs_scan(); it != complexTreeC.end_dfs_scan(); ++it) {
        cout << *it << "   ";
    }
    cout << endl;


    
    cout << "Pre-order Traversal of the Tree:" << endl;
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







