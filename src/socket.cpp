#include<iostream>
#include<tcp_server.h>
#include<tcp_client.h>


// Run executable with a dummy arg for server.
// Run executable without arg for client.
void test_tcp(bool is_server)
{
    if (is_server)
    {
        std::cout << "[TCP server]" << std::flush;

        tcp_server server(12345);
        while(true)
        {
            auto session = server.accept();
            session.run();
        }
    }
    else
    {
        std::cout << "[TCP client]" << std::flush;

        tcp_client client;
        client.connect("127.0.0.1", 12345);
        client.run();
    }
}

#include<udp_server.h>
#include<udp_client.h>
int test_udp_server();
int test_udp_client();

void test_udp(bool is_server)
{
    if (is_server)
    {
        std::cout << "[UDP server]" << std::flush;
        test_udp_server();
    }
    else
    {
        std::cout << "[UDP client]" << std::flush;
        test_udp_client();
    }
}