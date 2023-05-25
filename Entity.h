#pragma once
#include "Types.h"
#include "Component.h"
#include <unordered_map>
#include "Types.h"

class Component;

class Entity {
public:

    explicit Entity() {};

    Entity(ObjectType type) : type_(type) {};

    Entity(ObjectType type, int id) : type_(type), entity_id_(id) {};

    Component* getComponentByID(const ComponentID& id) { return components_[id]; }

    void deleteComponent(ComponentID id) { components_.erase(id); }

    void setType(ObjectType type) { type_ = type; }

    ObjectType getType() { return type_; }

    void putComponent(ComponentID id, Component* to_add) { components_.insert({ id,to_add }); };

    int getEntityID() { return entity_id_; };

    void setEntityID(int id) { entity_id_ = id; }

private:

    ObjectType type_ = ObjectType::Null; // если не задали тип, то будет видно 

    std::unordered_map<ComponentID, Component*> components_;

    int entity_id_ = 0;

};

