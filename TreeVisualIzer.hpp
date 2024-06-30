#ifndef TREE_VISUALIZER_HPP
#define TREE_VISUALIZER_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "node.hpp" // Ensure this is the correct path to your Node template class


using namespace sf;
using namespace std;

template<typename T>
class TreeVisualizer {
public:
    
    void showTree(const shared_ptr<Node<T>>& root ,RenderWindow& window) {
        if(!root) return;
        Font font;
        if (!font.loadFromFile("/home/shiraltman/Downloads/Roboto-BoldItalic.ttf")) {
            cerr << "Error loading font\n";
            return;
        }

        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed)
                    window.close();
            }
            window.clear();
            drawTree(window, root, font, 400, 50, 0);
            window.display();
        }
    }

private:
    void drawTree(RenderWindow& window, shared_ptr<Node<T>> node, const Font& font, int x, int y, int level) {
        if (!node) return;

        constexpr int HORIZONTAL_SPACING = 80;
        constexpr int VERTICAL_SPACING = 50;
        const int RADIUS = 50;
        int childrenCount = node->get_children().size();

        // Draw the node itself
        CircleShape shape(RADIUS);
        shape.setFillColor(Color::White);
        shape.setPosition(x - RADIUS / 2, y - RADIUS / 2);

        // Draw the value inside the node
        Text text(to_string(node->get_data()), font, 20);
        float textWidth = text.getLocalBounds().width;
        text.setPosition(x - textWidth / 2, y - 10);

        for (int i = 0; i < childrenCount; i++) {
            int offset = (i - childrenCount / 2) * (level + 1) * HORIZONTAL_SPACING;
            int childX = x + offset;
            int childY = y + VERTICAL_SPACING;

            // Draw line to child
            Vertex line[] = {
                Vertex(Vector2f(x, y + RADIUS)),
                Vertex(Vector2f(childX, childY - RADIUS))
            };

            window.draw(line, 2, Lines);
            drawTree(window, node->get_children()[i], font, childX, childY, level + 1);
        }

        window.draw(shape);
        window.draw(text);
    }
};

#endif // TREE_VISUALIZER_HPP
