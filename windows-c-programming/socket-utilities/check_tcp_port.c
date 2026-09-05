#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#pragma comment(lib, "Ws2_32.lib")
int main(int argc, char **argv) {
    WSADATA wsa; struct addrinfo hints = {0}, *list = NULL, *p; SOCKET s; int open = 0;
    if (argc != 3) { fprintf(stderr, "Usage: %s HOST PORT\n", argv[0]); return 2; }
    if (WSAStartup(MAKEWORD(2,2), &wsa)) return 1;
    hints.ai_family = AF_UNSPEC; hints.ai_socktype = SOCK_STREAM; hints.ai_protocol = IPPROTO_TCP;
    if (getaddrinfo(argv[1], argv[2], &hints, &list)) { WSACleanup(); return 1; }
    for (p = list; p; p = p->ai_next) {
        s = socket(p->ai_family, p->ai_socktype, p->ai_protocol); if (s == INVALID_SOCKET) continue;
        if (connect(s, p->ai_addr, (int)p->ai_addrlen) != SOCKET_ERROR) open = 1;
        closesocket(s); if (open) break;
    }
    printf("%s:%s is %s\n", argv[1], argv[2], open ? "open" : "closed or unreachable");
    freeaddrinfo(list); WSACleanup(); return open ? 0 : 1;
}
