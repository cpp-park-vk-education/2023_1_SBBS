#pragma once
#include "SoundSystem.h"
#include "SoundComponent.h"

int SoundSystem::update(sf::RenderWindow& window, std::vector<Entity>& scene) {

	for (int i = 0; i < scene.size(); ++i) {

		SoundComponent* current_music = dynamic_cast<SoundComponent*>(scene[i].getComponentByID(ComponentID::MusicComponent));
	}

	return 0;
} 