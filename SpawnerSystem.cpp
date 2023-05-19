#include "SpawnerSystem.h"
#include "netConnect.h"
#include "networkCodes.h"

int SpawnerSystem::update(sf::RenderWindow& window, std::vector<Entity>& scene) {
	std::vector<int> net_data = NetConnector::getInstance().get();
	BulletSpawner bs;

	while (net_data.size() >= 5) {
		if (net_data[4] != CHECKER) {
			net_data = NetConnector::getInstance().get();
			continue;
		}
		if (net_data[0] == BULLET_SPAWN_EVENT) {
			Position bullet_position;
			bullet_position.x = net_data[1];
			bullet_position.y = net_data[2];
			bullet_position.rotation = net_data[3];
			//char type = net_data[j+4];
			char type = '1'; ///////////////////нормально передать тип

			scene.push_back(bs.Spawn(bullet_position, type));
		}

		net_data = NetConnector::getInstance().get();
	}

	return 0;
}
