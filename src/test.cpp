#include<iostream>

void test_ipc_unnamed_pipe();
void test_ipc_named_pipe(bool);
void test_ipc_shared_memory();
void test_epoll_socket(std::uint16_t port);


int main(int argc, char* argv[])
{ 
//  test_ipc_unnamed_pipe();   
//  test_ipc_named_pipe(argc > 1); // with argument for producer
//  test_ipc_shared_memory(); 

    {
        if (argc!=2)
        {
            std::cout << "\nError in input, please enter : exe 12345";
        }
        else
        {
            test_epoll_socket(std::stoi(std::string(argv[1])));
        }
    }

    std::cout << "\n\n\n";
    return 0;
}
