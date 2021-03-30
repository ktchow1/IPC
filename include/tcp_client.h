#include<iostream>
#include<string>
#include<sys/socket.h>   // socket
#include<arpa/inet.h>    // inet_addr
#include<unistd.h>       // read & write

class tcp_client
{
public:
    void connect(const std::string& ip, std::uint16_t port)
    {
        // step 1 : create socket
        fd = socket(AF_INET, SOCK_STREAM, 0);
        if (fd == -1)
        {
            throw std::runtime_error("cannot create socket");
        }

        sockaddr_in addr;
        addr.sin_addr.s_addr = inet_addr(ip.c_str());
        addr.sin_family      = AF_INET;
        addr.sin_port        = htons(port);

        // step 2 : connection
        if (::connect(fd, (struct sockaddr*)(&addr), sizeof(addr)) < 0)
        {
            throw std::runtime_error("cannot connect server");
        }
        std::cout << "\nTCP client connection done" << std::flush;
    }

    bool run()
    {
        char message[1000] , server_reply[2000];
        while(true)
        {
            std::cout << "\nEnter message : " << std::flush;
            std::string message;
            std::cin >> message;

            if (send(fd, message.c_str(), message.size(), 0) < 0)
            {
                throw std::runtime_error("cannot send");
            }

            int read_size = recv(fd , buf, size, 0);
            if (read_size > 0)
            {
                std::cout << "TCP client received : " << std::string{buf, (size_t)read_size};
            }
            else if (read_size)
            {
                std::cout << "TCP client disconnected" << std::flush;
                return true;
            }
            else
            {
                std::cout << "TCP client read-failure" << std::flush;
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