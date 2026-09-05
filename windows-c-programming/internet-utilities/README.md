# Windows Internet Utilities in C

Ten small Windows C examples using WinINet, WinHTTP, Winsock, and ICMP APIs.

| Program | Purpose | Library |
| --- | --- | --- |
| `internet_connection.c` | Report Windows' current Internet connection state. | `Wininet.lib` |
| `http_status.c` | Display the HTTP status code for a URL. | `Wininet.lib` |
| `http_headers.c` | Display response headers for a URL. | `Wininet.lib` |
| `fetch_text.c` | Print a small HTTP/HTTPS text response. | `Wininet.lib` |
| `download_file.c` | Download a URL without overwriting a local file. | `Wininet.lib` |
| `url_parser.c` | Split a URL into its main components. | `Winhttp.lib` |
| `url_encode.c` | Percent-encode text for use in a URL query. | None |
| `proxy_config.c` | Display the current user's configured proxy. | `Winhttp.lib` |
| `dns_lookup.c` | Resolve a hostname to IP addresses. | `Ws2_32.lib` |
| `ping_host.c` | Send one IPv4 ICMP echo request. | `Iphlpapi.lib`, `Ws2_32.lib` |

## Build

From a Developer Command Prompt for Visual Studio:

```bat
cl /W4 http_status.c /link Wininet.lib
cl /W4 url_parser.c /link Winhttp.lib
cl /W4 dns_lookup.c /link Ws2_32.lib
cl /W4 ping_host.c /link Iphlpapi.lib Ws2_32.lib
```

Each source includes its own library directives. Use these programs only with URLs and systems you are authorized to access.

## Repository Notice

This account contains personal research, educational projects, experiments, and historical code developed over several years.

Names, domains, identifiers, and sample data appearing in older repositories may be test or demonstration values and should not, by their presence alone, be interpreted as representing an employer, customer, organization, product, or endorsement.

I periodically review older repositories for maintainability, security, documentation, and appropriate handling of confidential or proprietary information.
