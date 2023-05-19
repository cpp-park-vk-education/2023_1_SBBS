﻿#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include <vector>
#include "Types.h"
#include "netConnect.h"
#include <chrono>


int gameLoop(boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueInput,
	boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueOutput,
	ConnectionType* connection);

int main() {

	boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueInput = new boost::lockfree::queue<int, MAX_LENGTH>;
	boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueOutput = new boost::lockfree::queue<int, MAX_LENGTH>;
	boost::thread_group producer_threads;

	NetConnector::getInstance().openConnection(LockFreeQueueInput, LockFreeQueueOutput);

	ConnectionType* connection_ = new ConnectionType(ConnectionType::Null);

	producer_threads.create_thread([LockFreeQueueInput, LockFreeQueueOutput, connection_]() { netWork(LockFreeQueueInput, LockFreeQueueOutput, connection_); });
	//producer_threads.create_thread([LockFreeQueueInput, LockFreeQueueOutput, connection_]() { gameLoop(LockFreeQueueInput, LockFreeQueueOutput, connection_); });

	gameLoop(LockFreeQueueInput, LockFreeQueueOutput, connection_);

	producer_threads.join_all();

	return 0;

}

int gameLoop(boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueInput,
	boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueOutput,
	ConnectionType* connection) {

	GameState* curr_state = new MainMenuGameState(); // enable_sharing_form_this   -  

	sf::RenderWindow window(sf::VideoMode({ 1900,1000 }), "ACT-ION");

	std::chrono::steady_clock::time_point last_time = std::chrono::high_resolution_clock::now();


	while (1) {
		
		curr_state = curr_state->update(window);
		GameStateId curr_id = curr_state->getStateId();
		 
		/////////////////////////  
		if (curr_id == GameStateId::HostPlaying) {
			*connection = ConnectionType::Host;
			// тут вызввать ивент 
			// тут хранить меняли ли ивент до этого 
		}
		else if (curr_id == GameStateId::ClientPlaying) {
			*connection = ConnectionType::Client;
		}
		/////////////////////////
		// синглтон на время или глобальная переменная 

		std::chrono::steady_clock::time_point curr_time = std::chrono::high_resolution_clock::now();
		double elapsed_time = std::chrono::duration<double>(curr_time - last_time).count();
		//std::cout << elapsed_time << std::endl;


		if (elapsed_time < double(1.0 / 60.0)) {
			std::cout << double(1.0 / 60.0) - elapsed_time << std::endl;
			Sleep(double(1.0 / 60.0) - elapsed_time);
		}
		last_time = curr_time;
	}
}