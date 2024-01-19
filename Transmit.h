#include <iostream>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

class Transmitter {
public:
    int serverSocket_;
    int clientSocket_;
    struct sockaddr_in server_;

    Transmitter();
    ~Transmitter();

    void initialize();
    void transmit(const std::vector<float>& v);
};