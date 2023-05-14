#pragma once
#include "Types.h"
#include "Component.h"
#include <unordered_map>
#include "Types.h"

class Component;

class Entity {
public:

    Entity(ObjectType type) : type_(type) {};

    Entity(ObjectType type, int id) : type_(type), entity_id_(id) {};

   /* Entity operator= (Entity& other) {
        components_ = other.components_;
        return *this;
    }*/

    Component* getComponentByID(const ComponentID& id) {
            return components_[id];
    }

    ObjectType getType() { return type_; }

    void putComponent(ComponentID id, Component* to_add) { components_.insert({ id,to_add }); };

    int getEntityID() { return entity_id_; };

    void setEntityID(int id) { entity_id_ = id; }

private:

    ObjectType type_;

    std::unordered_map<ComponentID, Component*> components_;

    int entity_id_ = -1;

};

