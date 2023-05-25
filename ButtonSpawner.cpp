#pragma once
#include "SpawnerSystem.h"
#include "GraphicsComponent.h"
#include "PositionComponent.h"
#include "ClickComponent.h"
#include "SpawnID.h"
#include <fstream>
#include <vector>

Entity* ButtonSpawner::Spawn(Position position, int subType) {
	int height = 150;
	int width = 300;

	Entity* to_add = new Entity(ObjectType::Button);

	GraphicsComponent* graph_to_add = new GraphicsComponent();
	PositionComponent* pos_to_add = new PositionComponent();
	ClickComponent* click_to_add = new ClickComponent(position.x, position.y, width, height);

	Position pos_struc_to_add(position.x, position.y);
	pos_to_add->setPosition(pos_struc_to_add);

	sf::Image img;

	switch (subType) {
		case host_game: // host game button
			img.loadFromFile("Image/GUI_host_game.png");
			graph_to_add->setAliveImage(img);
			click_to_add->setButtonId(host_game_button_id);
			break;

		case client_game: //connect to game button (client state menu)
			img.loadFromFile("Image/GUI_connect_game.png");
			graph_to_add->setAliveImage(img);
			click_to_add->setButtonId(client_game_button_id);
			break;

		case back:  // back button
			img.loadFromFile("Image/GUI_back_button.png");
			graph_to_add->setAliveImage(img);
			click_to_add->setButtonId(back_button_id);
			break;

		case single_game:  // single game button
			img.loadFromFile("Image/GUI_single_game_button.png");
			graph_to_add->setAliveImage(img);
			click_to_add->setButtonId(single_game_button_id);
			break;

		case try_to_connect:  // try to connect button 
			img.loadFromFile("Image/GUI_try_to_connect_game.png");
			graph_to_add->setAliveImage(img);
			click_to_add->setButtonId(try_to_connect_button_id);
			break;

		case tank_hull_1:  // tank 1 hull
			img.loadFromFile("Image/tank_1_body_100_100.png");
			graph_to_add->setAliveImage(img, true);
			click_to_add->setButtonId(tank_hull_1_button_id);
			break;

		case tank_hull_2:  // tank 2 hull
			img.loadFromFile("Image/tank_2_body_100_100.png");
			graph_to_add->setAliveImage(img, true);
			click_to_add->setButtonId(tank_hull_2_button_id);
			break;

		case tank_turret_1:  // tank 1 turret
			img.loadFromFile("Image/tank_1_gun_100_100.png");
			graph_to_add->setAliveImage(img, true);
			click_to_add->setButtonId(tank_turret_1_button_id);
			break;

		case tank_turret_2:  // tank 2 turret
			img.loadFromFile("Image/tank_2_gun_100_100.png");
			graph_to_add->setAliveImage(img, true);
			click_to_add->setButtonId(tank_turret_2_button_id);
			break;

		case play:  // play button
			img.loadFromFile("Image/GUI_play_button.png");
			graph_to_add->setAliveImage(img);
			click_to_add->setButtonId(play_button_id);
			break;

		case map_1: // map_1 button
			img.loadFromFile("Image/map_1_.png");
			graph_to_add->setAliveImage(img);
			click_to_add->setButtonId(map_1_button_id);
			break;

		case map_2: // map_2 button
			img.loadFromFile("Image/map_2_.png");
			graph_to_add->setAliveImage(img);
			click_to_add->setButtonId(map_2_button_id);
			break;

		case map_3: // map_3 button
			img.loadFromFile("Image/map_3_.png");
			graph_to_add->setAliveImage(img);
			click_to_add->setButtonId(map_3_button_id);
			break;

		case map_4: // map_4 button
			img.loadFromFile("Image/map_4_.png");
			graph_to_add->setAliveImage(img);
			click_to_add->setButtonId(map_4_button_id);
			break;

		//case map_2_contoured: // map_2 button
		//	img.loadFromFile("Image/map_2_contoured.png");
		//	graph_to_add->setAliveImage(img);
		//	break;

		//case map_3_contoured: // map_3 button
		//	img.loadFromFile("Image/map_3_contoured.png");
		//	graph_to_add->setAliveImage(img);
		//	break;

		//case map_4_contoured: // map_4 button
		//	img.loadFromFile("Image/map_4_contoured.png");
		//	graph_to_add->setAliveImage(img);
		//	break;

		default: break;
	}


	to_add->putComponent(ComponentID::ClickComponent, click_to_add);
	to_add->putComponent(ComponentID::GraphicsComponent, graph_to_add);
	to_add->putComponent(ComponentID::PositionComponent, pos_to_add);
	return to_add;
}