#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#pragma comment(lib, "Ws2_32.lib")

int main(int argc, char **argv) {
    WSADATA wsa; struct addrinfo hints = {0}, *list = NULL, *item; char address[INET6_ADDRSTRLEN];
    if (argc != 2) { fprintf(stderr, "Usage: %s HOSTNAME\n", argv[0]); return 2; }
    if (WSAStartup(MAKEWORD(2,2), &wsa)) return 1;
    hints.ai_family = AF_UNSPEC;
    if (getaddrinfo(argv[1], NULL, &hints, &list)) { fprintf(stderr, "DNS lookup failed.\n"); WSACleanup(); return 1; }
    for (item = list; item; item = item->ai_next) {
        void *source = item->ai_family == AF_INET ? (void *)&((struct sockaddr_in *)item->ai_addr)->sin_addr : (void *)&((struct sockaddr_in6 *)item->ai_addr)->sin6_addr;
        if (inet_ntop(item->ai_family, source, address, sizeof(address))) printf("%s\n", address);
    }
    freeaddrinfo(list); WSACleanup(); return 0;
}
