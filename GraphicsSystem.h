#pragma once
#include "System.h"
#include "Types.h"
#include "Entity.h"

class GraphicsSystem : public System {
public:
    void renderScene(std::vector<Entity>& scene);
};