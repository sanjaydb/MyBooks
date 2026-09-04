#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#pragma comment(lib, "Ws2_32.lib")

int main(int argc, char **argv) {
    WSADATA wsa; SOCKET sock = INVALID_SOCKET; struct sockaddr_in local = {0}, peer = {0};
    int peerLength = sizeof(peer), received, result = 1; char buffer[1024];
    unsigned short port = (unsigned short)(argc > 1 ? atoi(argv[1]) : 9001);
    if (!port) { fprintf(stderr, "Usage: %s [port]\n", argv[0]); return 2; }
    if (WSAStartup(MAKEWORD(2, 2), &wsa)) return 1;
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); if (sock == INVALID_SOCKET) goto cleanup;
    local.sin_family = AF_INET; local.sin_port = htons(port); inet_pton(AF_INET, "127.0.0.1", &local.sin_addr);
    if (bind(sock, (SOCKADDR *)&local, sizeof(local)) == SOCKET_ERROR) goto cleanup;
    printf("Waiting on 127.0.0.1:%u\n", port);
    received = recvfrom(sock, buffer, sizeof(buffer), 0, (SOCKADDR *)&peer, &peerLength);
    if (received == SOCKET_ERROR || sendto(sock, buffer, received, 0, (SOCKADDR *)&peer, peerLength) == SOCKET_ERROR) goto cleanup;
    result = 0;
cleanup:
    if (result) fprintf(stderr, "Winsock error: %d\n", WSAGetLastError());
    if (sock != INVALID_SOCKET) closesocket(sock); WSACleanup(); return result;
}
