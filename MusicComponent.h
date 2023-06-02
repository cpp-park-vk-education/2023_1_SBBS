#pragma once
#include <SFML/Audio.hpp>
#include "Entity.h"
#include "Component.h"
#include <string>
#include <iostream>

class MusicComponent : public Component {
public:

    MusicComponent() {};

    MusicComponent(const std::string& file_name) { if (!music_.openFromFile(file_name)) std::cout<<"Didnt open music file"; }

    sf::Music* getMusic() { return &music_; };

    void setMusic(const std::string& file_name) { music_.openFromFile(file_name); };

private:
    sf::Music music_;
};
