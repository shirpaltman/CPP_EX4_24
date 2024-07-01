#include "doctest.hpp"
#include "tree.hpp"
#include "Complex.hpp"  // Assuming Complex class is in Complex.hpp
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <numeric>

using namespace std;

template <typename T>
void deleteTree(Node<T>* node) {
    for (auto child : node->get_children()) {
        deleteTree(child);
    }
    delete node;
}

TEST_CASE("Testing Tree with Complex Numbers") {
    Tree<Complex> complexTree;
    complexTree.add_root(Complex(1, 1));
    auto root = complexTree.get_root();
    complexTree.add_sub_node(root, Complex(2, 2));
    complexTree.add_sub_node(root, Complex(3, 3));

    SUBCASE("Test Pre-Order Traversal") {
        std::vector<Complex> expected{Complex(1, 1), Complex(2, 2), Complex(3, 3)};
        auto it = complexTree.begin_pre_order();
        for (const auto& exp : expected) {
            CHECK(*it == exp);
            ++it;
        }
    }

    SUBCASE("Test Post-Order Traversal") {
        std::vector<Complex> expected{Complex(2, 2), Complex(3, 3), Complex(1, 1)};
        auto it = complexTree.begin_post_order();
        for (const auto& exp : expected) {
            CHECK(*it == exp);
            ++it;
        }
    }

    SUBCASE("Test In-Order Traversal") {
        // This assumes binary tree behavior. Adjust as necessary for k-ary trees.
        std::vector<Complex> expected{Complex(2, 2), Complex(1, 1), Complex(3, 3)};
        auto it = complexTree.begin_in_order();
        for (const auto& exp : expected) {
            CHECK(*it == exp);
            ++it;
        }
    }

    SUBCASE("Test BFS Traversal") {
        std::vector<Complex> expected{Complex(1, 1), Complex(2, 2), Complex(3, 3)};
        auto it = complexTree.begin_bfs_scan();
        for (const auto& exp : expected) {
            CHECK(*it == exp);
            ++it;
        }
    }
}
TEST_CASE("Test Tree Creation") {
    auto root = std::make_shared<Node<int>>(10);
    auto child1 = std::make_shared<Node<int>>(20);
    auto child2 = std::make_shared<Node<int>>(30);

    root->add_child(child1);
    root->add_child(child2);

    CHECK(root->get_data() == 10);
    CHECK(root->get_children().size() == 2);
    CHECK(root->get_children()[0]->get_data() == 20);
    CHECK(root->get_children()[1]->get_data() == 30);
} 

TEST_CASE("Test Tree with 60 Children") {
    auto root = std::make_shared<Node<int>>(10);
    for (int i = 0; i < 60; ++i) {
        root->add_child(std::make_shared<Node<int>>(20 + i));
    }

    CHECK(root->get_data() == 10);
    CHECK(root->get_children().size() == 60);
    for (std::vector<std::shared_ptr<Node<int>>>::size_type i = 0; i < root->get_children().size(); ++i) {
        CHECK(root->get_children()[i]->get_data() == 20 + i);
    }
}

TEST_CASE("Test Add Child") {
    auto root = std::make_shared<Node<int>>(1);
    auto child = std::make_shared<Node<int>>(2);
    root->add_child(child);

    CHECK(root->get_children().size() == 1);
    CHECK(root->get_children()[0]->get_data() == 2);
}


TEST_CASE("Test Tree Creation with Doubles") {
    Tree<double> tree; // Binary tree that contains doubles.
    tree.add_root(1.1);
    auto root = tree.get_root();
    tree.add_sub_node(root, 1.2);
    tree.add_sub_node(root, 1.3);

    auto& children = root->get_children();
    tree.add_sub_node(children[0], 1.4);
    tree.add_sub_node(children[0], 1.5);
    tree.add_sub_node(children[1], 1.6);

    CHECK(root->get_data() == 1.1);
    CHECK(root->get_children().size() == 2);
    CHECK(root->get_children()[0]->get_data() == 1.2);
    CHECK(root->get_children()[1]->get_data() == 1.3);
    CHECK(root->get_children()[0]->get_children().size() == 2);
    CHECK(root->get_children()[1]->get_children().size() == 1);
    CHECK(root->get_children()[0]->get_children()[0]->get_data() == 1.4);
    CHECK(root->get_children()[0]->get_children()[1]->get_data() == 1.5);
    CHECK(root->get_children()[1]->get_children()[0]->get_data() == 1.6);
}

TEST_CASE("Test InOrderIterator with Doubles") {
    Tree<double> tree;
    tree.add_root(1.1);
    auto root = tree.get_root();
    tree.add_sub_node(root, 1.2);
    tree.add_sub_node(root, 1.3);

    auto& children = root->get_children();
    tree.add_sub_node(children[0], 1.4);
    tree.add_sub_node(children[0], 1.5);
    tree.add_sub_node(children[1], 1.6);

    std::vector<double> values;
    for (auto it = tree.begin_in_order(); it != tree.end_in_order(); ++it) {
        values.push_back(*it);
    }
    std::vector<double> expected = {1.4, 1.2, 1.5, 1.1, 1.6, 1.3};
    CHECK(values == expected);
}



