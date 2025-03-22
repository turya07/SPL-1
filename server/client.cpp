#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include <unistd.h>
#include <limits>
#include <arpa/inet.h>
#define PORT 8080

std::string decodeIp(unsigned long hashCode)
{
    std::vector<unsigned long> segments;
    for (int i = 0; i < 4; ++i)
    {
        segments.push_back((hashCode >> (24 - 8 * i)) & 0xFF);
    }

    std::stringstream ss;
    ss <<  segments[0] << "." << segments[1] << "." << segments[2] << "." << segments[3];
    std::cout << ss.str()<< std::endl;
    std::cout << ss.str().c_str()<< std::endl;

    return ss.str();
}

void connectServer(){
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    // Take number from input
    unsigned long hashCode;
    std::cout << "Enter the hash code: ";
    std::cin >> hashCode;

    // Decode the unsigned long value into string IP address
    std::string ipAddress = decodeIp(hashCode);

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cerr << "Socket creation error" << std::endl;
        return;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, ipAddress.c_str(), &serv_addr.sin_addr) <= 0)
    {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        return;
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cerr << "Connection Failed" << std::endl;
        return;
    }

    std::cout << "Connected to the server at " << ipAddress << std::endl;
    // send hash code to server through buffer
    strcpy(buffer, (std::to_string(hashCode)).c_str());
    send(sock, buffer, sizeof(hashCode), 0);
    std::cout << "Hash code sent to server" << std::endl;

    int j = 0;
    // Continue to send and receive data from server
    while (true) {
        

        strcpy(buffer, std::to_string(j).c_str());
        j+=50;
        send(sock, buffer, strlen(buffer), 0);
        strcpy(buffer, "");

        int valread = read(sock, buffer, 1024);
        if (valread > 0) {
            buffer[valread] = '\0';
            std::cout << "Server: " << buffer << std::endl;
        } else {
            std::cerr << "Failed to receive message from server" << std::endl;
            break;
        }
    }

    // Close the socket
    close(sock);
}

int main(int argc, char const *argv[])
{
    connectServer();
    return 0;
}
