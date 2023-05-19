#pragma once
#include "GameState.h"
#include "System.h"
#include "Types.h"
#include "GraphicsSystem.h"
#include "MenuSystem.h"
#include "MusicSystem.h"
#include "PhysicsSystem.h"
#include "SoundSystem.h"
#include "SpawnerSystem.h"


void GameState::addSystem(SystemId id) { 
	switch (id) {
	case SystemId::GraphicsSystemId:
		systems_.push_back(new GraphicsSystem());
		break;
	case SystemId::MenuSystemId:
		systems_.push_back(new MenuSystem());
		break;
	case SystemId::MusicSystemId:
		systems_.push_back(new MusicSystem());
		break;
	case SystemId::PhysicsSystemId:
		systems_.push_back(new PhysicsSystem());
		break;
	case SystemId::SoundSystemId:
		systems_.push_back(new SoundSystem());
		break;
	case SystemId::SpawnerSystemId:
		systems_.push_back(new SpawnerSystem());
		break;
	default:
		break;
	}
}
