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
#include "GameSingleton.h"

void PlayingState::setMyTank() {

    for (int i = 0; i < scene_.size(); ++i) {
        if (scene_[i] && scene_[i]->getEntityID() == Game::getInstance().getMyEntityId() && scene_[i]->getType() == ObjectType::Tank)
            my_tank_ = scene_[i];
    }
}

bool PlayingState::isDead(Entity* tank) {
    if (!tank)
        return true;

    HealthComponent* health_component = dynamic_cast<HealthComponent*>(tank->getComponentByID(ComponentID::HealthComponent));
    return health_component->getHealth() < 0;
}

void PlayingState::generateMap(const std::string& map_name) {
	const int block_size = 50; ////////потом как-то извне задавать

	int map_width = 0;
	int map_height = 0;
	int tank_amount = 0;

	MapSpawner ws;
	BannerSpawner bs;
	TankSpawner player_tank_spawner;
	TurretSpawner player_turret_spawner;
	TankSpawner opponent_tank_spawner;
	TurretSpawner opponent_turret_spawner;

	player_tank_spawner.setOwnerType(OwnerType::Player);
	player_turret_spawner.setOwnerType(OwnerType::Player);

	switch (id_) { 
	case GameStateId::HostPlaying:
		opponent_tank_spawner.setOwnerType(OwnerType::Network);
		opponent_turret_spawner.setOwnerType(OwnerType::Network);
		break;
	case GameStateId::ClientPlaying:
		opponent_tank_spawner.setOwnerType(OwnerType::Network);
		opponent_turret_spawner.setOwnerType(OwnerType::Network);
		break;
	case GameStateId::SinglePlaying:
		opponent_tank_spawner.setOwnerType(OwnerType::Bot);
		opponent_turret_spawner.setOwnerType(OwnerType::Bot);
		break;
	default:
		break;
	}

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
			Entity* temp_ent = ws.Spawn(curr_pos, current_block);
			scene_.push_back(temp_ent);
		}

	/// после генерации карты 
	for (int i = 0; i < scene_.size(); ++i) {
		for (int j = 0; j < scene_.size() - 1; ++j) {
			if (scene_[j]->getType() == ObjectType::Wall && scene_[j]->getType() == ObjectType::Wall)
				std::swap(scene_[j], scene_[j + 1]);
		}
	}

	for (int i = 0; i < scene_.size(); ++i) {
		if (scene_[i]->getType() == ObjectType::Wall) {
			Game::getInstance().setFirstCollidable(i);
		}
	}

	
	tank_amount = Game::getInstance().getNumberOfPlayers();
	/// tank spawn 
	for (int i = 1; i <= tank_amount; ++i)
	{
		int tank_x = 0;
		int tank_y = 0;

		Spawner* curr_tank_spawner = &(i == Game::getInstance().getMyEntityId()  ? player_tank_spawner : opponent_tank_spawner);
		Spawner* curr_turret_spawner = &(i == Game::getInstance().getMyEntityId() ? player_turret_spawner : opponent_turret_spawner);

		map_file >> tank_x >> tank_y;
		Position curr_pos;
		curr_pos.x = tank_x * block_size + int(block_size / 2);
		curr_pos.y = tank_y * block_size + int(block_size / 2);

		Entity* temp_ent;

		temp_ent = curr_tank_spawner->Spawn(curr_pos, Game::getInstance().getHullType(i-1));
		temp_ent->setEntityID(i);
		scene_.push_back(temp_ent);
		{///// спавн башни
			PositionComponent* tank_pos = dynamic_cast<PositionComponent*>(temp_ent->getComponentByID(ComponentID::PositionComponent));
			temp_ent = curr_turret_spawner->Spawn(curr_pos, Game::getInstance().getTurretType(i - 1));
			PositionComponent* turr_pos = dynamic_cast<PositionComponent*>(temp_ent->getComponentByID(ComponentID::PositionComponent));
			turr_pos->setParent(tank_pos);
		}

		temp_ent->setEntityID(i);
		scene_.push_back(temp_ent);
	}

	Entity* temp_ent;
	temp_ent = bs.Spawn(Position(0, 0), 'g');
	scene_.push_back(temp_ent);
}
