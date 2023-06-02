#include "InputHandler.h"
#include <chrono>

void Input::handleInput(sf::Window& window) {
    static std::chrono::steady_clock::time_point last_time = std::chrono::steady_clock::now();
    static Input curr_input;

    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::KeyPressed: ///////////////////// key pressed
            if (event.key.code == sf::Keyboard::D)
                curr_input.moving_right_ = true;
            else if (event.key.code == sf::Keyboard::S)
                curr_input.moving_down_ = true;
            else if (event.key.code == sf::Keyboard::A)
                curr_input.moving_left_ = true;
            else if (event.key.code == sf::Keyboard::W)
                curr_input.moving_up_ = true;
            break;
        case sf::Event::KeyReleased:///////////////////// key released
            if (event.key.code == sf::Keyboard::D)
                curr_input.moving_right_ = false;
            else if (event.key.code == sf::Keyboard::S)
                curr_input.moving_down_ = false;
            else if (event.key.code == sf::Keyboard::A)
                curr_input.moving_left_ = false;
            else if (event.key.code == sf::Keyboard::W)
                curr_input.moving_up_ = false;
            break;

        default:
            break;
        }
    }
    *this = curr_input;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        mouse_click_ = true;

    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    mouse_x_ = mousePosition.x;
    mouse_y_ = mousePosition.y;

    return;
}

