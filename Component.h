#pragma once

enum class ComponentID : char {
    GraphicsComponent, HealthComponent, PositionComponent, SoundComponent,
    CollisionComponent, ClickComponent, MusicComponent,
};

struct Position {

    int x = -1;
    int y = -1;

};

class Component {
public:
    Component() = default;

    virtual ~Component() = default;
};
