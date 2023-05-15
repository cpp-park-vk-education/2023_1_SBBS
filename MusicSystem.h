#pragma once
#include "System.h"
#include "Types.h"
#include "Entity.h"

class MusicSystem : public System {
public:

    void playMusic(std::vector<Entity>& scene);

};