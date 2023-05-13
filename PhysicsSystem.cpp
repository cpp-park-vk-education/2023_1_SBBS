#include "PhysicsSystem.h"
#include "PositionComponent.h"
#include "Types.h"
#include <math.h>

const int base_x = 0;
const int base_y = -1;

struct Input_vector {
    int x;
    int y;
};

int moving(int coordinate, int speed, float prop) {
    return int(coordinate + prop*speed);
}

int calculate_coner(const Input_vector& input_vector) {
    double cos = (base_x * input_vector.x + base_y * input_vector.y) /
    (sqrt(base_x * base_x + base_y * base_y) + sqrt(input_vector.x * input_vector.x + input_vector.y * input_vector.y));
    return acos(cos);
}

void updatePositions(const Input& inputs, std::vector<Entity> scene) {
    for (int i = 0; i < scene.size(); i++) {
        PositionComponent* temp_component = dynamic_cast<PositionComponent*>(scene[i].getComponentByID(ComponentID::PositionComponent));
        if (scene[i].getEntityID() == -1) {
            if (scene[i].getType() == ObjectType::Tank) {
                Position temp_position = *temp_component->getPosition();
                
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

                temp_position.x = moving(temp_position.x, temp_component->getSpeed(), prop);                
                temp_position.y = moving(temp_position.y, temp_component->getSpeed(), prop);


            }          
        }
        
        



    }
    /* bool moving_right_ = false;
    bool moving_left_ = false;
    bool moving_up_ = false;
    bool moving_down_ = false;*/


}


