#pragma once
#include "Entity.h"
#include "Component.h"

const double EPS = 1E-9;

inline int det(int a, int b, int c, int d) {
    return a * d - b * c;
}

inline bool between(int a, int b, double c) {
    return std::min(a, b) <= c + EPS && c <= std::max(a, b) + EPS;
}

inline bool intersect_1(int a, int b, int c, int d) {
    if (a > b)  std::swap(a, b);
    if (c > d)  std::swap(c, d);
    return std::max(a, c) <= std::min(b, d);
}

bool intersect(Position a, Position b, Position c, Position d) {
    int A1 = a.y - b.y, B1 = b.x - a.x, C1 = -A1 * a.x - B1 * a.y;
    int A2 = c.y - d.y, B2 = d.x - c.x, C2 = -A2 * c.x - B2 * c.y;
    int zn = det(A1, B1, A2, B2);
    if (zn != 0) {
        double x = -det(C1, B1, C2, B2) * 1. / zn;
        double y = -det(A1, C1, A2, C2) * 1. / zn;
        return between(a.x, b.x, x) && between(a.y, b.y, y)
            && between(c.x, d.x, x) && between(c.y, d.y, y);
    }
    else
        return det(A1, C1, A2, C2) == 0 && det(B1, C1, B2, C2) == 0
        && intersect_1(a.x, b.x, c.x, d.x)
        && intersect_1(a.y, b.y, c.y, d.y);
}

class CollisionComponent : public Component {
public:

    CollisionComponent(Position* position_, int rotation, int height_, int width_, ObjectType type_){
        this->position_ = position_;
        this->rotation = rotation;
        this->type_ = type_;
        if (type_ != ObjectType::Turret) {
            height_ = height_ / 2;
            width_ = width_ / 2;
            for (int i = 0; i < 4; i++) {
                hitbox_.push_back(*position_);
            }           
            hitbox_[0].x = position_->x + (cos(rotation) * (height_)+cos(rotation + 90) * (width_));
            hitbox_[1].x = position_->x + (cos(rotation) * (height_)+cos(90 - rotation) * (width_));
            hitbox_[2].x = position_->x - (cos(rotation) * (height_)+cos(rotation + 90) * (width_));
            hitbox_[3].x = position_->x - (cos(rotation) * (height_)+cos(90 - rotation) * (width_));
            hitbox_[0].y = position_->y + (sin(rotation) * (height_)+sin(rotation + 90) * (width_));
            hitbox_[1].y = position_->y + (sin(rotation) * (height_)+sin(90 - rotation) * (width_));
            hitbox_[2].y = position_->y - (sin(rotation) * (height_)+sin(rotation + 90) * (width_));
            hitbox_[3].y = position_->y - (sin(rotation) * (height_)+sin(90 - rotation) * (width_));
        }
        else {
            width_ = width_ / 2;
            hitbox_[0].x = position_->x + (cos(rotation) * (height_)+cos(rotation + 90) * (width_));
            hitbox_[1].x = position_->x + (cos(rotation) * (height_)+cos(90 - rotation) * (width_));
            hitbox_[2].y = position_->y + (sin(rotation) * (height_)+sin(rotation + 90) * (width_));
            hitbox_[3].y = position_->y + (sin(rotation) * (height_)+sin(90 - rotation) * (width_));
            hitbox_[0].x = position_->x - cos(rotation + 90) * (width_);
            hitbox_[1].x = position_->x - cos(90 - rotation) * (width_);
            hitbox_[2].y = position_->y - sin(rotation + 90) * (width_);
            hitbox_[3].y = position_->y - sin(90 - rotation) * (width_);
        }      
    }

    CollisionComponent(){
    
    }

    bool checkCollision(CollisionComponent* tested_object) {
        std::vector<Position> temp_hitbox_this = hitbox_;
        temp_hitbox_this.push_back(temp_hitbox_this[0]);
        std::vector<Position> temp_hitbox_in = tested_object->get_hitbox();
        temp_hitbox_in.push_back(temp_hitbox_in[0]);
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (intersect(temp_hitbox_this[i], temp_hitbox_this[i + 1], temp_hitbox_in[j], temp_hitbox_in[j + 1])) {
                    return false;
                }
            }
        }
        return true;
    }

    ~CollisionComponent();


    void setPosition(Position& position) { position_ = &position; }

    void setRotation(const int& coner) {
        rotation = coner;
    }

    std::vector<Position> get_hitbox() {
        return hitbox_;
    }

    CollisionComponent(CollisionComponent* comp) = delete;    

    //CollisionComponent operator= (CollisionComponent) = delete; ћне он нужен

private:

    ObjectType type_;

    Position* position_;

    std::vector<Position> hitbox_;

    int rotation;

    int height_ = -1;
    int width_ = -1;

    void (*onCollisionEvent)(Entity& collided);

};