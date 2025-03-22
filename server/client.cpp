#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unistd.h>
#include <string>
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
    ss << segments[0] << "." << segments[1] << "." << segments[2] << "." << segments[3];
    return ss.str();
}

int main()
{
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        std::cout << "Socket creation error" << std::endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    std::string ip_address = "";
    unsigned long hash_code;
    std::cout << "Enter Joining Code: ";
    std::cin >> hash_code;
    ip_address = decodeIp(hash_code);
    std::cout << "Decoded IP: " << ip_address << std::endl;
    std::cout << "Joining to server. Please wait...\n";

    // Convert IPv4 address from text to binary form
    if (inet_pton(AF_INET, ip_address.c_str(), &serv_addr.sin_addr) <= 0)
    {
        std::cout << "Invalid address / Address not supported" << std::endl;
        return -1;
    }

    bool isFirst = true;

    do
    {
        // Connect to server
        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        {
            std::cout << "Connection failed" << std::endl;
            return -1;
        }
        if(isFirst)
        {
            std::cout << "Connected to server" << std::endl;
            isFirst = false;
        }
     
        std::string message;
        std::cout << "Enter message: ";
        std::getline(std::cin, message);

        // Send message
        send(sock, message.c_str(), message.length(), 0);

        // Read server reply
        read(sock, buffer, 1024);
        std::cout << "Message from server: " << buffer << std::endl;
    } while (true);

    close(sock);
    return 0;
}
