#pragma once
#include "SpawnerSystem.h"
#include "GraphicsComponent.h"
#include "PositionComponent.h"
#include "CollisionComponent.h"
#include "HealthComponent.h"
#include "Types.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>

Entity* BulletSpawner::Spawn(Position position, char subType) {

	Entity* to_add = new Entity(ObjectType::Bullet);
	static sf::Image bullet;
	static sf::SoundBuffer buffer;
	static sf::Sound curr_sound;

	GraphicsComponent* graph_to_add = new GraphicsComponent();
	PositionComponent* pos_to_add = new BulletPositionComponent();
	CollisionComponent* coll_to_add = new CollisionComponent(position, 0, 10, 10);
	HealthComponent* health_to_add = new HealthComponent(true, false,false,to_add,10,50); /////////выставить дамаг для пули

	Position pos_struc_to_add(position.x, position.y,position.rotation);
	pos_to_add->setPosition(pos_struc_to_add);

	switch (subType)
	{
	case '1': // bullet 
		bullet.loadFromFile("Image/Bullet_20_40.png"); // пуля сжимается до 10 20, но я не знаю где 10 а где 20 
		graph_to_add->setAliveImage(bullet);
		pos_to_add->setSpeed(10); //// change speed 
		buffer.loadFromFile("Sound/Shot1.wav");
		curr_sound.setBuffer(buffer);
		curr_sound.setVolume(50.f); ///// громкость выстрела
		curr_sound.play();
		break;
	default:
		break;
	}

	graph_to_add->setOrigin(20, 10); // если че, меняй центр отрисовки пули тут 
	graph_to_add->layer = true;
	to_add->putComponent(ComponentID::HealthComponent, health_to_add);
	to_add->putComponent(ComponentID::CollisionComponent, coll_to_add);
	to_add->putComponent(ComponentID::GraphicsComponent, graph_to_add);
	to_add->putComponent(ComponentID::PositionComponent, pos_to_add);
	to_add->setEntityID(-1);
	return to_add;

}