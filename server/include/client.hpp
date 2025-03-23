#ifndef CLIENT_HPP
#define CLIENT_HPP

class Client {
public:
    Client() {}

    bool connect(const std::string& ip, unsigned short port) {
        std::cout << ip << " " << port << std::endl;
        if (socket.connect(ip, port) != sf::Socket::Done) {
            std::cerr << "Could not connect to server" << std::endl;
            return false;
        }
        std::cout << "Connected to server" << std::endl;

        std::thread receiveThread(&Client::receiveData, this);
        receiveThread.detach();

        return true;
    }

    void sendData(const std::string& data) {
        if (socket.send(data.c_str(), data.size() + 1) != sf::Socket::Done) {
            std::cerr << "Failed to send data to server" << std::endl;
        }
    }

    std::string getReceivedData() {
        return receivedData;
    }

private:
    void receiveData() {
        char buffer[1024];
        std::size_t received;
        while (true) {
            if (socket.receive(buffer, sizeof(buffer), received) == sf::Socket::Done) {
                receivedData = std::string(buffer, received);
                std::cout << "Received: " << receivedData << std::endl;
            }
        }
    }

    sf::TcpSocket socket;
    std::string receivedData;
};

#endif // CLIENT_HPP