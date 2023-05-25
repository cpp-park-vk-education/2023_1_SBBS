#pragma once
#include "SpawnerSystem.h"
#include "GraphicsComponent.h"
#include "PositionComponent.h"
#include "MusicComponent.h"
#include "Types.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include "SpawnID.h"

Entity* BannerSpawner::Spawn(Position position, int subType) {

	Entity* to_add = new Entity(ObjectType::Banner);

	GraphicsComponent* graph_to_add = nullptr; 
	PositionComponent* pos_to_add = new PositionComponent();
	MusicComponent* music_to_add = new MusicComponent;//("Sound/music_track_1.ogg"));

	Position pos_struc_to_add(position.x, position.y);
	pos_to_add->setPosition(pos_struc_to_add);

	sf::Image img;

	switch (subType) {
	case main_banner: // main menu banner
		graph_to_add = new GraphicsComponent();
		img.loadFromFile("Image/main_banner_2.png");
		graph_to_add->setAliveImage(img);
		music_to_add->setMusic(std::string("Sound/music_track_1.ogg"));
		break;

	case client_banner: // client menu banner
		graph_to_add = new GraphicsComponent();
		img.loadFromFile("Image/client_banner.png");
		graph_to_add->setAliveImage(img);
		//music_to_add->setMusic(std::string("Sound/music_track_1.ogg"));
		break;

	case host_banner: // host menu banner
		graph_to_add = new GraphicsComponent();
		img.loadFromFile("Image/host_banner.png");
		graph_to_add->setAliveImage(img);
		//music_to_add->setMusic(std::string("Sound/music_track_1.ogg"));
		break;

	case single_banner: // single menu banner
		graph_to_add = new GraphicsComponent();
		img.loadFromFile("Image/host_banner.png");
		graph_to_add->setAliveImage(img);
		//music_to_add->setMusic(std::string("Sound/music_track_1.ogg"));
		break;

	case 'g': // game music
		music_to_add->setMusic(std::string("Sound/music_track_2.wav"));
		break;
	default:
		break;
	}


	if (graph_to_add)
		to_add->putComponent(ComponentID::GraphicsComponent, graph_to_add);
	to_add->putComponent(ComponentID::PositionComponent, pos_to_add);
	to_add->putComponent(ComponentID::MusicComponent, music_to_add);


	return to_add;
}