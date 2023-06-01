#pragma once
#include "netConnect.h"
#include "GameSingleton.h"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "networkCodes.h"
#include <string>
#include <chrono>

#define GET_IO_SERVICE(s) ((boost::asio::io_context&)(s).get_executor().context())

using namespace boost::asio;
using ip::tcp;
using std::cout;
using std::endl;
using std::string;

NetConnector::NetConnector(boost::lockfree::queue<package, MAX_LENGTH>* LockFreeQueueInput,
		boost::lockfree::queue<package, MAX_LENGTH>* LockFreeQueueOutput)
		: lockFreeQueueInput_(LockFreeQueueInput),
		lockFreeQueueOutput_(LockFreeQueueOutput) {}


void NetConnector::openConnection(boost::lockfree::queue<package, MAX_LENGTH>* LockFreeQueueInput,
    boost::lockfree::queue<package, MAX_LENGTH>* LockFreeQueueOutput) {

    //std::cout << "Connection opened... "<<std::endl;
    lockFreeQueueInput_ = LockFreeQueueInput;
    lockFreeQueueOutput_ = LockFreeQueueOutput;
    int x = 0;
}

void  NetConnector::send(const package& to_send) {
    //std::cout << "Writing into queue..." << std::endl;

        //std::cout << to_send[i] << " ";
    lockFreeQueueOutput_->push(to_send);

    //std::cout << "Done writing" << std::endl;
};

void NetConnector::get() {
    package recieved;
    //std::cout << "Got from queue..." << std::endl;
    while (lockFreeQueueInput_->pop(recieved)) {

        if (recieved.eventType_ == TANK_POSITION_MARK ||
            recieved.eventType_ == TURRET_POSITION_MARK ||
            recieved.eventType_ == BULLET_POSITION_MARK) {
            positions_.push(recieved);
        }
        else if (recieved.eventType_ == HIT_EVENT || 
                 recieved.eventType_ == BULLET_SPAWN_EVENT ) {
            package bruh_recieved(recieved);
            events_.push(bruh_recieved);
        }
    }
    //std::cout << "Done recieving. " << std::endl;
}

package NetConnector::getPosition() {
    get();
    package position;


    static std::chrono::steady_clock::time_point last_time = std::chrono::high_resolution_clock::now();
    std::chrono::steady_clock::time_point curr_time = std::chrono::high_resolution_clock::now();
    double elapsed_time = std::chrono::duration<double>(curr_time - last_time).count();

    if (elapsed_time > 0.1) {
        std::queue<package> clean_queue;
        positions_.swap(clean_queue);
        last_time = std::chrono::high_resolution_clock::now();
    }


    if (!positions_.empty()) {

        position = positions_.front();
        positions_.pop();
    }
    return position;
}

package NetConnector::getEvent() {
    get();
    package event_;
    
    if (!events_.empty()) {
        event_ = events_.front();
        events_.pop();
    }
    return event_;
}

// Серверная часть реализации сети
class con_handler : public boost::enable_shared_from_this<con_handler> {
private:
    tcp::socket sock;

    std::string message = "Hello From Server!";

    enum { max_length = 1024 };

    char data[max_length];

    boost::lockfree::queue<package, MAX_LENGTH>* ServerQueueInput;

    boost::lockfree::queue<package, MAX_LENGTH>* ServerQueueOutput;

    bool state = false;

public:
    typedef boost::shared_ptr<con_handler> pointer;

    con_handler(boost::asio::io_service& io_service, boost::lockfree::queue<package, MAX_LENGTH>* LockFreeQueueInput, boost::lockfree::queue<package, MAX_LENGTH>* LockFreeQueueOutput) :
        sock(io_service), ServerQueueInput(LockFreeQueueInput), ServerQueueOutput(LockFreeQueueOutput) {}

    static pointer create(boost::asio::io_service& io_service, boost::lockfree::queue<package, MAX_LENGTH>* LockFreeQueueInput, boost::lockfree::queue<package, MAX_LENGTH>* LockFreeQueueOutput) {
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
            std::stringstream buf(data);
            string line;
            while (std::getline(buf, line)) {
                std::stringstream stringPackage(line);
                string sId, sEventType, sInfo1, sInfo2, sInfo3, sInfo4;
                if (stringPackage >> sId >> sEventType >> sInfo1 >> sInfo2 >> sInfo3 >> sInfo4) {
                    package new_package(stoi(sId), stoi(sEventType), stoi(sInfo1), stoi(sInfo2), stoi(sInfo3), stoi(sInfo4));
                    ServerQueueInput->push(new_package);
                }
            }
        }
        else {
            std::cerr << "error: " << err.message() << std::endl;
            sock.close();
        }
    }

    void handle_write(const boost::system::error_code& err, size_t bytes_transferred) {
        if (err) {
            cout << "Error" << endl;
            std::cerr << "error: " << err.message() << endl;
            sock.close();
        }
        /*
        else {
            cout << "Error" << endl;
            std::cerr << "error: " << err.message() << endl;
            sock.close();
        }*/
    }

    string translate_to_string() {
        package a;
        message = "\n ";
        while (ServerQueueOutput->pop(a)) { //////////// for test ServerQueueInput
            //cout << a << endl;
            message += std::to_string(a.id_) + " ";
            message += std::to_string(a.eventType_) + " ";
            message += std::to_string(a.info1_) + " ";
            message += std::to_string(a.info2_) + " ";
            message += std::to_string(a.info3_) + " ";
            message += std::to_string(a.info4_) + " ";
            message += "\n ";
        }
        return message;
    }
};

