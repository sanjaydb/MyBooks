#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#pragma comment(lib, "Ws2_32.lib")
int main(int argc, char **argv) {
    WSADATA wsa; struct addrinfo hints = {0}, *list = NULL, *p; char text[INET6_ADDRSTRLEN];
    if (argc != 2) { fprintf(stderr, "Usage: %s HOSTNAME\n", argv[0]); return 2; }
    if (WSAStartup(MAKEWORD(2,2), &wsa)) return 1;
    hints.ai_family = AF_UNSPEC; hints.ai_socktype = SOCK_STREAM;
    if (getaddrinfo(argv[1], NULL, &hints, &list)) { fprintf(stderr, "Resolution failed.\n"); WSACleanup(); return 1; }
    for (p = list; p; p = p->ai_next) {
        void *a = p->ai_family == AF_INET ? (void *)&((struct sockaddr_in *)p->ai_addr)->sin_addr : (void *)&((struct sockaddr_in6 *)p->ai_addr)->sin6_addr;
        if (inet_ntop(p->ai_family, a, text, sizeof(text))) printf("%s\n", text);
    }
    freeaddrinfo(list); WSACleanup(); return 0;
}
