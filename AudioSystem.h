#pragma once
#include "System.h"
#include "Types.h"
#include "Entity.h"

class AudioSystem : public System {
public:

    void playEffects(std::vector<Entity> scene);

};