TEST_CASE("Test PostOrderIterator with Doubles") {
    Tree<double> tree;
    tree.add_root(1.1);
    auto root = tree.get_root();
    tree.add_sub_node(root, 1.2);
    tree.add_sub_node(root, 1.3);

    auto& children = root->get_children();
    tree.add_sub_node(children[0], 1.4);
    tree.add_sub_node(children[0], 1.5);
    tree.add_sub_node(children[1], 1.6);

    std::vector<double> values;
    for (auto it = tree.begin_post_order(); it != tree.end_post_order(); ++it) {
        values.push_back(*it);
    }
    std::vector<double> expected = {1.4, 1.5, 1.2, 1.6, 1.3, 1.1};
    CHECK(values == expected);
}


TEST_CASE("Test BFSIterator with Doubles") {
    Tree<double> tree;
    tree.add_root(1.1);
    auto root = tree.get_root();
    tree.add_sub_node(root, 1.2);
    tree.add_sub_node(root, 1.3);

    auto& children = root->get_children();
    tree.add_sub_node(children[0], 1.4);
    tree.add_sub_node(children[0], 1.5);
    tree.add_sub_node(children[1], 1.6);

    std::vector<double> values;
    for (auto it = tree.begin_bfs_scan(); it != tree.end_bfs_scan(); ++it) {
        values.push_back(*it);
    }
    std::vector<double> expected = {1.1, 1.2, 1.3, 1.4, 1.5, 1.6};
    CHECK(values == expected);
}


TEST_CASE("Test DFSIterator with Doubles") {
    Tree<double> tree;
    tree.add_root(1.1);
    auto root = tree.get_root();
    tree.add_sub_node(root, 1.2);
    tree.add_sub_node(root, 1.3);

    auto& children = root->get_children();
    tree.add_sub_node(children[0], 1.4);
    tree.add_sub_node(children[0], 1.5);
    tree.add_sub_node(children[1], 1.6);

    std::vector<double> values;
    for (auto it = tree.begin_dfs_scan(); it != tree.end_dfs_scan(); ++it) {
        values.push_back(*it);
    }
    std::vector<double> expected = {1.1, 1.2, 1.4, 1.5, 1.3, 1.6};
    CHECK(values == expected);
}


TEST_CASE("Test PreOrderIterator with Doubles") {
    Tree<double> tree;
    tree.add_root(1.1);
    auto root = tree.get_root();
    tree.add_sub_node(root, 1.2);
    tree.add_sub_node(root, 1.3);

    auto& children = root->get_children();
    tree.add_sub_node(children[0], 1.4);
    tree.add_sub_node(children[0], 1.5);
    tree.add_sub_node(children[1], 1.6);

    std::vector<double> values;
    for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it) {
        values.push_back(*it);
    }
    std::vector<double> expected = {1.1, 1.2, 1.4, 1.5, 1.3, 1.6};
    CHECK(values == expected);
}

TEST_CASE("Test InOrderIterator with Only Root Node") {
    Tree<int> tree;
    tree.add_root(1);
    vector<int> values;
    for (auto it = tree.begin_in_order(); it != tree.end_in_order(); ++it) {
        values.push_back(*it);
    }
    vector<int> expected = {1};
    CHECK(values == expected);
}


TEST_CASE("Test InOrderIterator with Two Levels") {
    Tree<int> tree(2);
    tree.add_root(1);
    auto root = tree.get_root();
    tree.add_sub_node(root, 2);
    tree.add_sub_node(root, 3);

    vector<int> values;
    for (auto it = tree.begin_in_order(); it != tree.end_in_order(); ++it) {
        values.push_back(*it);
    }

    vector<int> expected = {2, 1, 3};
    CHECK(values == expected);
}

TEST_CASE("Test PreOrderIterator with Doubles in 3-ary Tree") {
    Tree<double> tree(3);
    tree.add_root(1.1);
    auto root = tree.get_root();
    tree.add_sub_node(root, 1.2);
    tree.add_sub_node(root, 1.3);
    tree.add_sub_node(root, 1.4);

    auto& children = root->get_children();
    tree.add_sub_node(children[0], 1.5);
    tree.add_sub_node(children[0], 1.6);
    tree.add_sub_node(children[1], 1.7);
    tree.add_sub_node(children[1], 1.8);
    tree.add_sub_node(children[2], 1.9);

    std::vector<double> values;
    for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it) {
        values.push_back(*it);
    }

    std::vector<double> expected = {1.1, 1.2, 1.5, 1.6, 1.3, 1.7, 1.8, 1.4, 1.9};
    CHECK(values == expected);
}

