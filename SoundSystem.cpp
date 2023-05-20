#pragma once
#include "SoundSystem.h"
#include "SoundComponent.h"
#include <queue>


int SoundSystem::update(sf::RenderWindow& window, std::vector<Entity*>& scene) {
	std::queue<sf::Sound*> sound_queue;

	for (int i = 0; i < scene.size(); ++i) {

		sf::Sound* curr_sound;
		SoundComponent* current_music = dynamic_cast<SoundComponent*>(scene[i]->getComponentByID(ComponentID::SoundComponent));
		if (current_music) {
			
			curr_sound = current_music->getSound(SoundType::RunnungSound);
			curr_sound->setVolume(10.f);
			sound_queue.push(curr_sound);
			//sf::SoundSource::Status status = curr_sound.getStatus();
			//if (status != sf::SoundSource::Playing) {
				//curr_sound = current_music->getSound(SoundType::RunnungSound);
				//curr_sound.play();
				//return 0;
			//}
		}
	}

	while (!sound_queue.empty()) {
		sf::Sound* curr_sound = sound_queue.front();
		sound_queue.pop();

		sf::SoundSource::Status status = curr_sound->getStatus();
			if (status != sf::SoundSource::Playing) {
				//curr_sound = current_music->getSound(SoundType::RunnungSound);
				curr_sound->play();////////////////////////////////////////////////////////////////////////////////////////////////
				return 0;
			}
		//curr_sound->play();

	}

	return 0;
} 