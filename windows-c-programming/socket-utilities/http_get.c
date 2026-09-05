#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#pragma comment(lib, "Ws2_32.lib")
int main(int argc, char **argv) {
    WSADATA wsa; struct addrinfo hints = {0}, *list = NULL, *p; SOCKET s = INVALID_SOCKET;
    char request[1024], buffer[4096]; int n, result = 1;
    if (argc < 2 || argc > 3) { fprintf(stderr, "Usage: %s HOST [path]\n", argv[0]); return 2; }
    if (WSAStartup(MAKEWORD(2,2), &wsa)) return 1;
    hints.ai_family = AF_UNSPEC; hints.ai_socktype = SOCK_STREAM;
    if (getaddrinfo(argv[1], "80", &hints, &list)) goto cleanup;
    for (p = list; p; p = p->ai_next) {
        s = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (s != INVALID_SOCKET && connect(s, p->ai_addr, (int)p->ai_addrlen) != SOCKET_ERROR) break;
        if (s != INVALID_SOCKET) closesocket(s); s = INVALID_SOCKET;
    }
    if (s == INVALID_SOCKET) goto cleanup;
    n = snprintf(request, sizeof(request), "GET %s HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n", argc == 3 ? argv[2] : "/", argv[1]);
    if (n < 0 || n >= (int)sizeof(request) || send(s, request, n, 0) == SOCKET_ERROR) goto cleanup;
    while ((n = recv(s, buffer, sizeof(buffer), 0)) > 0) fwrite(buffer, 1, n, stdout);
    result = n == 0 ? 0 : 1;
cleanup:
    if (result) fprintf(stderr, "Request failed (Winsock error %d).\n", WSAGetLastError());
    if (list) freeaddrinfo(list); if (s != INVALID_SOCKET) closesocket(s); WSACleanup(); return result;
}
