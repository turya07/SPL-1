#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h> // Added for inet_addr
#include <sstream>

#define PORT 8080

unsigned long encodeIp(const std::string &ip)
{
    std::stringstream ss(ip);
    std::string segment;
    unsigned long encodedIp = 0;
    int shift = 24;

    while (std::getline(ss, segment, '.'))
    {
        encodedIp |= (std::stoi(segment) << shift);
        shift -= 8;
    }

    return encodedIp;
}

std::string get_current_ip()
{
    char buffer[128];
    std::string result = "";
    FILE *fp = popen("hostname -I", "r");
    if (fp == NULL)
    {
        std::cout << "Failed to run command" << std::endl;
        exit(1);
    }
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        result += buffer;
    }
    pclose(fp);
    return result;
}

int main()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    std::string cur_device_ip = get_current_ip();
    unsigned long encoded_ip = encodeIp(cur_device_ip);
    // Create socket file descriptor
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0)
    {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // just ensuring if device IP is correct
    std::cout << "Device IP: " << cur_device_ip << std::endl;
    std::cout << "Encoded IP: " << encoded_ip << std::endl;

    // Forcefully attach socket to the port
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    // Bind the socket to the specific address and port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(cur_device_ip.c_str()); // Listen on specific IP
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Start listening for incoming connections
    listen(server_fd, 3);

    std::cout << "Waiting for client connection..." << std::endl;

    bool isFirst = true;


    do
    {
        // Accept the connection
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
        if (new_socket < 0)
        {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }

        if(isFirst)
        {
            std::cout << "Connected to client" << std::endl;
            isFirst = false;
        }

        std::string message;
        std::cout << "Enter message: ";
        std::getline(std::cin, message);


        // Read data from client
        read(new_socket, buffer, 1024);
        std::cout << "Message from client: " << buffer << std::endl;

        // Send reply to client
        send(new_socket, message.c_str(), message.length(), 0);

        if (message == "exit" || message == "quit")
        {
            break;
        }
    } while(true);

    close(new_socket);
    close(server_fd);
    return 0;
}
