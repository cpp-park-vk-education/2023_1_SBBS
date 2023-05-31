#pragma once
#include "Types.h"
#include "networkCodes.h"
#include <vector>
#include <memory>
#include <iostream>
#include <string>
#include <boost/lockfree/queue.hpp>
#include <boost/thread/thread.hpp>
#include <SFML/Graphics.hpp>
#include "GameState.h"

#define MAX_LENGTH boost::lockfree::capacity<100>

struct package {
	int id_ = 0;
	int eventType_ = 0;
	int info1_ = 0;
	int info2_ = 0;
	int info3_ = 0;
	int info4_ = 0;
	int checker_ = CHECKER;
	int breaker_ = BREAKER;

	package(int id, int eventType, int info1, int info2, int info3 = 0, int info4 = 0) :
		id_(id), eventType_(eventType), info1_(info1), info2_(info2),
		info3_(info3), info4_(info4) {}

	package() {};

	explicit operator bool() const { return eventType_ != 0; }
};

class NetConnector {
public:

	static NetConnector& getInstance() {
		static NetConnector singleton_;
		return singleton_;
	};

	void openConnection(boost::lockfree::queue<package, MAX_LENGTH>* LockFreeQueueInput,
		boost::lockfree::queue<package, MAX_LENGTH>* LockFreeQueueOutput);

	void send(const package& to_send);

	package get();

private:

	NetConnector() {};

	NetConnector(const NetConnector&) = delete;

	NetConnector& operator= (const NetConnector&) = delete;

	NetConnector& operator= (NetConnector&&) = delete;

	NetConnector(boost::lockfree::queue<package, MAX_LENGTH>* LockFreeQueueInput,
		boost::lockfree::queue<package, MAX_LENGTH>* LockFreeQueueOutput);

	int next_state_option;

	boost::lockfree::queue<package, MAX_LENGTH>* lockFreeQueueInput_;
	boost::lockfree::queue<package, MAX_LENGTH>* lockFreeQueueOutput_;

	std::vector<package> events;
	std::vector<package> positions;

};

void netWork(boost::lockfree::queue<package, MAX_LENGTH>* LockFreeQueueInput,
	boost::lockfree::queue<package, MAX_LENGTH>* LockFreeQueueOutput);

void startServer(boost::lockfree::queue<package, MAX_LENGTH>* LockFreeQueueInput,
	boost::lockfree::queue<package, MAX_LENGTH>* LockFreeQueueOutput);

void startClient(boost::lockfree::queue<package, MAX_LENGTH>* LockFreeQueueInput,
	boost::lockfree::queue<package, MAX_LENGTH>* LockFreeQueueOutput);
