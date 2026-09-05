#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#pragma comment(lib, "Ws2_32.lib")

int main(int argc, char **argv) {
    WSADATA wsa; SOCKET listener = INVALID_SOCKET, client = INVALID_SOCKET;
    struct sockaddr_in address = {0}; char buffer[1024]; int received, result = 1;
    unsigned short port = (unsigned short)(argc > 1 ? atoi(argv[1]) : 9000);
    if (!port) { fprintf(stderr, "Usage: %s [port]\n", argv[0]); return 2; }
    if (WSAStartup(MAKEWORD(2, 2), &wsa)) return 1;
    listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listener == INVALID_SOCKET) goto cleanup;
    address.sin_family = AF_INET; address.sin_port = htons(port);
    inet_pton(AF_INET, "127.0.0.1", &address.sin_addr);
    if (bind(listener, (SOCKADDR *)&address, sizeof(address)) == SOCKET_ERROR ||
        listen(listener, 1) == SOCKET_ERROR) goto cleanup;
    printf("Listening on 127.0.0.1:%u\n", port);
    client = accept(listener, NULL, NULL);
    if (client == INVALID_SOCKET) goto cleanup;
    while ((received = recv(client, buffer, sizeof(buffer), 0)) > 0)
        if (send(client, buffer, received, 0) == SOCKET_ERROR) goto cleanup;
    result = received == 0 ? 0 : 1;
cleanup:
    if (result) fprintf(stderr, "Winsock error: %d\n", WSAGetLastError());
    if (client != INVALID_SOCKET) closesocket(client);
    if (listener != INVALID_SOCKET) closesocket(listener);
    WSACleanup(); return result;
}
