#include "SpawnerSystem.h"
#include "GraphicsComponent.h"
#include "PositionComponent.h"
#include <SFML/Graphics.hpp>
#include <fstream>

std::vector<Entity> WallSpawner::Spawn(Position position, char subType) {
	std::vector<Entity> to_add_vec;

	Entity to_add;
	static sf::Image wood_wall;
	wood_wall.loadFromFile("Image/Stone.png");
	GraphicsComponent* graph_to_add = new GraphicsComponent();
	PositionComponent* pos_to_add = new PositionComponent();

	switch (subType)
	{
	case 'w' : // wood wall 
		graph_to_add->setImage(wood_wall);
		break;

	default:
		break;
	}

	to_add.putComponent(ComponentID::GraphicsComponent, graph_to_add);
	to_add_vec.push_back(to_add);
	return to_add_vec;
}