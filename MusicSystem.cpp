#include "SoundComponent.h"
#include "MusicComponent.h"
#include "Entity.h"
#include "MusicSystem.h"

void MusicSystem::playMusic(std::vector<Entity>& scene) {

	for (int i = 0; i < scene.size(); ++i) {

		MusicComponent* current_music = dynamic_cast<MusicComponent*>(scene[i].getComponentByID(ComponentID::MusicComponent));
		if (current_music) {
			current_music->playMusic();
		}
	}
}