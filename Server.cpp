#include "Server.h"
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include <iostream>

void netWork(boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueInput, 
             boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueOutput, ConnectionType* _connection) {
    while (*_connection == ConnectionType::Null) {}

    std::cout << "Connection type aquired";

    if (*_connection == ConnectionType::Host)
        start_server(LockFreeQueueInput, LockFreeQueueOutput);
    else
        ;

}


void start_server(boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueInput, 
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

void work_with_thread(boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueInput, boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueOutput) {
    int a;
    for (int i = 0; i < 100; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        cout << "Thread starts working" << endl;
        while (LockFreeQueueInput->pop(a)) {
            LockFreeQueueOutput->push(a);
            cout << a << endl;
        }
    }
}




//int tmain(int argc, char* argv[]) {
//    boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueInput = new boost::lockfree::queue<int, MAX_LENGTH>;
//    boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueOutput = new boost::lockfree::queue<int, MAX_LENGTH>;
//
//    boost::thread_group producer_threads;
//    producer_threads.create_thread([LockFreeQueueInput, LockFreeQueueOutput]() { start_server(LockFreeQueueInput, LockFreeQueueOutput); });
//    producer_threads.create_thread([LockFreeQueueInput, LockFreeQueueOutput]() { work_with_thread(LockFreeQueueInput, LockFreeQueueOutput); });
//    cout << "Complete" << endl;
//    producer_threads.join_all();
//    return 0;
//}