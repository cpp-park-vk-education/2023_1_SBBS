#pragma once
#include "netConnect.h"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "networkCodes.h"
#include <string>

#define GET_IO_SERVICE(s) ((boost::asio::io_context&)(s).get_executor().context())

using namespace boost::asio;
using ip::tcp;
using std::cout;
using std::endl;
using std::string;

NetConnector::NetConnector(boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueInput,
		boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueOutput)
		: lockFreeQueueInput_(LockFreeQueueInput),
		lockFreeQueueOutput_(LockFreeQueueOutput) {}


void NetConnector::openConnection(boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueInput,
    boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueOutput) {

    //std::cout << "Connection opened... "<<std::endl;
    lockFreeQueueInput_ = LockFreeQueueInput;
    lockFreeQueueOutput_ = LockFreeQueueOutput;
    int x = 0;
}

void  NetConnector::send(std::vector<int>& to_send) {
    //std::cout << "Writing into queue..." << std::endl;
    for (int i = 0; i < to_send.size(); ++i) {
        //std::cout << to_send[i] << " ";
        lockFreeQueueOutput_->push(to_send[i]);
    }
    //std::cout << "Done writing" << std::endl;
}

std::vector<int> NetConnector::get() {
    std::vector<int> recieved;
    int curr_data = 0;
    //std::cout << "Got from queue..." << std::endl;
    while (lockFreeQueueInput_->pop(curr_data)) {
        recieved.push_back(curr_data);
        if (curr_data == BREAKER) {
            break;
        }
        //std::cout << curr_data << "\n";
    }
    //std::cout << "Done recieving. " << std::endl;
    return recieved;
}

// Серверная часть реализации сети
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
            //cout << a << endl;
            message += std::to_string(a) + " ";
        }
        message += "\r\n";
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

//Клиентская часть реализации сети
class Client {
private:
    tcp::socket sock;

    std::string message = "1 2 3 4";

    enum { max_length = 1024 };

    char data[max_length];

    std::string line;

    boost::lockfree::queue<int, MAX_LENGTH>* ClientQueueInput;

    boost::lockfree::queue<int, MAX_LENGTH>* ClientQueueOutput;

public:
    Client(boost::asio::io_service& io_service, boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueInput,
        boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueOutput) :
        sock(io_service), ClientQueueInput(LockFreeQueueInput), ClientQueueOutput(LockFreeQueueOutput) {
        connect();
    }

    void connect() {
        sock.connect(tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 6001));
        start();
    }

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
    }
    /*string return_string_array() {
        std::string a = "1 2 3 4 5 10000";
        return a;
    }*/

};

//Функции для перехода в нужное состояние игры
void netWork(boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueInput,
    boost::lockfree::queue<int, MAX_LENGTH>* LockFreeQueueOutput, ConnectionType* _connection) {
    while (*_connection == ConnectionType::Null) {
        std::cout << " " << std::endl;


    }

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
///// буст сигнал 
/// на ивентах 
//// вектор функций, метод call, вызывающий функции 
// метод subscribe 

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
            //while (LockFreeQueueInput->pop(a)) {
            //    //cout << a << endl;
            //}
        }
        catch (std::exception& e) {
            std::cerr << e.what() << endl;
        }
    }
}