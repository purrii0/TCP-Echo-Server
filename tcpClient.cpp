#include <iostream>
#include <cstring>
#include <string>
#include <memory>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

constexpr int PORT = 8080;
constexpr int BUFFER_SIZE = 1024;

int main() {
    WSADATA wsData;
    int wsaInit = WSAStartup(MAKEWORD(2, 2), &wsData);
    if(wsaInit != 0) {
        std::cerr << "WSAStatrupt Failed: " << wsaInit << std::endl;
        return 1;
    }
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};
    
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == INVALID_SOCKET) {
        std::cerr << "Socket creation error" << WSAGetLastError() << std::endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported: " << WSAGetLastError() << std::endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR){
        std::cerr << "Connection Failed: " << WSAGetLastError() << std::endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    std::string sentMsg = "Hello from Client";
    send(sock, sentMsg.c_str(), sentMsg.size(), 0);
    std::cout << "Hello Message Sent" << std::endl;

    size_t valread = recv(sock, buffer, BUFFER_SIZE, 0);
    std::cout << "Received: " << buffer << std::endl;    

    closesocket(sock);
    WSACleanup();

    return 0;
}