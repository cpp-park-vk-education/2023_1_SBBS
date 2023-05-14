#pragma once
#include "SpawnerSystem.h"
#include "GraphicsComponent.h"
#include "PositionComponent.h"
#include "MusicComponent.h"
#include "Types.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>

std::vector<Entity> BannerSpawner::Spawn(Position position, char subType) {
	std::vector<Entity> to_add_vec;

	Entity to_add(ObjectType::Map);

	GraphicsComponent* graph_to_add = new GraphicsComponent();
	PositionComponent* pos_to_add = new PositionComponent();


	sf::Image img;
	img.loadFromFile("Image/Stone_100_100.png");
	graph_to_add->setImage(img);

	MusicComponent* music_to_add = new MusicComponent(std::string("Sound/music_track_1.ogg"));

	Position pos_struc_to_add(position.x, position.y);
	pos_to_add->setPosition(pos_struc_to_add);

	to_add.putComponent(ComponentID::MusicComponent, music_to_add);
	to_add.putComponent(ComponentID::GraphicsComponent, graph_to_add);
	to_add.putComponent(ComponentID::PositionComponent, pos_to_add);
	to_add_vec.push_back(to_add);
	return to_add_vec;
}