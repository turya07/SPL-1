#ifndef SERVER_HPP
#define SERVER_HPP

class Server {
public:
    Server(unsigned short port) {
        if (listener.listen(port) != sf::Socket::Done) {
            std::cerr << "Could not listen on port " << port << std::endl;
            return;
        }
        std::cout << "Server is listening on port " << port << std::endl;
    }

    void run() {
        if (listener.accept(client) != sf::Socket::Done) {
            std::cerr << "Could not accept client" << std::endl;
            return;
        }
        std::cout << "Client connected" << std::endl;

        std::thread receiveThread(&Server::receiveData, this);
        receiveThread.detach();
    }

    void sendData(const std::string& data) {
        if (client.send(data.c_str(), data.size() + 1) != sf::Socket::Done) {
            std::cerr << "Failed to send data to client" << std::endl;
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
            if (client.receive(buffer, sizeof(buffer), received) == sf::Socket::Done) {
                receivedData = std::string(buffer, received);
                std::cout << "Received: " << receivedData << std::endl;
            }
        }
    }

    sf::TcpListener listener;
    sf::TcpSocket client;
    std::string receivedData;
};

#endif // SERVER_HPP