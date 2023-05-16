#include "Server.h"
#include "Client.h"
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include <iostream>

void netWork(boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueInput, 
             boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueOutput, ConnectionType* _connection) {
    while (*_connection == ConnectionType::Null) {}

    std::cout << "Connection type aquired\n";

    if (*_connection == ConnectionType::Host) {
        std::cout << "Host State Active\n";
        startServer(LockFreeQueueInput, LockFreeQueueOutput);
    }
    else if (*_connection == ConnectionType::Client) {
        std::cout << "Client State Active\n";
        startClient(LockFreeQueueInput, LockFreeQueueOutput);
        
    }
}

void startServer(boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueInput, 
                  boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueOutput) {
    try
    {
        boost::asio::io_service io_service;
        Server server(io_service, LockFreeQueueInput, LockFreeQueueOutput);
        io_service.run();
    }
    catch (std::exception& e) {
        std::cerr << e.what() << endl;
    }
}

void startClient(boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueInput,
    boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueOutput) {

    while (true) {
        try {
            //std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            boost::asio::io_service io_service;
            Client client(io_service, LockFreeQueueInput, LockFreeQueueOutput);
            int a;
            while (LockFreeQueueInput->pop(a)) {
                //cout << a << endl;
            }
        }
        catch (std::exception& e) {
            std::cerr << e.what() << endl;
        }
    }
}