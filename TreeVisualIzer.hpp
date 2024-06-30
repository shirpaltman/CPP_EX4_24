#ifndef TREE_VISUALIZER_HPP
#define TREE_VISUALIZER_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "node.hpp" // Ensure this is the correct path to your Node template class


using namespace sf;
using namespace std;

template<typename T>
class TreeVisualizer{
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
    void drawTree(RenderWindow& window, shared_ptr<Node<T>> node, const Font& font, int x, int y, int level=0) {
        if (!node) return;

    constexpr int BASE_SPACING = 555;  // Base horizontal spacing
    int spacing = BASE_SPACING / (level + 1);  // Adjust spacing based on level
    constexpr int VERTICAL_SPACING = 100;
    const int RADIUS = 45;
    int childrenCount = node->get_children().size();

    


        // Calculate horizontal spacing based on the number of children
        int offsetIncrement = spacing/ (childrenCount + 1);
        int startX = x - (childrenCount - 1) * offsetIncrement / 2;

        

        // Draw the value inside the node
        Text text(to_string(node->get_data()), font, 22);
        float textWidth = text.getLocalBounds().width;
        float textHeight = text.getLocalBounds().height;

        text.setFillColor(Color::White);
        text.setPosition(x - textWidth / 2, y - textHeight/2);

        // Draw the node itself
        CircleShape shape(RADIUS);
        shape.setFillColor(Color::Green);
        shape.setPosition(x-RADIUS, y-RADIUS);

        
        window.draw(shape);
        window.draw(text);


        int childX = startX;
        for (int i = 0; i < childrenCount; ++i) {
            int childY = y + VERTICAL_SPACING;

            // Draw line to child
            Vertex line[] = {
                Vertex(Vector2f(x, y + RADIUS),Color::White),
                Vertex(Vector2f(childX, childY - RADIUS),Color::White)
            };

            window.draw(line, 2, Lines);
            drawTree(window, node->get_children()[i], font, childX, childY, level + 1);
            childX += offsetIncrement;
        }
    }
    
};

#endif // TREE_VISUALIZER_HPP
