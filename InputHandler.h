#pragma once
#include <SFML/Graphics.hpp>

struct Input {

    bool moving_right_ = false;
    bool moving_left_ = false;
    bool moving_up_ = false;
    bool moving_down_ = false;
    bool esc_pressed_ = false;
    bool mouse_click_ = false;
    int mouse_x_ = 0;
    int mouse_y_ = 0;

    void handleInput(sf::Window& window);
};

