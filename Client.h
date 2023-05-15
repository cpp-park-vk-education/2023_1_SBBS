#pragma once
#include <iostream>
#include <boost/asio.hpp>
#include <boost/lockfree/queue.hpp>

#define MAX_LENGTH boost::lockfree::capacity<100>

using namespace boost::asio;
using ip::tcp;
using std::string;
using std::cout;
using std::endl;
// "127.0.0.1"
class Client {
private:
    tcp::socket sock;
    std::string message = "1 2 3 4";
    enum { max_length = 1024 };
    char data[max_length];
    boost::lockfree::queue<int, MAX_LENGTH>* ClientQueueInput;
    boost::lockfree::queue<int, MAX_LENGTH>* ClientQueueOutput;
public:
    Client(boost::asio::io_service& io_service, boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueInput,
        boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueOutput) :
        sock(io_service), ClientQueueInput(LockFreeQueueInput), ClientQueueOutput(LockFreeQueueOutput) {
        connect();
    }

    void connect() {
        sock.connect(tcp::endpoint(boost::asio::ip::address::from_string("25.49.68.205"), 6001));
        start();
    }

    void start() {
        boost::system::error_code error;
        boost::asio::write(sock, boost::asio::buffer(message), error);
        if (!error) {
            cout << "Client sent " << message << endl;
        }
        else {
            cout << "send failed: " << error.message() << endl;
        }

        boost::asio::read(sock, boost::asio::buffer(data, max_length), boost::asio::transfer_all(), error);
        if (error && error != boost::asio::error::eof) {
            cout << "receive failed: " << error.message() << endl;
        }
        else {
            std::stringstream s(data);
            string num;
            while (s >> num) {
                ClientQueueInput->push(std::stoi(num));
                //cout << std::stoi(num) << endl;
            }
        }
    }
    /*
    void translate_to_string() {
        int a;
        message = "";
        while (ClientQueueOutput->pop(a)) {
            cout << a << endl;
            message += std::to_string(a) + " ";
        }
        return;
    }
    string return_string_array() {
        std::string a = "1 2 3 4 5 10000";
        return a;
    }*/

};

void startClient(boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueInput,
    boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueOutput);
