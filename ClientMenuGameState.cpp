#pragma once
#include "GameState.h"
#include "SpawnerSystem.h"
#include <iostream>
#include<sstream>

ClientMenuGameState::ClientMenuGameState() {
	id_ = GameStateId::ClientMenu;

	// Спавн клиентского меню тут
	BannerSpawner banner_spawner;
	ButtonSpawner button_spawner;

	//Спавн фона клиентского меню
	Position banner_pos;
	banner_pos.x = 0;
	banner_pos.y = 0;

	Entity* banner_ent = nullptr;

	banner_ent = banner_spawner.Spawn(banner_pos, 'c');
	banner_ent->setEntityID(1);

	scene_.push_back(banner_ent);
	addSystem(SystemId::MenuSystemId);
	addSystem(SystemId::GraphicsSystemId);
	//addSystem(SystemId::MusicSystemId);

	//Спавн кнопки назад клиенского меню
	Position back_button_pos;	// Эта кнопка будет возвращать игрока в главное меню
	back_button_pos.x = 200;  
	back_button_pos.y = 800;

	Entity* back_button_ent = nullptr;

	back_button_ent = button_spawner.Spawn(back_button_pos, 'b');
	back_button_ent->setEntityID(1);

	scene_.push_back(back_button_ent);

	// Спавн кнопки "попробовать подключиться"

	Position connect_button_pos;
	connect_button_pos.x = 1400;
	connect_button_pos.y = 800;

	Entity* connect_button_ent = nullptr;

	connect_button_ent = button_spawner.Spawn(connect_button_pos, 't');
	connect_button_ent->setEntityID(1);

	scene_.push_back(connect_button_ent);


	// Спавн Выбора скина танка. Две башни и два корпуса
	Position hull_1_pos;
	Position hull_2_pos;
	Position turret_1_pos;
	Position turret_2_pos;

	hull_1_pos.x = 1300;
	hull_1_pos.y = 200;

	hull_2_pos.x = 1600;
	hull_2_pos.y = 200;

	turret_1_pos.x = 1300;
	turret_1_pos.y = 500;

	turret_2_pos.x = 1600;
	turret_2_pos.y = 500;


	Entity* hukk_1_ent = nullptr;
	Entity* hukk_2_ent = nullptr;
	Entity* turret_1_ent = nullptr;
	Entity* turret_2_ent = nullptr;

	hukk_1_ent = button_spawner.Spawn(hull_1_pos, 'p');
	hukk_1_ent->setEntityID(1);
	scene_.push_back(hukk_1_ent);

	hukk_2_ent = button_spawner.Spawn(hull_2_pos, 'o');
	hukk_2_ent->setEntityID(1);
	scene_.push_back(hukk_2_ent);

	turret_1_ent = button_spawner.Spawn(turret_1_pos, 'i');
	turret_1_ent->setEntityID(1);
	scene_.push_back(turret_1_ent);

	turret_2_ent = button_spawner.Spawn(turret_2_pos, 'u');
	turret_2_ent->setEntityID(1);
	scene_.push_back(turret_2_ent);
}

GameStateId ClientMenuGameState::update(sf::RenderWindow& window) {
	for (int i = 0; i < systems_.size(); ++i) {
		systems_[i]->update(window, scene_);
	}

	sf::Event event;
	std::ostringstream player_input;
	sf::Font font;


	font.loadFromFile("CyrilicOld.ttf");
	sf::Text text("", font, 20);
	//text.setColor(sf::Color::Red);
	text.setStyle(sf::Text::Bold);

	text.setPosition(800, 800);

	std::string ip = std::string("");

	while (window.pollEvent(event)) {

		if (event.type == sf::Event::TextEntered)
		{
			if (event.text.unicode < 128) {
				//std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << std::endl;
				ip += (static_cast<char>(event.text.unicode));
				/*std::cout << "Current ip: " << ip << std::endl;*/
				/*player_input << static_cast<char>(event.text.unicode);
				text.setString(player_input.str());*/
			}
		}
	}

	if (ip == std::string("a")) {
		return GameStateId::ClientPlaying;
	}

	return id_;
}