TEST_CASE("Test PreOrderIterator with Only Root Node") {
    Tree<int> tree;
    tree.add_root(1);
    std::vector<int> values;
    for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it) {
        values.push_back(*it);
    }
    std::vector<int> expected = {1};
    CHECK(values == expected);
}

TEST_CASE("Test PreOrderIterator with Two Levels") {
    Tree<int> tree(2);
    tree.add_root(1);
    auto root = tree.get_root();
    tree.add_sub_node(root, 2);
    tree.add_sub_node(root, 3);

    vector<int> values;
    for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it) {
        values.push_back(*it);
    }

    vector<int> expected = {1, 2, 3};
    CHECK(values == expected);
}

TEST_CASE("Test Tree with Complex Numbers using PreOrderIterator") {
    Tree<Complex> tree;
    tree.add_root(Complex(1.1, 2.2));
    auto root = tree.get_root();
    tree.add_sub_node(root, Complex(3.3, 4.4));
    tree.add_sub_node(root, Complex(5.5, 6.6));

    auto& children = root->get_children();
    tree.add_sub_node(children[0], Complex(7.7, 8.8));
    tree.add_sub_node(children[0], Complex(9.9, 10.10));

    vector<Complex> values;
    for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it) {
        values.push_back(*it);
    }

    vector<Complex> expected = {Complex(1.1, 2.2), Complex(3.3, 4.4), Complex(7.7, 8.8), Complex(9.9, 10.10), Complex(5.5, 6.6)};
    CHECK(values == expected);
}

TEST_CASE("Test PostOrderIterator with Doubles in 3-ary Tree") {

    Tree<double> tree(3);
    tree.add_root(1.1);
    auto root = tree.get_root();
    tree.add_sub_node(root, 1.2);
    tree.add_sub_node(root, 1.3);
    tree.add_sub_node(root, 1.4);

    auto& children = root->get_children();
    tree.add_sub_node(children[0], 1.5);
    tree.add_sub_node(children[0], 1.6);
    tree.add_sub_node(children[1], 1.7);
    tree.add_sub_node(children[1], 1.8);
    tree.add_sub_node(children[2], 1.9);

    vector<double> values;
    for (auto it = tree.begin_post_order(); it != tree.end_post_order(); ++it) {
        values.push_back(*it);
    }

    vector<double> expected = {1.5, 1.6, 1.2, 1.7, 1.8, 1.3, 1.9, 1.4, 1.1};
    CHECK(values == expected);
}
TEST_CASE("Test PreOrderIterator with Large Tree") {
    Tree<int> tree(3);
    tree.add_root(1);
    auto root = tree.get_root();
    tree.add_sub_node(root, 2);
    tree.add_sub_node(root, 3);
    tree.add_sub_node(root, 4);

    auto& children = root->get_children();
    tree.add_sub_node(children[0], 5);
    tree.add_sub_node(children[0], 6);
    tree.add_sub_node(children[1], 7);
    tree.add_sub_node(children[1], 8);
    tree.add_sub_node(children[2], 9);

    vector<int> values;
    for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it) {
        values.push_back(*it);
    }

    vector<int> expected = {1, 2, 5, 6, 3, 7, 8, 4, 9};
    CHECK(values == expected);
}

TEST_CASE("Test PostOrderIterator with Only Root Node") {
    Tree<int> tree;
    tree.add_root(1);
    vector<int> values;
    for (auto it = tree.begin_post_order(); it != tree.end_post_order(); ++it) {
        values.push_back(*it);
    }
    vector<int> expected = {1};
    CHECK(values == expected);
}


TEST_CASE("Test PostOrderIterator with Two Levels") {
    Tree<int> tree(2);
    tree.add_root(1);
    auto root = tree.get_root();
    tree.add_sub_node(root, 2);
    tree.add_sub_node(root, 3);

    vector<int> values;
    for (auto it = tree.begin_post_order(); it != tree.end_post_order(); ++it) {
        values.push_back(*it);
    }

    vector<int> expected = {2, 3, 1};
    CHECK(values == expected);
}


TEST_CASE("Test PostOrderIterator with Large Tree") {
    Tree<int> tree(3);
    tree.add_root(1);
    auto root = tree.get_root();
    tree.add_sub_node(root, 2);
    tree.add_sub_node(root, 3);
    tree.add_sub_node(root, 4);

    auto& children = root->get_children();
    tree.add_sub_node(children[0], 5);
    tree.add_sub_node(children[0], 6);
    tree.add_sub_node(children[1], 7);
    tree.add_sub_node(children[1], 8);
    tree.add_sub_node(children[2], 9);

    vector<int> values;
    for (auto it = tree.begin_post_order(); it != tree.end_post_order(); ++it) {
        values.push_back(*it);
    }

    vector<int> expected = {5, 6, 2, 7, 8, 3, 9, 4, 1};
    CHECK(values == expected);
}



