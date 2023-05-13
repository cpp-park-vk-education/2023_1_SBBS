#pragma once
#include <SFML/Audio.hpp>
#include "Entity.h"
#include "Component.h"
#include <string>

class MusicComponent : public Component {
public:

    MusicComponent(const std::string& file_name) { music_.openFromFile(file_name);  }

    void playMusic() { music_.play(); };

    void setMusic(const std::string& file_name) { music_.openFromFile(file_name); };

private:
    sf::Music music_;
};
