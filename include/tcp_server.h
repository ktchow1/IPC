#include<iostream>
#include<string>
#include<sys/socket.h>   // socket
#include<arpa/inet.h>    // inet_addr
#include<unistd.h>       // read & write

// step 1 : create socket
// step 2 : bind socket to port
// step 3 : put socket to listening mode (become a passive socket)
// step 4 : accept new connection to spawn an active socket

class tcp_session
{
public:
    tcp_session(int fd_) : fd(fd_) {}

public:
    bool run()
    {
        std::cout << "\nTCP server connected with client" << std::flush;
        while(true)
        {
            int read_size = recv(fd ,buf, size, 0);
            if (read_size > 0)
            {
                write(fd, buf, read_size);
            }
            else if (read_size == 0)
            {
                std::cout << "\nTCP server disconnected with client" << std::flush;
                return true;
            }
            else
            {
                std::cout << "\nTCP server read-failure" << std::flush;
                return false;
            }
        }
    }

private:
    static const std::uint32_t size = 4096;

private:
    int fd;
    char buf[size];
};

class tcp_server
{
public:
    // step 1 : create socket
    tcp_server(std::uint16_t port) : fd(socket(AF_INET, SOCK_STREAM, 0))
    {
        if (fd == -1)
        {
            throw std::runtime_error("cannot create socket");
        }

        sockaddr_in addr;
        addr.sin_family      = AF_INET;
        addr.sin_addr.s_addr = INADDR_ANY;
        addr.sin_port        = htons(port);

        // step 2 : bind socket (without query)
        if (bind(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
        {
            throw std::runtime_error("cannot bind socket");
        }

        // step 3 : listen mode
        listen(fd,3);
    }

    tcp_session accept()
    {
        sockaddr_in client_addr;
        socklen_t socket_len = sizeof(sockaddr_in);

        // step 4 : accept connection and spawn active-socket
        int client_fd = ::accept(fd, (struct sockaddr*)(&client_addr), &socket_len);
        if (client_fd < 0)
        {
            throw std::runtime_error("cannot accept connection");
        }
        return tcp_session(client_fd);
    }

private:
    int fd;
};