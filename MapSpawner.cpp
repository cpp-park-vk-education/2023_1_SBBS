#pragma once
#include "SpawnerSystem.h"
#include "GraphicsComponent.h"
#include "CollisionComponent.h"
#include "PositionComponent.h"
#include "HealthComponent.h"
#include "Types.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include "SpawnID.h"

Entity* MapSpawner::Spawn(Position position, int subType) {
	Entity* to_add = new Entity(ObjectType::Map);
	static sf::Image img;
	
	GraphicsComponent* graph_to_add = new GraphicsComponent();
	PositionComponent* pos_to_add = new PositionComponent();
	CollisionComponent* coll_to_add = nullptr;
	HealthComponent* health_to_add = nullptr;// new HealthComponent(true, 100);

	Position pos_struc_to_add(position.x, position.y);
	pos_to_add->setPosition(pos_struc_to_add);


	//грамотный switch - case  написать 
	switch (subType)
	{
	case stone_wall : // stone wall 
		img.loadFromFile("Image/Stone_100_100.png");
		graph_to_add->setAliveImage(img);
		coll_to_add = new CollisionComponent(position, 0, 50, 50);
		health_to_add = new HealthComponent(false, false,false,to_add, 100);
		break;

	case wood_wall: // wood wall 
		img.loadFromFile("Image/Wood_100_100.png");
		graph_to_add->setAliveImage(img);
		img.loadFromFile("Image/dead_wood_100_100.png");
		graph_to_add->setDeadImage(img);
		coll_to_add = new CollisionComponent(position, 0, 50, 50);
		health_to_add = new HealthComponent(true, true, false, to_add, 100);
		break;

	case sand : // sand floor
		img.loadFromFile("Image/Sand_1_100_100.png");
		graph_to_add->setAliveImage(img);
		break;

	case dirt: // dirt floor
		img.loadFromFile("Image/Dirt_100_100.png");
		graph_to_add->setAliveImage(img);
		break;

	case smooth_stone: // snooth stone floor
		img.loadFromFile("Image/smooth_stone_100_100.png");
		graph_to_add->setAliveImage(img);
		break;

	//case 'c': // cave floor
	//	img.loadFromFile("Image/Cave_100_100.png");
	//	graph_to_add->setAliveImage(img);
	//	break;

	//case 'i': // iron floor
	//	img.loadFromFile("Image/Iron_100_100.png");
	//	graph_to_add->setAliveImage(img);
	//	break;

	

	default:
		break;
	}

	if (health_to_add) to_add->putComponent(ComponentID::HealthComponent, health_to_add);
	if (coll_to_add) to_add->putComponent(ComponentID::CollisionComponent, coll_to_add);
	to_add->putComponent(ComponentID::GraphicsComponent, graph_to_add);
	to_add->putComponent(ComponentID::PositionComponent, pos_to_add);
	return to_add;
}
