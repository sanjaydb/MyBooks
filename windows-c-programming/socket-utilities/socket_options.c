#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <stdio.h>
#pragma comment(lib, "Ws2_32.lib")
int main(void) {
    WSADATA wsa; SOCKET s; int sendSize, receiveSize, length; DWORD timeout;
    if (WSAStartup(MAKEWORD(2,2), &wsa)) return 1;
    s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); if (s == INVALID_SOCKET) { WSACleanup(); return 1; }
    length = sizeof(sendSize); getsockopt(s, SOL_SOCKET, SO_SNDBUF, (char *)&sendSize, &length);
    length = sizeof(receiveSize); getsockopt(s, SOL_SOCKET, SO_RCVBUF, (char *)&receiveSize, &length);
    length = sizeof(timeout); getsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, &length);
    printf("Send buffer: %d bytes\nReceive buffer: %d bytes\nReceive timeout: %lu ms\n", sendSize, receiveSize, timeout);
    closesocket(s); WSACleanup(); return 0;
}
