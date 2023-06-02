#pragma once
#include "GameState.h"
#include "SpawnerSystem.h"
#include "SpawnID.h"


HostMenuGameState::HostMenuGameState() {
	id_ = GameStateId::HostMenu;

	// Спавн хостового меню тут
	BannerSpawner banner_spawner;
	ButtonSpawner button_spawner;

	//Спавн фона хостового меню
	Position banner_pos(0, 0);


	Entity* temp_ent = nullptr;

	temp_ent = banner_spawner.Spawn(banner_pos, host_banner);
	temp_ent->setEntityID(1);

	scene_.push_back(temp_ent);

	addSystem(SystemId::MenuSystemId);
	addSystem(SystemId::GraphicsSystemId);
	//addSystem(SystemId::MusicSystemId);


	//Спавн кнопки назад хостового меню
	Position back_button_pos(200, 800);	// Эта кнопка будет возвращать игрока в главное меню


	temp_ent = button_spawner.Spawn(back_button_pos, back);
	temp_ent->setEntityID(1);

	scene_.push_back(temp_ent);

	// Спавн кнопки "Играть"
	Position connect_button_pos(1400, 800);

	temp_ent = button_spawner.Spawn(connect_button_pos, play);
	scene_.push_back(temp_ent);

	// Спавн Выбора скина танка. Две башни и два корпуса
	Position hull_1_pos(1300, 350);
	Position hull_2_pos(1650, 350);
	Position turret_1_pos(1300, 600);
	Position turret_2_pos(1650, 600);

	temp_ent = button_spawner.Spawn(hull_1_pos, tank_hull_1);
	scene_.push_back(temp_ent);

	temp_ent = button_spawner.Spawn(hull_2_pos, tank_hull_2);
	scene_.push_back(temp_ent);

	temp_ent = button_spawner.Spawn(turret_1_pos, tank_turret_1);
	scene_.push_back(temp_ent);

	temp_ent = button_spawner.Spawn(turret_2_pos, tank_turret_2);
	scene_.push_back(temp_ent);
}

GameStateId HostMenuGameState::update(sf::RenderWindow& window) {
	for (int i = 0; i < systems_.size(); ++i) {
		int sys_output = systems_[i]->update(window, scene_); // ненулевой будет только в menusystem
	}
	return id_;
}