#pragma once
#include "Server.h"
#include <vector>
#include <memory>
#include <iostream>


class NetConnector {
public:

	NetConnector() {};

	NetConnector(boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueInput,
		boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueOutput)
		: lockFreeQueueInput_(LockFreeQueueInput),
		  lockFreeQueueOutput_(LockFreeQueueOutput) {}


	void openConnection(boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueInput,
		boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueOutput) {

		std::cout << "Connection opened... "<<std::endl;
		lockFreeQueueInput_ = LockFreeQueueInput;
		lockFreeQueueOutput_ = LockFreeQueueOutput;
		int x = 0;
	}

	void send(std::vector<int>& to_send) {
		std::cout << "Writing into queue..." << std::endl;
		for (int i = 0; i < to_send.size(); ++i) { //// тут не уверен
			std::cout << to_send[i] << " ";
			lockFreeQueueOutput_->push(to_send[i]);
		}
		std::cout << "Done writing" << std::endl;
	}

	std::vector<int> get() {
		std::vector<int> recieved;
		int curr_data = 0;
		std::cout << "Got from queue..." << std::endl;
		while (lockFreeQueueInput_->pop(curr_data)) {
			recieved.push_back(curr_data);
			std::cout << curr_data << " ";
		}
		std::cout << "Done recieving. " << std::endl;
		return recieved;
	}

private:

	boost::lockfree::queue<int, MAX_LENGTH>* lockFreeQueueInput_;
	boost::lockfree::queue<int, MAX_LENGTH>* lockFreeQueueOutput_;

};


class SingletonSender {
public :

	static NetConnector& getInstance() {
		static std::unique_ptr<NetConnector> singleton_ = std::make_unique<NetConnector>();
		return *singleton_;
	};

private:

	SingletonSender() {};

	
};