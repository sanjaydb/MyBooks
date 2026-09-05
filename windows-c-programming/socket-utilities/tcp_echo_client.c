#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <string.h>
#pragma comment(lib, "Ws2_32.lib")

int main(int argc, char **argv) {
    WSADATA wsa; SOCKET sock = INVALID_SOCKET; struct addrinfo hints = {0}, *addresses = NULL, *item;
    char buffer[1024]; int received, result = 1;
    if (argc != 4) { fprintf(stderr, "Usage: %s HOST PORT MESSAGE\n", argv[0]); return 2; }
    if (WSAStartup(MAKEWORD(2, 2), &wsa)) return 1;
    hints.ai_family = AF_UNSPEC; hints.ai_socktype = SOCK_STREAM; hints.ai_protocol = IPPROTO_TCP;
    if (getaddrinfo(argv[1], argv[2], &hints, &addresses)) goto cleanup;
    for (item = addresses; item; item = item->ai_next) {
        sock = socket(item->ai_family, item->ai_socktype, item->ai_protocol);
        if (sock != INVALID_SOCKET && connect(sock, item->ai_addr, (int)item->ai_addrlen) != SOCKET_ERROR) break;
        if (sock != INVALID_SOCKET) closesocket(sock); sock = INVALID_SOCKET;
    }
    if (sock == INVALID_SOCKET || send(sock, argv[3], (int)strlen(argv[3]), 0) == SOCKET_ERROR) goto cleanup;
    shutdown(sock, SD_SEND); received = recv(sock, buffer, sizeof(buffer) - 1, 0);
    if (received <= 0) goto cleanup; buffer[received] = '\0'; printf("Reply: %s\n", buffer); result = 0;
cleanup:
    if (result) fprintf(stderr, "Connection failed (Winsock error %d).\n", WSAGetLastError());
    if (addresses) freeaddrinfo(addresses); if (sock != INVALID_SOCKET) closesocket(sock);
    WSACleanup(); return result;
}
