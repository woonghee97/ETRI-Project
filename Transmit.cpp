#include <rtabmap/core/Transmit.h>

Transmitter::Transmitter() : clientSocket_(-1), serverSocket_(-1) {
    memset(&server_, 0, sizeof(server_));
}

Transmitter::~Transmitter() {
    close(clientSocket_);
    close(serverSocket_);
}

void Transmitter::initialize() {
    serverSocket_ = socket(AF_INET, SOCK_STREAM, 0);

    server_.sin_family = AF_INET;
    server_.sin_addr.s_addr = INADDR_ANY;
    server_.sin_port = htons(8080);

    bind(serverSocket_, (struct sockaddr*)&server_, sizeof(server_));
    listen(serverSocket_, 3);

    std::cout << "Waiting for connections..." << std::endl;
    clientSocket_ = accept(serverSocket_, NULL, NULL);
}

void Transmitter::transmit(const std::vector<float>& v) {
    std::string message;
    for (float value : v) {
        message += std::to_string(value) + ",";
    }

    std::cout << "message : " << message << std::endl;

    send(clientSocket_, message.c_str(), message.length(), 0);
}

int main() {
    Transmitter transmitter;
    transmitter.initialize();

    std::vector<float> data = {1.1, 2.2, 3.3, 90, 45, 45};
    transmitter.transmit(data);

    return 0;
}