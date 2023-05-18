#include "SpawnerSystem.h"
#include "netConnect.h"
#include "networkCodes.h"

int SpawnerSystem::update(sf::RenderWindow& window, std::vector<Entity>& scene) {
	std::vector<int> net_data = NetConnector::getInstance().get();
	BulletSpawner bs;

	auto it = std::find(net_data.begin(), net_data.end(), BULLET_SPAWN_EVENT);

	while (it != net_data.end()) {
		int j = std::distance(net_data.begin(), it);

		Position new_position;

		new_position.x = net_data[j + 1];
		new_position.y = net_data[j + 2];
		new_position.rotation = net_data[j + 3];

		//char type = net_data[j+4];
		char type = '1'; ///////////////////нормально передать тип

		scene.push_back(bs.Spawn(new_position, type));

		it = std::find(net_data.begin() + j + 1, net_data.end(), BULLET_SPAWN_EVENT);
	}

	return 0;
}
