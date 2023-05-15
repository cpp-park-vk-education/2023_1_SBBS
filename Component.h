#pragma once

enum class ComponentID : char {
    GraphicsComponent, HealthComponent, PositionComponent, SoundComponent,
    CollisionComponent, ClickComponent, MusicComponent,
};

struct Position {

    int x;
    int y;

    int rotation;

    Position() { x = -1; y = -1; rotation = 0;  }

    Position(int _x, int _y, int _rotation = 0) { x = _x; y = _y; rotation = _rotation; }
};

class Component {
public:
    Component() = default;

    virtual ~Component() = default;
};
