#include "GameState.h"
#include "AudioSystem.h"
#include "GraphicsSystem.h"
#include "PhysicsSystem.h"
#include "InputHandler.h"
#include "SpawnerSystem.h"
#include <fstream>


Entity* getMyTank(std::vector<Entity>& scene);
bool isDead(Entity* tank);

GameState* ClientPlayingGameState::update(sf::RenderWindow& window) {

	int map_width = 0;
	int map_height = 0;

	std::vector<Entity> scene;
	
	MapSpawner ws;
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
				scene.push_back(ws.Spawn(curr_pos, '0')[0]);
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

	Entity* my_tank = getMyTank(scene);
	bool ESC_pressed = false;

	while (!isDead(my_tank) && !ESC_pressed) {
		ps.updatePositions(handleInput(window), scene);
		gs.renderScene(scene);
		as.playEffects(scene);
	}
	return this;
}

Entity* getMyTank(std::vector<Entity>& scene) {
    Entity* my_tank = nullptr;

    for (int i = 0; i < scene.size(); ++i) {
        if (scene[i].getEntityID() == -1 && scene[i].getType() == ObjectType::Tank)
            my_tank = &scene[i];
    }
    return my_tank;
}


bool isDead(Entity* tank) {
    HealthComponent* health_component = dynamic_cast<HealthComponent*>(tank->getComponentByID(ComponentID::HealthComponent));
    return health_component->getHealth() > 0;
}
