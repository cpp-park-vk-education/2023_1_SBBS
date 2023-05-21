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
#include "PlayingArgsHolder.h"

static Input_vector input_vector_1;
static int counter = 0;

Input_vector attractivness(std::vector<Entity*>& scene, Position& new_position, std::vector<int>& blok_x, std::vector<int>& blok_y) {
    Input_vector input_vector;
    double max_attractive = 0;
    Input_vector attractive_vector;

    for (int k = -1; k < 2; k++) {
        for (int l = -1; l < 2; l++) {
            bool flag = true;
            double attractive = 0;
            if (k == 0 && l == 0) continue;
            for (int n = 0; n < blok_x.size(); n++) {
                if (blok_x[n] == k && blok_y[n] == l) flag = false;
            }
            if (!flag) continue;
            input_vector.x = k;
            input_vector.y = l;
            for (int j = 0; j < scene.size(); j++) {
                if (scene[j]->getType() == ObjectType::Tank) {
                    if (scene[j]->getEntityID() == PlayingArgsHolder::getInstance().getMyEntityId()) {
                        PositionComponent* meet_component = dynamic_cast<PositionComponent*>(scene[j]->getComponentByID(ComponentID::PositionComponent));
                        Position meet_position = meet_component->getPosition();
                        PositionComponent* Tank_position = dynamic_cast<PositionComponent*>(scene[j]->getComponentByID(ComponentID::PositionComponent));
                        CollisionComponent* Tank_collision1 = dynamic_cast<CollisionComponent*>(scene[j]->getComponentByID(ComponentID::CollisionComponent));
                        CollisionComponent Tank_collision = *Tank_collision1;
                        Input_vector vector;
                        vector.x = meet_position.x - new_position.x;
                        vector.y = meet_position.y - new_position.y;
                        int betha = calculate_angle(input_vector, vector);
                        if (input_vector.x * vector.x < 0 && input_vector.y * vector.y < 0) {
                            betha += 180;
                        }
                        attractive += (180 - betha);
                        Position tmp_position = new_position;
                        tmp_position.x += input_vector.x * 500;
                        tmp_position.y += input_vector.y * 500;
                        int change_dist;
                        Position temp_position;
                        temp_position.x = new_position.x + 200 * input_vector.x;
                        temp_position.y = new_position.y + 200 * input_vector.y;
                        change_dist = distance_p(new_position, meet_position) - distance_p(temp_position, meet_position);
                        attractive += change_dist * 10;

                        bool flag2 = true;
                        for (int u = 0; u < scene.size(); u++) {
                            if (scene[u]->getType() == ObjectType::Map) {
                                CollisionComponent* wall_collision = dynamic_cast<CollisionComponent*>(scene[u]->getComponentByID(ComponentID::CollisionComponent));
                                if (!wall_collision) continue;
                                if (!wall_collision->checkBullet(temp_position, meet_position)) {
                                    flag2 = false;
                                    break;
                                }
                            }
                        }
                        if (flag2) {
                            attractive += 1000000;
                        }

                        temp_position.x = new_position.x + 100 * input_vector.x;
                        temp_position.y = new_position.y + 100 * input_vector.y;
                        flag2 = true;
                        for (int u = 0; u < scene.size(); u++) {
                            if (scene[u]->getType() == ObjectType::Map) {
                                CollisionComponent* wall_collision = dynamic_cast<CollisionComponent*>(scene[u]->getComponentByID(ComponentID::CollisionComponent));
                                if (!wall_collision) continue;
                                if (!wall_collision->checkBullet(temp_position, meet_position)) {
                                    flag2 = false;
                                    break;
                                }
                            }
                        }
                        if (flag2) {
                            attractive += 10000;
                        }

                        temp_position.x = new_position.x + 150 * input_vector.x;
                        temp_position.y = new_position.y + 150 * input_vector.y;
                        flag2 = true;
                        for (int u = 0; u < scene.size(); u++) {
                            if (scene[u]->getType() == ObjectType::Map) {
                                CollisionComponent* wall_collision = dynamic_cast<CollisionComponent*>(scene[u]->getComponentByID(ComponentID::CollisionComponent));
                                if (!wall_collision) continue;
                                if (!wall_collision->checkBullet(temp_position, meet_position)) {
                                    flag2 = false;
                                    break;
                                }
                            }
                        }
                        if (flag2) {
                            attractive += 10000;
                        }

                        temp_position.x = new_position.x + 250 * input_vector.x;
                        temp_position.y = new_position.y + 250 * input_vector.y;
                        flag2 = true;
                        for (int u = 0; u < scene.size(); u++) {
                            if (scene[u]->getType() == ObjectType::Map) {
                                CollisionComponent* wall_collision = dynamic_cast<CollisionComponent*>(scene[u]->getComponentByID(ComponentID::CollisionComponent));
                                if (!wall_collision) continue;
                                if (!wall_collision->checkBullet(temp_position, meet_position)) {
                                    flag2 = false;
                                    break;
                                }
                            }
                        }
                        if (flag2) {
                            attractive += 10000;
                        }

                        temp_position.x = new_position.x + 300 * input_vector.x;
                        temp_position.y = new_position.y + 300 * input_vector.y;
                        flag2 = true;
                        for (int u = 0; u < scene.size(); u++) {
                            if (scene[u]->getType() == ObjectType::Map) {
                                CollisionComponent* wall_collision = dynamic_cast<CollisionComponent*>(scene[u]->getComponentByID(ComponentID::CollisionComponent));
                                if (!wall_collision) continue;
                                if (!wall_collision->checkBullet(temp_position, meet_position)) {
                                    flag2 = false;
                                    break;
                                }
                            }
                        }
                        if (flag2) {
                            attractive += 10000;
                        }

                        temp_position.x = new_position.x + 50 * input_vector.x;
                        temp_position.y = new_position.y + 50 * input_vector.y;
                        flag2 = true;
                        for (int u = 0; u < scene.size(); u++) {
                            if (scene[u]->getType() == ObjectType::Map) {
                                CollisionComponent* wall_collision = dynamic_cast<CollisionComponent*>(scene[u]->getComponentByID(ComponentID::CollisionComponent));
                                if (!wall_collision) continue;
                                Tank_collision.update(temp_position, betha);
                                if (!wall_collision->checkCollision(&Tank_collision)) {
                                    flag2 = false;
                                    break;
                                }
                            }
                        }
                        if (!flag2) {
                            attractive -= 1000000000000000;
                        }
                    }
                }
                else if (scene[j]->getType() == ObjectType::Map) {
                    CollisionComponent* wall_collision = dynamic_cast<CollisionComponent*>(scene[j]->getComponentByID(ComponentID::CollisionComponent));
                    PositionComponent* wall_position = dynamic_cast<PositionComponent*>(scene[j]->getComponentByID(ComponentID::PositionComponent));
                    if (!wall_collision) continue;
                    Position tmp_position = new_position;
                    tmp_position.x += input_vector.x * 500;
                    tmp_position.y += input_vector.y * 500;
                    if (wall_position) {
                        if (!wall_collision->checkBullet(new_position, tmp_position)) {
                            int temp = (100 - distance_p(new_position, wall_position->getPosition()));
                            if (temp > 0) {
                                attractive -= temp * 0.01;
                            }
                        }
                    }
                }
            }
            if (attractive > max_attractive) {
                max_attractive = attractive;
                attractive_vector = input_vector;
            }
            attractive = 0;
        }
    }
    return attractive_vector;
}

