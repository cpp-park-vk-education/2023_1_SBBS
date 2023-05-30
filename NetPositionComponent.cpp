#include "PositionComponent.h"
#include "CollisionComponent.h"
#include "netConnect.h"
#include "networkCodes.h"

void NetTankPositionComponent::update(sf::RenderWindow& window, std::vector<Entity*>& scene, int& i) {

    PositionComponent new_component = *this; // по идее создается копия 
    Position new_position = new_component.getPosition();
    package from_net_position = NetConnector::getInstance().get();

    while (from_net_position.eventType_ != TANK_POSITION_MARK) {
        from_net_position = NetConnector::getInstance().get();
    }


    new_position.x = from_net_position.info1_;
    new_position.y = from_net_position.info2_;
    new_position.rotation = from_net_position.info3_;

    /// 
    CollisionComponent* my_collision = dynamic_cast<CollisionComponent*>(scene[i]->getComponentByID(ComponentID::CollisionComponent));
    if (my_collision) { /// проверяем наличие компоненты только для гарантии безопасности исключений 
        CollisionComponent new_collision = *my_collision;
        new_collision.update(new_position, new_position.rotation);
        *my_collision = new_collision;
    }
    setPosition(new_position);
}



void NetTurretPositionComponent::update(sf::RenderWindow& window, std::vector<Entity*>& scene, int& i) {
    ObjectType currEntityType = scene[i]->getType();
    PositionComponent* original_component = dynamic_cast<PositionComponent*>(scene[i]->getComponentByID(ComponentID::PositionComponent));
    PositionComponent new_component = *original_component;
    Position new_position = new_component.getPosition();
    package from_net_position = NetConnector::getInstance().get();

    while (from_net_position.eventType_ != TURRET_POSITION_MARK) {
        from_net_position = NetConnector::getInstance().get();
    }

    new_position.x = from_net_position.info1_;
    new_position.y = from_net_position.info2_;
    new_position.rotation = from_net_position.info3_;
    
    CollisionComponent* my_collision = dynamic_cast<CollisionComponent*>(scene[i]->getComponentByID(ComponentID::CollisionComponent));
    if (my_collision) {
        CollisionComponent new_collision = *my_collision;
        new_collision.update(new_position, new_position.rotation);
        *my_collision = new_collision;
    }
    original_component->setPosition(new_position);
}

void NetBulletPositionComponent::update(sf::RenderWindow& window, std::vector<Entity*>& scene, int& i) {
    ObjectType currEntityType = scene[i]->getType();
    PositionComponent* original_component = dynamic_cast<PositionComponent*>(scene[i]->getComponentByID(ComponentID::PositionComponent));
    PositionComponent new_component = *original_component;
    Position new_position = new_component.getPosition();
    package from_net_position = NetConnector::getInstance().get();

    while (from_net_position.eventType_ != BULLET_POSITION_MARK) {
        from_net_position = NetConnector::getInstance().get();
    }

    new_position.x = from_net_position.info1_;
    new_position.y = from_net_position.info2_;
    new_position.rotation = from_net_position.info3_;
    /// 
    CollisionComponent* my_collision = dynamic_cast<CollisionComponent*>(scene[i]->getComponentByID(ComponentID::CollisionComponent));
    if (my_collision) {
        CollisionComponent new_collision = *my_collision;
        new_collision.update(new_position, new_position.rotation);
        *my_collision = new_collision;
    }
    original_component->setPosition(new_position);
}
