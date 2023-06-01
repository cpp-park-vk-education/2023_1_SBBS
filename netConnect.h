#pragma once
#include "Types.h"
#include "networkCodes.h"
#include <vector>
#include <memory>
#include <iostream>
#include <string>
#include <queue>
#include <chrono>
#include <boost/lockfree/queue.hpp>
#include <boost/thread/thread.hpp>
#include <SFML/Graphics.hpp>
#include "GameState.h"

#define MAX_LENGTH boost::lockfree::capacity<10000>


struct package {
	int id_ = 0;
	int eventType_ = 0;
	int info1_ = 0;
	int info2_ = 0;
	int info3_ = 0;
	int info4_ = 0;

	package(int id, int eventType, int info1, int info2, int info3 = 0, int info4 = 0) :
		id_(id), eventType_(eventType), info1_(info1), info2_(info2),
		info3_(info3), info4_(info4) {}

	package() {};

	package(const package& other) : id_(other.id_), eventType_(other.eventType_), info1_(other.info1_), info2_(other.info2_),
		info3_(other.info3_), info4_(other.info4_) {
	};

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

	package getPosition();

	void pushPosition(const package& to_return);

	package getEvent();

private:
	void get();

	NetConnector() {};

	NetConnector(const NetConnector&) = delete;

	NetConnector& operator= (const NetConnector&) = delete;

	NetConnector& operator= (NetConnector&&) = delete;

	NetConnector(boost::lockfree::queue<package, MAX_LENGTH>* LockFreeQueueInput,
		boost::lockfree::queue<package, MAX_LENGTH>* LockFreeQueueOutput);


	boost::lockfree::queue<package, MAX_LENGTH>* lockFreeQueueInput_;
	boost::lockfree::queue<package, MAX_LENGTH>* lockFreeQueueOutput_;

	std::queue<package> events_;
	std::queue<package> positions_;

};

void netWork(boost::lockfree::queue<package, MAX_LENGTH>* LockFreeQueueInput,
	boost::lockfree::queue<package, MAX_LENGTH>* LockFreeQueueOutput);

void startServer(boost::lockfree::queue<package, MAX_LENGTH>* LockFreeQueueInput,
	boost::lockfree::queue<package, MAX_LENGTH>* LockFreeQueueOutput);

void startClient(boost::lockfree::queue<package, MAX_LENGTH>* LockFreeQueueInput,
	boost::lockfree::queue<package, MAX_LENGTH>* LockFreeQueueOutput);