void BotTankPositionComponent::update(sf::RenderWindow& window, std::vector<Entity*>& scene, int& i) {

    PositionComponent* original_component = dynamic_cast<PositionComponent*>(scene[i]->getComponentByID(ComponentID::PositionComponent));
    int currEntityId = scene[i]->getEntityID();
    if (currEntityId == 0) // проверка на смерть - 0 в случае смерти
        return;

    ObjectType currEntityType = scene[i]->getType();

    PositionComponent new_component = *original_component;
    int new_rotation = new_component.getRotation();
    std::vector<int> blok_x;
    std::vector<int> blok_y;
    bool flag2 = true;
    int m = 0;
    while (flag2) {
        if (m > 8) break;
        bool flag = true;
        Position new_position = new_component.getPosition();

        if (counter == 25) {
            input_vector_1 = attractivness(scene, new_position, blok_x, blok_y); //////////10 - количество кадров
            counter = 0;
        }
        counter++;

        Input_vector base = input_vector_1;
        int alpha;
        if (!(input_vector_1.x == 0 && input_vector_1.y == 0)) {
            alpha = calculate_coner(input_vector_1);
        }
        else alpha = new_rotation;
        float prop;
        if (abs(input_vector_1.x * input_vector_1.y))
            prop = 0.707;
        else prop = 1;
        new_position.x = moving(new_position.x, new_component.getSpeed(), prop * input_vector_1.x);
        new_position.y = moving(new_position.y, new_component.getSpeed(), prop * input_vector_1.y);

        Input_vector input_vector_2;

        input_vector_2.x = new_position.x + input_vector_1.x;
        input_vector_2.y = new_position.y + input_vector_1.y;
        if (input_vector_2.y < new_position.y) {
            alpha = 360 - alpha;
        }
        new_rotation = alpha;
        CollisionComponent* my_collision = dynamic_cast<CollisionComponent*>(scene[i]->getComponentByID(ComponentID::CollisionComponent));
        CollisionComponent new_collision = *my_collision;
        new_collision.update(new_position, new_rotation);
        for (int j = 0; j < scene.size(); j++) {
            if (j == i) continue;
            CollisionComponent* another_collision = dynamic_cast<CollisionComponent*>(scene[j]->getComponentByID(ComponentID::CollisionComponent));
            if (!another_collision) continue;
            if (!new_collision.checkCollision(another_collision)) {
                flag = false;
                blok_x.push_back(base.x);
                blok_y.push_back(base.y);
                break;
            }
        }
        if (flag) {
            original_component->setPosition(new_position);
            original_component->setRotation(new_rotation);
            *my_collision = new_collision;
            flag2 = false;
            break;
            //std::vector<int> to_send;
            //to_send.push_back(myEntityId);
            //to_send.push_back(TANK_POSITION_MARK);
            //to_send.push_back(new_position.x);
            //to_send.push_back(new_position.y);
            //to_send.push_back(new_position.rotation);
            //to_send.push_back(CHECKER);
            //to_send.push_back(BREAKER);
            //NetConnector::getInstance().send(to_send);
            /////// я так понимаю тут мы ставим позицию танка 
        }
        m++;
    }
}

