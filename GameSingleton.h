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

	void setNumberOfPlayers(int number) { numberOfPlayers_ = number; }

	void setTurretType(int i, int type) { turret_type_[i] = type; };

	void setStateDecision(bool decision) { stateIsDecided_ = decision; }

	void setConnectionType(ConnectionType type) { connectionType_ = type; }

	void setHullType(int i, int type) { hull_type_[i] = type; };

	void setMyEntityId(int id) { myEntityId_ = id; };

	void setFirstCollidable(int collidable) { firstCollidable_ = collidable; }

	int getNumberOfPlayers() { return numberOfPlayers_; }

	int getTurretType(int i) { return turret_type_[i]; }

	int getHullType(int i) { return hull_type_[i]; }

	int getMyEntityId() { return myEntityId_; }

	bool getStateDecision() { return stateIsDecided_; }

	int getFirstCollidable() { return firstCollidable_; }
	
	ConnectionType getConnectionType() { return connectionType_; }

	static Game& getInstance() {
		static Game singleton_;
		return singleton_;
	};

private:

	int myEntityId_;

	int firstCollidable_ = 0;

	bool stateIsDecided_ = false;

	int numberOfPlayers_ = 4;

	ConnectionType connectionType_ = ConnectionType::Null;

	std::vector<int> turret_type_ = std::vector<int>(numberOfPlayers_);
	std::vector<int> hull_type_ = std::vector<int>(numberOfPlayers_);

	Game() {};

	Game(const Game&) = delete;

	Game& operator= (const Game&) = delete;

	Game& operator= (Game&&) = delete;

};
