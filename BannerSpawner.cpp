#pragma once
#include "SpawnerSystem.h"
#include "GraphicsComponent.h"
#include "PositionComponent.h"
#include "MusicComponent.h"
#include "Types.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>

Entity BannerSpawner::Spawn(Position position, char subType) {

	Entity to_add(ObjectType::Banner);

	GraphicsComponent* graph_to_add = new GraphicsComponent();
	PositionComponent* pos_to_add = new PositionComponent();
	MusicComponent* music_to_add = new MusicComponent(std::string("Sound/music_track_1.ogg"));

	Position pos_struc_to_add(position.x, position.y);
	pos_to_add->setPosition(pos_struc_to_add);

	sf::Image img;

	switch (subType) {
	case 'm': // main menu banner
		img.loadFromFile("Image/AUF.png");
		graph_to_add->setImage(img);
	}


	to_add.putComponent(ComponentID::MusicComponent, music_to_add);
	to_add.putComponent(ComponentID::GraphicsComponent, graph_to_add);
	to_add.putComponent(ComponentID::PositionComponent, pos_to_add);

	return to_add;
}