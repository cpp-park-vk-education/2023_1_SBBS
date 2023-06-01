#pragma once
#include "PhysicsSystem.h"
#include "PositionComponent.h"
#include "Types.h"
#include <math.h>
#include "CollisionComponent.h"
#include <iostream>
#include "SpawnerSystem.h"
#include "HealthComponent.h"
#include "netConnect.h"
#include "networkCodes.h"
#include "ShootComponent.h"
#include "SoundComponent.h"
#include "InputHandler.h"
#include "PositionComponent.h"
#include "GameSingleton.h"

const int BULLET_OFFSET_1 = 10'000;
int BULLET_OFFSET_2 = 100;


void TankPositionComponent::update(sf::RenderWindow& window, std::vector<Entity*>& scene, int& i) {
    int myEntityId = Game::getInstance().getMyEntityId();

    Input inputs;
    inputs.handleInput(window);

    PositionComponent* original_component = dynamic_cast<PositionComponent*>(scene[i]->getComponentByID(ComponentID::PositionComponent));

    int currEntityId = scene[i]->getEntityID();
    if (currEntityId != myEntityId) // условие на смерть (после смерти currEntityId становится равным 0) 
        return;

    PositionComponent new_component = *original_component;

    Position new_position = new_component.getPosition();

    int new_rotation = new_component.getRotation();

    Input_vector input_vector;
    input_vector.x = 0;
    input_vector.y = 0;

    if (inputs.moving_right_) {
        input_vector.x += 1;
    }
    if (inputs.moving_left_) {
        input_vector.x += -1;
    }
    if (inputs.moving_up_) {
        input_vector.y += -1;
    }
    if (inputs.moving_down_) {
        input_vector.y += 1;
    }

    int alpha;

    if (!(input_vector.x == 0 && input_vector.y == 0)) {
        alpha = calculate_base_angle(input_vector);
    }
    else alpha = new_rotation;
    float prop;

    if (abs(input_vector.x * input_vector.y))
        prop = 0.707;
    else prop = 1;

    new_position.x = moving(new_position.x, new_component.getSpeed(), prop * input_vector.x);
    new_position.y = moving(new_position.y, new_component.getSpeed(), prop * input_vector.y);

    input_vector.x = new_position.x + input_vector.x;
    input_vector.y = new_position.y + input_vector.y;
    if (input_vector.y < new_position.y) {
        alpha = 360 - alpha;
    }
    new_rotation = alpha;

    CollisionComponent* my_collision = dynamic_cast<CollisionComponent*>(scene[i]->getComponentByID(ComponentID::CollisionComponent));
    CollisionComponent new_collision = *my_collision;
    new_collision.update(new_position, new_rotation);

    bool flag = true;
    for (int j = 0; j < scene.size(); j++) {
        if (j == i) continue;

        CollisionComponent* another_collision = dynamic_cast<CollisionComponent*>(scene[j]->getComponentByID(ComponentID::CollisionComponent));
        if (!another_collision) continue;
        if (!new_collision.checkCollision(another_collision)) {
            flag = false;
            break;
        }
    }
    if (flag) {
        original_component->setPosition(new_position);
        original_component->setRotation(new_rotation);
        *my_collision = new_collision;


        NetConnector::getInstance().send(package(
            myEntityId, TANK_POSITION_MARK, new_position.x,
            new_position.y, new_position.rotation));

        /////// я так понимаю тут мы ставим позицию танка 

    }
}

