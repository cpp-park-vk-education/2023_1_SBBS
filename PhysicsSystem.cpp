#include "PhysicsSystem.h"
#include "PositionComponent.h"
#include "Types.h"
#include <math.h>
#include "CollisionComponent.h"

const int base_x = 0;
const int base_y = -1;

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
    return acos(cos);
}

bool check(PositionComponent temp_component);

void PhysicsSystem::updatePositions(const Input& inputs, std::vector<Entity>& scene) {
    for (int i = 0; i < scene.size(); i++) {
        PositionComponent* original_component = dynamic_cast<PositionComponent*>(scene[i].getComponentByID(ComponentID::PositionComponent));
        if (scene[i].getEntityID() == -1) {
            if (scene[i].getType() == ObjectType::Tank) {
                PositionComponent new_component = *original_component;
                Position new_position = *new_component.getPosition();
                int new_rotation = new_component.getRotation();

                Input_vector input_vector;

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

                new_position.x = moving(new_position.x, new_component.getSpeed(), prop);                
                new_position.y = moving(new_position.y, new_component.getSpeed(), prop);
                new_rotation += alpha;

                original_component->setPosition(new_position);

                //CollisionComponent* my_collision = dynamic_cast<CollisionComponent*>(scene[i].getComponentByID(ComponentID::CollisionComponent));

                //CollisionComponent new_collision = *my_collision;

                //new_collision.setPosition(new_position);
                //new_collision.setRotation(new_rotation);

                //bool flag = true;
                //for (int j = 0; j < scene.size(); j++) {
                //    if (j == i) continue;
                //    /////////////// Добавить условие на то, что i-й объект - это не своя же башня, а то никуда не поедем.
                //    CollisionComponent* another_collision = dynamic_cast<CollisionComponent*>(scene[j].getComponentByID(ComponentID::CollisionComponent));
                //    if (!new_collision.checkCollision(another_collision)) {
                //        flag = false;
                //        break;
                //    }
                //}
                //if (flag) {
                //    original_component->setPosition(new_position);
                //    original_component->setRotation(new_rotation); // нахуй два раза делать?
                //    *my_collision = new_collision;
                //}
                return;
            }          
        }
    }
}


