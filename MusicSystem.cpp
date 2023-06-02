#pragma once
#include "SoundComponent.h"
#include "MusicComponent.h"
#include "Entity.h"
#include "MusicSystem.h"
#include "SFML/Graphics.hpp"

int MusicSystem::update(sf::RenderWindow& window, std::vector<Entity*>& scene){

	for (int i = 0; i < scene.size(); ++i) {

		MusicComponent* current_music_comp = dynamic_cast<MusicComponent*>(scene[i]->getComponentByID(ComponentID::MusicComponent));
		if (current_music_comp) {

			if (!curr_music) {
				curr_music = current_music_comp->getMusic();
				curr_music->play();
			}
			else if (curr_music->getStatus() != sf::SoundSource::Playing) {
				curr_music = current_music_comp->getMusic();
				curr_music->play();
			}
		}
	}
	return 0;
}