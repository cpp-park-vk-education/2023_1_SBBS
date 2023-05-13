#pragma once
#include <SFML/Audio.hpp>
#include "Entity.h"
#include "Component.h"

class MusicComponent : public Component {
public:
    void playMusic();

    void setMusic();

private:
    sf::Music music;
};
