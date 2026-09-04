# Windows Administrator Utilities in C

Ten small, read-only Windows administration examples written in C.

| Program | Purpose | Additional library |
| --- | --- | --- |
| `system_info.c` | Show the computer name, processor architecture, and CPU count. | None |
| `disk_space.c` | Show total and available space for a drive or path. | None |
| `memory_status.c` | Show physical and virtual memory usage. | None |
| `process_list.c` | List running processes and their process IDs. | None |
| `service_status.c` | Query a Windows service's current state. | `Advapi32.lib` |
| `event_log_info.c` | Show record counts for a Windows event log. | `Advapi32.lib` |
| `local_users.c` | List local Windows user accounts. | `Netapi32.lib` |
| `local_groups.c` | List local Windows groups. | `Netapi32.lib` |
| `network_adapters.c` | List network adapters and operational state. | `Iphlpapi.lib`, `Ws2_32.lib` |
| `system_uptime.c` | Display how long Windows has been running. | None |

## Build

Open a **Developer Command Prompt for Visual Studio**, enter this directory, and run:

```bat
cl /W4 /DUNICODE /D_UNICODE system_info.c
cl /W4 /DUNICODE /D_UNICODE service_status.c /link Advapi32.lib
cl /W4 /DUNICODE /D_UNICODE local_users.c /link Netapi32.lib
cl /W4 /DUNICODE /D_UNICODE network_adapters.c /link Iphlpapi.lib Ws2_32.lib
```

Each source file also includes its required library through `#pragma comment`, so `cl /W4 filename.c` is normally sufficient.

## Usage and permissions

Run a program with no arguments or follow the usage message it prints. These examples only read system information; some queries may need an elevated terminal or may be restricted by local policy.

## Repository Notice

This account contains personal research, educational projects, experiments, and historical code developed over several years.

Names, domains, identifiers, and sample data appearing in older repositories may be test or demonstration values and should not, by their presence alone, be interpreted as representing an employer, customer, organization, product, or endorsement.

I periodically review older repositories for maintainability, security, documentation, and appropriate handling of confidential or proprietary information.
