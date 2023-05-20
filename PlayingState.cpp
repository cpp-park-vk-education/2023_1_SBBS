#pragma once
#include "GameState.h"
#include "MusicSystem.h"
#include "GraphicsSystem.h"
#include "HealthComponent.h"
#include "PositionComponent.h"
#include "PhysicsSystem.h"
#include "InputHandler.h"
#include "SpawnerSystem.h"
#include <fstream>
#include "GameState.h"
#include "HealthComponent.h"

Entity* PlayingState::getMyTank() {
    Entity* my_tank = nullptr;

    for (int i = 0; i < scene_.size(); ++i) {
        if (scene_[i] && scene_[i]->getEntityID() == -1 && scene_[i]->getType() == ObjectType::Tank)
            my_tank = scene_[i];
    }
    return my_tank;
}

bool PlayingState::isDead(Entity* tank) {
    return false;

    if (!tank)
        return false;

    HealthComponent* health_component = dynamic_cast<HealthComponent*>(tank->getComponentByID(ComponentID::HealthComponent));
    return health_component->getHealth() > 0;
}

void PlayingState::generateMap(const std::string& map_name, int my_tank_id) {

	const int block_size = 50; ////////потом как-то извне задавать

	int map_width = 0;
	int map_height = 0;
	int tank_amount = 0;

	MapSpawner ws;
	TankSpawner ts;
	BannerSpawner bs;
	TurretSpawner tr;
	//scene.push_back(bs.Spawn(Position(0, 0), 's')[0]); /// menu music

	std::ifstream map_file(map_name);

	map_file >> map_width;
	map_file >> map_height;
	map_file >> tank_amount;

	/// map generation
	for (int i = 0; i < map_height; ++i)
		for (int j = 0; j < map_width; ++j) {
			char current_block = 0;
			map_file >> current_block;

			Position curr_pos;
			curr_pos.x = j * block_size + int(block_size / 2);
			curr_pos.y = i * block_size + int(block_size / 2);
			Entity* temp_ent;

			switch (current_block) {
			case 'w':
				temp_ent = ws.Spawn(curr_pos, 'w');
				scene_.push_back(temp_ent);
				break;
			case's':
				temp_ent = ws.Spawn(curr_pos, 's');
				scene_.push_back(temp_ent);
				break;
			case'd':
				temp_ent = ws.Spawn(curr_pos, 'd');
				scene_.push_back(temp_ent);
				break;
			default:
				break;
			}
		}

	/// tank spawn 
	for (int i = 0; i < tank_amount; ++i)
	{
		int tank_x = 0;
		int tank_y = 0;

		map_file >> tank_x >> tank_y;
		Position curr_pos;
		curr_pos.x = tank_x * block_size + int(block_size / 2);
		curr_pos.y = tank_y * block_size + int(block_size / 2);

		Entity* temp_ent;
		temp_ent = ts.Spawn(curr_pos, '1');
		if (i == my_tank_id)
			temp_ent->setEntityID(-1);
		else
			temp_ent->setEntityID(i + 1);


		scene_.push_back(temp_ent);
		{
			PositionComponent* tank_pos = dynamic_cast<PositionComponent*>(temp_ent->getComponentByID(ComponentID::PositionComponent));
			temp_ent = tr.Spawn(curr_pos, '1');
			PositionComponent* turr_pos = dynamic_cast<PositionComponent*>(temp_ent->getComponentByID(ComponentID::PositionComponent));
			turr_pos->setParent(tank_pos);
		}

		if (i == my_tank_id)
			temp_ent->setEntityID(-1);
		else
			temp_ent->setEntityID(i + 1);

		scene_.push_back(temp_ent);
	}

	Entity* temp_ent;
	temp_ent = bs.Spawn(Position(0, 0), 'g');
	scene_.push_back(temp_ent);
}
