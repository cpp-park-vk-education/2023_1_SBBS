#pragma once
#include "PhysicsSystem.h"
#include "PositionComponent.h"
#include "Types.h"
#include <math.h>
#include "CollisionComponent.h"
#include <iostream>
#include "SpawnerSystem.h"
//#include <Windows.h>
#include "HealthComponent.h"


#include "netConnect.h"

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
    Input inputs;
    inputs.handleInput(window);
    BulletSpawner bs;
    for (int i = 0; i < scene.size(); i++) {       
        PositionComponent* original_component = dynamic_cast<PositionComponent*>(scene[i].getComponentByID(ComponentID::PositionComponent));
        if (scene[i].getEntityID() == -1) {
            if (scene[i].getType() == ObjectType::Tank) {
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
                    to_send.push_back(new_position.x);
                    to_send.push_back(new_position.y);
                    SingletonSender::getInstance().send(to_send);
                    //Sleep(2000);
                    /////// я так понимаю тут мы ставим позицию танка 
                }                 
            }
            else if (scene[i].getType() == ObjectType::Turret) {
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
                
              
                if (inputs.shoot_ == true) {
                    new_position.x += 50 * cos(new_rotation * 3.1415926 / 180);
                    new_position.y += 50 * sin(new_rotation * 3.1415926 / 180);
                    new_position.rotation = alpha;
                    scene.push_back(bs.Spawn(new_position, '1'));
                }               
            }
            else if (scene[i].getType() == ObjectType::Bullet) {

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
                    }
                    else  {
                        HealthComponent* Health = dynamic_cast<HealthComponent*>(scene[j].getComponentByID(ComponentID::HealthComponent));
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
        else if (scene[i].getEntityID() == -2) {
            PositionComponent new_component = *original_component;
            Position new_position = new_component.getPosition();

            std::vector<int> from_net_position = SingletonSender::getInstance().get();
            if (from_net_position.size() >= 2) {
                new_position.x = from_net_position[0];
                new_position.y = from_net_position[1];

                original_component->setPosition(new_position);
            }
        }
    }
    return 0;
}
                   
    



