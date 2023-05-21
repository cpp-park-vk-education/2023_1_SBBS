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
#include "PlayingArgsHolder.h"


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

GameState::~GameState() {
	for (int i = 0; i < systems_.size(); ++i) {
		delete systems_[i];
	}
	for (int i = 0; i < scene_.size(); ++i) {
		delete scene_[i];
	}
}

SubMenuState::~SubMenuState() {
	PlayingArgsHolder::getInstance().setHullType(PlayingArgsHolder::getInstance().getMyEntityId() - 1, tank_hull);
	PlayingArgsHolder::getInstance().setTurretType(PlayingArgsHolder::getInstance().getMyEntityId() - 1, tank_turret);
}