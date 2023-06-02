#pragma once
#include "Entity.h"
#include "Component.h"
#include <SFML/Graphics.hpp>

inline const int base_x = 1;
inline const int base_y = 0;

struct Input_vector {
    int x = 0;
    int y = 0;
};

int moving(int coordinate, int speed, float prop);

int calculate_coner(const Input_vector& input_vector);

int calculate_angle(Input_vector a, Input_vector b);

int distance_p(Position a, Position b);

class PositionComponent : public Component {
public:
    PositionComponent() = default;

    Position getPosition() const { return parent_ ? parent_->getPosition() : position_; }

    int getSpeed() const { return speed_; }

    void setSpeed(int speed) { speed_ = speed; }

    int getRotation() { return position_.rotation; }

    void setPosition(Position position) { position_ = position; }; //пока костыль, потом исправим

    void setRotation(const int& coner) { position_.rotation = coner; }

    void setParent(PositionComponent* parent) { parent_ = parent; }

    virtual void update(sf::RenderWindow& window, std::vector<Entity*>& scene, int& i) {};
    // передаем по ссылке, чтобы не было ошибок при удалении пули 

private:

    PositionComponent* parent_ = nullptr;

    Position position_;

    int speed_ = 0;
};


class TankPositionComponent : public PositionComponent {
public:
    void update(sf::RenderWindow& window, std::vector<Entity*>& scene, int& i) override;
};

class TurretPositionComponent : public PositionComponent {
public:
    void update(sf::RenderWindow& window, std::vector<Entity*>& scene, int& i) override;
};

class BulletPositionComponent : public PositionComponent {
public:
    void update(sf::RenderWindow& window, std::vector<Entity*>& scene, int& i) override;
};

class BotTankPositionComponent : public PositionComponent {
public:
    void update(sf::RenderWindow& window, std::vector<Entity*>& scene, int& i) override;
};

class BotTurretPositionComponent : public PositionComponent {
public:
    void update(sf::RenderWindow& window, std::vector<Entity*>& scene, int& i) override;
};

class NetTankPositionComponent : public PositionComponent {
public:
    void update(sf::RenderWindow& window, std::vector<Entity*>& scene, int& i) override;
};

class NetTurretPositionComponent : public PositionComponent {
public:
    void update(sf::RenderWindow& window, std::vector<Entity*>& scene, int& i) override;
};

class NetBulletPositionComponent : public PositionComponent {
public:
    void update(sf::RenderWindow& window, std::vector<Entity*>& scene, int& i) override;
};
