#pragma once
#include "Types.h"
#include "Component.h"
#include <unordered_map>
#include "Types.h"
#include "HealthComponent.h"

class Component;

class Entity {
public:

    Entity(ObjectType type) : type_(type) {};

    Component* getComponentByID(const ComponentID& id) {
        return components_.at(id);
    }

    ObjectType getType() { return type_; }

    void putComponent(ComponentID id, Component* to_add) { components_.insert({ id,to_add }); };

    int getEntityID() { return entity_id_; };

private:

    ObjectType type_;

    std::unordered_map<ComponentID, Component*> components_;

    int entity_id_ = -1;

};

