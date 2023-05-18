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

int base_x = 1;
int base_y = 0;

struct Input_vector {
    int x = 0;
    int y = 0;
};

int moving(int coordinate, int speed, float prop) {
    return coordinate + int(prop*speed);
}

int calculate_coner(const Input_vector& input_vector) {
    double cos = (base_x * input_vector.x + base_y * input_vector.y) /
    (sqrt(base_x * base_x + base_y * base_y) * sqrt(input_vector.x * input_vector.x + input_vector.y * input_vector.y));
    return acos(cos)*180/3.14;
}

bool check(PositionComponent temp_component);

int PhysicsSystem::update(sf::RenderWindow& window, std::vector<Entity>& scene) {

    int myEntityId = -1; //////////////// синглтон на мой id

    Input inputs;
    inputs.handleInput(window);
    BulletSpawner bs;

 
    for (int i = 0; i < scene.size(); i++) {       
        PositionComponent* original_component = dynamic_cast<PositionComponent*>(scene[i].getComponentByID(ComponentID::PositionComponent));
        int currEntityId = scene[i].getEntityID();
        ObjectType currEntityType = scene[i].getType();

        if (currEntityId == myEntityId) {
            if (currEntityType == ObjectType::Tank) {
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
                    alpha = calculate_coner(input_vector);
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

                CollisionComponent* my_collision = dynamic_cast<CollisionComponent*>(scene[i].getComponentByID(ComponentID::CollisionComponent));
                CollisionComponent new_collision = *my_collision;
                new_collision.update(new_position, new_rotation);

                bool flag = true;
                for (int j = 0; j < scene.size(); j++) {
                    if (j == i) continue;
                    CollisionComponent* another_collision = dynamic_cast<CollisionComponent*>(scene[j].getComponentByID(ComponentID::CollisionComponent));
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


                    std::vector<int> to_send;
                    to_send.push_back(myEntityId);
                    to_send.push_back(TANK_POSITION_MARK);
                    to_send.push_back(new_position.x);
                    to_send.push_back(new_position.y);
                    to_send.push_back(new_position.rotation);
                    SingletonSender::getInstance().send(to_send);
                    /////// я так понимаю тут мы ставим позицию танка 
                }                 
            }
            else if (currEntityType == ObjectType::Turret) {
                PositionComponent new_component = *original_component;
                Position new_position = new_component.getPosition();
                int new_rotation = new_component.getRotation();

                Input_vector input_vector;

                input_vector.x = inputs.mouse_x_ - new_position.x;
                input_vector.y = inputs.mouse_y_ - new_position.y;


                int alpha = calculate_coner(input_vector);

                if (inputs.mouse_y_ < new_position.y) {
                    alpha = 360 - alpha;
                }

                new_rotation = alpha;
                original_component->setRotation(new_rotation);
                
                // отправка позиции башни по сети
                std::vector<int> to_send;
                to_send.push_back(myEntityId);
                to_send.push_back(TURRET_POSITION_MARK);
                to_send.push_back(new_position.x);
                to_send.push_back(new_position.y);
                to_send.push_back(new_position.rotation);
                SingletonSender::getInstance().send(to_send);
                ///////////
              
                if (inputs.shoot_ == true) {
                    new_position.x += 50 * cos(new_rotation * 3.1415926 / 180);
                    new_position.y += 50 * sin(new_rotation * 3.1415926 / 180);
                    new_position.rotation = alpha;
                    ///  тип пули должен соответствовать нужному типу 
                    scene.push_back(bs.Spawn(new_position, '1'));

                    std::vector<int> to_send;
                    to_send.push_back(BULLET_SPAWN_EVENT);
                    to_send.push_back(new_position.x);
                    to_send.push_back(new_position.y);
                    to_send.push_back(new_position.rotation);
                    //to_send.push_back(type)  ////////////// сделать
                    SingletonSender::getInstance().send(to_send);
                }               
            }
            else if (currEntityType == ObjectType::Bullet) {

                PositionComponent new_component = *original_component;
                Position new_position = new_component.getPosition();
                int new_rotation = new_component.getRotation();

                new_position.x = moving(new_position.x, 30, cos(new_rotation * 3.1415926 / 180));
                new_position.y = moving(new_position.y, 30, sin(new_rotation * 3.1415926 / 180));

                CollisionComponent* my_collision = dynamic_cast<CollisionComponent*>(scene[i].getComponentByID(ComponentID::CollisionComponent));
                CollisionComponent new_collision = *my_collision;

                new_collision.update(new_position, new_rotation);

                bool flag = true;
                for (int j = 0; j < scene.size(); j++) {
                    if (j == i) continue;
                    CollisionComponent* another_collision = dynamic_cast<CollisionComponent*>(scene[j].getComponentByID(ComponentID::CollisionComponent));
                    if (!another_collision) continue;
                    if (!new_collision.checkCollision(another_collision)) {
                        flag = false;
                    }
                    if (flag) {
                        original_component->setPosition(new_position);
                        original_component->setRotation(new_rotation);
                        *my_collision = new_collision;



                        /////////// передача позиции пули по сети 
                        std::vector<int> to_send;
                        to_send.push_back(myEntityId);
                        to_send.push_back(BULLET_POSITION_MARK);
                        to_send.push_back(new_position.x);
                        to_send.push_back(new_position.y);
                        to_send.push_back(new_position.rotation);
                        SingletonSender::getInstance().send(to_send);

                    }
                    else  {
                        HealthComponent* Health = dynamic_cast<HealthComponent*>(scene[j].getComponentByID(ComponentID::HealthComponent));

                        // прописать хит ивент для сети 
                        if (!Health->get_dead() && Health->get_mortal()) {
                            Health->damage(50);
                        }
                        if (Health->get_dead()) {
                            scene.erase(scene.begin() + i);
                            scene.erase(scene.begin() + j);
                            break;
                        }
                        else {
                            scene.erase(scene.begin() + i);
                            break;
                        }                       
                    }
                }
            }
        }
        else if (currEntityId < 0) {//// прием данных из сети 
            PositionComponent new_component = *original_component;
            Position new_position = new_component.getPosition();

            std::vector<int> from_net_position = SingletonSender::getInstance().get();


            auto it = std::find(from_net_position.begin(), from_net_position.end(), currEntityId);

            // проверка соответствия элемента и типа из сети
            if (it != from_net_position.end()) {
               int j = std::distance(from_net_position.begin(), it);

               if (currEntityType == ObjectType::Tank   && from_net_position[j + 1] == TANK_POSITION_MARK ||
                   currEntityType == ObjectType::Bullet && from_net_position[j + 1] == BULLET_POSITION_MARK ||
                   currEntityType == ObjectType::Turret && from_net_position[j + 1] == TURRET_POSITION_MARK) {

                   new_position.x = from_net_position[j + 2];
                   new_position.y = from_net_position[j + 3];
                   new_position.rotation = from_net_position[j + 4];
               }
            }

            original_component->setPosition(new_position);
        }
    }
    return 0;
}
                   
    



