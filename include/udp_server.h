#include<iostream>
#include<string>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>


int test_udp_server()
{
    static const std::uint32_t size = 4096;
    static const std::uint16_t port = 12345;

    // step 1. create socket
    int fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (fd == -1)
    {
        throw std::runtime_error("cannot create socket");
    }

    sockaddr_in addr_this;
    addr_this.sin_family = AF_INET;
    addr_this.sin_port = htons(port);
    addr_this.sin_addr.s_addr = htonl(INADDR_ANY);

    // step 2. bind socket
    if (bind(fd, (struct sockaddr*)&addr_this, sizeof(addr_this)) == -1)
    {
        throw std::runtime_error("cannot bind socket");
    }

    // No session for UDP, start to read / write ...
    sockaddr_in addr_client;
    socklen_t socket_len = sizeof(addr_client);
    while(true)
    {
        char buf[size];
        int read_size = recvfrom(fd, buf, size, 0, (struct sockaddr*)&addr_client, &socket_len);
        if (read_size > 0)
        {
            std::cout << "\ndata from "
                      << inet_ntoa(addr_client.sin_addr) << ":"
                      <<     ntohs(addr_client.sin_port);
            std::cout << "\n" << std::string{buf, (size_t)read_size};
            sendto(fd, buf, read_size, 0, (struct sockaddr*)&addr_client, socket_len);
        }
        else
        {
            std::cout << " \nnUDP server read-failure" << std::flush;
        }
    }
    close(fd);
    return 0;
}