#pragma once
#include "Types.h"
#include "Component.h"
#include <unordered_map>

class Component;

class Entity {
public:

    Entity();

    Component* getComponentByID(const ComponentID& id) {
        return components_.at(id);
    }

    //void putComponent(Component* to_add) {components_.insert() };

    int getEntityID();

private:
    std::unordered_map<ComponentID, Component*> components_;

    int entity_id_ = -1;

};