void TurretPositionComponent::update(sf::RenderWindow& window, std::vector<Entity*>& scene, int& i) {
    int myEntityId = Game::getInstance().getMyEntityId();
    int bulletsEntityId = myEntityId * BULLET_OFFSET_1 + BULLET_OFFSET_2;

    Input inputs;
    inputs.handleInput(window);
    BulletSpawner bs;
    bs.setOwnerType(OwnerType::Player);

    PositionComponent* original_component = dynamic_cast<PositionComponent*>(scene[i]->getComponentByID(ComponentID::PositionComponent));

    int currEntityId = scene[i]->getEntityID();
    if (currEntityId != myEntityId) // условие на смерть (после смерти currEntityId становится равным 0) 
        return;

    PositionComponent new_component = *original_component;
    Position new_position = new_component.getPosition();
    int new_rotation = new_component.getRotation();

    Input_vector input_vector;

    input_vector.x = inputs.mouse_x_ - new_position.x;
    input_vector.y = inputs.mouse_y_ - new_position.y;

    int alpha = calculate_base_angle(input_vector);

    if (inputs.mouse_y_ < new_position.y) {
        alpha = 360 - alpha;
    }

    new_rotation = alpha;
    original_component->setRotation(new_rotation);

    // отправка позиции башни по сети


    ///////////



    NetConnector::getInstance().send(package(
        myEntityId, TURRET_POSITION_MARK, new_position.x,
        new_position.y, alpha));

        /////// я так понимаю тут мы ставим позицию танка 

    if (inputs.mouse_click_ == true) {
        static std::chrono::steady_clock::time_point last_time = std::chrono::high_resolution_clock::now();
        std::chrono::steady_clock::time_point curr_time = std::chrono::high_resolution_clock::now();
        double elapsed_time = std::chrono::duration<double>(curr_time - last_time).count();
        ShootComponent* shoot_component = dynamic_cast<ShootComponent*>(scene[i]->getComponentByID(ComponentID::ShootComponent));

        if (elapsed_time > shoot_component->getCooldown()) {

            new_position.x += 50 * cos(new_rotation * 3.1415926 / 180);
            new_position.y += 50 * sin(new_rotation * 3.1415926 / 180);
            new_position.rotation = alpha;

            Entity* bullet = bs.Spawn(new_position, shoot_component->getBulletType());
            bullet->setEntityID(bulletsEntityId);
            scene.push_back(bullet);

            NetConnector::getInstance().send(package(
                bulletsEntityId, BULLET_SPAWN_EVENT, new_position.x,
                new_position.y, new_position.rotation, shoot_component->getBulletType()));
            ++BULLET_OFFSET_2;

            last_time = std::chrono::high_resolution_clock::now();
        }
    }
}

void BulletPositionComponent::update(sf::RenderWindow& window, std::vector<Entity*>& scene, int& i) {
    int bulletEntityId = scene[i]->getEntityID();

    PositionComponent* original_component = dynamic_cast<PositionComponent*>(scene[i]->getComponentByID(ComponentID::PositionComponent));
    int currEntityId = scene[i]->getEntityID();
    ObjectType currEntityType = scene[i]->getType();

    PositionComponent new_component = *original_component;
    Position new_position = new_component.getPosition();
    int new_rotation = new_component.getRotation();

    new_position.x = moving(new_position.x, new_component.getSpeed(), cos(new_rotation * 3.1415926 / 180));
    new_position.y = moving(new_position.y, new_component.getSpeed(), sin(new_rotation * 3.1415926 / 180));

    CollisionComponent* my_collision = dynamic_cast<CollisionComponent*>(scene[i]->getComponentByID(ComponentID::CollisionComponent));
    CollisionComponent new_collision = *my_collision;

    new_collision.update(new_position, new_rotation);

    for (int j = 0; j < scene.size(); j++) {
        if (j == i) continue;

        CollisionComponent* another_collision = dynamic_cast<CollisionComponent*>(scene[j]->getComponentByID(ComponentID::CollisionComponent));
        if (!another_collision) continue;

        if (new_collision.checkCollision(another_collision)) {
            original_component->setPosition(new_position);
            original_component->setRotation(new_rotation);
            *my_collision = new_collision;

            /////////// передача позиции пули по сети 
            NetConnector::getInstance().send(package(
                bulletEntityId, BULLET_POSITION_MARK, new_position.x,
                new_position.y, new_position.rotation));
        }
        else {
            HealthComponent* objectHealth = dynamic_cast<HealthComponent*>(scene[j]->getComponentByID(ComponentID::HealthComponent));
            HealthComponent* BulletHealth = dynamic_cast<HealthComponent*>(scene[i]->getComponentByID(ComponentID::HealthComponent));

            // прописать хит ивент для сети 

            int curr_health = objectHealth->getHealth();
            int curr_damage = BulletHealth->getDamage();
            int new_health = curr_health - curr_damage;

            objectHealth->setHealth(new_health);

            if (scene[j]->getType() == ObjectType::Tank && objectHealth->getHealth() <= 0) {/// удаление башни

                scene[j + 1]->setEntityID(0);
            }

            // объект умер
            if (objectHealth->getHealth() < 0 && !objectHealth->hasAfterlife()) {

                Entity* to_delete = scene[j];
                scene[j] = nullptr;
                delete to_delete;
                scene.erase(scene.begin() + j);
                if (j < i) /// удаляем объект, который в сцене перед пулей 
                    --i;

                --j;
                //continue;

            }// если у объекта есть "жизнь после смерти", то это обработалось в HealthComponent         

            ////////////// пулю удаляем
            Entity* to_delete = scene[i];
            scene[i] = nullptr;
            delete to_delete;
            scene.erase(scene.begin() + i);
            break;
        }
    }
}
