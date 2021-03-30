#include<iostream>
#include<string>
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>

#define SERVER "127.0.0.1"

int test_udp_client()
{
    static const std::uint32_t size = 4096;
    static const std::uint16_t port = 12345;

    // step 1. create socket
    int fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (fd == -1)
    {
        throw std::runtime_error("cannot create socket");
    }

    std::string ip = "127.0.0.1";
    struct sockaddr_in addr_server;
    addr_server.sin_family = AF_INET;
    addr_server.sin_port = htons(port);
    inet_aton(ip.c_str(), &addr_server.sin_addr);
    socklen_t socket_len = sizeof(addr_server);

    // No connect for UDP, start to read / write ...
    while(true)
    {
        std::cout << "\nEnter message : " << std::flush;
        std::string message;
        std::cin >> message;

        sendto(fd, message.c_str(), message.size(), 0, (struct sockaddr*)&addr_server, socket_len);

        char buf[size];
        int read_size = recvfrom(fd, buf, size, 0, (struct sockaddr*)&addr_server, &socket_len);
        std::cout << "data from server : " << std::string{buf, (size_t)read_size};
    }
    close(fd);
    return 0;
}