#include "SpawnerSystem.h"
#include "GraphicsComponent.h"
#include "PositionComponent.h"
#include "Types.h"
#include <SFML/Graphics.hpp>
#include <fstream>

std::vector<Entity> BulletSpawner::Spawn(Position& position, char subType) {
	std::vector<Entity> to_add_vec;

	Entity to_add(ObjectType::Bullet);
	static sf::Image bullet;

	GraphicsComponent* graph_to_add = new GraphicsComponent();
	PositionComponent* pos_to_add = new PositionComponent();
	pos_to_add->setPosition(position);

	switch (subType)
	{
	case 'b': // banner 
		bullet.loadFromFile("Image/Bullet_20_40.png");
		graph_to_add->setImage(bullet);
		break;

	default:
		break;
	}

	to_add.putComponent(ComponentID::GraphicsComponent, graph_to_add);
	to_add_vec.push_back(to_add);
	return to_add_vec;
}