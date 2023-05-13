#pragma once
#include "Entity.h"
#include "Component.h"

class SoundComponent : public Component {
public:
    void playSound(const SoundType& type);

    void setSound();

private:
    std::unordered_map<SoundType, sf::Sound> _comp;

};