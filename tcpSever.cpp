#include <iostream>
#include <string>
#include <memory>
#include <cstring>
#include <winsock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")
using socklen_t = int;

constexpr int PORT = 8080;
constexpr int BUFFER_SIZE = 1024;

int main() {
    WSADATA wsData;
    int wsaInit = WSAStartup(MAKEWORD(2,2), &wsData);
    if(wsaInit !=  0) {
        std::cerr << "WSAStatrupt Failed: " << wsaInit << std::endl;
        return 1;
    }
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    socklen_t addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    server_fd = socket(AF_INET, SOCK_STREAM, 0);


    if(server_fd == INVALID_SOCKET) {
        std::cerr << "Socket Creation failed with error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (const char*)&opt, sizeof(opt)) == SOCKET_ERROR) {
        std::cerr << "setsocketopt failed with error: " << WSAGetLastError() << std::endl;
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if(bind(server_fd, (struct sockaddr*)&address, sizeof(address)) == SOCKET_ERROR) {
        std::cerr << "Bind failed with error: " << WSAGetLastError() << std::endl;
        closesocket(server_fd);
        WSACleanup(); 
        return 1;
    }

    if(listen(server_fd, 3) == SOCKET_ERROR) {
        std::cerr << "Error while listening: " << WSAGetLastError() << std::endl;
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    std::cout << "Server listening on the port: " << PORT << std::endl;

    new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen);
    if(new_socket == INVALID_SOCKET) {
        std::cerr << "Accept failed with error: " << WSAGetLastError() << std::endl;
        closesocket(new_socket);
        closesocket(server_fd);
        WSACleanup();
    }

    int valread = recv(new_socket, buffer, BUFFER_SIZE, 0);
    if(valread == SOCKET_ERROR) {
        std::cerr << "recv failed with error: " << WSAGetLastError() << std::endl;
        closesocket(new_socket);
        closesocket(server_fd);
        return 1;
    }
    std::cout << "Received: " << buffer << std::endl;

    send(new_socket, buffer, valread, 0);
    closesocket(new_socket);
    closesocket(server_fd);
    WSACleanup();

    std::cout << "Echo message sent" << std::endl;
    
    return 0;
}