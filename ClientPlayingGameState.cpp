#include "GameState.h"
#include "AudioSystem.h"
#include "GraphicsSystem.h"
#include "PhysicsSystem.h"
#include "InputHandler.h"
#include "SpawnerSystem.h"
#include <fstream>

GameState* ClientPlayingGameState::update(sf::RenderWindow& window) {

	int map_width = 0;
	int map_height = 0;

	std::vector<Entity> to_add;

	std::ifstream map_file("Maps/lvl1.txt");

	map_file >> map_width;
	map_file >> map_height;

	for (int i = 0; i < map_height; ++i)
		for (int j = 0; j < map_width; ++j) {
			char current_block = 0;
			map_file >> current_block;

			switch (current_block) {
			case 'w':
				break;
			case' ':
				break;
			case 'b':
				break;
			default:
				break;
			}


		}


	AudioSystem as;
	GraphicsSystem gs;
	PhysicsSystem ps;

	ps.updatePositions(handleInput(window));

	return this;
}
