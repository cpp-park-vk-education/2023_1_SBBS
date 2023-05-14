#include "GameState.h"
#include "MusicSystem.h"
#include "GraphicsSystem.h"
#include "PhysicsSystem.h"
#include "InputHandler.h"
#include "SpawnerSystem.h"
#include <fstream>
#include <iostream>
#include <Windows.h>

Entity* getMyTank(std::vector<Entity>& scene);
bool isDead(Entity* tank);

GameState* ClientPlayingGameState::update(sf::RenderWindow& window) {

	int map_width = 0;
	int map_height = 0;

	std::vector<Entity> scene;
	
	MapSpawner ws;
	TankSpawner ts;
	std::ifstream map_file("Maps/lvl4.txt");

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
			curr_pos.x = j * 50 + 25;
			curr_pos.y = i * 50 + 25;
			std::vector<Entity> temp_ent{ Entity(ObjectType::Map) };

			switch (current_block) {
			case 'w':
				temp_ent = ws.Spawn(curr_pos, 'w');
				temp_ent[0].setEntityID(i * map_width + j);
				scene.push_back(temp_ent[0]);
				break;
			case's':
				temp_ent = ws.Spawn(curr_pos, 's');
				temp_ent[0].setEntityID(i * map_width + j);
				scene.push_back(temp_ent[0]);
				break;
			case'd':
				temp_ent = ws.Spawn(curr_pos, 'd');
				temp_ent[0].setEntityID(i * map_width + j);
				scene.push_back(temp_ent[0]);
				break;
			case 't':
				temp_ent = ts.Spawn(curr_pos, '1');
				scene.insert(scene.end(), temp_ent.begin(), temp_ent.end());
				temp_ent = ws.Spawn(curr_pos, 's');
				temp_ent[0].setEntityID(i * map_width + j);
				scene.push_back(temp_ent[0]);
				break;
			default:
				break;
			}
		}
	BannerSpawner bs;
	scene.push_back(bs.Spawn(Position(0, 0), 's')[0]);
		
	MusicSystem ms;
	GraphicsSystem gs;
	PhysicsSystem ps;

	ms.playMusic(scene);

	Entity* my_tank = getMyTank(scene);
	bool ESC_pressed = false;

	while (!isDead(my_tank) && !ESC_pressed && window.isOpen()) {
		ps.updatePositions(handleInput(window), scene);
		gs.renderScene(scene,window);
		
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
	return false;

	if (!tank)
		return false;

    HealthComponent* health_component = dynamic_cast<HealthComponent*>(tank->getComponentByID(ComponentID::HealthComponent));
    return health_component->getHealth() > 0;
}
