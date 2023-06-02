#include "SoundComponent.h"

void SoundComponent::setSound(const SoundType& type, sf::SoundBuffer buffer) {

    buffers_.insert({ type,buffer });
    sf::Sound sound;
    sound.setBuffer(buffers_[type]);
    sounds_.insert({ type,sound });
};
