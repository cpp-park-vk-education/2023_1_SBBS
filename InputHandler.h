#pragma once
#include <chrono>
#include <SFML/Graphics.hpp>

struct Input {
	bool moving_right_ = false;
	bool moving_left_ = false;
	bool moving_up_ = false;
	bool moving_down_ = false;
	bool shoot_ = false;
	int mouse_x_ = 0;
	int mouse_y_ = 0;

    inline void handleInput(sf::Window& window) {
        static auto last_time = std::chrono::steady_clock::time_point();
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


        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            auto curr_time = std::chrono::high_resolution_clock::now();
            double elapsed_time = std::chrono::duration<double>(curr_time - last_time).count();

            if (elapsed_time >= 1) {
                shoot_ = true;
                last_time = curr_time;
            }
        }
        else {
            shoot_ = false;
        }

        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        mouse_x_ = mousePosition.x;
        mouse_y_ = mousePosition.y;

        return;
    }


};

