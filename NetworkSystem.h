#pragma once
#include "System.h"
#include "Types.h"
#include "Entity.h"


class GameEvent {

};


class NetworkSystem : public System {
public:

    std::vector<GameEvent> getEvents();

    void sendEvents(std::vector<GameEvent> events);

    void updateScene(std::vector<GameEvent> events, std::vector<Entity> scene);

};
