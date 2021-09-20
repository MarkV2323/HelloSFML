#include <SFML/Graphics.hpp>
#include <iostream>

// Main
int main() {

    // Build a window object.
    sf::RenderWindow window(sf::VideoMode(500, 500), "Pong via SFML!");

    // Allow the GPU to handle control of the framerate.
    window.setVerticalSyncEnabled(true);

    // Create player
    sf::RectangleShape playerOne(sf::Vector2f(50, 10));
    playerOne.setPosition(50, 440); // Spawn in the bottom.
    enum playerMoveDirection {left, right, none} playerOneMoveDirection = none, playerTwoMoveDirection = none;

    // Create enemy player
    sf::RectangleShape playerTwo(sf::Vector2f(50, 10));
    playerTwo.setPosition(400, 50); // Spawn in the top.

    // Create a ball
    sf::CircleShape ball(5);
    ball.setPointCount(20);
    ball.setPosition(70, 429); // Spawn on the player.

    // Init ball to follow player movements until shot.
    bool ballShot = false;
    sf::Vector2f ballMotion(0,0);

    // Primary loop
    while (window.isOpen()) {
        // container to store events in.
        sf::Event event;

        // poll an event (handles resizing and closure).
        while (window.pollEvent(event)) {
            // Check the type of event.
            switch (event.type) {
                case sf::Event::Resized:
                    window.setSize(sf::Vector2u(event.size.width, event.size.height));
                    std::cout << "New size: " << event.size.width << " " << event.size.height << std::endl;
                    break;

                case sf::Event::Closed:
                    window.close();
                    std::cout << "Close event triggered." << std::endl;
                    break;

                default:
                    break;
            }
        }

        // Clear -> Draw -> Display
        window.clear(sf::Color::Black);
        window.draw(playerOne);
        window.draw(playerTwo);
        window.draw(ball);
        window.display();

        // gather new input from user.
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            // Move Left
            if ((playerOne.getPosition().x - 2) >= 0) {
                playerOne.move(-2, 0);
                playerOneMoveDirection = left;
                if (!ballShot) {
                    // have ball follow player.
                    ball.move(-2, 0);
                }
            } else {
                playerOneMoveDirection = none;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            // Move Right
            if ((playerOne.getPosition().x + 2 + 50) <= 500) {
                playerOne.move(2, 0);
                playerOneMoveDirection = right;
                if (!ballShot) {
                    // have ball follow player.
                    ball.move(2, 0);
                }
            } else {
                playerOneMoveDirection = none;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            // trigger the ball to be shot.
            ballShot = true;
            // Decide how to move based on what the player was doing.
            switch (playerOneMoveDirection) {
                case none:
                    // Go north
                    ballMotion.x = 0;
                    ballMotion.y = -2;
                    break;
                case left:
                    // Go north left
                    ballMotion.x = -2;
                    ballMotion.y = -2;
                    break;
                case right:
                    // Go north right
                    ballMotion.x = 2;
                    ballMotion.y = -2;
                    break;
            }

        }

        // Basic AI Implementation (move towards ball center based on current paddle position)
        if (playerTwo.getPosition().x + 50 < (ball.getPosition().x + 5)) {
            // Move right.
            if ((playerTwo.getPosition().x + 2 + 50) <= 500) {
                playerTwo.move(2, 0);
                playerTwoMoveDirection = right;
            } else {
                playerTwoMoveDirection = none;
            }
        } else if (playerTwo.getPosition().x > (ball.getPosition().x + 5)) {
            // Move left.
            if ((playerTwo.getPosition().x - 2) >= 0) {
                playerTwo.move(-2, 0);
                playerTwoMoveDirection = left;
            } else {
                playerTwoMoveDirection = none;
            }
        } else {
            // Do not move.
        }

        // Logic for ball movement.
        if (ballShot) {
            // Calculate possible values based on current ballMotion vector.
            float ballPosX = ball.getPosition().x + ballMotion.x;
            float ballPosY = ball.getPosition().y + ballMotion.y;

            // Check for paddle collisions.
            if (ballPosY == 61) {   // Top Player Paddle (p2)
                // Gather playerTwo position.
                float minTmpPosition = playerTwo.getPosition().x;
                if (ballPosX + 8 >= minTmpPosition && ballPosX <= minTmpPosition + 50) {
                    // Ball has made contact with paddle, send in opposite direction.
                    // Calculate Spin based on paddle movement.
                    switch (playerTwoMoveDirection) {
                        case none:
                            // Go south
                            ballMotion.x = ballMotion.x * -1;
                            ballMotion.y = 2;
                            break;
                        case left:
                            // Go south left
                            ballMotion.x = -2;
                            ballMotion.y = 2;
                            break;
                        case right:
                            // Go south right
                            ballMotion.x = 2;
                            ballMotion.y = 2;
                            break;
                    }
                    // Recalculate possible values.
                    ballPosX = ball.getPosition().x + ballMotion.x;
                    ballPosY = ball.getPosition().y + ballMotion.y;
                }
            }
            if (ballPosY == 435) {  // Bottom Player Paddle (p1)
                // Gather playerOne position.
                float minTmpPosition = playerOne.getPosition().x;
                if (ballPosX + 8 >= minTmpPosition && ballPosX <= minTmpPosition + 50) {
                    // Ball has made contact with paddle, send in opposite direction.
                    // Calculate Spin based on paddle movement.
                    switch (playerOneMoveDirection) {
                        case none:
                            // Go north
                            ballMotion.x = ballMotion.x * -1;
                            ballMotion.y = -2;
                            break;
                        case left:
                            // Go north left
                            ballMotion.x = -2;
                            ballMotion.y = -2;
                            break;
                        case right:
                            // Go north right
                            ballMotion.x = 2;
                            ballMotion.y = -2;
                            break;
                    }
                    // Recalculate possible values.
                    ballPosX = ball.getPosition().x + ballMotion.x;
                    ballPosY = ball.getPosition().y + ballMotion.y;
                }
            }

            // Check for wall collisions.
            if (ballPosX < 0) {
                // bounce off left wall
                ballMotion.x = 2;
            }
            if (ballPosX > 495) {
                // bounce off right wall
                ballMotion.x = -2;
            }

            // Check for end games.
            if (ballPosY <= 0) {
                // Game over! (respawn players, respawn ball, lock ball)
                playerOne.setPosition(50, 440); // Spawn in the bottom.
                playerTwo.setPosition(400, 50); // Spawn in the top.
                ball.setPosition(70, 429);      // Spawn on the player.
                ballShot = false;                     // Lock ball on player.
                ballMotion.x = 0, ballMotion.y = 0;   // Reset motion vector.

            }
            if (ballPosY >= 495) {
                // Game over! (respawn players, respawn ball, lock ball)
                playerOne.setPosition(50, 440); // Spawn in the bottom.
                playerTwo.setPosition(400, 50); // Spawn in the top.
                ball.setPosition(70, 429);      // Spawn on the player.
                ballShot = false;                     // Lock ball on player.
                ballMotion.x = 0, ballMotion.y = 0;   // Reset motion vector.
            }

            // Move based on motion vector
            ball.move(ballMotion);
        }

        // Reset player movement enum to none.
        playerOneMoveDirection = none;

    }

    return 0;
}