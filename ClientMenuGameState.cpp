#pragma once
#include "GameState.h"
#include "SpawnerSystem.h"
#include "ButtonID.h"
#include "BannerID.h"
#include "InputHandler.h"
#include <iostream>
#include <sstream>

ClientMenuGameState::ClientMenuGameState() {
	id_ = GameStateId::ClientMenu;

	// Спавн клиентского меню тут
	BannerSpawner banner_spawner;
	ButtonSpawner button_spawner;
	addSystem(SystemId::MenuSystemId);
	addSystem(SystemId::GraphicsSystemId);
	//addSystem(SystemId::MusicSystemId);

	//Спавн фона клиентского меню
	Position banner_pos(0, 0);

	Entity* temp_ent = nullptr;

	temp_ent = banner_spawner.Spawn(banner_pos, client_banner);//// убрать магическую константу
	scene_.push_back(temp_ent);

	//Спавн кнопки назад клиенского меню
	Position back_button_pos;	// Эта кнопка будет возвращать игрока в главное меню
	back_button_pos.x = 200;  
	back_button_pos.y = 800;


	temp_ent = button_spawner.Spawn(back_button_pos, back);
	scene_.push_back(temp_ent);

	// Спавн кнопки "попробовать подключиться"

	Position connect_button_pos(1400, 800);

	temp_ent = button_spawner.Spawn(connect_button_pos, try_to_connect);
	scene_.push_back(temp_ent);

	// Спавн Выбора скина танка. Две башни и два корпуса
	/////////////////////////////////////////////////////можно сократить
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

GameStateId ClientMenuGameState::update(sf::RenderWindow& window) {

	Input input;
	input.handleInput(window);

	int chosen_button_id = 0;
	for (int i = 0; i < systems_.size(); ++i) {
		int sys_output = systems_[i]->update(window, scene_); // ненулевой будет только в menusystem
		if (sys_output) {
			chosen_button_id = sys_output;
		}
	}
	// вводить ip и получить название карты
	setStateArgument(std::string("Maps/lvlTest2.txt"));
	// получить entity id 

	if (input.shoot_) { ////////////////////////////// shoot не понятно, поменять на mouce click
		switch (chosen_button_id)
		{
		case try_to_connect_button_id:
			return GameStateId::ClientPlaying;
			break;
		case tank_hull_1_button_id:
			setTankHull(tank_hull_1);
			break;
		case tank_hull_2_button_id:
			setTankHull(tank_hull_2);
			break;
		case tank_turret_1_button_id:
			setTankTurret(tank_turret_1);
			break;
		case tank_turret_2_button_id:
			setTankTurret(tank_turret_2);
			break;
		case back_button_id:
			return GameStateId::MainMenu;
			break;
		default:
			return id_;
			break;
		}
	}

	// сделал область видимости чтобы ее свернуть, много букв 
	{
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
	}

	return id_;
}
