#pragma once
#pragma once
#include "Types.h"
#include <vector>
#include <memory>
#include <iostream>
#include <string>
#include <boost/lockfree/queue.hpp>
#include <boost/thread/thread.hpp>
#include <SFML/Graphics.hpp>
#include "GameState.h"

class Game {
public:

	void setTurretType(int i, int type) { turret_type_[i] = type; };

	void setHullType(int i, int type) { hull_type_[i] = type; };

	void setMyEntityId(int id) { my_entity_id_ = id; };

	int getTurretType(int i) { return turret_type_[i]; }

	int getHullType(int i) { return hull_type_[i]; }

	int getMyEntityId() { return my_entity_id_; }

	static Game& getInstance() {
		static Game singleton_;
		return singleton_;
	};

private:

	std::vector<int> turret_type_ = std::vector<int>(4);
	std::vector<int> hull_type_ = std::vector<int>(4);

	int my_entity_id_;

	Game() {};

	Game(const Game&) = delete;

	Game& operator= (const Game&) = delete;

	Game& operator= (Game&&) = delete;

};
