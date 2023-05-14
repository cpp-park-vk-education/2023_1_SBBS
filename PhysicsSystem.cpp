#include "PhysicsSystem.h"
#include "PositionComponent.h"
#include "Types.h"
#include <math.h>
#include "CollisionComponent.h"
#include <iostream>

int base_x = 1;
int base_y = 0;

struct Input_vector {
    int x = 0;
    int y = 0;
};

int moving(int coordinate, int speed, float prop) {
    return int(coordinate + prop*speed);
}

int calculate_coner(const Input_vector& input_vector) {
    double cos = (base_x * input_vector.x + base_y * input_vector.y) /
    (sqrt(base_x * base_x + base_y * base_y) + sqrt(input_vector.x * input_vector.x + input_vector.y * input_vector.y));
    return acos(cos)*180/3.14;
}

bool check(PositionComponent temp_component);

void PhysicsSystem::updatePositions(const Input& inputs, std::vector<Entity>& scene) {
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

                
                int alpha = calculate_coner(input_vector);
                float prop;

                if (input_vector.x * input_vector.y)
                    prop = 0.7;
                else prop = 1;
                
                /*std::cout << new_position.x << ' ' << new_position.y << std::endl;*/

                new_position.x = moving(new_position.x, new_component.getSpeed(), prop * input_vector.x);                
                new_position.y = moving(new_position.y, new_component.getSpeed(), prop * input_vector.y);
                new_rotation = alpha;


                CollisionComponent* my_collision = dynamic_cast<CollisionComponent*>(scene[i].getComponentByID(ComponentID::CollisionComponent));
                if (!my_collision) {

                    original_component->setPosition(new_position);
                    original_component->setRotation(new_rotation);
                    continue;
                }

                CollisionComponent new_collision = *my_collision;

                new_collision.setPosition(new_position);
                new_collision.setRotation(new_rotation);

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
                }
                return;
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

                std::cout << alpha << std::endl;
            }
            else if (scene[i].getType() == ObjectType::Bullet) {
                PositionComponent new_component = *original_component;
                Position new_position = new_component.getPosition();
                int new_rotation = new_component.getRotation();

                new_position.y = moving(new_position.x, new_component.getSpeed(), cos(new_rotation));
                new_position.y = moving(new_position.x, new_component.getSpeed(), cos(new_rotation));
            }
        }
    }
}
                    
        
    



