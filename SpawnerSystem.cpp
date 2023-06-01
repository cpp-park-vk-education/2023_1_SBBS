#include "SpawnerSystem.h"
#include "netConnect.h"
#include "networkCodes.h"

int SpawnerSystem::update(sf::RenderWindow& window, std::vector<Entity*>& scene) {

	package net_data = NetConnector::getInstance().getEvent();


	BulletSpawner bs;
	bs.setOwnerType(OwnerType::Player);

	while (net_data) {
		int event_type = net_data.eventType_;
		switch (event_type) {
		case TANK_HIT_EVENT:

			break;
		case BULLET_SPAWN_EVENT:
			scene.push_back(bs.Spawn(Position(net_data.info1_, net_data.info2_, net_data.info3_), net_data.info4_));
			break;

		default:
			break;
		}
		net_data = NetConnector::getInstance().getEvent();
	}	

	return 0;
}
