#pragma once
#include "Entity.h"
#include "Component.h"
#include "SoundComponent.h"
#include <SFML/Audio.hpp>

class SoundComponent : public Component {
public:
    sf::Sound* getSound(const SoundType& type) { return &sounds_[type]; };

    void setSound(const SoundType& type, sf::SoundBuffer buffer) {

        buffers_.insert({ type,buffer });
        sf::Sound sound;
        sound.setBuffer(buffers_[type]);
        sounds_.insert({ type,sound });
    };

private:
    //sf::SoundBuffer buffer_;
    //sf::Sound sound_;
    std::unordered_map<SoundType, sf::SoundBuffer> buffers_;
    std::unordered_map<SoundType, sf::Sound> sounds_;

};