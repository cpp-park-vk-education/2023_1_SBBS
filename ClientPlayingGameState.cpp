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

	std::vector<Entity> scene;
	
	WallSpawner ws;
	std::ifstream map_file("Maps/lvl1.txt");

	map_file >> map_width;
	map_file >> map_height;

	for (int i = 0; i < map_height; ++i)
		for (int j = 0; j < map_width; ++j) {
			char current_block = 0;
			map_file >> current_block;

			Position curr_pos;
			curr_pos.x = j * 10;
			curr_pos.y = i * 10;

			switch (current_block) {
			case 'w':
				scene.push_back(ws.Spawn(curr_pos, 'w')[0]);
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
