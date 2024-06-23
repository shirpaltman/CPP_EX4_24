#include "tree.hpp"
#include "node.hpp"
#include <SFML/Graphics.hpp>
using  namespace sf;
using namespace std;

void drawTree(const Tree<double>& tree, RenderWindow& window, shared_ptr<Node<double>> node, int x, int y, int level = 0) {
    if (!node) return;

    constexpr int HORIZONTAL_SPACING = 80;
    constexpr int VERTICAL_SPACING = 50;
    int childrenCount = node->get_children().size();

    // Draw the node itself
    sf::CircleShape shape(20);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(x, y);

    // Draw the value inside the node
    sf::Font font;
    if (!font.loadFromFile("Arial.ttf")) {
        cerr << "Error loading font\n";
    }

    sf::Text text(to_string(node->get_data()), font, 20);
    text.setPosition(x + 10, y + 5);

    for (int i = 0; i < childrenCount; i++) {
        int childX = x + (i - childrenCount/2) * (level + 1) * HORIZONTAL_SPACING;
        int childY = y + VERTICAL_SPACING;

        // Draw line to child
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(x + 20, y + 20)),
            sf::Vertex(sf::Vector2f(childX + 20, childY + 20))
        };

        window.draw(line, 2, sf::Lines);
        drawTree(tree, window, node->get_children()[i], childX, childY, level + 1);
    }

    window.draw(shape);
    window.draw(text);
}