void BotTurretPositionComponent::update(sf::RenderWindow& window, std::vector<Entity*>& scene, int& i) {

    BulletSpawner bs;
    bs.setOwnerType(OwnerType::Bot);

    PositionComponent* original_component = dynamic_cast<PositionComponent*>(scene[i]->getComponentByID(ComponentID::PositionComponent));
    int currEntityId = scene[i]->getEntityID();
    if (currEntityId == 0)
        return;

    ObjectType currEntityType = scene[i]->getType();

    PositionComponent bot_component = *original_component;
    Position bot_position = bot_component.getPosition();
    int bot_rotation = bot_component.getRotation();
    Input_vector input_vector;
    int min_dist = 100000;
    PositionComponent Enemy_tank;
    for (int j = 0; j < scene.size(); j++) {
        if (scene[j]->getType() == ObjectType::Tank) {
            PositionComponent* meet_component = dynamic_cast<PositionComponent*>(scene[j]->getComponentByID(ComponentID::PositionComponent));
            if (scene[j]->getEntityID() == PlayingArgsHolder::getInstance().getMyEntityId()) {//////////////////////////// Заменить на проверку
                Position meet_position = meet_component->getPosition();
                if (distance_p(bot_position, meet_position) < min_dist) {
                    min_dist = distance_p(bot_position, meet_position);
                    Enemy_tank = *meet_component;
                }
            }
        }
    }
    if (min_dist != 10000) {
        Position Enemy_pos = Enemy_tank.getPosition();

        input_vector.x = Enemy_pos.x - bot_position.x;
        input_vector.y = Enemy_pos.y - bot_position.y;

        int alpha = calculate_coner(input_vector);

        if (Enemy_pos.y < bot_position.y) {
            alpha = 360 - alpha;
        }
        bot_rotation = alpha;
        original_component->setRotation(bot_rotation);
        bool flag = true;
        for (int j = 0; j < scene.size(); j++) {
            if (scene[j]->getType() == ObjectType::Map) {
                CollisionComponent* wall_collision = dynamic_cast<CollisionComponent*>(scene[j]->getComponentByID(ComponentID::CollisionComponent));
                if (!wall_collision) continue;
                if (!wall_collision->checkBullet(bot_position, Enemy_pos)) {
                    flag = false;
                    break;
                }
            }
        }
        if (flag) {
            static std::chrono::steady_clock::time_point bot_last_shoot = std::chrono::high_resolution_clock::now();
            std::chrono::steady_clock::time_point bot_curr_time = std::chrono::high_resolution_clock::now();
            double elapsed_time = std::chrono::duration<double>(bot_curr_time - bot_last_shoot).count();
            ShootComponent* shoot_component = dynamic_cast<ShootComponent*>(scene[i]->getComponentByID(ComponentID::ShootComponent));
            if (elapsed_time > shoot_component->getCooldown()) {
                bot_position.x += 50 * cos(bot_rotation * 3.1415926 / 180);
                bot_position.y += 50 * sin(bot_rotation * 3.1415926 / 180);
                bot_position.rotation = alpha;
                ///  тип пули должен соответствовать нужному типу 
                scene.push_back(bs.Spawn(bot_position, shoot_component->getBulletType()));

                //std::vector<int> to_send;
                //to_send.push_back(BULLET_SPAWN_EVENT);
                //to_send.push_back(new_position.x);
                //to_send.push_back(new_position.y);
                //to_send.push_back(new_position.rotation);
                //to_send.push_back(CHECKER);
                //to_send.push_back(BREAKER);
                ////to_send.push_back(type)  ////////////// сделать
                //NetConnector::getInstance().send(to_send);
                bot_last_shoot = std::chrono::high_resolution_clock::now();
            }
        }
    }
}
