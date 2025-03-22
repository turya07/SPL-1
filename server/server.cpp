#include <iostream>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h> // Added for inet_addr
#include <sstream>
#include <sys/types.h>
#include <sys/socket.h>

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

void runServer()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    std::string current_ip = get_current_ip();
    std::cout << "Current IP: " << current_ip << std::endl;
    unsigned long encoded_ip = encodeIp(current_ip);
    std::cout << "Encoded IP: " << encoded_ip << std::endl;

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(current_ip.c_str());
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while (true)
    {
        // wait for a response from the client
        char buffer[1024] = {0};
        int valread = read(new_socket, buffer, 1024);
        if (valread > 0)
        {
            std::cout << "Client: " << buffer << std::endl;

            // Echo the message back to the client
            strcpy(buffer, std::to_string(i).c_str());
            i+=10;
            send(new_socket, buffer, strlen(buffer), 0);
        }
        else if (valread == 0)
        {
            std::cout << "Client disconnected" << std::endl;
            break;
        }
        else
        {
            perror("read");
            break;
        }
    }

    // Close the socket
    close(new_socket);
    close(server_fd);
}

int main(int argc, char const *argv[])
{
    std::cout << "TEST SERVER\n";
    runServer();
    return 0;
}
