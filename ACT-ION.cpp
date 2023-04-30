#include <SFML/Graphics.hpp>

class Entity;

class Component {
public:

    virtual void deleteComponent();

    virtual void update() = 0;
};

class HealthComponent : public Component {
public:

    int getHealth() const;

    void setHealth();

private:

    int health_;
};

class GraphicsComponent : public Component {
public:
    void update() override;

private:
    sf::Image obj_image_;
    sf::Texture obj_texture;
    sf::Sprite obj_sprite;
};

class PositionComponent : public Component {
public:

    void getPosition() const;

    void setPosition();

private:

    PositionComponent* parent_ = nullptr;

    int pos_x_;
    int pos_y_;
    
    int speed_x_;
    int speed_y_;
};

class MoveComponent : public Component {

};

class AudioComponent : public Component {

};

class ShootComponent : public Component {
public:
    

private:
    void shoot(Entity* scene);


};

class CollisionComponent : public Component {
public:

    void onCollisionEvent(Entity ent_1, Entity ent_2);


private:


};


class Entity {
public:

    Component* getComponentByID(int componentID) const;

    int getEntityID();

private:
    Component* components_[9];

    int entity_id_;

};

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}