#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include <vector>
#include "Types.h"
#include "netConnect.h"
#include <chrono>
#include <thread>
#include "GameStateManager.h"


int gameLoop(boost::lockfree::queue<package, MAX_LENGTH>* LockFreeQueueInput,
	boost::lockfree::queue<package, MAX_LENGTH>* LockFreeQueueOutput);


int main() {

	boost::lockfree::queue<package, MAX_LENGTH>* LockFreeQueueInput = new boost::lockfree::queue<package, MAX_LENGTH>;
	boost::lockfree::queue<package, MAX_LENGTH>* LockFreeQueueOutput = new boost::lockfree::queue<package, MAX_LENGTH>;
	boost::thread_group producer_threads;

	NetConnector::getInstance().openConnection(LockFreeQueueInput, LockFreeQueueOutput);

	producer_threads.create_thread([LockFreeQueueInput, LockFreeQueueOutput]() { netWork(LockFreeQueueInput, LockFreeQueueOutput); });
	//producer_threads.create_thread([LockFreeQueueInput, LockFreeQueueOutput, connection_]() { gameLoop(LockFreeQueueInput, LockFreeQueueOutput, connection_); });

	gameLoop(LockFreeQueueInput, LockFreeQueueOutput);

	producer_threads.join_all();

	return 0;

}

int gameLoop(boost::lockfree::queue<package, MAX_LENGTH>* LockFreeQueueInput,
	boost::lockfree::queue<package, MAX_LENGTH>* LockFreeQueueOutput) {

	sf::RenderWindow window(sf::VideoMode({ 1900,1000 }), "ACT-ION", sf::Style::Close);
	std::chrono::steady_clock::time_point last_time = std::chrono::high_resolution_clock::now();

	const double tick_time = 1.0 / 60;
	
	StateManager manager;
	manager.changeState(GameStateId::MainMenu);
	
	while (window.isOpen()) {
		
		manager.run(window);
		GameStateId curr_id = manager.getStateId();
		 
		///////////////////////
		// синглтон на время или глобальная переменная 


		std::chrono::steady_clock::time_point curr_time = std::chrono::high_resolution_clock::now();
		double elapsed_time = std::chrono::duration<double>(curr_time - last_time).count();

		if (elapsed_time < tick_time) {
			double sleep_time = tick_time - elapsed_time;
			std::chrono::duration<double> sleep_duration(sleep_time);
			std::this_thread::sleep_for(sleep_duration);
		}
		else {
			//////////////////////////////////////////////////////////////////
			std::cout << "missed by " << elapsed_time - tick_time << std::endl;
			//////////////////////////////////////////////////////////////////
		}
		last_time = std::chrono::high_resolution_clock::now();
	}
	return 0;
}