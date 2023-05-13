#include "PhysicsSystem.h"
#include "PositionComponent.h"
#include "Types.h"

void updatePositions(const Input& inputs, std::vector<Entity> scene) {
    for (int i = 0; i < scene.size(); i++) {
        PositionComponent* temp_component = dynamic_cast<PositionComponent*>(scene[i].getComponentByID(ComponentID::PositionComponent));
        if (scene[i].getEntityID() == -1) {
            if (scene[i].getType() == ObjectType::Tank) {
                Position temp_position = *temp_component->getPosition();
                
                if (inputs.moving_right_ && !inputs.moving_left_ && inputs.moving_down_ == false && inputs.moving_up_ == false) {
                    temp_position.x = moving(temp_position.x, temp_component->getSpeed()->speed_x_);
                }
                if (inputs.moving_left_) {
                    temp_position.x = moving(temp_position.x, -temp_component->getSpeed()->speed_x_);
                }
                if (inputs.moving_down_) {
                    temp_position.y = moving(temp_position.y, temp_component->getSpeed()->speed_x_);
                }
                if (inputs.moving_up_) {
                    temp_position.y = moving(temp_position.y, -temp_component->getSpeed()->speed_x_);
                }

                


            }          
        }
        
        



    }
    /* bool moving_right_ = false;
    bool moving_left_ = false;
    bool moving_up_ = false;
    bool moving_down_ = false;*/


}

int moving(int coordinate, int speed) {
    coordinate = coordinate + speed;
}
