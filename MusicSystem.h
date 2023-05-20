#pragma once
#include "System.h"
#include "Types.h"
#include "Entity.h"
#include <SFML/Audio.hpp>


class MusicSystem : public System {
public:

    int update(sf::RenderWindow& window, std::vector<Entity*>& scene) override;

    ~MusicSystem() override{
        curr_music->stop();
    }

private:
    sf::Music* curr_music = nullptr;
};