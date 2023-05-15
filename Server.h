#pragma once
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/thread/thread.hpp>
#include <string>
#include "Types.h"

#define GET_IO_SERVICE(s) ((boost::asio::io_context&)(s).get_executor().context())
#define MAX_LENGTH boost::lockfree::capacity<100>

using namespace boost::asio;
using ip::tcp;
using std::cout;
using std::endl;
using std::string;


class con_handler : public boost::enable_shared_from_this<con_handler> {
private:
    tcp::socket sock;
    std::string message = "Hello From Server!";
    enum { max_length = 1024 };
    char data[max_length];
    boost::lockfree::queue<int, MAX_LENGTH>* ServerQueueInput;
    boost::lockfree::queue<int, MAX_LENGTH>* ServerQueueOutput;
    bool state = false;

public:
    typedef boost::shared_ptr<con_handler> pointer;
    con_handler(boost::asio::io_service& io_service, boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueInput, boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueOutput) :
        sock(io_service), ServerQueueInput(LockFreeQueueInput), ServerQueueOutput(LockFreeQueueOutput) {}
    static pointer create(boost::asio::io_service& io_service, boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueInput, boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueOutput) {
        return pointer(new con_handler(io_service, LockFreeQueueInput, LockFreeQueueOutput));
    }
    tcp::socket& socket() {
        return sock;
    }

    void start() {
        sock.async_read_some(
            boost::asio::buffer(data, max_length),
            boost::bind(&con_handler::handle_read,
                shared_from_this(),
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
        translate_to_string();
        sock.async_write_some(
            boost::asio::buffer(message, max_length),
            boost::bind(&con_handler::handle_write,
                shared_from_this(),
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    }

    void handle_read(const boost::system::error_code& err, size_t bytes_transferred) {
        if (!err) {
            std::stringstream s(data);
            string num;
            while (s >> num) {
                ServerQueueInput->push(std::stoi(num));
                //cout << std::stoi(num) << endl;
            }
        }
        else {
            std::cerr << "error: " << err.message() << std::endl;
            sock.close();
        }
    }
    void handle_write(const boost::system::error_code& err, size_t bytes_transferred) {
        if (!err) {
            cout << "Server sent Hello message!" << endl;
        }
        else {
            cout << "Error" << endl;
            std::cerr << "error: " << err.message() << endl;
            sock.close();
        }
    }
    string translate_to_string() {
        int a;
        message = "";
        while (ServerQueueOutput->pop(a)) { //////////// for test ServerQueueInput
            cout << a << endl;
            message += std::to_string(a) + " ";
        }
        return message;
    }
};

class Server {
private:
    tcp::acceptor acceptor_;
    boost::lockfree::queue<int, MAX_LENGTH>* ServerQueueInput;
    boost::lockfree::queue<int, MAX_LENGTH>* ServerQueueOutput;
    void start_accept() {
        con_handler::pointer connection = con_handler::create(GET_IO_SERVICE(acceptor_), ServerQueueInput, ServerQueueOutput);

        acceptor_.async_accept(connection->socket(),
            boost::bind(&Server::handle_accept, this, connection,
                boost::asio::placeholders::error));
    }
public:
    Server(boost::asio::io_service& io_service, boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueInput, boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueOutput) :
        acceptor_(io_service, tcp::endpoint(tcp::v4(), 6001)), ServerQueueInput(LockFreeQueueInput), ServerQueueOutput(LockFreeQueueOutput) {
        start_accept();
    }
    void handle_accept(con_handler::pointer connection, const boost::system::error_code& err) {
        if (!err) {
            connection->start();
        }
        start_accept();
    }
};

void netWork(boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueInput, boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueOutput, ConnectionType* _connection);

void startServer(boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueInput, boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueOutput);