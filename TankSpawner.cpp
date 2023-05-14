#include "SpawnerSystem.h"
#include "GraphicsComponent.h"
#include "PositionComponent.h"
#include "CollisionComponent.h"
#include "Types.h"
#include <SFML/Graphics.hpp>
#include <fstream>


std::vector<Entity> TankSpawner::Spawn(Position position, char subType) {

	std::vector<Entity> to_add_vec;

	Entity tank(ObjectType::Tank);
	static sf::Image img;

	GraphicsComponent* graph_to_add = new GraphicsComponent();
	PositionComponent* pos_to_add = new PositionComponent();
	CollisionComponent* coll_to_add =  new CollisionComponent(position, 0, 50, 50);

	Position pos_struc_to_add(position.x, position.y);
	pos_to_add->setPosition(pos_struc_to_add);

	switch (subType)
	{
	case '1': // tank type 1
		img.loadFromFile("Image/tank_1_body_100_100.png");
		graph_to_add->setImage(img);
		break;

	case '2': // tank type 2
		img.loadFromFile("Image/tank_2_body_100_100.png");
		graph_to_add->setImage(img);
		break;

	default:
		break;
	}

	
	pos_to_add->setSpeed(2);
	graph_to_add->layer = true;
	tank.putComponent(ComponentID::CollisionComponent, coll_to_add);
	tank.putComponent(ComponentID::GraphicsComponent, graph_to_add);
	tank.putComponent(ComponentID::PositionComponent, pos_to_add);
	to_add_vec.push_back(tank);

	/////////////////////////////////////////////////////////////////////////////////////////// turret


	Entity turret(ObjectType::Turret);

	graph_to_add = new GraphicsComponent();
	PositionComponent* turr_pos_to_add = new PositionComponent();

	turr_pos_to_add->setPosition(pos_struc_to_add);

	switch (subType)
	{
	case '1': // tank type 1
		img.loadFromFile("Image/tank_1_gun_100_100.png");
		graph_to_add->setImage(img);
		break;

	case '2': // tank type 1
		img.loadFromFile("Image/tank_2_gun_100_100.png");
		graph_to_add->setImage(img);
		break;

	default:
		break;
	}

	turr_pos_to_add->setParent(pos_to_add);
	graph_to_add->layer = true;
	turret.putComponent(ComponentID::GraphicsComponent, graph_to_add);
	turret.putComponent(ComponentID::PositionComponent, turr_pos_to_add);
	to_add_vec.push_back(turret);

	return to_add_vec;

}
