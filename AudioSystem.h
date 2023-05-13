#pragma once
#include "System.h"
#include "Types.h"
#include "Entity.h"
#include "Input.h"

class AudioSystem : public System {
public:

    void playEffects(std::vector<Entity> scene);

};