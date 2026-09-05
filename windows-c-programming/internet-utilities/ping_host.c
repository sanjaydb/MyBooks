#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <iphlpapi.h>
#include <icmpapi.h>
#include <stdio.h>
#include <stdlib.h>
#pragma comment(lib, "Iphlpapi.lib")
#pragma comment(lib, "Ws2_32.lib")

int main(int argc, char **argv) {
    WSADATA wsa; struct addrinfo hints = {0}, *list = NULL; HANDLE icmp;
    char payload[] = "Simple Windows ICMP test"; BYTE reply[sizeof(ICMP_ECHO_REPLY) + sizeof(payload) + 8];
    DWORD count; ICMP_ECHO_REPLY *result = (ICMP_ECHO_REPLY *)reply;
    if (argc != 2) { fprintf(stderr, "Usage: %s IPV4_HOST\n", argv[0]); return 2; }
    if (WSAStartup(MAKEWORD(2,2), &wsa)) return 1;
    hints.ai_family = AF_INET;
    if (getaddrinfo(argv[1], NULL, &hints, &list)) { fprintf(stderr, "Host lookup failed.\n"); WSACleanup(); return 1; }
    icmp = IcmpCreateFile();
    if (icmp == INVALID_HANDLE_VALUE) { freeaddrinfo(list); WSACleanup(); return 1; }
    count = IcmpSendEcho(icmp, ((struct sockaddr_in *)list->ai_addr)->sin_addr.s_addr,
        payload, sizeof(payload), NULL, reply, sizeof(reply), 3000);
    if (count) printf("Reply from %s: time=%lu ms, TTL=%u\n", argv[1], result->RoundTripTime, result->Options.Ttl);
    else fprintf(stderr, "No reply (%lu).\n", GetLastError());
    IcmpCloseHandle(icmp); freeaddrinfo(list); WSACleanup(); return count ? 0 : 1;
}
