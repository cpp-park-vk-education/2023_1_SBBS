#pragma once

enum class ComponentID : char {
    GraphicsComponent, HealthComponent, PositionComponent, SoundComponent,
    CollisionComponent, ClickComponent, MusicComponent,
};

struct Position {

    int x;
    int y;

    Position() { x = -1; y = -1; }

    Position(int _x, int _y) { x = _x; y = _y; }
};

class Component {
public:
    Component() = default;

    virtual ~Component() = default;
};
