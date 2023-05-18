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

#define MAX_LENGTH boost::lockfree::capacity<100>


class NetConnector {
public:

	static NetConnector& getInstance() {
		static std::unique_ptr<NetConnector> singleton_ = std::make_unique<NetConnector>();
		return *singleton_;
	};

	void openConnection(boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueInput,
		boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueOutput);

	void send(std::vector<int>& to_send);

	std::vector<int> get();

private:

	NetConnector() {};

	//NetConnector(const NetConnector&) = delete;

	//NetConnector& operator= (const NetConnector&) = delete;

	//NetConnector& operator= (NetConnector&&) = delete;

	NetConnector(boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueInput,
		boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueOutput);

	boost::lockfree::queue<int, MAX_LENGTH>* lockFreeQueueInput_;
	boost::lockfree::queue<int, MAX_LENGTH>* lockFreeQueueOutput_;

};


void netWork(boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueInput,
	boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueOutput, ConnectionType* _connection);

void startServer(boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueInput,
	boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueOutput);

void startClient(boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueInput,
	boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueOutput);
