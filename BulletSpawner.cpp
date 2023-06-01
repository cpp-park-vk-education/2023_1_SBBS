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
#include "SpawnID.h"

Entity* BulletSpawner::Spawn(Position position, int subType) {

	Entity* to_add = new Entity(ObjectType::Bullet);
	static sf::Image bullet;
	static sf::SoundBuffer buffer;
	static sf::Sound curr_sound;

	PositionComponent* pos_to_add = nullptr;

	switch (current_type_)
	{
	case OwnerType::Network:
		pos_to_add = new NetBulletPositionComponent();
		break;
	case OwnerType::Bot:
		pos_to_add = new BulletPositionComponent();
		break;
	case OwnerType::Player:
		pos_to_add = new BulletPositionComponent();
		break;
	default:
		break;
	}

	GraphicsComponent* graph_to_add = new GraphicsComponent();
	CollisionComponent* coll_to_add = new CollisionComponent(position, 0, 10, 10);
	HealthComponent* health_to_add = nullptr; /////////выставить дамаг дл€ пули

	Position pos_struc_to_add(position.x, position.y,position.rotation);
	pos_to_add->setPosition(pos_struc_to_add);

	switch (subType)
	{
	case bullet_1: // bullet 
		bullet.loadFromFile("Image/Bullet_20_40.png"); // пул€ сжимаетс€ до 10 20, но € не знаю где 10 а где 20 
		graph_to_add->setAliveImage(bullet);
		pos_to_add->setSpeed(15); //// change speed было 30 
		buffer.loadFromFile("Sound/Shot1.wav");
		curr_sound.setBuffer(buffer);
		curr_sound.setVolume(50.f); ///// громкость выстрела
		curr_sound.play();
		health_to_add = new HealthComponent(true, false, false, to_add, 10, 50);
		break;
	case bullet_2:
		bullet.loadFromFile("Image/Bullet_20_40.png"); // пул€ сжимаетс€ до 10 20, но € не знаю где 10 а где 20 
		graph_to_add->setAliveImage(bullet);
		pos_to_add->setSpeed(10); //// change speed было 15
		buffer.loadFromFile("Sound/Shot1.wav");
		curr_sound.setBuffer(buffer);
		curr_sound.setVolume(50.f); ///// громкость выстрела
		curr_sound.play();
		health_to_add = new HealthComponent(true, false, false, to_add, 10, 100);
	default:
		break;
	}

	graph_to_add->setOrigin(20, 10); // если че, мен€й центр отрисовки пули тут 
	graph_to_add->layer = true;
	to_add->putComponent(ComponentID::HealthComponent, health_to_add);
	to_add->putComponent(ComponentID::CollisionComponent, coll_to_add);
	to_add->putComponent(ComponentID::GraphicsComponent, graph_to_add);
	to_add->putComponent(ComponentID::PositionComponent, pos_to_add);
	to_add->setEntityID(-1);
	return to_add;

}