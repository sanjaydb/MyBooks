#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma comment(lib, "Ws2_32.lib")

int main(int argc, char **argv) {
    WSADATA wsa; SOCKET sock = INVALID_SOCKET; struct sockaddr_in server = {0};
    char buffer[1024]; int received, length = sizeof(server), result = 1; DWORD timeout = 3000;
    if (argc != 4) { fprintf(stderr, "Usage: %s IPV4_ADDRESS PORT MESSAGE\n", argv[0]); return 2; }
    if (WSAStartup(MAKEWORD(2, 2), &wsa)) return 1;
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); if (sock == INVALID_SOCKET) goto cleanup;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));
    server.sin_family = AF_INET; server.sin_port = htons((unsigned short)atoi(argv[2]));
    if (inet_pton(AF_INET, argv[1], &server.sin_addr) != 1) goto cleanup;
    if (sendto(sock, argv[3], (int)strlen(argv[3]), 0, (SOCKADDR *)&server, length) == SOCKET_ERROR) goto cleanup;
    received = recvfrom(sock, buffer, sizeof(buffer) - 1, 0, (SOCKADDR *)&server, &length);
    if (received == SOCKET_ERROR) goto cleanup; buffer[received] = '\0'; printf("Reply: %s\n", buffer); result = 0;
cleanup:
    if (result) fprintf(stderr, "Request failed (Winsock error %d).\n", WSAGetLastError());
    if (sock != INVALID_SOCKET) closesocket(sock); WSACleanup(); return result;
}
