#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#pragma comment(lib, "Ws2_32.lib")
int main(int argc, char **argv) {
    WSADATA wsa; struct sockaddr_storage storage = {0}; int length; char host[NI_MAXHOST];
    if (argc != 2) { fprintf(stderr, "Usage: %s IP_ADDRESS\n", argv[0]); return 2; }
    if (WSAStartup(MAKEWORD(2,2), &wsa)) return 1;
    if (inet_pton(AF_INET, argv[1], &((struct sockaddr_in *)&storage)->sin_addr) == 1) {
        ((struct sockaddr_in *)&storage)->sin_family = AF_INET; length = sizeof(struct sockaddr_in);
    } else if (inet_pton(AF_INET6, argv[1], &((struct sockaddr_in6 *)&storage)->sin6_addr) == 1) {
        ((struct sockaddr_in6 *)&storage)->sin6_family = AF_INET6; length = sizeof(struct sockaddr_in6);
    } else { fprintf(stderr, "Invalid IP address.\n"); WSACleanup(); return 2; }
    if (getnameinfo((SOCKADDR *)&storage, length, host, sizeof(host), NULL, 0, NI_NAMEREQD)) {
        fprintf(stderr, "No hostname was found.\n"); WSACleanup(); return 1;
    }
    printf("Hostname: %s\n", host); WSACleanup(); return 0;
}
