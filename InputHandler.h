#pragma once
#include "Input.h"
#include <SFML/Window.hpp>
#include <iostream>

Input handleInput(sf::Window& window) {
    Input curr_input;

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

    //std::cout << curr_input.moving_right_ << curr_input.moving_down_ << curr_input.moving_left_ << curr_input.moving_up_ << "\n";
    //curr_input.moving_right_ = true;

    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    curr_input.mouse_x_ = mousePosition.x;
    curr_input.mouse_y_ = mousePosition.y;
    curr_input.shoot_ = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

    return curr_input;
}