class Server {
private:
    tcp::acceptor acceptor_;

    boost::lockfree::queue<package, MAX_LENGTH>* ServerQueueInput;

    boost::lockfree::queue<package, MAX_LENGTH>* ServerQueueOutput;

    void start_accept() {
        con_handler::pointer connection = con_handler::create(GET_IO_SERVICE(acceptor_), ServerQueueInput, ServerQueueOutput);

        acceptor_.async_accept(connection->socket(),
            boost::bind(&Server::handle_accept, this, connection,
                boost::asio::placeholders::error));
    }

public:
    Server(boost::asio::io_service& io_service, boost::lockfree::queue<package, MAX_LENGTH>* LockFreeQueueInput, boost::lockfree::queue<package, MAX_LENGTH>* LockFreeQueueOutput) :
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

//Клиентская часть реализации сети
class Client {
private:
    tcp::socket sock;

    con_handler::pointer connection;

    std::string message = "1 2 3 4";

    enum { max_length = 1024 };

    char data[max_length];

    std::string line;

    boost::lockfree::queue<package, MAX_LENGTH>* ClientQueueInput;

    boost::lockfree::queue<package, MAX_LENGTH>* ClientQueueOutput;

public:
    Client(boost::asio::io_service& io_service, boost::lockfree::queue<package, MAX_LENGTH>* LockFreeQueueInput,
        boost::lockfree::queue<package, MAX_LENGTH>* LockFreeQueueOutput) :
        sock(io_service), ClientQueueInput(LockFreeQueueInput), ClientQueueOutput(LockFreeQueueOutput) {
        connection = con_handler::create(io_service, ClientQueueInput, ClientQueueOutput);
        connect();
    }

    void connect() {
        connection->socket().connect(tcp::endpoint(boost::asio::ip::address::from_string("25.49.163.248"), 6001));
        connection->start();
        //start();
    }
    /*
    void start() {
        boost::system::error_code error;
        boost::asio::write(sock, boost::asio::buffer(translate_to_string()), error);
        if (!error) {
            //cout << "Client sent " << message << endl;
        }
        else {
            cout << "send failed: " << error.message() << endl;
        }


        boost::asio::streambuf b;
        boost::asio::read_until(sock, b, "\r\n");
        std::istream is(&b);
        std::getline(is, line);

        //boost::asio::read_until(sock, boost::asio::streambuf, '\\');
        if (error && error != boost::asio::error::eof) {
            cout << "receive failed: " << error.message() << endl;
        }
        else {
            std::stringstream s(line);
            string num;
            while (s >> num) {
                ClientQueueInput->push(std::stoi(num));
                cout << std::stoi(num) << endl;
            }
        }
    }



    string translate_to_string() {
        int a;
        string mess = "";
        while (ClientQueueOutput->pop(a)) {
            //cout << a << endl;
            mess += std::to_string(a) + " ";
        }
        mess += "\r\n";
        return mess;
    }*/
    /*string return_string_array() {
        std::string a = "1 2 3 4 5 10000";
        return a;
    }*/

};

//Функции для перехода в нужное состояние игры
void netWork(boost::lockfree::queue<package, MAX_LENGTH>* LockFreeQueueInput,
    boost::lockfree::queue<package, MAX_LENGTH>* LockFreeQueueOutput) {
    while (true) {
        while (!Game::getInstance().getStateDecision()) {
            std::chrono::duration<double> sleep_duration(0.1);
            std::this_thread::sleep_for(sleep_duration);
        }

        std::cout << "Connection type aquired\n";

        if (Game::getInstance().getConnectionType() == ConnectionType::Host) {
            std::cout << "Host State Active\n";
            startServer(LockFreeQueueInput, LockFreeQueueOutput);
        }

        else if (Game::getInstance().getConnectionType() == ConnectionType::Client) {
            std::cout << "Client State Active\n";
            startClient(LockFreeQueueInput, LockFreeQueueOutput);
        }
    }
}

void startServer(boost::lockfree::queue<package, MAX_LENGTH>* LockFreeQueueInput,
    boost::lockfree::queue<package, MAX_LENGTH>* LockFreeQueueOutput) {
    while (Game::getInstance().getStateDecision()) {
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
    std::cout << "Server closed" << std::endl;
}

void startClient(boost::lockfree::queue<package, MAX_LENGTH>* LockFreeQueueInput,
    boost::lockfree::queue<package, MAX_LENGTH>* LockFreeQueueOutput) {

    while (Game::getInstance().getStateDecision()) {
        try {
            //std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            boost::asio::io_service io_service;
            Client client(io_service, LockFreeQueueInput, LockFreeQueueOutput);
            io_service.run();
            //while (LockFreeQueueInput->pop(a)) {
            //    //cout << a << endl;
            //}
        }
        catch (std::exception& e) {
            std::cerr << e.what() << endl;
        }
    }
    std::cout << "Client closed" << std::endl;
}