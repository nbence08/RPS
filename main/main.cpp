#pragma once

#include "client.hpp"
#include "server.hpp"

int main(int argc, char* argv[])
{
    srand(time(nullptr));
    if (argc != 1) {
        RPS::run_client(argv[1]);
    }
    else {
        RPS::run_server();
    }
    
    return 0;
}
