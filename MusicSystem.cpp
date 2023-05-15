#pragma once
#include "SoundComponent.h"
#include "MusicComponent.h"
#include "Entity.h"
#include "MusicSystem.h"
#include "SFML/Graphics.hpp"

int MusicSystem::update(sf::RenderWindow& window, std::vector<Entity>& scene){

	for (int i = 0; i < scene.size(); ++i) {

		MusicComponent* current_music = dynamic_cast<MusicComponent*>(scene[i].getComponentByID(ComponentID::MusicComponent));
		if (current_music) {
			current_music->playMusic();
		}
	}
	return 0;
}