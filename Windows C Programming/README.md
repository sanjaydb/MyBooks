# Windows C Programming

Store Windows C source code, Windows API examples, build instructions, and notes here.

## Suggested layout

Create one directory per program or topic:

```text
Windows C Programming/
├── console-apps/
├── windows-api/
├── networking/
└── README.md
```

Each project should include its source files and a README describing the compiler, dependencies, build command, usage, and supported Windows version.

Keep generated executables and build output out of Git.

## Administrator utilities

The [`administrator-utilities`](./administrator-utilities/) directory contains ten read-only C examples for inspecting Windows system information, disks, memory, processes, services, event logs, local accounts, network adapters, and uptime.

## User utilities

The [`user-utilities`](./user-utilities/) directory contains ten everyday Windows C examples for inspecting files and folders, viewing clipboard text, searching text, listing drives, checking display and environment information, using a countdown timer, and safely copying files.

## Socket utilities

The [`socket-utilities`](./socket-utilities/) directory contains ten standalone Winsock examples covering TCP, UDP, name resolution, a single-port connection check, basic HTTP, local addresses, and socket options.

## IPC examples

The [`ipc-examples`](./ipc-examples/) directory contains ten Windows C demonstrations of named and anonymous pipes, shared memory, mailslots, mutexes, semaphores, and event objects.

## SMB utilities

The [`smb-utilities`](./smb-utilities/) directory contains ten defensive Windows C examples for inspecting authorized SMB servers and shares, browsing UNC paths, reading remote text, and safely copying files from a share.

## Internet utilities

The [`internet-utilities`](./internet-utilities/) directory contains ten Windows C examples for connectivity checks, HTTP requests and downloads, URL handling, proxy inspection, DNS, and ICMP ping.

## Backup and restore utilities

The [`backup-restore-utilities`](./backup-restore-utilities/) directory contains ten conservative Windows C examples for file and directory backup, safe restoration, integrity checks, manifests, snapshots, and free-space checks.

## Encryption and data protection

The [`encryption-utilities`](./encryption-utilities/) directory contains ten Windows C examples using DPAPI, EFS, Base64 conversion, SHA-256, and secure random generation.

## Repository Notice

This account contains personal research, educational projects, experiments, and historical code developed over several years.

Names, domains, identifiers, and sample data appearing in older repositories may be test or demonstration values and should not, by their presence alone, be interpreted as representing an employer, customer, organization, product, or endorsement.

I periodically review older repositories for maintainability, security, documentation, and appropriate handling of confidential or proprietary information.
