#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

int main() {
    // Build a window object.
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Application");
    // Allow the GPU to handle control of the framerate.
    window.setVerticalSyncEnabled(true);

    // Our program runs while the window is still open.
    while (window.isOpen()) {

        // container to store events in.
        sf::Event event;

        // Access global input devices (keyboard and mouse globally)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) {
            std::cout << "The F1 key has been pressed!\n";
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            std::cout << "The left mouse button has been pressed globally!\n";
        }

        // poll an event (while loop stops if no events happening, continues essentially.)
        while (window.pollEvent(event)) {
            // Check the type of event.
            switch (event.type) {

                // Handles mouse press event.
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        std::cout << "The left mouse button has been pressed.\n";
                        std::cout << "Position: " << event.mouseButton.x << ", " << event.mouseButton.y << "\n";
                    } else {
                        std::cout << "Non left mouse button has been pressed!\n";
                    }
                    break;

                // Handles text entered event.
                case sf::Event::TextEntered:
                    std::cout << "You entered:  " << sf::String(event.text.unicode).toAnsiString() << std::endl;
                    break;

                // Handles resize window event.
                case sf::Event::Resized:
                    window.setSize(sf::Vector2u(event.size.width, event.size.height));
                    std::cout << "New size: " << event.size.width << " " << event.size.height << std::endl;
                    break;

                // Handles close window event.
                case sf::Event::Closed:
                    window.close();
                    std::cout << "Close event triggered." << std::endl;
                    break;

                // Ignore event.
                default:
                    break;
            }

        }

        // We can now begin drawing to our window.
        // You want to do this as, Clear -> Draw -> Display
        // Clear the current frame.
        window.clear(sf::Color::Black);

        // Draw logic for frame.
        sf::RectangleShape line (sf::Vector2f(800, 5));
        line.setPosition(0, 20);
        window.draw(line);

        // Display frame.
        window.display();

    }

}