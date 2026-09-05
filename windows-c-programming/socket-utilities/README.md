# Windows Socket Programming in C

Ten small, standalone Winsock examples for learning and local development.

| Program | Purpose |
| --- | --- |
| `tcp_echo_server.c` | Local TCP echo server. |
| `tcp_echo_client.c` | TCP echo client. |
| `udp_echo_server.c` | Local UDP echo server. |
| `udp_echo_client.c` | UDP echo client. |
| `resolve_hostname.c` | Resolve a hostname to IP addresses. |
| `reverse_lookup.c` | Resolve an IP address to a hostname. |
| `check_tcp_port.c` | Test whether one TCP port accepts a connection. |
| `http_get.c` | Send a basic HTTP GET request. |
| `local_addresses.c` | List the computer's resolved IP addresses. |
| `socket_options.c` | Display default socket buffer and timeout values. |

## Build

Use a Developer Command Prompt for Visual Studio:

```bat
cl /W4 tcp_echo_server.c /link Ws2_32.lib
cl /W4 tcp_echo_client.c /link Ws2_32.lib
```

Every file also contains `#pragma comment(lib, "Ws2_32.lib")`, so `cl /W4 filename.c` normally works.

Start the TCP server in one terminal and its client in another:

```bat
tcp_echo_server.exe 9000
tcp_echo_client.exe 127.0.0.1 9000 "Hello"
```

The echo servers bind only to `127.0.0.1`. These examples use blocking sockets and are intentionally small rather than production-ready.

## Repository Notice

This account contains personal research, educational projects, experiments, and historical code developed over several years.

Names, domains, identifiers, and sample data appearing in older repositories may be test or demonstration values and should not, by their presence alone, be interpreted as representing an employer, customer, organization, product, or endorsement.

I periodically review older repositories for maintainability, security, documentation, and appropriate handling of confidential or proprietary information.
