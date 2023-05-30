#include "SpawnerSystem.h"
#include "netConnect.h"
#include "networkCodes.h"

int SpawnerSystem::update(sf::RenderWindow& window, std::vector<Entity*>& scene) {

	package net_data = NetConnector::getInstance().get();


	BulletSpawner bs;


	while (net_data) {
		int event_type = net_data.eventType_;
		switch (event_type) {
		case TANK_HIT_EVENT:

			break;
		case BULLET_SPAWN_EVENT:
			bs.Spawn(Position(net_data.info1_, net_data.info2_, net_data.info3_), net_data.info4_);
			break;

		default:
			break;
		}
		net_data = NetConnector::getInstance().get();
	}


		//if (net_data == BULLET_SPAWN_EVENT) {
		//	Position bullet_position;
		//	bullet_position.x = net_data[1];
		//	bullet_position.y = net_data[2];
		//	bullet_position.rotation = net_data[3];
		//	//char type = net_data[j+4];
		//	char type = '1'; ///////////////////нормально передать тип

		//	scene.push_back(bs.Spawn(bullet_position, type));
		//}

		//net_data = NetConnector::getInstance().get();
	

	return 0;
}
