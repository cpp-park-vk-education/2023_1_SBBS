#pragma once
#include "GameState.h"
#include "SpawnerSystem.h"
#include "SpawnID.h"

SinglePlayerMenuGameState::SinglePlayerMenuGameState() {
	id_ = GameStateId::SingleMenu;

	addSystem(SystemId::GraphicsSystemId);
	addSystem(SystemId::MenuSystemId);
	addSystem(SystemId::MusicSystemId);

	BannerSpawner banner_spawner;
	ButtonSpawner button_spawner;


	//Спавн фона одиночного меню
	Position banner_pos(0, 0);

	Entity* temp_ent = nullptr;

	temp_ent = banner_spawner.Spawn(banner_pos, single_banner);//// убрать магическую константу
	scene_.push_back(temp_ent);


	//Спавн кнопки назад
	Position back_button_pos(200, 800);	// Эта кнопка будет возвращать игрока в главное меню


	temp_ent = button_spawner.Spawn(back_button_pos, back);
	scene_.push_back(temp_ent);

	// Спавн кнопки "Играть"
	Position connect_button_pos(1400, 800);

	temp_ent = button_spawner.Spawn(connect_button_pos, play);
	scene_.push_back(temp_ent);
}

GameStateId SinglePlayerMenuGameState::update(sf::RenderWindow& window) {
	return id_;
}

