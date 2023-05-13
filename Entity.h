#pragma once
#include "Types.h"
#include "Component.h"
#include <unordered_map>

class Component;

class Entity {
public:

    Entity() = default;

    Component* getComponentByID(const ComponentID& id) {
        return components_.at(id);
    }

    void putComponent(ComponentID id, Component* to_add) { components_.insert({ id,to_add }); };

    int getEntityID();

private:
    std::unordered_map<ComponentID, Component*> components_;

    int entity_id_ = -1;

};
