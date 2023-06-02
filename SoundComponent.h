#pragma once
#include "Entity.h"
#include "Component.h"
#include "SoundComponent.h"
#include <SFML/Audio.hpp>

class SoundComponent : public Component {
public:
    sf::Sound* getSound(const SoundType& type) { return &sounds_[type]; };

    void setSound(const SoundType& type, sf::SoundBuffer buffer);

private:
    std::unordered_map<SoundType, sf::SoundBuffer> buffers_;

    std::unordered_map<SoundType, sf::Sound> sounds_;

};