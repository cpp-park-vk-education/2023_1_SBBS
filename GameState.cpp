#include "GameState.h"
#include "System.h"
#include "Types.h"

void GameState::addSystem(SystemId id, System* system) { systems_.insert({ id,system }); }

System* GameState::getSystemById(SystemId id) { return systems_.at(id); }