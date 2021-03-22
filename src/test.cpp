#include<iostream>

void test_ipc_unnamed_pipe();
void test_ipc_named_pipe(bool);
void test_ipc_shared_memory();


int main(int argc, char* argv[])
{ 
//  test_ipc_unnamed_pipe();
//  test_ipc_named_pipe(argc > 1); // with argument for producer
    test_ipc_shared_memory();

    std::cout << "\n\n\n";
    return 0;
}
