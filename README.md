# 🚀 TCP Echo Server & Client in C++ (Winsock)

This project implements a simple **TCP Echo Server and Client** using **C++** with the **Windows Winsock2 API**.  
It demonstrates how to:

- Set up a TCP socket server that accepts connections
- Receive data from a client
- Echo the same data back
- Create a TCP client that connects to the server, sends a message, and prints the echoed response

---
Build the Server
```bash
g++ tcoServer.cpp -o server -lws2_32
```
Build the Client
```bash
g++ tcpClient.cpp -o client -lws2_32
```
(The -lws2_32 flag links against the Windows Sockets 2 library.)

1️⃣ Start the server
In your terminal or command prompt:
```bash
./server
```
It will start listening on 127.0.0.1:8080

2️⃣ Start the client
In another terminal:
```bash
./client
```
The client connects to 127.0.0.1:8080 , sends a message, and prints the echoed reply.