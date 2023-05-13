#pragma once
#include "Entity.h"
#include "Component.h"
#include "GameState.h"

class ClickComponent : public Component {
public:
    void onClickEvent(GameState* curr_state);

private:
    Entity* owner_ = nullptr;
};
