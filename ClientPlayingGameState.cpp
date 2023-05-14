#include "GameState.h"
#include "AudioSystem.h"
#include "GraphicsSystem.h"
#include "PhysicsSystem.h"
#include "InputHandler.h"
#include "SpawnerSystem.h"
#include <fstream>
#include <iostream>

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


			if ((i * map_width + j) == 61) {
				int x = 0;
			}

			Position curr_pos;
			curr_pos.x = j * 50;
			curr_pos.y = i * 50;
			Entity temp_ent(ObjectType::Map);

			switch (current_block) {
			case 'w':
				temp_ent = ws.Spawn(curr_pos, 'w')[0];
				temp_ent.setEntityID(i * map_width + j);
				scene.push_back(temp_ent);
				break;
			case's':
				temp_ent = ws.Spawn(curr_pos, 's')[0];
				temp_ent.setEntityID(i * map_width + j);
				scene.push_back(temp_ent);
				break;
			case ' ':
				std::cout << "Have s here\n";
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
		gs.renderScene(scene,window);
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
	if (!tank)
		return false;

    HealthComponent* health_component = dynamic_cast<HealthComponent*>(tank->getComponentByID(ComponentID::HealthComponent));
    return health_component->getHealth() > 0;
}
