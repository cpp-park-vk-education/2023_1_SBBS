#include "SpawnerSystem.h"
#include "GraphicsComponent.h"
#include "PositionComponent.h"
#include "Types.h"
#include <SFML/Graphics.hpp>
#include <fstream>

std::vector<Entity> MapSpawner::Spawn(Position position, char subType) {
	std::vector<Entity> to_add_vec;

	Entity to_add(ObjectType::Map);
	static sf::Image img;
	
	GraphicsComponent* graph_to_add = new GraphicsComponent();
	PositionComponent* pos_to_add = new PositionComponent();

	Position pos_struc_to_add(position.x, position.y);
	pos_to_add->setPosition(pos_struc_to_add);

	switch (subType)
	{
	case 'w' : // stone wall 
		img.loadFromFile("Image/Stone_100_100.png");
		graph_to_add->setImage(img);
		break;

	case 's' : // sand floor
		img.loadFromFile("Image/Sand_100_100.png");
		graph_to_add->setImage(img);
		break;

	case 'd': // dirt floor
		img.loadFromFile("Image/Dirt_100_100.png");
		graph_to_add->setImage(img);
		break;

	case 'c': // cave floor
		img.loadFromFile("Image/Cave_100_100.png");
		graph_to_add->setImage(img);
		break;

	case 'i': // iron floor
		img.loadFromFile("Image/Iron_100_100.png");
		graph_to_add->setImage(img);
		break;

	default:
		break;
	}

	to_add.putComponent(ComponentID::GraphicsComponent, graph_to_add);
	to_add.putComponent(ComponentID::PositionComponent, pos_to_add);
	to_add_vec.push_back(to_add);
	return to_add_vec;
}
