#include "SpawnerSystem.h"
#include "netConnect.h"
#include "networkCodes.h"
#include "GameSingleton.h"
#include "HealthComponent.h"

void hitObjectOnScene(std::vector<Entity*>& scene, int bulletId, int idToHit, int newHealth);

int SpawnerSystem::update(sf::RenderWindow& window, std::vector<Entity*>& scene) {

	package net_data = NetConnector::getInstance().getEvent();

	BulletSpawner bs;
	bs.setOwnerType(OwnerType::Network);
	Entity* bullet;

	while (net_data) {
		int event_type = net_data.eventType_;
		switch (event_type) {
		case HIT_EVENT:
			hitObjectOnScene(scene, net_data.id_, net_data.info1_, net_data.info2_);
			break;
		case BULLET_SPAWN_EVENT:
			bullet = bs.Spawn(Position(net_data.info1_, net_data.info2_, net_data.info3_), net_data.info4_);
			bullet->setEntityID(net_data.id_);
			scene.push_back(bullet);
			break;

		default:
			break;
		}
		net_data = NetConnector::getInstance().getEvent();
	}	

	return 0;
}

void hitObjectOnScene(std::vector<Entity*>& scene, int bulletId, int idToHit, int newHealth) {
	for (int i = Game::getInstance().getFirstCollidable(); i < scene.size(); ++i) {
		int currEntityId = scene[i]->getEntityID();
		if (currEntityId == idToHit) {
			HealthComponent* objectHealth = dynamic_cast<HealthComponent*>(scene[i]->getComponentByID(ComponentID::HealthComponent));
			objectHealth->setHealth(newHealth);

			if (scene[i]->getType() == ObjectType::Tank && objectHealth->getHealth() <= 0) {/// удаление башни

				scene[i + 1]->setEntityID(0);
			}

			// объект умер
			if (objectHealth->getHealth() < 0 && !objectHealth->hasAfterlife()) {

				Entity* to_delete = scene[i];
				scene[i] = nullptr;
				delete to_delete;
				scene.erase(scene.begin() + i);

			}// если у объекта есть "жизнь после смерти", то это обработалось в HealthComponent         
		}
		else if (currEntityId == bulletId) {
			Entity* to_delete = scene[i];
			scene[i] = nullptr;
			delete to_delete;
			scene.erase(scene.begin() + i);
		}
	}
}