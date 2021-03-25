#include<iostream>

void test_ipc_unnamed_pipe();
void test_ipc_named_pipe(bool);
void test_ipc_shared_memory();
void test_socket(int argc, char *argv[]);


int main(int argc, char* argv[])
{ 
//  test_ipc_unnamed_pipe();   
    test_ipc_named_pipe(argc > 1); // with argument for producer
//  test_ipc_shared_memory(); 
    test_socket(argc, argv);

    std::cout << "\n\n\n";
    return 0;
}
